#include "interoplib.h"

#include <stdarg.h>

/*********************************************************************/

#define NOTIFICATIONCENTER_GLOBALSENDER ("Global")

/*********************************************************************/

#define BASE16SYM          ("0123456789ABCDEF")

#define Base16_EncodeLo(b) (BASE16SYM[(b & 0xff) >> 4])
#define Base16_EncodeHi(b) (BASE16SYM[b & 0xF])

/*********************************************************************/

bool String_ConvertToHex(char *Binary, int32_t BinarySize, char *Hex, int32_t MaxHex) {
    while ((MaxHex > 2) && (BinarySize > 0)) {
        Hex[0] = Base16_EncodeLo(*Binary);
        Hex[1] = Base16_EncodeHi(*Binary);

        Hex += 2;
        MaxHex -= 2;
        Binary += 1;
        BinarySize -= 1;
    }
    if (MaxHex > 0)
        *Hex = 0;
    return BinarySize == 0;
}

/*********************************************************************/

static const uint8_t Base64Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/*********************************************************************/

bool Base64_Encode(const uint8_t *Source, int32_t SourceLength, char *Target, int32_t MaxTarget,
                   int32_t *TargetLength) {
    int32_t i = 0, n = 0;
    uint8_t b1, b2, b3, b4, b5, b6, b7;

    *TargetLength = 0;

    for (i = 0; i < SourceLength && n + 2 <= MaxTarget; i += 3) {
        b1 = Source[i], b2 = 0, b3 = 0;

        if ((i + 1) < SourceLength)
            b2 = Source[i + 1];
        if ((i + 2) < SourceLength)
            b3 = Source[i + 2];

        b4 = b1 >> 2;
        b5 = ((b1 & 0x3) << 4) | (b2 >> 4);
        b6 = ((b2 & 0xf) << 2) | (b3 >> 6);
        b7 = b3 & 0x3f;

        Target[n++] = Base64Alphabet[b4];
        Target[n++] = Base64Alphabet[b5];

        if ((i + 1) < SourceLength) {
            if (n >= MaxTarget)
                break;
            Target[n++] = Base64Alphabet[b6];
        } else if (n < MaxTarget)
            Target[n++] = '=';

        if ((i + 2) < SourceLength) {
            if (n >= MaxTarget)
                break;
            Target[n++] = Base64Alphabet[b7];
        } else if (n < MaxTarget)
            Target[n++] = '=';
    }

    *TargetLength = n;
    if (n < MaxTarget)
        Target[n] = 0;

    if (i < SourceLength)
        return false;
    return true;
}

bool Base64_CalculateEncodeSize(int32_t SourceLength, int32_t *BytesRequired) {
    // Round up to the nearest multiple of 4.
    *BytesRequired = (SourceLength + 2) / 3 * 4;

    // Include NULL terminator
    *BytesRequired += 1;

    return true;
}

/*********************************************************************/

typedef void *(*Class_ConvertFromInstanceIdCallback)(const char *InstanceId);
typedef char *(*Class_ConvertToInstanceIdCallback)(void *Pointer);
typedef bool (*Class_TrackInstanceCallback)(void *Pointer, const char *InstanceId);
typedef bool (*Class_UntrackInstanceCallback)(void *Pointer);

Class_ConvertFromInstanceIdCallback Class_ConvertFromInstanceIdPtr = NULL;
Class_ConvertToInstanceIdCallback Class_ConvertToInstanceIdPtr = NULL;
Class_TrackInstanceCallback Class_TrackInstancePtr = NULL;
Class_UntrackInstanceCallback Class_UntrackInstancePtr = NULL;

typedef bool (*Dictionary_CreateCallback)(echandle *DictionaryHandle);
typedef bool (*Dictionary_DeleteCallback)(echandle *DictionaryHandle);

Dictionary_CreateCallback Dictionary_CreatePtr = NULL;
Dictionary_DeleteCallback Dictionary_DeletePtr = NULL;

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

NotificationCenter_AddInstanceObserverCallback NotificationCenter_AddInstanceObserverPtr = NULL;
NotificationCenter_RemoveInstanceObserverCallback NotificationCenter_RemoveInstanceObserverPtr = NULL;
NotificationCenter_FireCallback NotificationCenter_FirePtr = NULL;
NotificationCenter_FireWithJSONCallback NotificationCenter_FireWithJSONPtr = NULL;
NotificationCenter_FireWithJSONVCallback NotificationCenter_FireWithJSONVPtr = NULL;
NotificationCenter_FireAfterDelayCallback NotificationCenter_FireAfterDelayPtr = NULL;
NotificationCenter_FireAfterDelayWithJSONCallback NotificationCenter_FireAfterDelayWithJSONPtr = NULL;
NotificationCenter_FireAfterDelayWithJSONVCallback NotificationCenter_FireAfterDelayWithJSONVPtr = NULL;

typedef bool (*Interop_GenerateInstanceIdCallback)(char *String, int32_t MaxString);

Interop_GenerateInstanceIdCallback Interop_GenerateInstanceIdPtr = NULL;

/*********************************************************************/

void *Class_ConvertFromInstanceId(const char *InstanceId) {
    return Class_ConvertFromInstanceIdPtr(InstanceId);
}

char *Class_ConvertToInstanceId(void *Pointer) {
    return Class_ConvertToInstanceIdPtr(Pointer);
}

bool Class_TrackInstance(void *Pointer, const char *InstanceId) {
    return Class_TrackInstancePtr(Pointer, InstanceId);
}

bool Class_UntrackInstance(void *Pointer) {
    return Class_UntrackInstancePtr(Pointer);
}

bool Dictionary_Create(echandle *DictionaryHandle) {
    return Dictionary_CreatePtr(DictionaryHandle);
}

bool Dictionary_Delete(echandle *DictionaryHandle) {
    return Dictionary_DeletePtr(DictionaryHandle);
}

bool Interop_GenerateInstanceId(char *String, int32_t MaxString);

bool NotificationCenter_AddInstanceObserver(const char *Type, const char *Notification, const void *Sender,
                                            void *UserPtr, NotificationCenter_ObserverCallback Callback) {
    return NotificationCenter_AddInstanceObserverPtr(Type, Notification, Sender, UserPtr, Callback);
}

bool NotificationCenter_AddObserver(const char *Type, const char *Notification, void *UserPtr,
                                    NotificationCenter_ObserverCallback Callback) {
    return NotificationCenter_AddInstanceObserver(Type, Notification, NOTIFICATIONCENTER_GLOBALSENDER, UserPtr,
                                                  Callback);
}

bool NotificationCenter_RemoveInstanceObserver(const char *Type, const char *Notification, const void *Sender,
                                               void *UserPtr, NotificationCenter_ObserverCallback Callback) {
    return NotificationCenter_RemoveInstanceObserverPtr(Type, Notification, Sender, UserPtr, Callback);
}

bool NotificationCenter_RemoveObserver(const char *Type, const char *Notification, void *UserPtr,
                                       NotificationCenter_ObserverCallback Callback) {
    return NotificationCenter_RemoveInstanceObserver(Type, Notification, NOTIFICATIONCENTER_GLOBALSENDER, UserPtr,
                                                     Callback);
}

bool NotificationCenter_Fire(const char *Type, const char *Notification, const void *Sender,
                             echandle DictionaryHandle) {
    return NotificationCenter_FirePtr(Type, Notification, Sender, DictionaryHandle);
}

bool NotificationCenter_FireWithJSON(const char *Type, const char *Notification, const void *Sender, const char *Format,
                                     ...) {
    va_list ArgumentList;
    bool RetVal = false;
    va_start(ArgumentList, Format);
    RetVal = NotificationCenter_FireWithJSONVPtr(Type, Notification, Sender, Format, ArgumentList);
    va_end(ArgumentList);
    return RetVal;
}

bool NotificationCenter_FireAfterDelay(const char *Type, const char *Notification, const void *Sender, int32_t DelayMS,
                                       echandle DictionaryHandle) {
    return NotificationCenter_FireAfterDelayPtr(Type, Notification, Sender, DelayMS, DictionaryHandle);
}

bool NotificationCenter_FireAfterDelayWithJSON(const char *Type, const char *Notification, const void *Sender,
                                               int32_t DelayMS, const char *Format, ...) {
    va_list ArgumentList;
    bool RetVal = false;
    va_start(ArgumentList, Format);
    RetVal = NotificationCenter_FireAfterDelayWithJSONVPtr(Type, Notification, Sender, DelayMS, Format, ArgumentList);
    va_end(ArgumentList);
    return RetVal;
}

bool Interop_GenerateInstanceId(char *String, int32_t MaxString) {
    return Interop_GenerateInstanceIdPtr(String, MaxString);
}

/*********************************************************************/

bool Interop_SetOverride(const char *Key, void *Value) {
    if (strcmp(Key, "Class_ConvertFromInstanceId") == 0)
        Class_ConvertFromInstanceIdPtr = (Class_ConvertFromInstanceIdCallback)Value;
    else if (strcmp(Key, "Class_ConvertToInstanceId") == 0)
        Class_ConvertToInstanceIdPtr = (Class_ConvertToInstanceIdCallback)Value;
    else if (strcmp(Key, "Class_TrackInstance") == 0)
        Class_TrackInstancePtr = (Class_TrackInstanceCallback)Value;
    else if (strcmp(Key, "Class_UntrackInstance") == 0)
        Class_UntrackInstancePtr = (Class_UntrackInstanceCallback)Value;

    else if (strcmp(Key, "Dictionary_Create") == 0)
        Dictionary_CreatePtr = (Dictionary_CreateCallback)Value;
    else if (strcmp(Key, "Dictionary_Delete") == 0)
        Dictionary_DeletePtr = (Dictionary_DeleteCallback)Value;

    else if (strcmp(Key, "NotificationCenter_AddInstanceObserver") == 0)
        NotificationCenter_AddInstanceObserverPtr = (NotificationCenter_AddInstanceObserverCallback)Value;
    else if (strcmp(Key, "NotificationCenter_RemoveInstanceObserver") == 0)
        NotificationCenter_RemoveInstanceObserverPtr = (NotificationCenter_RemoveInstanceObserverCallback)Value;
    else if (strcmp(Key, "NotificationCenter_Fire") == 0)
        NotificationCenter_FirePtr = (NotificationCenter_FireCallback)Value;
    else if (strcmp(Key, "NotificationCenter_FireWithJSON") == 0)
        NotificationCenter_FireWithJSONPtr = (NotificationCenter_FireWithJSONCallback)Value;
    else if (strcmp(Key, "NotificationCenter_FireWithJSONV") == 0)
        NotificationCenter_FireWithJSONVPtr = (NotificationCenter_FireWithJSONVCallback)Value;
    else if (strcmp(Key, "NotificationCenter_FireAfterDelay") == 0)
        NotificationCenter_FireAfterDelayPtr = (NotificationCenter_FireAfterDelayCallback)Value;
    else if (strcmp(Key, "NotificationCenter_FireAfterDelayWithJSON") == 0)
        NotificationCenter_FireAfterDelayWithJSONPtr = (NotificationCenter_FireAfterDelayWithJSONCallback)Value;
    else if (strcmp(Key, "NotificationCenter_FireAfterDelayWithJSONV") == 0)
        NotificationCenter_FireAfterDelayWithJSONVPtr = (NotificationCenter_FireAfterDelayWithJSONVCallback)Value;

    else if (strcmp(Key, "Interop_GenerateInstanceId") == 0)
        Interop_GenerateInstanceIdPtr = (Interop_GenerateInstanceIdCallback)Value;

    return true;
}

/*********************************************************************/