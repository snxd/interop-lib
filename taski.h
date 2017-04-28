#ifndef _TASK_INTERFACE_H_
#define _TASK_INTERFACE_H_

/*********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************/

typedef struct ITask {
    char     *Type;
    int32    (*Create)(echandle *Handle, echandle TaskHandle);
    echandle (*AddRef)(echandle Handle);
    int32    (*Release)(echandle *Handle);
} ITask;

/*********************************************************************/

typedef int32 (*ITask_ExpandStringCallback)(echandle TaskHandle, void *UserPtr, char *Key, char *Buffer, int32 MaxBuffer);
typedef int32 (*ITask_EvaluatePathCallback)(echandle TaskHandle, void *UserPtr, char *Path, char *Buffer, int32 MaxBuffer);
typedef int32 (*ITask_CompleteCallback)(echandle TaskHandle, void *UserPtr, echandle DictionaryHandle);

/*********************************************************************/

typedef struct ITaskVtbl {
    int32 (*SubAction_Null)(echandle TaskHandle, void *UserPtr, echandle DictionaryHandle);
    int32 (*SubAction_Complete)(echandle TaskHandle, void *UserPtr, echandle DictionaryHandle);

    int32 (*IsCompleted)(echandle TaskHandle);
    int32 (*IsCancelled)(echandle TaskHandle);

    char* (*GetType)(echandle TaskHandle);
    int32 (*GetTimeElapsed)(echandle TaskHandle, float64 *ElapsedTime);
    int32 (*GetName)(echandle TaskHandle, char *Name, int32 MaxName);
    int32 (*GetNamePtr)(echandle TaskHandle, char **NamePtr);
    int32 (*HasArgument)(echandle TaskHandle, char *Name);
    int32 (*GetArgumentPtr)(echandle TaskHandle, char *Name, char **ValuePtr);
    int32 (*GetArgumentType)(echandle TaskHandle, char *Name, int32 *Type);
    int32 (*GetStringArgument)(echandle TaskHandle, char *Name, char *Value, int32 MaxValue);
    int32 (*GetMultiStringArgument)(echandle TaskHandle, char *Name, char *Value, int32 MaxValue);
    int32 (*GetBooleanArgument)(echandle TaskHandle, char *Name, int32 *Value);
    int32 (*GetNumberArgument)(echandle TaskHandle, char *Name, float64 *Value);
    int32 (*SetStatus)(echandle TaskHandle, char *Status);
    int32 (*SetStatusString)(echandle TaskHandle, char *Name, char *Value);
    int32 (*SetStatusNumber)(echandle TaskHandle, char *Name, float64 Value);
    int32 (*SetStatusWithDictionary)(echandle TaskHandle, echandle DictionaryHandle);
    int32 (*SetProgress)(echandle TaskHandle, float64 Progress);

    int32 (*RunSubAction)(echandle TaskHandle, char *Name, void *UserPtr, ITask_CompleteCallback Callback);
    int32 (*RunSubTask)(echandle TaskHandle, char *Name, echandle DictionaryHandle, void *UserPtr, ITask_CompleteCallback Callback);

    int32 (*Start)(echandle TaskHandle);
    int32 (*Complete)(echandle TaskHandle, echandle DictionaryHandle);
    int32 (*Cancel)(echandle TaskHandle);
    int32 (*Dump)(echandle TaskHandle);
    int32 (*Print)(echandle TaskHandle, char *Format, ...);
    int32 (*VPrint)(echandle TaskHandle, int32 Depth, char *Format, va_list ArgumentLst);
    int32 (*VerbosePrint)(echandle TaskHandle, char *Format, ...);
    int32 (*ExpandString)(echandle TaskHandle, char *String, int32 MaxString);

    int32 (*LoadFromDictionary)(echandle TaskHandle, echandle DictionaryHandle, echandle ItemHandle);

    int32 (*HasError)(echandle TaskHandle, char *Error);
    int32 (*HasWarning)(echandle TaskHandle, char *Warning);
    int32 (*GetErrorCount)(echandle TaskHandle);
    int32 (*GetWarningCount)(echandle TaskHandle);
    int32 (*AddError)(echandle TaskHandle, char *Format, ...);
    int32 (*AddErrorFromMap)(echandle TaskHandle, int32 ExitCode, char *DefaultExitCodeString);
    int32 (*GetError)(echandle TaskHandle, int32 Index, char *Error, int32 MaxError);
    int32 (*AddWarning)(echandle TaskHandle, char *Format, ...);
    int32 (*GetWarning)(echandle TaskHandle, int32 Index, char *Warning, int32 MaxWarning);
    int32 (*ClearErrors)(echandle TaskHandle);
    int32 (*ClearWarnings)(echandle TaskHandle);

    int32 (*SetDelayedCancel)(echandle TaskHandle, int32 DelayedCancel);
    int32 (*GetDelayedCancel)(echandle TaskHandle, int32 *DelayedCancel);
    int32 (*GetWorkflowHandle)(echandle TaskHandle, echandle *WorkflowHandle);
    int32 (*GetDictionaryHandle)(echandle TaskHandle, echandle *DictionaryHandle);
    int32 (*GetStatusDictionaryHandle)(echandle TaskHandle, echandle *DictionaryHandle);
    int32 (*SetExpandStringCallback)(echandle TaskHandle, void *UserPtr, ITask_ExpandStringCallback Callback);
    int32 (*GetExpandStringCallback)(echandle TaskHandle, void **UserPtr, ITask_ExpandStringCallback *Callback);
} ITaskVtbl;

/*********************************************************************/

#define ITask_RequireArgument(HND, NAME)                        \
    if (ITask_HasArgument(HND, NAME) == FALSE)                  \
    {                                                           \
        ITask_Print(HND, #NAME " argument not defined\n");      \
        ITask_AddError(HND, "Task_Error_MissingArg");                 \
        ITask_Complete(HND, NULL);                              \
        return TRUE;                                            \
    }                                                           \

#define ITask_SubAction_Null(TaskHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->SubAction_Null
#define ITask_SubAction_Complete(TaskHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->SubAction_Complete

#define ITask_IsCompleted(TaskHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->IsCompleted(TaskHandle)
#define ITask_IsCancelled(TaskHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->IsCancelled(TaskHandle)

#define ITask_GetType(TaskHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetType(TaskHandle)
#define ITask_GetTimeElapsed(TaskHandle, ElapsedTime) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetTimeElapsed(TaskHandle, ElapsedTime)
#define ITask_GetName(TaskHandle, Name, MaxName) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetName(TaskHandle, Name, MaxName)
#define ITask_GetNamePtr(TaskHandle, NamePtr) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetName(TaskHandle, NamePtr)
#define ITask_HasArgument(TaskHandle, Name) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->HasArgument(TaskHandle, Name)
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
#define ITask_SetStatus(TaskHandle, Status) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->SetStatus(TaskHandle, Status)
#define ITask_SetStatusString(TaskHandle, Name, Value) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->SetStatusString(TaskHandle, Name, Value)
#define ITask_SetStatusNumber(TaskHandle, Name, Value) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->SetStatusNumber(TaskHandle, Name, Value)
#define ITask_SetStatusWithDictionary(TaskHandle, DictionaryHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->SetStatusWithDictionary(TaskHandle, DictionaryHandle)
#define ITask_SetProgress(TaskHandle, Progress) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->SetProgress(TaskHandle, Progress)

#define ITask_RunSubAction(TaskHandle, Name, UserPtr, Callback) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->RunSubAction(TaskHandle, Name, UserPtr, Callback)
#define ITask_RunSubTask(TaskHandle, Name, DictionaryHandle, UserPtr, Callback) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->RunSubTask(TaskHandle, Name, DictionaryHandle, UserPtr, Callback)

#define ITask_Start(TaskHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->Start(TaskHandle)
#define ITask_Complete(TaskHandle, DictionaryHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->Complete(TaskHandle, DictionaryHandle)
#define ITask_Cancel(TaskHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->Cancel(TaskHandle)
#define ITask_Dump(TaskHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->Dump(TaskHandle)
#define ITask_Print(TaskHandle, Format, ...) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->Print(TaskHandle, Format, ##__VA_ARGS__)
#define ITask_VPrint(TaskHandle, Depth, Format, ArgumentList) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->VPrint(TaskHandle, Depth, Format, ArgumentList)
#define ITask_VerbosePrint(TaskHandle, Format, ...) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->VerbosePrint(TaskHandle, Format, ##__VA_ARGS__)
#define ITask_ExpandString(TaskHandle, String, MaxString) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->ExpandString(TaskHandle, String, MaxString)

#define ITask_LoadFromDictionary(TaskHandle, DictionaryHandle, ItemHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->LoadFromDictionary(TaskHandle, DictionaryHandle, ItemHandle)

#define ITask_GetErrorCount(TaskHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetErrorCount(TaskHandle)
#define ITask_GetWarningCount(TaskHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetWarningCount(TaskHandle)
#define ITask_AddError(TaskHandle, Format, ...) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->AddError(TaskHandle, Format, ##__VA_ARGS__)
#define ITask_AddErrorFromMap(TaskHandle, ExitCode, DefaultExitCodeString) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->AddErrorFromMap(TaskHandle, ExitCode, DefaultExitCodeString)
#define ITask_GetError(TaskHandle, Index, Error, MaxError) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetError(TaskHandle, Index, Error, MaxError)
#define ITask_AddWarning(TaskHandle, Format, ...) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->AddWarning(TaskHandle, Format, ##__VA_ARGS__)
#define ITask_GetWarning(TaskHandle, Index, Warning, MaxWarning) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetWarning(TaskHandle, Index, Warning, MaxWarning)
#define ITask_ClearErrors(TaskHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->ClearErrors(TaskHandle)
#define ITask_ClearWarnings(TaskHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->ClearWarnings(TaskHandle)

#define ITask_SetDelayedCancel(TaskHandle, DelayedCancel) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->SetDelayedCancel(TaskHandle, DelayedCancel)
#define ITask_GetDelayedCancel(TaskHandle, DelayedCancel) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetDelayedCancel(TaskHandle, DelayedCancel)
#define ITask_GetWorkflowHandle(TaskHandle, WorkflowHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetWorkflowHandle(TaskHandle, WorkflowHandle)
#define ITask_GetDictionaryHandle(TaskHandle, DictionaryHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetDictionaryHandle(TaskHandle, DictionaryHandle)
#define ITask_GetStatusDictionaryHandle(TaskHandle, DictionaryHandle) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetStatusDictionaryHandle(TaskHandle, DictionaryHandle)
#define ITask_SetExpandStringCallback(TaskHandle, UserPtr, Callback) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->SetExpandStringCallback(TaskHandle, UserPtr, Callback)
#define ITask_GetExpandStringCallback(TaskHandle, UserPtr, Callback) \
    Class_VtblCast(TaskHandle, ITaskVtbl)->GetExpandStringCallback(TaskHandle, UserPtr, Callback)

/*********************************************************************/

#define ITask_Declare(CLASS)                                                \
    extern ITask CLASS##_INTERFACE;
#define ITask_DefineInt(TASK, CLASS)                                        \
    ITask CLASS##_INTERFACE = {                                             \
        #TASK,                                                              \
        CLASS##_Create,                                                     \
        CLASS##_AddRef,                                                     \
        CLASS##_Release                                                     \
    };
#define ITask_Define(TASK)                                                  \
    ITask_DefineInt(TASK, TASK)

/*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
