/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.5-dev at Tue Mar  8 21:19:47 2016. */

#ifndef PB_SUBMARINE_PB_H_INCLUDED
#define PB_SUBMARINE_PB_H_INCLUDED
#include "../nanopb/pb.h"

#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _ControlMessage_MessageType {
    ControlMessage_MessageType_DIVE = 0,
    ControlMessage_MessageType_CANCEL_DIVE = 1,
    ControlMessage_MessageType_STATUS_REQUEST = 2,
    ControlMessage_MessageType_DATA_REQUEST = 3
} ControlMessage_MessageType;

typedef enum _SubmarineMessage_MessageType {
    SubmarineMessage_MessageType_STATUS = 0,
    SubmarineMessage_MessageType_DATA = 1
} SubmarineMessage_MessageType;

typedef enum _Status_StatusType {
    Status_StatusType_AVAILABLE = 0,
    Status_StatusType_DIVE_SCHEDULED = 1,
    Status_StatusType_DIVING = 2
} Status_StatusType;

/* Struct definitions */
typedef struct _Datum {
    uint32_t timestamp;
    float depth;
    float temperature;
    float pressure;
} Datum;

typedef struct _Dive {
    uint32_t offset_s;
    uint32_t depth_m;
} Dive;

typedef struct _Status_Informations {
    bool has_battery_percentage;
    float battery_percentage;
} Status_Informations;

typedef struct _ControlMessage {
    ControlMessage_MessageType type;
    bool has_dive;
    Dive dive;
} ControlMessage;

typedef struct _Status {
    Status_StatusType type;
    bool has_spent_time_s;
    uint32_t spent_time_s;
    pb_callback_t message;
    bool has_informations;
    Status_Informations informations;
} Status;

typedef struct _SubmarineMessage {
    SubmarineMessage_MessageType type;
    bool has_status;
    Status status;
    pb_callback_t data;
} SubmarineMessage;

/* Default values for struct fields */

/* Initializer values for message structs */
#define ControlMessage_init_default              {(ControlMessage_MessageType)0, false, Dive_init_default}
#define Dive_init_default                        {0, 0}
#define SubmarineMessage_init_default            {(SubmarineMessage_MessageType)0, false, Status_init_default, {{NULL}, NULL}}
#define Status_init_default                      {(Status_StatusType)0, false, 0, {{NULL}, NULL}, false, Status_Informations_init_default}
#define Status_Informations_init_default         {false, 0}
#define Datum_init_default                       {0, 0, 0, 0}
#define ControlMessage_init_zero                 {(ControlMessage_MessageType)0, false, Dive_init_zero}
#define Dive_init_zero                           {0, 0}
#define SubmarineMessage_init_zero               {(SubmarineMessage_MessageType)0, false, Status_init_zero, {{NULL}, NULL}}
#define Status_init_zero                         {(Status_StatusType)0, false, 0, {{NULL}, NULL}, false, Status_Informations_init_zero}
#define Status_Informations_init_zero            {false, 0}
#define Datum_init_zero                          {0, 0, 0, 0}

/* Field tags (for use in manual encoding/decoding) */
#define Datum_timestamp_tag                      1
#define Datum_depth_tag                          2
#define Datum_temperature_tag                    3
#define Datum_pressure_tag                       4
#define Dive_offset_s_tag                        1
#define Dive_depth_m_tag                         2
#define Status_Informations_battery_percentage_tag 1
#define ControlMessage_type_tag                  1
#define ControlMessage_dive_tag                  2
#define Status_type_tag                          1
#define Status_spent_time_s_tag                  2
#define Status_message_tag                       3
#define Status_informations_tag                  4
#define SubmarineMessage_type_tag                1
#define SubmarineMessage_status_tag              2
#define SubmarineMessage_data_tag                3

/* Struct field encoding specification for nanopb */
extern const pb_field_t ControlMessage_fields[3];
extern const pb_field_t Dive_fields[3];
extern const pb_field_t SubmarineMessage_fields[4];
extern const pb_field_t Status_fields[5];
extern const pb_field_t Status_Informations_fields[2];
extern const pb_field_t Datum_fields[5];

/* Maximum encoded size of messages (where known) */
#define ControlMessage_size                      16
#define Dive_size                                12
#define Status_Informations_size                 5
#define Datum_size                               21

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define SUBMARINE_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif