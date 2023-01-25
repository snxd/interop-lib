#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************/

typedef bool (*IWorkflow_ExpandStringCallback)(void *UserPtr, const char *Key, const char *Value, char *Buffer,
                                               int32_t MaxBuffer);
typedef bool (*IWorkflow_CompleteCallback)(echandle WorkflowHandle, void *UserPtr, echandle DictionaryHandle);

/*********************************************************************/

typedef struct IWorkflowVtbl {
    bool (*FindTaskByInstanceId)(echandle WorkflowHandle, const char *InstanceId, echandle *TaskHandle);
    bool (*FindTaskByName)(echandle WorkflowHandle, const char *Name, echandle *TaskHandle);
    bool (*GetParentTaskHandle)(echandle WorkflowHandle, echandle TaskHandle, echandle *ParentTaskHandle);

    bool (*FindTaskHandler)(echandle WorkflowHandle, char *Type, ITask **Interface);
    bool (*RegisterTaskHandler)(echandle WorkflowHandle, ITask *Interface);
    bool (*UnregisterTaskHandler)(echandle WorkflowHandle, ITask *Interface);

    bool (*CanCreateTask)(echandle WorkflowHandle, const char *Name);
    bool (*CreateTask)(echandle WorkflowHandle, const char *Name, echandle DictionaryHandle, echandle ParentTaskHandle,
                       echandle *TaskHandle);
    bool (*RunTask)(echandle WorkflowHandle, const char *Name, echandle ParentTaskHandle, void *UserPtr,
                    IWorkflow_CompleteCallback Callback);
    bool (*QueueTask)(echandle WorkflowHandle, const char *Name, echandle ParentTaskHandle, void *UserPtr,
                      IWorkflow_CompleteCallback Callback);
    bool (*CancelTasks)(echandle WorkflowHandle);
    bool (*ClearTasks)(echandle WorkflowHandle);
    bool (*IsTaskRunning)(echandle WorkflowHandle, const char *Name);
    bool (*IsTaskQueued)(echandle WorkflowHandle, const char *Name);
    bool (*IsActivated)(echandle WorkflowHandle);
    bool (*Complete)(echandle WorkflowHandle, echandle DictionaryHandle);
    bool (*Reset)(echandle WorkflowHandle);

    bool (*AddMacro)(echandle WorkflowHandle, const char *Key, const char *Value);
    bool (*ExpandString)(echandle WorkflowHandle, char *String, int32_t MaxString);
    bool (*LoadFile)(echandle WorkflowHandle, const char *Path);
    bool (*LoadBuffer)(echandle WorkflowHandle, char *Buffer, int32_t BufferSize, int32_t Merge);
    bool (*LoadDictionary)(echandle WorkflowHandle, echandle DictionaryHandle, int32_t Merge);
    bool (*RegisterDefaultTasks)(echandle WorkflowHandle);
    bool (*UnregisterDefaultTasks)(echandle WorkflowHandle);
    bool (*Log)(echandle WorkflowHandle, const char *Format, ...);

    bool (*SetExpandStringCallback)(echandle WorkflowHandle, void *UserPtr, IWorkflow_ExpandStringCallback Callback);
    bool (*GetExpandStringCallback)(echandle WorkflowHandle, void **UserPtr, IWorkflow_ExpandStringCallback *Callback);
    bool (*GetMacroDictionaryHandle)(echandle WorkflowHandle, echandle *MacroDictionaryHandle);
    bool (*GetDictionaryHandle)(echandle WorkflowHandle, echandle *DictionaryHandle);

    bool (*IsGlobal)(echandle WorkflowHandle);

    bool (*CreateTaskWithMacros)(echandle WorkflowHandle, const char *Name, echandle DictionaryHandle,
                                 echandle MacroDictionaryHandle, echandle ParentTaskHandle, echandle *TaskHandle);
    bool (*RunTaskWithMacros)(echandle WorkflowHandle, const char *Name, echandle MacroDictionaryHandle,
                              echandle ParentTaskHandle, void *UserPtr, IWorkflow_CompleteCallback Callback);
    bool (*QueueTaskWithMacros)(echandle WorkflowHandle, const char *Name, echandle MacroDictionaryHandle,
                                echandle ParentTaskHandle, void *UserPtr, IWorkflow_CompleteCallback Callback);
} IWorkflowVtbl;

/*********************************************************************/

#define IWorkflow_FindTaskByInstanceId(WorkflowHandle, InstanceId, TaskHandle) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->FindTaskByInstanceId(WorkflowHandle, InstanceId, TaskHandle)
#define IWorkflow_FindTaskByName(WorkflowHandle, Name, TaskHandle) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->FindTaskByName(WorkflowHandle, Name, TaskHandle)
#define IWorkflow_GetParentTaskHandle(WorkflowHandle, TaskHandle, ParentTaskHandle) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->GetParentTaskHandle(WorkflowHandle, TaskHandle, ParentTaskHandle)

#define IWorkflow_FindTaskHandler(WorkflowHandle, Type, Interface) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->FindTaskHandler(WorkflowHandle, Type, Interface)
#define IWorkflow_RegisterTaskHandler(WorkflowHandle, Interface) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->RegisterTaskHandler(WorkflowHandle, Interface)
#define IWorkflow_UnregisterTaskHandler(WorkflowHandle, Interface) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->UnregisterTaskHandler(WorkflowHandle, Interface)

#define IWorkflow_CanCreateTask(WorkflowHandle, Name) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->CanCreateTask(WorkflowHandle, Name)
#define IWorkflow_CreateTask(WorkflowHandle, Name, DictionaryHandle, ParentTaskHandle, SubTaskHandle) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->CreateTask(WorkflowHandle, Name, DictionaryHandle, ParentTaskHandle)
#define IWorkflow_CreateTaskWithMacros(WorkflowHandle, Name, DictionaryHandle, MacroDictionaryHandle, \
                                       ParentTaskHandle, SubTaskHandle)                               \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)                                                     \
        ->CreateTaskWithMacros(WorkflowHandle, Name, DictionaryHandle, MacroDictionaryHandle, ParentTaskHandle)
#define IWorkflow_RunTask(WorkflowHandle, Name, ParentTaskHandle, UserPtr, Callback) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->RunTask(WorkflowHandle, Name, ParentTaskHandle, UserPtr, Callback)
#define IWorkflow_RunTaskWithMacros(WorkflowHandle, Name, MacroDictionaryHandle, ParentTaskHandle, UserPtr, Callback) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)                                                                     \
        ->RunTaskWithMacros(WorkflowHandle, Name, MacroDictionaryHandle, ParentTaskHandle, UserPtr, Callback)
#define IWorkflow_QueueTask(WorkflowHandle, Name, ParentTaskHandle, UserPtr, Callback) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->QueueTask(WorkflowHandle, Name, ParentTaskHandle, UserPtr, Callback)
#define IWorkflow_QueueTaskWithMacros(WorkflowHandle, Name, MacroDictionaryHandle, ParentTaskHandle, UserPtr, \
                                      Callback)                                                               \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)                                                             \
        ->QueueTaskWithMacros(WorkflowHandle, Name, MacroDictionaryHandle, ParentTaskHandle, UserPtr, Callback)
#define IWorkflow_CancelTasks(WorkflowHandle) Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->CancelTasks(WorkflowHandle)
#define IWorkflow_ClearTasks(WorkflowHandle)  Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->ClearTasks(WorkflowHandle)
#define IWorkflow_IsTaskRunning(WorkflowHandle, Name) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->IsTaskRunning(WorkflowHandle, Name)
#define IWorkflow_IsTaskQueued(WorkflowHandle, Name) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->IsTaskQueued(WorkflowHandle, Name)
#define IWorkflow_IsActivated(WorkflowHandle, Name) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->IsActivated(WorkflowHandle)
#define IWorkflow_Complete(WorkflowHandle, DictionaryHandle) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->Complete(WorkflowHandle, DictionaryHandle)
#define IWorkflow_Reset(WorkflowHandle) Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->Reset(WorkflowHandle)

#define IWorkflow_AddMacro(WorkflowHandle, Key, Value) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->AddMacro(WorkflowHandle, Key, Value)
#define IWorkflow_ExpandString(WorkflowHandle, String, MaxString) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->ExpandString(WorkflowHandle, String, MaxString)
#define IWorkflow_LoadFile(WorkflowHandle, Path) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->LoadFile(WorkflowHandle, Path)
#define IWorkflow_LoadBuffer(WorkflowHandle, Buffer, BufferSize, Merge) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->LoadBuffer(WorkflowHandle, Buffer, BufferSize, Merge)
#define IWorkflow_RegisterDefaultTasks(WorkflowHandle) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->RegisterDefaultTasks(WorkflowHandle)
#define IWorkflow_UnregisterDefaultTasks(WorkflowHandle) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->UnregisterDefaultTasks(WorkflowHandle)
#define IWorkflow_Log(WorkflowHandle, Format, ...) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->Log(WorkflowHandle, Format, ##__VA_ARGS__)

#define IWorkflow_IsGlobal(WorkflowHandle) Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->IsGlobal(WorkflowHandle)
#define IWorkflow_SetExpandStringCallback(WorkflowHandle, UserPtr, Callback) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->SetExpandStringCallback(WorkflowHandle, UserPtr, Callback)
#define IWorkflow_GetExpandStringCallback(WorkflowHandle, UserPtr, Callback) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->GetExpandStringCallback(WorkflowHandle, UserPtr, Callback)
#define IWorkflow_GetMacroDictionaryHandle(WorkflowHandle, MacroDictionaryHandle) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->GetMacroDictionaryHandle(WorkflowHandle, MacroDictionaryHandle)
#define IWorkflow_GetDictionaryHandle(WorkflowHandle, DictionaryHandle) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->GetDictionaryHandle(WorkflowHandle, DictionaryHandle)

#define IWorkflow_RegisterTask(WorkflowHandle, TASK) IWorkflow_RegisterTaskHandler(WorkflowHandle, &TASK##_INTERFACE)
#define IWorkflow_UnregisterTask(WorkflowHandle, TASK) \
    IWorkflow_UnregisterTaskHandler(WorkflowHandle, &TASK##_INTERFACE)

/*********************************************************************/

#ifdef __cplusplus
}
#endif
