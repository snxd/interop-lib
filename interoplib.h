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

#define INTEROP_VERSION   "7.2.90"
#define INTEROP_MAXSTRING (1024 * 8)

/*********************************************************************/

typedef struct ClassStruct {
    char InstanceId[36];
    uint32_t Id;
    volatile int32_t RefCount;
    bool (*Delete)(echandle *ClassHandle);
} ClassStruct;

#define Class_Id(CLASS)               (((ClassStruct *)(CLASS))->Id)
#define Class_InstanceId(CLASS)       ((CLASS)->Class.InstanceId)
#define Class_InstanceIdUnsafe(PTR)   (((ClassStruct *)(PTR))->InstanceId)
#define Class_Define(TYPE, ID)        static int32_t Global##TYPE##ClassId = ID;
#define Class_Cast(HANDLE, TYPE)      ((TYPE *)(HANDLE))
#define Class_VtblCast(PTR, VTBLTYPE) (*(VTBLTYPE **)((uint8_t *)PTR + sizeof(ClassStruct)))

/*********************************************************************/

bool String_ConvertToHex(const uint8_t *binary, int32_t binary_size, bool lower, char *hex, int32_t max_hex);

/*********************************************************************/

bool Base64_Encode(const uint8_t *source, int32_t source_length, char *target, int32_t max_target,
                   int32_t *target_length);
int32_t Base64_CalculateEncodeSize(int32_t source_length);

/*********************************************************************/

typedef bool (*Generic_LogCallback)(echandle log_handle, const char *format, ...);

/*********************************************************************/

typedef bool (*NotificationCenter_ObserverCallback)(void *user_ptr, const char *type, const char *notification,
                                                    const char *sender, echandle dictionary_handle);

/*********************************************************************/

void *Class_ConvertFromInstanceId(const char *instance_id);
char *Class_ConvertToInstanceId(void *pointer);
bool Class_TrackInstance(void *pointer, const char *instance_id);
bool Class_UntrackInstance(void *pointer);

echandle Dictionary_Create(void);
int32_t Dictionary_Release(echandle *dictionary_handle);

bool NotificationCenter_AddObserver(const char *type, const char *notification, void *user_ptr,
                                    NotificationCenter_ObserverCallback callback);
bool NotificationCenter_AddInstanceObserver(const char *type, const char *notification, const char *sender,
                                            void *user_ptr, NotificationCenter_ObserverCallback callback);
bool NotificationCenter_RemoveObserver(const char *type, const char *notification, void *user_ptr,
                                       NotificationCenter_ObserverCallback callback);
bool NotificationCenter_RemoveInstanceObserver(const char *type, const char *notification, const char *sender,
                                               void *user_ptr, NotificationCenter_ObserverCallback callback);
bool NotificationCenter_Fire(const char *type, const char *notification, const char *sender,
                             echandle dictionary_handle);
bool NotificationCenter_FireWithJSON(const char *type, const char *notification, const char *sender, const char *format,
                                     ...);
bool NotificationCenter_FireAfterDelay(const char *type, const char *notification, const char *sender, int32_t delay_ms,
                                       echandle dictionary_handle);
bool NotificationCenter_FireAfterDelayWithJSON(const char *type, const char *notification, const char *sender,
                                               int32_t delay_ms, const char *format, ...);
bool Interop_GenerateInstanceId(char *string, int32_t max_string);

/*********************************************************************/

#ifdef __cplusplus
}
#endif
