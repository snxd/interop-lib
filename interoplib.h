#pragma once

#ifndef _INTEROPLIB_H_
#define _INTEROPLIB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*********************************************************************/

#ifndef _EMU_CORE_H_

typedef uint8_t                                 uint8;
typedef uint16_t                                uint16;
typedef uint32_t                                uint32;
typedef uint64_t                                uint64;
typedef int8_t                                  int8;
typedef int16_t                                 int16;
typedef int32_t                                 int32;
typedef int64_t                                 int64;
typedef intptr_t                                intptr;
typedef float                                   float32;
typedef double                                  float64;
typedef void*                                   echandle;
typedef uint32                                  time32;
typedef uint64                                  time64;

#ifndef FALSE
#define FALSE   (0)
#endif
#ifndef TRUE
#define TRUE    (1)
#endif

#endif

/*********************************************************************/

#define MAX_JSON_STRINGLENGTH                   (1024 * 8)
#define MAX_JSON_PARAMETERS                     (10)

/*********************************************************************/

typedef int32 (*NotificationCenter_FireWithJSONCallback)(char *Type, char *Notification, void *Sender, char *Format, ...);
typedef int32 (*NotificationCenter_FireAfterDelayWithJSONCallback)(char *Type, char *Notification, void *Sender, int32 DelayMS, char *Format, ...);

typedef int32 (*Interop_GenerateInstanceIdCallback)(char *String, int32 MaxString);
typedef int32 (*Interop_ExecuteCallback)(void* UserPtr, char *InstanceId, char *String, char *ResultString, int32 ResultStringLength);
typedef int32 (*Interop_ReleaseInstanceCallback)(void** UserPtr);
typedef int32 (*Interop_InvokeInstanceCallback)(void* UserPtr, char *String, char *ResultString, int32 ResultStringLength);
typedef int32 (*Interop_ProcessInstanceCallback)(void* UserPtr);

/*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
