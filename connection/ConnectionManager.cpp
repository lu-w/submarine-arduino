   #include "ConnectionManager.h"

SoftwareSerial connection::ConnectionManager::bluetoothSerial = SoftwareSerial(BT_RX_PIN, BT_TX_PIN);

void connection::ConnectionManager::setup() {
   connection::ConnectionManager::bluetoothSerial.begin(9600);
}

bool connection::ConnectionManager::hasMessage() {
   return connection::ConnectionManager::bluetoothSerial.available();
}

ControlMessage* const connection::ConnectionManager::getMessage() {
   // Receives message from bluetooth serial interface.
   // Fetches length of the message which is contained in the first byte.
   byte length = 0;
   // Busy waiting until data is available;
   while(!connection::ConnectionManager::bluetoothSerial.available()) {}
   length = (byte)bluetoothSerial.read();
   // If we received anything (i.e. a message length), we receive the rest.
   byte received[length];
   // Fetches the actual message.
   for(size_t i = 0; i < length; i++) {
      // Busy waiting until data is available;
      while(!bluetoothSerial.available());
      received[i] = bluetoothSerial.read();
      Serial.write(received[i]);
   }
   // We then proceed to parse the message using the nanopb library.
   ControlMessage* message = (ControlMessage*)malloc(sizeof(ControlMessage));
   if(message != NULL) {
      pb_istream_t stream = pb_istream_from_buffer(received, length);
      int status = pb_decode(&stream, ControlMessage_fields, message);
   } else {
      #if DEBUG
         const String mallocFailMessage PROGMEM = "No memory for message parsing.";
         Serial.println(mallocFailMessage);
      #endif
   }
   return message;
}

void printHex8(uint8_t *data, uint8_t length) {
     char tmp[16];
       for (int i=0; i<length; i++) {
         sprintf(tmp, "0x%.2X",data[i]);
         Serial.print(tmp); Serial.print(" ");
       }
}

void connection::ConnectionManager::sendMessage(SubmarineMessage_MessageType type) {
   size_t length = 0;
   byte* buffer;
   switch(type) {
      case SubmarineMessage_MessageType_DATA:
      {
         #if DEBUG
            const String dataRequestMessage PROGMEM = "Sending data update of size ";
            Serial.print(dataRequestMessage);
            Serial.println(sizeof(SubmarineMessage) + sizeof(Datum) * DATA_BUFFER_SIZE);
         #endif
         buffer = (byte*)malloc(sizeof(SubmarineMessage) * 2 + sizeof(Datum) * DATA_BUFFER_SIZE);
         connection::ConnectionManager::assembleDataMessage(buffer, &length);
         break;
      }
      case SubmarineMessage_MessageType_STATUS:
      {
         #if DEBUG
            const String statusRequestMessage PROGMEM = "Sending status update of size ";
            Serial.print(statusRequestMessage);
            Serial.println(sizeof(SubmarineMessage) + sizeof(Status));
         #endif
         buffer = (byte*)malloc(sizeof(SubmarineMessage) + sizeof(Status));
         connection::ConnectionManager::assembleStatusUpdateMessage(buffer, &length);
         break;
      }
   }
   #if DEBUG
      Serial.print("Message is: ");
      printHex8(buffer, length);
      Serial.print(" with length ");
      Serial.println(length);
   #endif
   if(length <= 255) {
      connection::ConnectionManager::bluetoothSerial.write(length);
      connection::ConnectionManager::bluetoothSerial.write(buffer, length);
   } else {
      #if DEBUG
         Serial.print("Message too long to send!");
      #endif
   }
   free(buffer);
}

void const connection::ConnectionManager::assembleDataMessage(byte* const buffer, size_t* const length) {
   bool status = true;
   SubmarineMessage message = SubmarineMessage_init_zero;
   Datum* data = automaton::Diving::getData();
   pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(SubmarineMessage) * 2 + sizeof(Datum) * DATA_BUFFER_SIZE);
   // Encodes TYPE field
   status &= pb_encode_tag_for_field(&stream, &SubmarineMessage_fields[0]);
   status &= pb_encode_varint(&stream, SubmarineMessage_MessageType_DATA);
   // Encodes DATA field
   for(size_t i = 0; i < DATA_BUFFER_SIZE; i++) {
      for(const pb_field_t *field = SubmarineMessage_fields; field->tag != 0; field++) {
         if (field->ptr == Datum_fields) {
               status &= pb_encode_tag_for_field(&stream, field);
         }
      }
      status &= pb_encode_submessage(&stream, Datum_fields, &(data[i]));
      Serial.print("TEMP = ");
      Serial.println(data[i].temperature);
   }
   *length = stream.bytes_written;
   #if DEBUG
      if(!status) {
         const String failMessage PROGMEM = "Encoding failed: ";
         Serial.print(failMessage);
         Serial.write(PB_GET_ERROR(&stream));
         Serial.println();
      }
   #endif
}

void const connection::ConnectionManager::assembleStatusUpdateMessage(byte* const buffer, size_t* const length) {
   bool status = true;
   SubmarineMessage message = SubmarineMessage_init_zero;
   Status statusMessage = Status_init_zero;
   statusMessage.type = automaton::SubmarineAutomaton::getState();
   statusMessage.spent_time_s = automaton::SubmarineAutomaton::getTimeSpentInPreviousStateS();
   pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(SubmarineMessage) + sizeof(Status));
   status &= pb_encode_tag_for_field(&stream, &SubmarineMessage_fields[0]);
   status &= pb_encode_varint(&stream, SubmarineMessage_MessageType_STATUS);
   for(const pb_field_t *field = SubmarineMessage_fields; field->tag != 0; field++) {
      if (field->ptr == Status_fields) {
         status &= pb_encode_tag_for_field(&stream, field);
      }
   }
   status &= pb_encode_submessage(&stream, Status_fields, &statusMessage);
   *length = stream.bytes_written;
   #if DEBUG
      if(!status) {
         const String failMessage PROGMEM = "Encoding failed: ";
         Serial.print(failMessage);
         Serial.write(PB_GET_ERROR(&stream));
         Serial.println();
      }
   #endif
}
