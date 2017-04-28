#pragma once

#ifndef _INTEROPLIB_H_
#define _INTEROPLIB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <string.h>

/*********************************************************************/

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
#ifndef NULL
#define NULL    (0)
#endif

/*********************************************************************/

#define MAX_JSON_STRINGLENGTH                   (1024 * 8)
#define MAX_JSON_PARAMETERS                     (10)

/*********************************************************************/

#define Element_Count(x)                        ((int32)(sizeof(x) / sizeof((x)[0])))
#define StructOffsetOf(STRUCT, MEMBER)          ((int32)(intptr)(&((STRUCT *)0)->MEMBER))

/*********************************************************************/

typedef int32 (*Class_DeleteCallback)(echandle *ClassHandle);
typedef int32 (*Class_DeleteMemTypeCallback)(echandle *ClassHandle, int32 MemType);

typedef struct ClassStruct
{
    char     InstanceId[40];
    int32    Id;
    int32    RefCount;
    int32   (*Delete)(echandle *ClassHandle);
    int32   (*DeleteMemType)(echandle *ClassHandle, int32 MemType);
} ClassStruct;

#define Class_Id(CLASS)                         (((ClassStruct *)(CLASS))->Id)
#define Class_InstanceId(CLASS)                 (((ClassStruct *)(CLASS))->InstanceId)
#define Class_Define(TYPE, ID)                  static int32 Global##TYPE##ClassId = ID;
#define Class_Cast(HANDLE, TYPE)                ((TYPE *)(HANDLE))

#define Class_BaseCast(PTR, MEMBER, CLASS)      Class_Cast((echandle)((uint8*)PTR - StructOffsetOf(CLASS, MEMBER)), CLASS)
#define Class_VtblCast(PTR, VTBLTYPE)           ((VTBLTYPE *)((uint8 *)PTR + sizeof(ClassStruct)))

/*********************************************************************/

typedef void *(*Class_ConvertFromInstanceIdCallback)(char *InstanceId);
typedef char *(*Class_ConvertToInstanceIdCallback)(void *Pointer);
typedef int32 (*Class_TrackInstanceCallback)(void *Pointer, char *InstanceId);
typedef int32 (*Class_UntrackInstanceCallback)(void *Pointer);

/*********************************************************************/

#define String_IsEmpty(s)                               (*s == 0)
#define String_Print                                    snprintf
#define String_Compare(s1,s2)                           (strcmp(s1, s2) == 0)
#define String_Length                                   strlen
#if defined(__APPLE__)
#define String_CompareWithoutCase(s1,s2)                (strcasecmp(s1, s2) == 0)
#define String_CopyLength(t,s,l)                        strncpy(t, l, s)
#elif defined(_WINDOWS)
#define String_CompareWithoutCase(s1,s2)                (_strcmpi(s1, s2) == 0)
#define String_CopyLength(t,s,l)                        strcpy_s(t, l, s)
#elif defined(__linux__)
#define String_CompareWithoutCase(s1,s2)                (strcmpi(s1, s2) == 0)
#define String_CopyLength(t,s,l)                        strncpy(t, s, l)
#endif

/*********************************************************************/

typedef int32 (*Generic_PrintCallback)(echandle PrintHandle, char *Format, ...);

/*********************************************************************/

typedef int32 (*Dictionary_CreateCallback)(echandle *DictionaryHandle);
typedef int32 (*Dictionary_DeleteCallback)(echandle *DictionaryHandle);

typedef int32 (*NotificationCenter_InteropExecuteCallback)(void* UserPtr, char *InstanceId, char *String, char *ResultString, int32 ResultStringLength);
typedef int32 (*NotificationCenter_ObserverCallback)(void *UserPtr, char *Type, char *Notification, void *Sender, echandle DictionaryHandle);
typedef int32 (*NotificationCenter_AddInstanceObserverCallback)(char *Type, char *Notification, void *Sender, void *UserPtr, NotificationCenter_ObserverCallback Callback);
typedef int32 (*NotificationCenter_RemoveInstanceObserverCallback)(char *Type, char *Notification, void *Sender, void *UserPtr, NotificationCenter_ObserverCallback Callback);
typedef int32 (*NotificationCenter_AssertInstanceCallback)(void *Sender);
typedef int32 (*NotificationCenter_FireCallback)(char *Type, char *Notification, void *Sender, echandle DictionaryHandle);
typedef int32 (*NotificationCenter_FireWithJSONCallback)(char *Type, char *Notification, void *Sender, char *Format, ...);
typedef int32 (*NotificationCenter_FireWithJSONVCallback)(char *Type, char *Notification, void *Sender, char *Format, va_list ArgumentList);
typedef int32 (*NotificationCenter_FireAfterDelayCallback)(char *Type, char *Notification, void *Sender, int32 DelayMS, echandle DictionaryHandle);
typedef int32 (*NotificationCenter_FireAfterDelayWithJSONCallback)(char *Type, char *Notification, void *Sender, int32 DelayMS, char *Format, ...);
typedef int32 (*NotificationCenter_FireAfterDelayWithJSONVCallback)(char *Type, char *Notification, void *Sender, int32 DelayMS, char *Format, va_list ArgumentList);

typedef int32 (*Interop_GenerateInstanceIdCallback)(char *String, int32 MaxString);
typedef int32 (*Interop_ExecuteCallback)(void* UserPtr, char *InstanceId, char *String, char *ResultString, int32 ResultStringLength);
typedef int32 (*Interop_ReleaseInstanceCallback)(void** UserPtr);
typedef int32 (*Interop_InvokeInstanceCallback)(void* UserPtr, char *String, char *ResultString, int32 ResultStringLength);
typedef int32 (*Interop_ProcessInstanceCallback)(void* UserPtr);

/*********************************************************************/

int32 InteropLib_SetOverride(char *Key, void *Value);

void *Class_ConvertFromInstanceId(char *InstanceId);
char *Class_ConvertToInstanceId(void *Pointer);
int32 Class_TrackInstance(void *Pointer, char *InstanceId);
int32 Class_UntrackInstance(void *Pointer);

int32 Dictionary_Create(echandle *DictionaryHandle);
int32 Dictionary_Delete(echandle *DictionaryHandle);

int32 NotificationCenter_AddObserver(char *Type, char *Notification, void *UserPtr, NotificationCenter_ObserverCallback Callback);
int32 NotificationCenter_AddInstanceObserver(char *Type, char *Notification, void *Sender, void *UserPtr, NotificationCenter_ObserverCallback Callback);
int32 NotificationCenter_RemoveObserver(char *Type, char *Notification, void *UserPtr, NotificationCenter_ObserverCallback Callback);
int32 NotificationCenter_RemoveInstanceObserver(char *Type, char *Notification, void *Sender, void *UserPtr, NotificationCenter_ObserverCallback Callback);
int32 NotificationCenter_Fire(char *Type, char *Notification, void *Sender, echandle DictionaryHandle);
int32 NotificationCenter_FireWithJSON(char *Type, char *Notification, void *Sender, char *Format, ...);
int32 NotificationCenter_FireAfterDelay(char *Type, char *Notification, void *Sender, int32 DelayMS, echandle DictionaryHandle);
int32 NotificationCenter_FireAfterDelayWithJSON(char *Type, char *Notification, void *Sender, int32 DelayMS, char *Format, ...);

int32 Interop_GenerateInstanceId(char *String, int32 MaxString);

/*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
