#pragma once

#ifndef CORE_CORE_H_
#define CORE_CORE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

/*********************************************************************/

typedef float float32_t;  /* Single precision floating point */
typedef double float64_t; /* Double precision floating point */
typedef void *echandle;   /* Handle */
                          /* Define some universal truths... */
typedef uint32_t time32_t;
typedef uint64_t time64_t;

/*********************************************************************/

#define INTEROP_MAXSTRING (1024 * 8)

/*********************************************************************/

typedef struct ClassStruct {
    char InstanceId[36];
    uint32_t Id;
    int32_t RefCount;
    bool (*Reserved)(echandle *ClassHandle);
} ClassStruct;

#define Class_Id(CLASS)               (((ClassStruct *)(CLASS))->Id)
#define Class_InstanceId(CLASS)       (((ClassStruct *)(CLASS))->InstanceId)
#define Class_Define(TYPE, ID)        static int32 Global##TYPE##ClassId = ID;
#define Class_Cast(HANDLE, TYPE)      ((TYPE *)(HANDLE))
#define Class_VtblCast(PTR, VTBLTYPE) (*(VTBLTYPE **)((uint8 *)PTR + sizeof(ClassStruct)))

/*********************************************************************/

typedef void *(*Class_ConvertFromInstanceIdCallback)(char *InstanceId);
typedef char *(*Class_ConvertToInstanceIdCallback)(void *Pointer);
typedef bool (*Class_TrackInstanceCallback)(void *Pointer, char *InstanceId);
typedef bool (*Class_UntrackInstanceCallback)(void *Pointer);

/*********************************************************************/

#define Element_Count(x)       ((int32)(sizeof(x) / sizeof((x)[0])))

#define String_IsEmpty(s)      (*s == 0)
#define String_Compare(s1, s2) (strcmp(s1, s2) == 0)
#define String_Length          strlen
#if defined(_WINDOWS)
#define String_Print                      _snprintf
#define String_CompareWithoutCase(s1, s2) (_strcmpi(s1, s2) == 0)
#define String_CopyLength(t, s, l)        strcpy_s(t, l, s)
#define String_AtoI64(s)                  _strtoui64(s, NULL, 10)
#else
#define String_Print                      snprintf
#define String_CompareWithoutCase(s1, s2) (strcasecmp(s1, s2) == 0)
#define String_CopyLength(t, s, l)        strncpy(t, s, l)
#define String_AtoI64(s)                  strtoull(s, NULL, 10)
#endif

bool String_ConvertToHex(char *Binary, int32_t BinarySize, char *Hex, int32_t MaxHex);

/*********************************************************************/

bool Base64_Encode(const uint8_t *Source, int32_t SourceLength, char *Target, int32_t MaxTarget, int32_t *TargetLength);
bool Base64_CalculateEncodeSize(int32_t SourceLength, int32_t *BytesRequired);

/*********************************************************************/

typedef bool (*Generic_PrintCallback)(echandle PrintHandle, const char *Format, ...);

/*********************************************************************/

typedef bool (*Dictionary_CreateCallback)(echandle *DictionaryHandle);
typedef bool (*Dictionary_DeleteCallback)(echandle *DictionaryHandle);

typedef bool (*NotificationCenter_ObserverCallback)(void *UserPtr, const char *Type, const char *Notification,
                                                    const void *Sender, echandle DictionaryHandle);
typedef bool (*NotificationCenter_AddInstanceObserverCallback)(const char *Type, const char *Notification,
                                                               const void *Sender, void *UserPtr,
                                                               NotificationCenter_ObserverCallback Callback);
typedef bool (*NotificationCenter_RemoveInstanceObserverCallback)(const char *Type, const char *Notification,
                                                                  const void *Sender, void *UserPtr,
                                                                  NotificationCenter_ObserverCallback Callback);
typedef bool (*NotificationCenter_AssertInstanceCallback)(const void *Sender);
typedef bool (*NotificationCenter_FireCallback)(const char *Type, const char *Notification, const void *Sender,
                                                echandle DictionaryHandle);
typedef bool (*NotificationCenter_FireWithJSONCallback)(const char *Type, const char *Notification, const void *Sender,
                                                        const char *Format, ...);
typedef bool (*NotificationCenter_FireWithJSONVCallback)(const char *Type, const char *Notification, const void *Sender,
                                                         const char *Format, va_list ArgumentList);
typedef bool (*NotificationCenter_FireAfterDelayCallback)(const char *Type, const char *Notification,
                                                          const void *Sender, int32_t DelayMS,
                                                          echandle DictionaryHandle);
typedef bool (*NotificationCenter_FireAfterDelayWithJSONCallback)(const char *Type, const char *Notification,
                                                                  const void *Sender, int32_t DelayMS,
                                                                  const char *Format, ...);
typedef bool (*NotificationCenter_FireAfterDelayWithJSONVCallback)(const char *Type, const char *Notification,
                                                                   const void *Sender, int32_t DelayMS,
                                                                   const char *Format, va_list ArgumentList);

typedef bool (*Interop_GenerateInstanceIdCallback)(char *String, int32_t MaxString);

/*********************************************************************/

void *Class_ConvertFromInstanceId(char *InstanceId);
char *Class_ConvertToInstanceId(void *Pointer);
bool Class_TrackInstance(void *Pointer, char *InstanceId);
bool Class_UntrackInstance(void *Pointer);

bool Dictionary_Create(echandle *DictionaryHandle);
bool Dictionary_Delete(echandle *DictionaryHandle);

bool NotificationCenter_AddObserver(const char *Type, const char *Notification, void *UserPtr,
                                    NotificationCenter_ObserverCallback Callback);
bool NotificationCenter_AddInstanceObserver(const char *Type, const char *Notification, const void *Sender,
                                            void *UserPtr, NotificationCenter_ObserverCallback Callback);
bool NotificationCenter_RemoveObserver(const char *Type, const char *Notification, void *UserPtr,
                                       NotificationCenter_ObserverCallback Callback);
bool NotificationCenter_RemoveInstanceObserver(const char *Type, const char *Notification, const void *Sender,
                                               void *UserPtr, NotificationCenter_ObserverCallback Callback);
bool NotificationCenter_Fire(const char *Type, const char *Notification, const void *Sender, echandle DictionaryHandle);
bool NotificationCenter_FireWithJSON(const char *Type, const char *Notification, const void *Sender, const char *Format,
                                     ...);
bool NotificationCenter_FireAfterDelay(const char *Type, const char *Notification, const void *Sender, int32_t DelayMS,
                                       echandle DictionaryHandle);
bool NotificationCenter_FireAfterDelayWithJSON(const char *Type, const char *Notification, const void *Sender,
                                               int32_t DelayMS, const char *Format, ...);
bool Interop_GenerateInstanceId(char *String, int32_t MaxString);

/*********************************************************************/

bool InteropLib_SetOverride(const char *Key, void *Value);

/*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
