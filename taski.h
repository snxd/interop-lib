#pragma once

typedef struct ITask {
    const char *type;
    echandle (*create)(echandle handle);
    echandle (*add_ref)(echandle handle);
    int32_t (*release)(echandle *handle);
} ITask;

/*********************************************************************/

typedef bool (*ITask_ExpandStringCallback)(echandle handle, void *user_ptr, char *key, char *buffer,
                                           int32_t max_buffer);
typedef bool (*ITask_EvaluatePathCallback)(echandle handle, void *user_ptr, char *path, char *buffer,
                                           int32_t max_buffer);
typedef bool (*ITask_CompleteCallback)(echandle handle, void *user_ptr, echandle dictionary_handle);
typedef bool (*ITask_RequestCompleteCallback)(echandle handle, void *user_ptr, const uint8_t *buffer,
                                              int32_t buffer_size, int32_t error_code, int32_t error_code_ex);

/*********************************************************************/

typedef struct ITaskVtbl {
    bool (*subaction_null)(echandle handle, void *user_ptr, echandle dictionary_handle);
    bool (*subaction_complete)(echandle handle, void *user_ptr, echandle dictionary_handle);

    bool (*is_complete)(echandle handle);
    bool (*is_cancelled)(echandle handle);

    const char *(*get_type)(echandle handle);
    float64_t (*get_time_elapsed)(echandle handle);
    const char *(*get_name)(echandle handle);
    bool (*has_argument)(echandle handle, const char *name);
    bool (*get_argument_ptr)(echandle handle, const char *name, const char **value_ptr);
    bool (*get_argument_type)(echandle handle, const char *name, int32_t *type);
    bool (*get_string_argument)(echandle handle, const char *name, char *value, int32_t max_value);
    bool (*get_multistring_argument)(echandle handle, const char *name, char *value, int32_t max_value);
    bool (*get_boolean_argument)(echandle handle, const char *name, bool *value);
    bool (*get_number_argument)(echandle handle, const char *name, float64_t *value);
    bool (*set_status)(echandle handle, const char *status);
    bool (*set_status_string)(echandle handle, const char *name, const char *value);
    bool (*set_status_number)(echandle handle, const char *name, float64_t value);
    bool (*set_status_with_dictionary)(echandle handle, echandle dictionary_handle);
    bool (*set_progress)(echandle handle, float64_t progress);

    bool (*run_subaction)(echandle handle, const char *name, void *user_ptr, ITask_CompleteCallback callback);
    bool (*run_subtask)(echandle handle, const char *name, echandle dictionary_handle, void *user_ptr,
                        ITask_CompleteCallback callback);

    bool (*start)(echandle handle);
    bool (*complete)(echandle handle, echandle dictionary_handle);
    bool (*cancel)(echandle handle);
    bool (*dump)(echandle handle);
    bool (*log)(echandle handle, const char *format, ...);
    bool (*verbose_log)(echandle handle, int32_t level, const char *format, ...);
    bool (*expand_string)(echandle handle, char *string, int32_t max_string);

    bool (*load_from_dictionary)(echandle handle, echandle dictionary_handle, const char *path);

    bool (*has_error)(echandle handle, const char *error);
    bool (*has_warning)(echandle handle, const char *warning);
    int32_t (*get_error_count)(echandle handle);
    int32_t (*get_warning_count)(echandle handle);
    bool (*add_error)(echandle handle, const char *error);
    bool (*add_error_from_map)(echandle handle, int32_t exit_code, const char *default_exit_code_str);
    const char *(*get_error)(echandle handle, int32_t index);
    bool (*add_warning)(echandle handle, const char *warning);
    const char *(*get_warning)(echandle handle, int32_t index);
    bool (*clear_errors)(echandle handle);
    bool (*clear_warnings)(echandle handle);

    bool (*set_delayed_cancel)(echandle handle, bool delayed_cancel);
    bool (*get_delayed_cancel)(echandle handle);
    echandle (*get_workflow_handle)(echandle handle);
    echandle (*get_dictionary_handle)(echandle handle);
    echandle (*get_status_dictionary_handle)(echandle handle);
    bool (*set_expand_string_callback)(echandle handle, void *user_ptr, ITask_ExpandStringCallback callback);
    bool (*get_expand_string_callback)(echandle handle, void **user_ptr, ITask_ExpandStringCallback *callback);

    bool (*request_url)(echandle handle, const char *url, void *user_ptr, ITask_RequestCompleteCallback callback);

    bool (*run_subaction_next)(echandle handle, const char *name, echandle prev_complete_dictionary_handle,
                               void *user_ptr, ITask_CompleteCallback callback);
} ITaskVtbl;

/*********************************************************************/

#define ITask_RequireArgument(HND, NAME)               \
    if (!ITask_HasArgument(HND, NAME)) {               \
        ITask_Log(HND, #NAME " argument not defined"); \
        ITask_AddError(HND, "Task_Error_MissingArg");  \
        ITask_Complete(HND, NULL);                     \
        return true;                                   \
    }

#define ITask_SubAction_Null(handle, user_ptr, dictionary_handle) \
    Class_VtblCast(handle, ITaskVtbl)->subaction_null(handle, user_ptr, dictionary_handle)
#define ITask_SubAction_Complete(handle, user_ptr, dictionary_handle) \
    Class_VtblCast(handle, ITaskVtbl)->subaction_complete(handle, user_ptr, dictionary_handle)

#define ITask_IsCompleted(handle)       Class_VtblCast(handle, ITaskVtbl)->is_complete(handle)
#define ITask_IsCancelled(handle)       Class_VtblCast(handle, ITaskVtbl)->is_cancelled(handle)

#define ITask_GetType(handle)           Class_VtblCast(handle, ITaskVtbl)->get_type(handle)
#define ITask_GetTimeElapsed(handle)    Class_VtblCast(handle, ITaskVtbl)->get_time_elapsed(handle)
#define ITask_GetName(handle)           Class_VtblCast(handle, ITaskVtbl)->get_name(handle)
#define ITask_HasArgument(handle, name) Class_VtblCast(handle, ITaskVtbl)->has_argument(handle, name)
#define ITask_GetArgumentPtr(handle, name, value_ptr) \
    Class_VtblCast(handle, ITaskVtbl)->get_argument_ptr(handle, name, value_ptr)
#define ITask_GetArgumentType(handle, name, type) \
    Class_VtblCast(handle, ITaskVtbl)->get_argument_type(handle, name, type)
#define ITask_GetStringArgument(handle, name, value, max_value) \
    Class_VtblCast(handle, ITaskVtbl)->get_string_argument(handle, name, value, max_value)
#define ITask_GetMultiStringArgument(handle, name, value, max_value) \
    Class_VtblCast(handle, ITaskVtbl)->get_multistring_argument(handle, name, value, max_value)
#define ITask_GetBooleanArgument(handle, name, value) \
    Class_VtblCast(handle, ITaskVtbl)->get_boolean_argument(handle, name, value)
#define ITask_GetNumberArgument(handle, name, value) \
    Class_VtblCast(handle, ITaskVtbl)->get_number_argument(handle, name, value)
#define ITask_SetStatus(handle, status) Class_VtblCast(handle, ITaskVtbl)->set_status(handle, status)
#define ITask_SetStatusString(handle, name, value) \
    Class_VtblCast(handle, ITaskVtbl)->set_status_string(handle, name, value)
#define ITask_SetStatusNumber(handle, name, value) \
    Class_VtblCast(handle, ITaskVtbl)->set_status_number(handle, name, value)
#define ITask_SetStatusWithDictionary(handle, dictionary_handle) \
    Class_VtblCast(handle, ITaskVtbl)->set_status_with_dictionary(handle, dictionary_handle)
#define ITask_SetProgress(handle, progress) Class_VtblCast(handle, ITaskVtbl)->set_progress(handle, progress)

#define ITask_RunSubAction(handle, name, user_ptr, callback) \
    Class_VtblCast(handle, ITaskVtbl)->run_subaction(handle, name, user_ptr, callback)
#define ITask_RunSubActionNext(handle, name, prev_complete_dictionary_handle, user_ptr, callback) \
    Class_VtblCast(handle, ITaskVtbl)                                                             \
        ->run_subaction_next(handle, name, prev_complete_dictionary_handle, user_ptr, callback)
#define ITask_RunSubTask(handle, name, dictionary_handle, user_ptr, callback) \
    Class_VtblCast(handle, ITaskVtbl)->run_subtask(handle, name, dictionary_handle, user_ptr, callback)

#define ITask_Start(handle)                       Class_VtblCast(handle, ITaskVtbl)->start(handle)
#define ITask_Complete(handle, dictionary_handle) Class_VtblCast(handle, ITaskVtbl)->complete(handle, dictionary_handle)
#define ITask_Cancel(handle)                      Class_VtblCast(handle, ITaskVtbl)->cancel(handle)
#define ITask_Dump(handle)                        Class_VtblCast(handle, ITaskVtbl)->dump(handle)
#define ITask_Log(handle, format, ...)            Class_VtblCast(handle, ITaskVtbl)->log(handle, format, ##__VA_ARGS__)
#define ITask_VerboseLog(handle, level, format, ...) \
    Class_VtblCast(handle, ITaskVtbl)->verbose_log(handle, level, format, ##__VA_ARGS__)
#define ITask_ExpandString(handle, string, max_string) \
    Class_VtblCast(handle, ITaskVtbl)->expand_string(handle, string, max_string)

#define ITask_LoadFromDictionary(handle, dictionary_handle, path) \
    Class_VtblCast(handle, ITaskVtbl)->load_from_dictionary(handle, dictionary_handle, path)

#define ITask_HasError(handle, error)     Class_VtblCast(handle, ITaskVtbl)->has_error(handle, error)
#define ITask_HasWarning(handle, warning) Class_VtblCast(handle, ITaskVtbl)->has_warning(handle, warning)
#define ITask_GetErrorCount(handle)       Class_VtblCast(handle, ITaskVtbl)->get_error_count(handle)
#define ITask_GetWarningCount(handle)     Class_VtblCast(handle, ITaskVtbl)->get_warning_count(handle)
#define ITask_AddError(handle, error)     Class_VtblCast(handle, ITaskVtbl)->add_error(handle, error)
#define ITask_AddErrorFromMap(handle, exit_code, default_exit_code_str) \
    Class_VtblCast(handle, ITaskVtbl)->add_error_from_map(handle, exit_code, default_exit_code_str)
#define ITask_GetError(handle, index)     Class_VtblCast(handle, ITaskVtbl)->get_error(handle, index)
#define ITask_AddWarning(handle, warning) Class_VtblCast(handle, ITaskVtbl)->add_warning(handle, warning)
#define ITask_GetWarning(handle, index)   Class_VtblCast(handle, ITaskVtbl)->get_warning(handle, index)
#define ITask_ClearErrors(handle)         Class_VtblCast(handle, ITaskVtbl)->clear_errors(handle)
#define ITask_ClearWarnings(handle)       Class_VtblCast(handle, ITaskVtbl)->clear_warnings(handle)

#define ITask_SetDelayedCancel(handle, delayed_cancel) \
    Class_VtblCast(handle, ITaskVtbl)->set_delayed_cancel(handle, delayed_cancel)
#define ITask_GetDelayedCancel(handle)          Class_VtblCast(handle, ITaskVtbl)->get_delayed_cancel(handle)
#define ITask_GetWorkflowHandle(handle)         Class_VtblCast(handle, ITaskVtbl)->get_workflow_handle(handle)
#define ITask_GetDictionaryHandle(handle)       Class_VtblCast(handle, ITaskVtbl)->get_dictionary_handle(handle)
#define ITask_GetStatusDictionaryHandle(handle) Class_VtblCast(handle, ITaskVtbl)->get_status_dictionary_handle(handle)
#define ITask_SetExpandStringCallback(handle, user_ptr, callback) \
    Class_VtblCast(handle, ITaskVtbl)->set_expand_string_callback(handle, user_ptr, callback)
#define ITask_GetExpandStringCallback(handle, user_ptr, callback) \
    Class_VtblCast(handle, ITaskVtbl)->get_expand_string_callback(handle, user_ptr, callback)

#define ITask_RequestURL(handle, url, user_ptr, callback) \
    Class_VtblCast(handle, ITaskVtbl)->request_url(handle, url, user_ptr, callback)

/*********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#define ITask_Declare(CLASS)         extern ITask CLASS##_INTERFACE;
#define ITask_DefineInt(TASK, CLASS) ITask CLASS##_INTERFACE = {#TASK, CLASS##_Create, CLASS##_AddRef, CLASS##_Release};
#define ITask_Define(TASK)           ITask_DefineInt(TASK, TASK)

#ifdef __cplusplus
}
#endif
