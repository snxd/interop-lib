#pragma once

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

#define INTEROP_VERSION   "7.2.8"
#define INTEROP_MAXSTRING (1024 * 8)

/*********************************************************************/

typedef struct ClassStruct {
    char InstanceId[36];
    uint32_t Id;
    int32_t RefCount;
    bool (*Reserved)(echandle *ClassHandle);
} ClassStruct;

#define Class_Id(CLASS)               (((ClassStruct *)(CLASS))->Id)
#define Class_InstanceId(CLASS)       ((CLASS)->Class.InstanceId)
#define Class_InstanceIdUnsafe(PTR)   (((ClassStruct *)(PTR))->InstanceId)
#define Class_Define(TYPE, ID)        static int32_t Global##TYPE##ClassId = ID;
#define Class_Cast(HANDLE, TYPE)      ((TYPE *)(HANDLE))
#define Class_VtblCast(PTR, VTBLTYPE) (*(VTBLTYPE **)((uint8_t *)PTR + sizeof(ClassStruct)))

/*********************************************************************/

bool String_ConvertToHex(const uint8_t *Binary, int32_t BinarySize, bool Lower, char *Hex, int32_t MaxHex);

/*********************************************************************/

bool Base64_Encode(const uint8_t *Source, int32_t SourceLength, char *Target, int32_t MaxTarget, int32_t *TargetLength);
bool Base64_CalculateEncodeSize(int32_t SourceLength, int32_t *BytesRequired);

/*********************************************************************/

typedef bool (*Generic_LogCallback)(echandle LogHandle, const char *Format, ...);

/*********************************************************************/

typedef bool (*NotificationCenter_ObserverCallback)(void *UserPtr, const char *Type, const char *Notification,
                                                    const char *Sender, echandle DictionaryHandle);

/*********************************************************************/

void *Class_ConvertFromInstanceId(const char *InstanceId);
char *Class_ConvertToInstanceId(void *Pointer);
bool Class_TrackInstance(void *Pointer, const char *InstanceId);
bool Class_UntrackInstance(void *Pointer);

bool Dictionary_Create(echandle *DictionaryHandle);
int32_t Dictionary_Release(echandle *DictionaryHandle);

bool NotificationCenter_AddObserver(const char *Type, const char *Notification, void *UserPtr,
                                    NotificationCenter_ObserverCallback Callback);
bool NotificationCenter_AddInstanceObserver(const char *Type, const char *Notification, const char *Sender,
                                            void *UserPtr, NotificationCenter_ObserverCallback Callback);
bool NotificationCenter_RemoveObserver(const char *Type, const char *Notification, void *UserPtr,
                                       NotificationCenter_ObserverCallback Callback);
bool NotificationCenter_RemoveInstanceObserver(const char *Type, const char *Notification, const char *Sender,
                                               void *UserPtr, NotificationCenter_ObserverCallback Callback);
bool NotificationCenter_Fire(const char *Type, const char *Notification, const char *Sender, echandle DictionaryHandle);
bool NotificationCenter_FireWithJSON(const char *Type, const char *Notification, const char *Sender, const char *Format,
                                     ...);
bool NotificationCenter_FireAfterDelay(const char *Type, const char *Notification, const char *Sender, int32_t DelayMS,
                                       echandle DictionaryHandle);
bool NotificationCenter_FireAfterDelayWithJSON(const char *Type, const char *Notification, const char *Sender,
                                               int32_t DelayMS, const char *Format, ...);
bool Interop_GenerateInstanceId(char *String, int32_t MaxString);

/*********************************************************************/

#ifdef __cplusplus
}
#endif
