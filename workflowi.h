#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************/

typedef bool (*IWorkflow_ExpandStringCallback)(void *user_ptr, const char *key, const char *value, char *buffer,
                                               int32_t max_buffer);
typedef bool (*IWorkflow_CompleteCallback)(echandle handle, void *user_ptr, echandle dictionary_handle);

/*********************************************************************/

typedef struct IWorkflowVtbl {
    bool (*find_task_by_instance_id)(echandle handle, const char *instance_id, echandle *task_handle);
    bool (*find_task_by_name)(echandle handle, const char *name, echandle *task_handle);
    echandle (*get_parent_task_handle)(echandle handle, echandle task_handle);

    bool (*find_task_handler)(echandle handle, const char *type, ITask **task_interface);
    bool (*register_task_handler)(echandle handle, ITask *task_interface);
    bool (*unregister_task_handler)(echandle handle, ITask *task_interface);

    bool (*can_create_task)(echandle handle, const char *name);
    bool (*create_task)(echandle handle, const char *name, echandle dictionary_handle, echandle parent_task_handle,
                        echandle *task_handle);
    bool (*run_task)(echandle handle, const char *name, echandle parent_task_handle, void *user_ptr,
                     IWorkflow_CompleteCallback callback);
    bool (*queue_task)(echandle handle, const char *name, echandle parent_task_handle, void *user_ptr,
                       IWorkflow_CompleteCallback callback);
    bool (*cancel_tasks)(echandle handle);
    bool (*clear_tasks)(echandle handle);
    bool (*is_task_running)(echandle handle, const char *name);
    bool (*is_task_queued)(echandle handle, const char *name);
    bool (*is_activated)(echandle handle);
    bool (*complete)(echandle handle, echandle dictionary_handle);
    bool (*reset)(echandle handle);

    bool (*add_macro)(echandle handle, const char *key, const char *value);
    bool (*expand_string)(echandle handle, char *string, int32_t max_string);
    bool (*load_file)(echandle handle, const char *path);
    bool (*load_buffer)(echandle handle, char *buffer, int32_t buffer_size, bool merge);
    bool (*load_dictionary)(echandle handle, echandle dictionary_handle, bool merge);
    bool (*register_default_tasks)(echandle handle);
    bool (*unregister_default_tasks)(echandle handle);

    bool (*log)(echandle handle, const char *format, ...);

    bool (*set_expand_string_callback)(echandle handle, void *user_ptr, IWorkflow_ExpandStringCallback callback);
    bool (*get_expand_string_callback)(echandle handle, void **user_ptr, IWorkflow_ExpandStringCallback *callback);
    echandle (*get_macro_dictionary_handle)(echandle handle);
    echandle (*get_dictionary_handle)(echandle handle);

    bool (*is_global)(echandle handle);

    bool (*create_task_with_macros)(echandle handle, const char *name, echandle dictionary_handle,
                                    echandle macro_dictionary_handle, echandle parent_task_handle,
                                    echandle *task_handle);
    bool (*run_task_with_macros)(echandle handle, const char *name, echandle macro_dictionary_handle,
                                 echandle parent_task_handle, void *user_ptr, IWorkflow_CompleteCallback callback);
    bool (*queue_task_with_macros)(echandle handle, const char *name, echandle macro_dictionary_handle,
                                   echandle parent_task_handle, void *user_ptr, IWorkflow_CompleteCallback callback);
} IWorkflowVtbl;

/*********************************************************************/

#define IWorkflow_FindTaskByInstanceId(handle, instance_id, task_handle) \
    Class_VtblCast(handle, IWorkflowVtbl)->find_task_by_instance_id(handle, instance_id, task_handle)
#define IWorkflow_FindTaskByName(handle, name, task_handle) \
    Class_VtblCast(handle, IWorkflowVtbl)->find_task_by_name(handle, name, task_handle)
#define IWorkflow_GetParentTaskHandle(handle, task_handle) \
    Class_VtblCast(handle, IWorkflowVtbl)->get_parent_task_handle(handle, task_handle)

#define IWorkflow_FindTaskHandler(handle, type, task_interface) \
    Class_VtblCast(handle, IWorkflowVtbl)->find_task_handler(handle, type, task_interface)
#define IWorkflow_RegisterTaskHandler(handle, task_interface) \
    Class_VtblCast(handle, IWorkflowVtbl)->register_task_handler(handle, task_interface)
#define IWorkflow_UnregisterTaskHandler(handle, task_interface) \
    Class_VtblCast(handle, IWorkflowVtbl)->unregister_task_handler(handle, task_interface)

#define IWorkflow_CanCreateTask(handle, name) Class_VtblCast(handle, IWorkflowVtbl)->can_create_task(handle, name)
#define IWorkflow_CreateTask(handle, name, dictionary_handle, parent_task_handle, sub_task_handle) \
    Class_VtblCast(handle, IWorkflowVtbl)                                                          \
        ->create_task(handle, name, dictionary_handle, parent_task_handle, sub_task_handle)
#define IWorkflow_CreateTaskWithMacros(handle, name, dictionary_handle, macro_dictionary_handle, parent_task_handle, \
                                       sub_task_handle)                                                              \
    Class_VtblCast(handle, IWorkflowVtbl)                                                                            \
        ->create_task_with_macros(handle, name, dictionary_handle, macro_dictionary_handle, parent_task_handle,      \
                                  sub_task_handle)
#define IWorkflow_RunTask(handle, name, parent_task_handle, user_ptr, callback) \
    Class_VtblCast(handle, IWorkflowVtbl)->run_task(handle, name, parent_task_handle, user_ptr, callback)
#define IWorkflow_RunTaskWithMacros(handle, name, macro_dictionary_handle, parent_task_handle, user_ptr, callback) \
    Class_VtblCast(handle, IWorkflowVtbl)                                                                          \
        ->run_task_with_macros(handle, name, macro_dictionary_handle, parent_task_handle, user_ptr, callback)
#define IWorkflow_QueueTask(handle, name, parent_task_handle, user_ptr, callback) \
    Class_VtblCast(handle, IWorkflowVtbl)->queue_task(handle, name, parent_task_handle, user_ptr, callback)
#define IWorkflow_QueueTaskWithMacros(handle, name, macro_dictionary_handle, parent_task_handle, user_ptr, callback) \
    Class_VtblCast(handle, IWorkflowVtbl)                                                                            \
        ->queue_task_with_macros(handle, name, macro_dictionary_handle, parent_task_handle, user_ptr, callback)
#define IWorkflow_CancelTasks(handle)         Class_VtblCast(handle, IWorkflowVtbl)->cancel_tasks(handle)
#define IWorkflow_ClearTasks(handle)          Class_VtblCast(handle, IWorkflowVtbl)->clear_tasks(handle)
#define IWorkflow_IsTaskRunning(handle, name) Class_VtblCast(handle, IWorkflowVtbl)->is_task_running(handle, name)
#define IWorkflow_IsTaskQueued(handle, name)  Class_VtblCast(handle, IWorkflowVtbl)->is_task_queued(handle, name)
#define IWorkflow_IsActivated(handle)         Class_VtblCast(handle, IWorkflowVtbl)->is_activated(handle)
#define IWorkflow_Complete(handle, dictionary_handle) \
    Class_VtblCast(handle, IWorkflowVtbl)->complete(handle, dictionary_handle)
#define IWorkflow_Reset(handle)                Class_VtblCast(handle, IWorkflowVtbl)->reset(handle)

#define IWorkflow_AddMacro(handle, key, value) Class_VtblCast(handle, IWorkflowVtbl)->add_macro(handle, key, value)
#define IWorkflow_ExpandString(handle, string, max_string) \
    Class_VtblCast(handle, IWorkflowVtbl)->expand_string(handle, string, max_string)
#define IWorkflow_LoadFile(handle, path) Class_VtblCast(handle, IWorkflowVtbl)->load_file(handle, path)
#define IWorkflow_LoadBuffer(handle, buffer, buffer_size, merge) \
    Class_VtblCast(handle, IWorkflowVtbl)->load_buffer(handle, buffer, buffer_size, merge)
#define IWorkflow_LoadDictionary(handle, dictionary, merge) \
    Class_VtblCast(handle, IWorkflowVtbl)->load_dictionary(handle, dictionary, merge)
#define IWorkflow_RegisterDefaultTasks(handle)   Class_VtblCast(handle, IWorkflowVtbl)->register_default_tasks(handle)
#define IWorkflow_UnregisterDefaultTasks(handle) Class_VtblCast(handle, IWorkflowVtbl)->unregister_default_tasks(handle)
#define IWorkflow_Log(handle, format, ...)       Class_VtblCast(handle, IWorkflowVtbl)->log(handle, format, ##__VA_ARGS__)

#define IWorkflow_IsGlobal(handle)               Class_VtblCast(handle, IWorkflowVtbl)->is_global(handle)
#define IWorkflow_SetExpandStringCallback(handle, user_ptr, callback) \
    Class_VtblCast(handle, IWorkflowVtbl)->set_expand_string_callback(handle, user_ptr, callback)
#define IWorkflow_GetExpandStringCallback(handle, user_ptr, callback) \
    Class_VtblCast(handle, IWorkflowVtbl)->get_expand_string_callback(handle, user_ptr, callback)
#define IWorkflow_GetMacroDictionaryHandle(handle) \
    Class_VtblCast(handle, IWorkflowVtbl)->get_macro_dictionary_handle(handle)
#define IWorkflow_GetDictionaryHandle(handle)  Class_VtblCast(handle, IWorkflowVtbl)->get_dictionary_handle(handle)

#define IWorkflow_RegisterTask(handle, TASK)   IWorkflow_RegisterTaskHandler(handle, &TASK##_INTERFACE)
#define IWorkflow_UnregisterTask(handle, TASK) IWorkflow_UnregisterTaskHandler(handle, &TASK##_INTERFACE)

/*********************************************************************/

#ifdef __cplusplus
}
#endif
