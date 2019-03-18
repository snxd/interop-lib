#include "interoplib.h"

#include <stdarg.h>

/*********************************************************************/

#define NOTIFICATIONCENTER_GLOBALSENDER             ("Global")

/*********************************************************************/

#define BASE16SYM                                   ("0123456789ABCDEF")

#define Base16_EncodeLo(b)                          (BASE16SYM[(b & 0xff) >> 4])
#define Base16_EncodeHi(b)                          (BASE16SYM[b & 0xF])

/*********************************************************************/

Class_ConvertFromInstanceIdCallback                 Class_ConvertFromInstanceIdPtr = NULL;
Class_ConvertToInstanceIdCallback                   Class_ConvertToInstanceIdPtr = NULL;
Class_TrackInstanceCallback                         Class_TrackInstancePtr = NULL;
Class_UntrackInstanceCallback                       Class_UntrackInstancePtr = NULL;

Dictionary_CreateCallback                           Dictionary_CreatePtr = NULL;
Dictionary_DeleteCallback                           Dictionary_DeletePtr = NULL;

NotificationCenter_AddInstanceObserverCallback      NotificationCenter_AddInstanceObserverPtr = NULL;
NotificationCenter_RemoveInstanceObserverCallback   NotificationCenter_RemoveInstanceObserverPtr = NULL;
NotificationCenter_FireCallback                     NotificationCenter_FirePtr = NULL;
NotificationCenter_FireWithJSONCallback             NotificationCenter_FireWithJSONPtr = NULL;
NotificationCenter_FireWithJSONVCallback            NotificationCenter_FireWithJSONVPtr = NULL;
NotificationCenter_FireAfterDelayCallback           NotificationCenter_FireAfterDelayPtr = NULL;
NotificationCenter_FireAfterDelayWithJSONCallback   NotificationCenter_FireAfterDelayWithJSONPtr = NULL;
NotificationCenter_FireAfterDelayWithJSONVCallback  NotificationCenter_FireAfterDelayWithJSONVPtr = NULL;

Interop_GenerateInstanceIdCallback                  Interop_GenerateInstanceIdPtr = NULL;

/*********************************************************************/

int32 String_ConvertToHex(char *Binary, int32 BinarySize, char *Hex, int32 MaxHex)
{
    int32 ReturnVal = TRUE;

    while ((MaxHex > 2) && (BinarySize > 0))
    {
        Hex[0] = Base16_EncodeLo(*Binary);
        Hex[1] = Base16_EncodeHi(*Binary);

        Hex += 2;
        MaxHex -= 2;
        Binary += 1;
        BinarySize -= 1;
    }

    if (BinarySize > 0)
        ReturnVal = FALSE;

    *Hex = 0;
    return ReturnVal;
}

/*********************************************************************/

static uint8 Base64EncodeLookup[256] = { 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x2B, 0x2F, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 };

/*********************************************************************/

int32 Base64_Encode(uint8 *Source, int32 SourceLength, char *Target, int32 MaxTarget, int32 *TargetLength)
{
    int32 i, n;
    int32 Done = FALSE;
    int32 ReturnVal = TRUE;
    char *TargetStart = Target;
    char *TargetEnd = Target + (MaxTarget - 4);
    uint8 InBuffer[3], OutBuffer[4];



    *TargetLength = 0;

    while (Done == FALSE)
    {
        InBuffer[0] = 0;
        InBuffer[1] = 0;
        InBuffer[2] = 0;
        for (n = 0; n < 3; n++)
        {
            InBuffer[n] = *Source++;
            SourceLength -= 1;
            if (SourceLength < 0)
            {
                Done = TRUE;
                break;
            }
        }

        if (n > 0)
        {
            OutBuffer[0] = Base64EncodeLookup[InBuffer[0] >> 2];
            OutBuffer[1] = Base64EncodeLookup[((InBuffer[0] & 3) << 4) | (InBuffer[1] >> 4)];
            OutBuffer[2] = Base64EncodeLookup[((InBuffer[1] & 0xF) << 2) | (InBuffer[2] >> 6)];
            OutBuffer[3] = Base64EncodeLookup[InBuffer[2] & 0x3F];

            /* Replace characters in output stream with "=" pad
            characters if fewer than three characters were
            read from the end of the input stream. */

            if (n < 3)
            {
                OutBuffer[3] = '=';

                if (n < 2)
                {
                    OutBuffer[2] = '=';
                }
            }
            for (i = 0; i < 4; i++)
                *Target++ = OutBuffer[i];
            if (Target >= TargetEnd)
            {
                ReturnVal = FALSE;
                break;
            }
        }
    }

    *Target++ = 0;
    *TargetLength = (int32)(Target - TargetStart);
    return ReturnVal;
}

int32 Base64_CalculateEncodeSize(int32 SourceLength, int32 *BytesRequired)
{
    // Round up to the nearest multiple of 4.
    *BytesRequired = ((4 * SourceLength / 3) + 3) & ~3;

    // Include NULL terminator
    *BytesRequired += 1;

    return TRUE;
}

void *Class_ConvertFromInstanceId(char *InstanceId)
{
    return Class_ConvertFromInstanceIdPtr(InstanceId);
}

char *Class_ConvertToInstanceId(void *Pointer)
{
    return Class_ConvertToInstanceIdPtr(Pointer);
}

int32 Class_TrackInstance(void *Pointer, char *InstanceId)
{
    return Class_TrackInstancePtr(Pointer, InstanceId);
}

int32 Class_UntrackInstance(void *Pointer)
{
    return Class_UntrackInstancePtr(Pointer);
}

int32 Dictionary_Create(echandle *DictionaryHandle)
{
    return Dictionary_CreatePtr(DictionaryHandle);
}

int32 Dictionary_Delete(echandle *DictionaryHandle)
{
    return Dictionary_DeletePtr(DictionaryHandle);
}

int32 NotificationCenter_AddInstanceObserver(char *Type, char *Notification, void *Sender, void *UserPtr, NotificationCenter_ObserverCallback Callback)
{
    return NotificationCenter_AddInstanceObserverPtr(Type, Notification, Sender, UserPtr, Callback);
}

int32 NotificationCenter_AddObserver(char *Type, char *Notification, void *UserPtr, NotificationCenter_ObserverCallback Callback)
{
    return NotificationCenter_AddInstanceObserver(Type, Notification, NOTIFICATIONCENTER_GLOBALSENDER, UserPtr, Callback);
}

int32 NotificationCenter_RemoveInstanceObserver(char *Type, char *Notification, void *Sender, void *UserPtr, NotificationCenter_ObserverCallback Callback)
{
    return NotificationCenter_RemoveInstanceObserverPtr(Type, Notification, Sender, UserPtr, Callback);
}

int32 NotificationCenter_RemoveObserver(char *Type, char *Notification, void *UserPtr, NotificationCenter_ObserverCallback Callback)
{
    return NotificationCenter_RemoveInstanceObserver(Type, Notification, NOTIFICATIONCENTER_GLOBALSENDER, UserPtr, Callback);
}

int32 NotificationCenter_Fire(char *Type, char *Notification, void *Sender, echandle DictionaryHandle)
{
    return NotificationCenter_FirePtr(Type, Notification, Sender, DictionaryHandle);
}

int32 NotificationCenter_FireWithJSON(char *Type, char *Notification, void *Sender, char *Format, ...)
{
    va_list ArgumentList;
    int32 RetVal = FALSE;
    va_start(ArgumentList, Format);
    RetVal = NotificationCenter_FireWithJSONVPtr(Type, Notification, Sender, Format, ArgumentList);
    va_end(ArgumentList);
    return RetVal;
}

int32 NotificationCenter_FireAfterDelay(char *Type, char *Notification, void *Sender, int32 DelayMS, echandle DictionaryHandle)
{
    return NotificationCenter_FireAfterDelayPtr(Type, Notification, Sender, DelayMS, DictionaryHandle);
}

int32 NotificationCenter_FireAfterDelayWithJSON(char *Type, char *Notification, void *Sender, int32 DelayMS, char *Format, ...)
{
    va_list ArgumentList;
    int32 RetVal = FALSE;
    va_start(ArgumentList, Format);
    RetVal = NotificationCenter_FireAfterDelayWithJSONVPtr(Type, Notification, Sender, DelayMS, Format, ArgumentList);
    va_end(ArgumentList);
    return RetVal;
}

int32 Interop_GenerateInstanceId(char *String, int32 MaxString)
{
    return Interop_GenerateInstanceIdPtr(String, MaxString);
}

/*********************************************************************/

int32 InteropLib_SetOverride(char *Key, void *Value)
{
    if (String_Compare(Key, "Class_ConvertFromInstanceId") == TRUE)
        Class_ConvertFromInstanceIdPtr = (Class_ConvertFromInstanceIdCallback)Value;
    else if (String_Compare(Key, "Class_ConvertToInstanceId") == TRUE)
        Class_ConvertToInstanceIdPtr = (Class_ConvertToInstanceIdCallback)Value;
    else if (String_Compare(Key, "Class_TrackInstance") == TRUE)
        Class_TrackInstancePtr = (Class_TrackInstanceCallback)Value;
    else if (String_Compare(Key, "Class_UntrackInstance") == TRUE)
        Class_UntrackInstancePtr = (Class_UntrackInstanceCallback)Value;
    
    else if (String_Compare(Key, "Dictionary_Create") == TRUE)
        Dictionary_CreatePtr = (Dictionary_CreateCallback)Value;
    else if (String_Compare(Key, "Dictionary_Delete") == TRUE)
        Dictionary_DeletePtr = (Dictionary_DeleteCallback)Value;

    else if (String_Compare(Key, "NotificationCenter_AddInstanceObserver") == TRUE)
        NotificationCenter_AddInstanceObserverPtr = (NotificationCenter_AddInstanceObserverCallback)Value;
    else if (String_Compare(Key, "NotificationCenter_RemoveInstanceObserver") == TRUE)
        NotificationCenter_RemoveInstanceObserverPtr = (NotificationCenter_RemoveInstanceObserverCallback)Value;
    else if (String_Compare(Key, "NotificationCenter_Fire") == TRUE)
        NotificationCenter_FirePtr = (NotificationCenter_FireCallback)Value;
    else if (String_Compare(Key, "NotificationCenter_FireWithJSON") == TRUE)
        NotificationCenter_FireWithJSONPtr = (NotificationCenter_FireWithJSONCallback)Value;
    else if (String_Compare(Key, "NotificationCenter_FireWithJSONV") == TRUE)
        NotificationCenter_FireWithJSONVPtr = (NotificationCenter_FireWithJSONVCallback)Value;
    else if (String_Compare(Key, "NotificationCenter_FireAfterDelay") == TRUE)
        NotificationCenter_FireAfterDelayPtr = (NotificationCenter_FireAfterDelayCallback)Value;
    else if (String_Compare(Key, "NotificationCenter_FireAfterDelayWithJSON") == TRUE)
        NotificationCenter_FireAfterDelayWithJSONPtr = (NotificationCenter_FireAfterDelayWithJSONCallback)Value;
    else if (String_Compare(Key, "NotificationCenter_FireAfterDelayWithJSONV") == TRUE)
        NotificationCenter_FireAfterDelayWithJSONVPtr = (NotificationCenter_FireAfterDelayWithJSONVCallback)Value;

    else if (String_Compare(Key, "Interop_GenerateInstanceId") == TRUE)
        Interop_GenerateInstanceIdPtr = (Interop_GenerateInstanceIdCallback)Value;

    return TRUE;
}

/*********************************************************************/