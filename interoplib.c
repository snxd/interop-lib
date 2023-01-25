#include "interoplib.h"

#include <stdarg.h>

/*********************************************************************/

#define NOTIFICATIONCENTER_GLOBALSENDER ("Global")

/*********************************************************************/

#define BASE16_LOWERCHARS ("0123456789abcdef")
#define BASE16_UPPERCHARS ("0123456789ABCDEF")

/*********************************************************************/

bool String_ConvertToHex(const uint8_t *Binary, int32_t BinarySize, bool Lower, char *Hex, int32_t MaxHex) {
    char *Base16Symbols = NULL;

    if (Lower == true)
        Base16Symbols = BASE16_LOWERCHARS;
    else
        Base16Symbols = BASE16_UPPERCHARS;

    while ((MaxHex > 2) && (BinarySize > 0)) {
        Hex[0] = Base16Symbols[*Binary >> 4];
        Hex[1] = Base16Symbols[*Binary & 0xF];

        Hex += 2;
        MaxHex -= 2;
        Binary += 1;
        BinarySize -= 1;
    }
    if (MaxHex > 1 && BinarySize > 0)
        *Hex++ = Base16Symbols[*Binary >> 4];

    if (MaxHex == 0)
        return false;
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

typedef bool (*Dictionary_CreateCallback)(echandle *DictionaryHandle);
typedef int32_t (*Dictionary_ReleaseCallback)(echandle *DictionaryHandle);

typedef bool (*NotificationCenter_AddInstanceObserverCallback)(const char *Type, const char *Notification,
                                                               const char *Sender, void *UserPtr,
                                                               NotificationCenter_ObserverCallback Callback);
typedef bool (*NotificationCenter_RemoveInstanceObserverCallback)(const char *Type, const char *Notification,
                                                                  const char *Sender, void *UserPtr,
                                                                  NotificationCenter_ObserverCallback Callback);
typedef bool (*NotificationCenter_FireCallback)(const char *Type, const char *Notification, const char *Sender,
                                                echandle DictionaryHandle);
typedef bool (*NotificationCenter_FireWithJSONCallback)(const char *Type, const char *Notification, const char *Sender,
                                                        const char *Format, ...);
typedef bool (*NotificationCenter_FireWithJSONVCallback)(const char *Type, const char *Notification, const char *Sender,
                                                         const char *Format, va_list ArgumentList);
typedef bool (*NotificationCenter_FireAfterDelayCallback)(const char *Type, const char *Notification,
                                                          const char *Sender, int32_t DelayMS,
                                                          echandle DictionaryHandle);
typedef bool (*NotificationCenter_FireAfterDelayWithJSONCallback)(const char *Type, const char *Notification,
                                                                  const char *Sender, int32_t DelayMS,
                                                                  const char *Format, ...);
typedef bool (*NotificationCenter_FireAfterDelayWithJSONVCallback)(const char *Type, const char *Notification,
                                                                   const char *Sender, int32_t DelayMS,
                                                                   const char *Format, va_list ArgumentList);

typedef bool (*Interop_GenerateInstanceIdCallback)(char *String, int32_t MaxString);

typedef struct GlobalInteropLibStruct {
    Class_ConvertFromInstanceIdCallback Class_ConvertFromInstanceId;
    Class_ConvertToInstanceIdCallback Class_ConvertToInstanceId;
    Class_TrackInstanceCallback Class_TrackInstance;
    Class_UntrackInstanceCallback Class_UntrackInstance;
    Dictionary_CreateCallback Dictionary_Create;
    Dictionary_ReleaseCallback Dictionary_Release;
    NotificationCenter_AddInstanceObserverCallback NotificationCenter_AddInstanceObserver;
    NotificationCenter_RemoveInstanceObserverCallback NotificationCenter_RemoveInstanceObserver;
    NotificationCenter_FireCallback NotificationCenter_Fire;
    NotificationCenter_FireWithJSONCallback NotificationCenter_FireWithJSON;
    NotificationCenter_FireWithJSONVCallback NotificationCenter_FireWithJSONV;
    NotificationCenter_FireAfterDelayCallback NotificationCenter_FireAfterDelay;
    NotificationCenter_FireAfterDelayWithJSONCallback NotificationCenter_FireAfterDelayWithJSON;
    NotificationCenter_FireAfterDelayWithJSONVCallback NotificationCenter_FireAfterDelayWithJSONV;
    Interop_GenerateInstanceIdCallback Interop_GenerateInstanceId;
} GlobalInteropLibStruct;

GlobalInteropLibStruct GlobalInteropLib;

/*********************************************************************/

void *Class_ConvertFromInstanceId(const char *InstanceId) {
    return GlobalInteropLib.Class_ConvertFromInstanceId(InstanceId);
}

char *Class_ConvertToInstanceId(void *Pointer) {
    return GlobalInteropLib.Class_ConvertToInstanceId(Pointer);
}

bool Class_TrackInstance(void *Pointer, const char *InstanceId) {
    return GlobalInteropLib.Class_TrackInstance(Pointer, InstanceId);
}

bool Class_UntrackInstance(void *Pointer) {
    return GlobalInteropLib.Class_UntrackInstance(Pointer);
}

bool Dictionary_Create(echandle *DictionaryHandle) {
    return GlobalInteropLib.Dictionary_Create(DictionaryHandle);
}

int32_t Dictionary_Release(echandle *DictionaryHandle) {
    return GlobalInteropLib.Dictionary_Release(DictionaryHandle);
}

bool Interop_GenerateInstanceId(char *String, int32_t MaxString);

bool NotificationCenter_AddInstanceObserver(const char *Type, const char *Notification, const char *Sender,
                                            void *UserPtr, NotificationCenter_ObserverCallback Callback) {
    return GlobalInteropLib.NotificationCenter_AddInstanceObserver(Type, Notification, Sender, UserPtr, Callback);
}

bool NotificationCenter_AddObserver(const char *Type, const char *Notification, void *UserPtr,
                                    NotificationCenter_ObserverCallback Callback) {
    return NotificationCenter_AddInstanceObserver(Type, Notification, NOTIFICATIONCENTER_GLOBALSENDER, UserPtr,
                                                  Callback);
}

bool NotificationCenter_RemoveInstanceObserver(const char *Type, const char *Notification, const char *Sender,
                                               void *UserPtr, NotificationCenter_ObserverCallback Callback) {
    return GlobalInteropLib.NotificationCenter_RemoveInstanceObserver(Type, Notification, Sender, UserPtr, Callback);
}

bool NotificationCenter_RemoveObserver(const char *Type, const char *Notification, void *UserPtr,
                                       NotificationCenter_ObserverCallback Callback) {
    return NotificationCenter_RemoveInstanceObserver(Type, Notification, NOTIFICATIONCENTER_GLOBALSENDER, UserPtr,
                                                     Callback);
}

bool NotificationCenter_Fire(const char *Type, const char *Notification, const char *Sender,
                             echandle DictionaryHandle) {
    return GlobalInteropLib.NotificationCenter_Fire(Type, Notification, Sender, DictionaryHandle);
}

bool NotificationCenter_FireWithJSON(const char *Type, const char *Notification, const char *Sender, const char *Format,
                                     ...) {
    va_list ArgumentList;
    bool RetVal = false;
    va_start(ArgumentList, Format);
    RetVal = GlobalInteropLib.NotificationCenter_FireWithJSONV(Type, Notification, Sender, Format, ArgumentList);
    va_end(ArgumentList);
    return RetVal;
}

bool NotificationCenter_FireAfterDelay(const char *Type, const char *Notification, const char *Sender, int32_t DelayMS,
                                       echandle DictionaryHandle) {
    return GlobalInteropLib.NotificationCenter_FireAfterDelay(Type, Notification, Sender, DelayMS, DictionaryHandle);
}

bool NotificationCenter_FireAfterDelayWithJSON(const char *Type, const char *Notification, const char *Sender,
                                               int32_t DelayMS, const char *Format, ...) {
    va_list ArgumentList;
    bool RetVal = false;
    va_start(ArgumentList, Format);
    RetVal = GlobalInteropLib.NotificationCenter_FireAfterDelayWithJSONV(Type, Notification, Sender, DelayMS, Format,
                                                                         ArgumentList);
    va_end(ArgumentList);
    return RetVal;
}

bool Interop_GenerateInstanceId(char *String, int32_t MaxString) {
    return GlobalInteropLib.Interop_GenerateInstanceId(String, MaxString);
}

/*********************************************************************/

bool Interop_SetOverride(const char *Key, void *Value) {
    if (strcmp(Key, "Class_ConvertFromInstanceId") == 0)
        GlobalInteropLib.Class_ConvertFromInstanceId = (Class_ConvertFromInstanceIdCallback)Value;
    else if (strcmp(Key, "Class_ConvertToInstanceId") == 0)
        GlobalInteropLib.Class_ConvertToInstanceId = (Class_ConvertToInstanceIdCallback)Value;
    else if (strcmp(Key, "Class_TrackInstance") == 0)
        GlobalInteropLib.Class_TrackInstance = (Class_TrackInstanceCallback)Value;
    else if (strcmp(Key, "Class_UntrackInstance") == 0)
        GlobalInteropLib.Class_UntrackInstance = (Class_UntrackInstanceCallback)Value;

    else if (strcmp(Key, "Dictionary_Create") == 0)
        GlobalInteropLib.Dictionary_Create = (Dictionary_CreateCallback)Value;
    else if (strcmp(Key, "Dictionary_Release") == 0)
        GlobalInteropLib.Dictionary_Release = (Dictionary_ReleaseCallback)Value;

    else if (strcmp(Key, "NotificationCenter_AddInstanceObserver") == 0)
        GlobalInteropLib.NotificationCenter_AddInstanceObserver = (NotificationCenter_AddInstanceObserverCallback)Value;
    else if (strcmp(Key, "NotificationCenter_RemoveInstanceObserver") == 0)
        GlobalInteropLib.NotificationCenter_RemoveInstanceObserver =
            (NotificationCenter_RemoveInstanceObserverCallback)Value;
    else if (strcmp(Key, "NotificationCenter_Fire") == 0)
        GlobalInteropLib.NotificationCenter_Fire = (NotificationCenter_FireCallback)Value;
    else if (strcmp(Key, "NotificationCenter_FireWithJSON") == 0)
        GlobalInteropLib.NotificationCenter_FireWithJSON = (NotificationCenter_FireWithJSONCallback)Value;
    else if (strcmp(Key, "NotificationCenter_FireWithJSONV") == 0)
        GlobalInteropLib.NotificationCenter_FireWithJSONV = (NotificationCenter_FireWithJSONVCallback)Value;
    else if (strcmp(Key, "NotificationCenter_FireAfterDelay") == 0)
        GlobalInteropLib.NotificationCenter_FireAfterDelay = (NotificationCenter_FireAfterDelayCallback)Value;
    else if (strcmp(Key, "NotificationCenter_FireAfterDelayWithJSON") == 0)
        GlobalInteropLib.NotificationCenter_FireAfterDelayWithJSON =
            (NotificationCenter_FireAfterDelayWithJSONCallback)Value;
    else if (strcmp(Key, "NotificationCenter_FireAfterDelayWithJSONV") == 0)
        GlobalInteropLib.NotificationCenter_FireAfterDelayWithJSONV =
            (NotificationCenter_FireAfterDelayWithJSONVCallback)Value;

    else if (strcmp(Key, "Interop_GenerateInstanceId") == 0)
        GlobalInteropLib.Interop_GenerateInstanceId = (Interop_GenerateInstanceIdCallback)Value;

    return true;
}

/*********************************************************************/