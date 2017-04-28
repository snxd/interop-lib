#ifndef _WORKFLOW_INTERFACE_H_
#define _WORKFLOW_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************/

typedef int32 (*IWorkflow_ExpandStringCallback)(void *UserPtr, char *Key, char *Buffer, int32 MaxBuffer);
typedef int32 (*IWorkflow_CompleteCallback)(echandle WorkflowHandle, void *UserPtr, echandle DictionaryHandle);

/*********************************************************************/

typedef struct IWorkflowVtbl {
    int32 (*FindTaskByInstanceId)(echandle WorkflowHandle, char *InstanceId, echandle *TaskHandle);
    int32 (*FindTaskByName)(echandle WorkflowHandle, char *Name, echandle *TaskHandle);
    int32 (*GetParentTaskHandle)(echandle WorkflowHandle, echandle TaskHandle, echandle *ParentTaskHandle);

    int32 (*FindTaskHandler)(echandle WorkflowHandle, char *Type, ITask **Interface);
    int32 (*RegisterTaskHandler)(echandle WorkflowHandle, ITask *Interface);
    int32 (*UnregisterTaskHandler)(echandle WorkflowHandle, ITask *Interface);

    int32 (*CanCreateTask)(echandle WorkflowHandle, char *Name);
    int32 (*CreateTask)(echandle WorkflowHandle, char *Name, echandle DictionaryHandle, echandle ParentTaskHandle, echandle *TaskHandle);
    int32 (*RunTask)(echandle WorkflowHandle, char *Name, echandle ParentTaskHandle, void *UserPtr, IWorkflow_CompleteCallback Callback);
    int32 (*QueueTask)(echandle WorkflowHandle, char *Name, echandle ParentTaskHandle, void *UserPtr, IWorkflow_CompleteCallback Callback);
    int32 (*CancelTasks)(echandle WorkflowHandle);
    int32 (*ClearTasks)(echandle WorkflowHandle);
    int32 (*IsTaskRunning)(echandle WorkflowHandle, char *Name);
    int32 (*IsTaskQueued)(echandle WorkflowHandle, char *Name);
    int32 (*IsActivated)(echandle WorkflowHandle);
    int32 (*Complete)(echandle WorkflowHandle, echandle DictionaryHandle);
    int32 (*Reset)(echandle WorkflowHandle);

    int32 (*AddMacro)(echandle WorkflowHandle, char *Key, char *Value);
    int32 (*ExpandString)(echandle WorkflowHandle, char *String, int32 MaxString);
    int32 (*LoadFile)(echandle WorkflowHandle, char *Path);
    int32 (*LoadBuffer)(echandle WorkflowHandle, char *Buffer, int32 BufferSize, int32 Merge);
    int32 (*LoadDictionary)(echandle WorkflowHandle, echandle DictionaryHandle, int32 Merge);
    int32 (*RegisterDefaultTasks)(echandle WorkflowHandle);
    int32 (*UnregisterDefaultTasks)(echandle WorkflowHandle);
    int32 (*Print)(echandle WorkflowHandle, char *Format, ...);

    int32 (*SetExpandStringCallback)(echandle WorkflowHandle, void *UserPtr, IWorkflow_ExpandStringCallback Callback);
    int32 (*GetExpandStringCallback)(echandle WorkflowHandle, void **UserPtr, IWorkflow_ExpandStringCallback *Callback);
    int32 (*GetMacroDictionaryHandle)(echandle WorkflowHandle, echandle *MacroDictionaryHandle);
    int32 (*GetDictionaryHandle)(echandle WorkflowHandle, echandle *DictionaryHandle);
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
#define IWorkflow_RunTask(WorkflowHandle, Name, ParentTaskHandle, UserPtr, Callback) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->RunTask(WorkflowHandle, Name, ParentTaskHandle, UserPtr, Callback)
#define IWorkflow_QueueTask(WorkflowHandle, Name, ParentTaskHandle, UserPtr, Callback) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->QueueTask(WorkflowHandle, Name, ParentTaskHandle, UserPtr, Callback)
#define IWorkflow_CancelTasks(WorkflowHandle) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->CancelTasks(WorkflowHandle)
#define IWorkflow_ClearTasks(WorkflowHandle) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->ClearTasks(WorkflowHandle)
#define IWorkflow_IsTaskRunning(WorkflowHandle, Name) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->IsTaskRunning(WorkflowHandle, Name)
#define IWorkflow_IsTaskQueued(WorkflowHandle, Name) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->IsTaskQueued(WorkflowHandle, Name)
#define IWorkflow_IsActivated(WorkflowHandle, Name) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->IsActivated(WorkflowHandle)
#define IWorkflow_Complete(WorkflowHandle, DictionaryHandle) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->Complete(WorkflowHandle, DictionaryHandle)
#define IWorkflow_Reset(WorkflowHandle) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->Reset(WorkflowHandle)

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
#define IWorkflow_Print(WorkflowHandle, Format, ...) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->Print(WorkflowHandle, Format, ##__VA_ARGS__)

#define IWorkflow_SetExpandStringCallback(WorkflowHandle, UserPtr, Callback) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->SetExpandStringCallback(WorkflowHandle, UserPtr, Callback)
#define IWorkflow_GetExpandStringCallback(WorkflowHandle, UserPtr, Callback) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->GetExpandStringCallback(WorkflowHandle, UserPtr, Callback)
#define IWorkflow_GetMacroDictionaryHandle(WorkflowHandle, MacroDictionaryHandle) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->GetMacroDictionaryHandle(WorkflowHandle, MacroDictionaryHandle)
#define IWorkflow_GetDictionaryHandle(WorkflowHandle, DictionaryHandle) \
    Class_VtblCast(WorkflowHandle, IWorkflowVtbl)->GetDictionaryHandle(WorkflowHandle, DictionaryHandle)

#define IWorkflow_RegisterTask(WorkflowHandle, TASK) \
    IWorkflow_RegisterTaskHandler(WorkflowHandle, &TASK##_INTERFACE)
#define IWorkflow_UnregisterTask(WorkflowHandle, TASK) \
    IWorkflow_UnregisterTaskHandler(WorkflowHandle, &TASK##_INTERFACE)

/*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
