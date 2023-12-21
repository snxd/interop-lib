#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************/

typedef struct ITask {
    const char *Type;
    echandle (*Create)(echandle TaskHandle);
    echandle (*AddRef)(echandle Handle);
    int32_t (*Release)(echandle *Handle);
} ITask;

/*********************************************************************/

typedef bool (*ITask_ExpandStringCallback)(echandle TaskHandle, void *UserPtr, char *Key, char *Buffer,
                                           int32_t MaxBuffer);
typedef bool (*ITask_EvaluatePathCallback)(echandle TaskHandle, void *UserPtr, char *Path, char *Buffer,
                                           int32_t MaxBuffer);
typedef bool (*ITask_CompleteCallback)(echandle TaskHandle, void *UserPtr, echandle DictionaryHandle);
typedef bool (*ITask_RequestCompleteCallback)(echandle TaskHandle, void *UserPtr, uint8_t *BufferPtr,
                                              int32_t BufferSize, int32_t ErrorCode, int32_t ErrorCodeEx);

/*********************************************************************/

typedef struct ITaskVtbl {
    bool (*SubAction_Null)(echandle TaskHandle, void *UserPtr, echandle DictionaryHandle);
    bool (*SubAction_Complete)(echandle TaskHandle, void *UserPtr, echandle DictionaryHandle);

    bool (*IsCompleted)(echandle TaskHandle);
    bool (*IsCancelled)(echandle TaskHandle);

    const char *(*GetType)(echandle TaskHandle);
    float64_t (*GetTimeElapsed)(echandle TaskHandle);
    const char *(*GetName)(echandle TaskHandle);
    bool (*HasArgument)(echandle TaskHandle, const char *Name);
    bool (*GetArgumentPtr)(echandle TaskHandle, const char *Name, const char **ValuePtr);
    bool (*GetArgumentType)(echandle TaskHandle, const char *Name, int32_t *Type);
    bool (*GetStringArgument)(echandle TaskHandle, const char *Name, char *Value, int32_t MaxValue);
    bool (*GetMultiStringArgument)(echandle TaskHandle, const char *Name, char *Value, int32_t MaxValue);
    bool (*GetBooleanArgument)(echandle TaskHandle, const char *Name, bool *Value);
    bool (*GetNumberArgument)(echandle TaskHandle, const char *Name, float64_t *Value);
    bool (*SetStatus)(echandle TaskHandle, const char *Status);
    bool (*SetStatusString)(echandle TaskHandle, const char *Name, const char *Value);
    bool (*SetStatusNumber)(echandle TaskHandle, const char *Name, float64_t Value);
    bool (*SetStatusWithDictionary)(echandle TaskHandle, echandle DictionaryHandle);
    bool (*SetProgress)(echandle TaskHandle, float64_t Progress);

    bool (*RunSubAction)(echandle TaskHandle, const char *Name, void *UserPtr, ITask_CompleteCallback Callback);
    bool (*RunSubTask)(echandle TaskHandle, const char *Name, echandle DictionaryHandle, void *UserPtr,
                       ITask_CompleteCallback Callback);

    bool (*Start)(echandle TaskHandle);
    bool (*Complete)(echandle TaskHandle, echandle DictionaryHandle);
    bool (*Cancel)(echandle TaskHandle);
    bool (*Dump)(echandle TaskHandle);
    bool (*Log)(echandle TaskHandle, const char *Format, ...);
    bool (*VerboseLog)(echandle TaskHandle, int32_t Level, const char *Format, ...);
    bool (*ExpandString)(echandle TaskHandle, char *String, int32_t MaxString);

    bool (*LoadFromDictionary)(echandle TaskHandle, echandle DictionaryHandle, const char *Path);

    bool (*HasError)(echandle TaskHandle, const char *Error);
    bool (*HasWarning)(echandle TaskHandle, const char *Warning);
    int32_t (*GetErrorCount)(echandle TaskHandle);
    int32_t (*GetWarningCount)(echandle TaskHandle);
    bool (*AddError)(echandle TaskHandle, const char *Format, ...);
    bool (*AddErrorFromMap)(echandle TaskHandle, int32_t ExitCode, const char *DefaultExitCodeString);
    const char *(*GetError)(echandle TaskHandle, int32_t Index);
    bool (*AddWarning)(echandle TaskHandle, const char *Format, ...);
    const char *(*GetWarning)(echandle TaskHandle, int32_t Index);
    bool (*ClearErrors)(echandle TaskHandle);
    bool (*ClearWarnings)(echandle TaskHandle);

    bool (*SetDelayedCancel)(echandle TaskHandle, bool DelayedCancel);
    bool (*GetDelayedCancel)(echandle TaskHandle);
    echandle (*GetWorkflowHandle)(echandle TaskHandle);
    echandle (*GetDictionaryHandle)(echandle TaskHandle);
    echandle (*GetStatusDictionaryHandle)(echandle TaskHandle);
    bool (*SetExpandStringCallback)(echandle TaskHandle, void *UserPtr, ITask_ExpandStringCallback Callback);
    bool (*GetExpandStringCallback)(echandle TaskHandle, void **UserPtr, ITask_ExpandStringCallback *Callback);

    bool (*RequestURL)(echandle TaskHandle, const char *URL, void *UserPtr, ITask_RequestCompleteCallback Callback);

    bool (*RunSubActionNext)(echandle TaskHandle, const char *Name, echandle PreviousCompleteDictionaryHandle,
                             void *UserPtr, ITask_CompleteCallback Callback);
} ITaskVtbl;

/*********************************************************************/

#define ITask_RequireArgument(HND, NAME)               \
    if (!ITask_HasArgument(HND, NAME)) {               \
        ITask_Log(HND, #NAME " argument not defined"); \
        ITask_AddError(HND, "Task_Error_MissingArg");  \
        ITask_Complete(HND, NULL);                     \
        return true;                                   \
    }

#define ITask_SubAction_Null(TaskHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->SubAction_Null(TaskHandle, UserPtr, DictionaryHandle)
#define ITask_SubAction_Complete(TaskHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->SubAction_Complete(TaskHandle, UserPtr, DictionaryHandle)

#define ITask_IsCompleted(TaskHandle)       Class_VtblCast(TaskHandle, ITaskVtbl)->IsCompleted(TaskHandle)
#define ITask_IsCancelled(TaskHandle)       Class_VtblCast(TaskHandle, ITaskVtbl)->IsCancelled(TaskHandle)

#define ITask_GetType(TaskHandle)           Class_VtblCast(TaskHandle, ITaskVtbl)->GetType(TaskHandle)
#define ITask_GetTimeElapsed(TaskHandle)    Class_VtblCast(TaskHandle, ITaskVtbl)->GetTimeElapsed(TaskHandle)
#define ITask_GetName(TaskHandle)           Class_VtblCast(TaskHandle, ITaskVtbl)->GetName(TaskHandle)
#define ITask_HasArgument(TaskHandle, Name) Class_VtblCast(TaskHandle, ITaskVtbl)->HasArgument(TaskHandle, Name)
#define ITask_GetArgumentPtr(TaskHandle, Name, ValuePtr) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetArgumentPtr(TaskHandle, Name, ValuePtr)
#define ITask_GetArgumentType(TaskHandle, Name, Type) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetArgumentType(TaskHandle, Name, Type)
#define ITask_GetStringArgument(TaskHandle, Name, Value, MaxValue) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetStringArgument(TaskHandle, Name, Value, MaxValue)
#define ITask_GetMultiStringArgument(TaskHandle, Name, Value, MaxValue) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetMultiStringArgument(TaskHandle, Name, Value, MaxValue)
#define ITask_GetBooleanArgument(TaskHandle, Name, Value) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetBooleanArgument(TaskHandle, Name, Value)
#define ITask_GetNumberArgument(TaskHandle, Name, Value) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetNumberArgument(TaskHandle, Name, Value)
#define ITask_SetStatus(TaskHandle, Status) Class_VtblCast(TaskHandle, ITaskVtbl)->SetStatus(TaskHandle, Status)
#define ITask_SetStatusString(TaskHandle, Name, Value) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->SetStatusString(TaskHandle, Name, Value)
#define ITask_SetStatusNumber(TaskHandle, Name, Value) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->SetStatusNumber(TaskHandle, Name, Value)
#define ITask_SetStatusWithDictionary(TaskHandle, DictionaryHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->SetStatusWithDictionary(TaskHandle, DictionaryHandle)
#define ITask_SetProgress(TaskHandle, Progress) Class_VtblCast(TaskHandle, ITaskVtbl)->SetProgress(TaskHandle, Progress)

#define ITask_RunSubAction(TaskHandle, Name, UserPtr, Callback) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->RunSubAction(TaskHandle, Name, UserPtr, Callback)
#define ITask_RunSubActionNext(TaskHandle, Name, PreviousCompleteDictionaryHandle, UserPtr, Callback) \
    Class_VtblCast(TaskHandle, ITaskVtbl)                                                             \
        ->RunSubActionNext(TaskHandle, Name, PreviousCompleteDictionaryHandle, UserPtr, Callback)
#define ITask_RunSubTask(TaskHandle, Name, DictionaryHandle, UserPtr, Callback) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->RunSubTask(TaskHandle, Name, DictionaryHandle, UserPtr, Callback)

#define ITask_Start(TaskHandle) Class_VtblCast(TaskHandle, ITaskVtbl)->Start(TaskHandle)
#define ITask_Complete(TaskHandle, DictionaryHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->Complete(TaskHandle, DictionaryHandle)
#define ITask_Cancel(TaskHandle)           Class_VtblCast(TaskHandle, ITaskVtbl)->Cancel(TaskHandle)
#define ITask_Dump(TaskHandle)             Class_VtblCast(TaskHandle, ITaskVtbl)->Dump(TaskHandle)
#define ITask_Log(TaskHandle, Format, ...) Class_VtblCast(TaskHandle, ITaskVtbl)->Log(TaskHandle, Format, ##__VA_ARGS__)
#define ITask_VerboseLog(TaskHandle, Level, Format, ...) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->VerboseLog(TaskHandle, Level, Format, ##__VA_ARGS__)
#define ITask_ExpandString(TaskHandle, String, MaxString) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->ExpandString(TaskHandle, String, MaxString)

#define ITask_LoadFromDictionary(TaskHandle, DictionaryHandle, Path) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->LoadFromDictionary(TaskHandle, DictionaryHandle, Path)

#define ITask_HasError(TaskHandle)        Class_VtblCast(TaskHandle, ITaskVtbl)->HasError(TaskHandle)
#define ITask_HasWarning(TaskHandle)      Class_VtblCast(TaskHandle, ITaskVtbl)->HasWarning(TaskHandle)
#define ITask_GetErrorCount(TaskHandle)   Class_VtblCast(TaskHandle, ITaskVtbl)->GetErrorCount(TaskHandle)
#define ITask_GetWarningCount(TaskHandle) Class_VtblCast(TaskHandle, ITaskVtbl)->GetWarningCount(TaskHandle)
#define ITask_AddError(TaskHandle, Format, ...) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->AddError(TaskHandle, Format, ##__VA_ARGS__)
#define ITask_AddErrorFromMap(TaskHandle, ExitCode, DefaultExitCodeString) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->AddErrorFromMap(TaskHandle, ExitCode, DefaultExitCodeString)
#define ITask_GetError(TaskHandle, Index) Class_VtblCast(TaskHandle, ITaskVtbl)->GetError(TaskHandle, Index)
#define ITask_AddWarning(TaskHandle, Format, ...) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->AddWarning(TaskHandle, Format, ##__VA_ARGS__)
#define ITask_GetWarning(TaskHandle, Index) Class_VtblCast(TaskHandle, ITaskVtbl)->GetWarning(TaskHandle, Index)
#define ITask_ClearErrors(TaskHandle)       Class_VtblCast(TaskHandle, ITaskVtbl)->ClearErrors(TaskHandle)
#define ITask_ClearWarnings(TaskHandle)     Class_VtblCast(TaskHandle, ITaskVtbl)->ClearWarnings(TaskHandle)

#define ITask_SetDelayedCancel(TaskHandle, DelayedCancel) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->SetDelayedCancel(TaskHandle, DelayedCancel)
#define ITask_GetDelayedCancel(TaskHandle)    Class_VtblCast(TaskHandle, ITaskVtbl)->GetDelayedCancel(TaskHandle)
#define ITask_GetWorkflowHandle(TaskHandle)   Class_VtblCast(TaskHandle, ITaskVtbl)->GetWorkflowHandle(TaskHandle)
#define ITask_GetDictionaryHandle(TaskHandle) Class_VtblCast(TaskHandle, ITaskVtbl)->GetDictionaryHandle(TaskHandle)
#define ITask_GetStatusDictionaryHandle(TaskHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetStatusDictionaryHandle(TaskHandle)
#define ITask_SetExpandStringCallback(TaskHandle, UserPtr, Callback) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->SetExpandStringCallback(TaskHandle, UserPtr, Callback)
#define ITask_GetExpandStringCallback(TaskHandle, UserPtr, Callback) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetExpandStringCallback(TaskHandle, UserPtr, Callback)

#define ITask_RequestURL(TaskHandle, URL, UserPtr, Callback) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->RequestURL(TaskHandle, URL, UserPtr, Callback)

/*********************************************************************/

#define ITask_Declare(CLASS)         extern ITask CLASS##_INTERFACE;
#define ITask_DefineInt(TASK, CLASS) ITask CLASS##_INTERFACE = {#TASK, CLASS##_Create, CLASS##_AddRef, CLASS##_Release};
#define ITask_Define(TASK)           ITask_DefineInt(TASK, TASK)

/*********************************************************************/

#ifdef __cplusplus
}
#endif
