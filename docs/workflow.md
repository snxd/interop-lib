## Workflow <!-- omit in toc -->

The workflow header and interface provides functions for operating on workflow instances. The workflow engine can run multiple workflows.

It is possible for one workflow to run another workflow using the _workflowRun_ task. In this instance, the two workflows have a parent/child relationship. Workflows that have no parent are considered global workflows.

**Interface**

- [Workflow\_HasTask](#workflow_hastask)
- [Workflow\_HasRemoteTask](#workflow_hasremotetask)
- [Workflow\_HasRemoteWorkflow](#workflow_hasremoteworkflow)
- [Workflow\_FindTaskByInstanceId](#workflow_findtaskbyinstanceid)
- [Workflow\_FindTaskByName](#workflow_findtaskbyname)
- [Workflow\_GetParentTaskHandle](#workflow_getparenttaskhandle)
- [Workflow\_GetParentTaskHandleByName](#workflow_getparenttaskhandlebyname)
- [Workflow\_FindTaskHandler](#workflow_findtaskhandler)
- [Workflow\_RegisterTaskHandler](#workflow_registertaskhandler)
- [Workflow\_UnregisterTaskHandler](#workflow_unregistertaskhandler)
- [Workflow\_SetStatus](#workflow_setstatus)
- [Workflow\_SetStatusString](#workflow_setstatusstring)
- [Workflow\_SetStatusNumber](#workflow_setstatusnumber)
- [Workflow\_SetStatusWithDictionary](#workflow_setstatuswithdictionary)
- [Workflow\_CanCreateTask](#workflow_cancreatetask)
- [Workflow\_CreateTask](#workflow_createtask)
- [Workflow\_CompleteCallback](#workflow_completecallback)
- [Workflow\_RunTask](#workflow_runtask)
- [Workflow\_QueueTask](#workflow_queuetask)
- [Workflow\_CancelTasks](#workflow_canceltasks)
- [Workflow\_ClearTasks](#workflow_cleartasks)
- [Workflow\_ClearTasksByHandle](#workflow_cleartasksbyhandle)
- [Workflow\_IsTaskRunning](#workflow_istaskrunning)
- [Workflow\_IsTaskQueued](#workflow_istaskqueued)
- [Workflow\_IsActivated](#workflow_isactivated)
- [Workflow\_Complete](#workflow_complete)
- [Workflow\_Reset](#workflow_reset)
- [Workflow\_AddMacro](#workflow_addmacro)
- [Workflow\_ExpandString](#workflow_expandstring)
- [Workflow\_ExpandKey](#workflow_expandkey)
- [Workflow\_LoadFile](#workflow_loadfile)
- [Workflow\_LoadBuffer](#workflow_loadbuffer)
- [Workflow\_LoadDictionary](#workflow_loaddictionary)
- [Workflow\_RegisterDefaultTasks](#workflow_registerdefaulttasks)
- [Workflow\_RegisterCustomTasks](#workflow_registercustomtasks)
- [Workflow\_UnregisterDefaultTasks](#workflow_unregisterdefaulttasks)
- [Workflow\_UnregisterCustomTasks](#workflow_unregistercustomtasks)
- [Workflow\_Log](#workflow_log)
- [Workflow\_VerboseLog](#workflow_verboselog)
- [Workflow\_IsGlobal](#workflow_isglobal)
- [Workflow\_SetVerbose](#workflow_setverbose)
- [Workflow\_IsVerbose](#workflow_isverbose)
- [Workflow\_GetRemoteInstanceId](#workflow_getremoteinstanceid)
- [Workflow\_ExpandStringCallback](#workflow_expandstringcallback)
- [Workflow\_SetExpandStringCallback](#workflow_setexpandstringcallback)
- [Workflow\_GetMacroDictionaryHandle](#workflow_getmacrodictionaryhandle)
- [Workflow\_GetDictionaryHandle](#workflow_getdictionaryhandle)
- [Workflow\_GetStatusDictionaryHandle](#workflow_getstatusdictionaryhandle)
- [Workflow\_GetCertStoreListHandle](#workflow_getcertstorelisthandle)
- [Workflow\_GetInstanceId](#workflow_getinstanceid)
- [Workflow\_AddRef](#workflow_addref)
- [Workflow\_Release](#workflow_release)
- [Workflow\_RegisterTask](#workflow_registertask)
- [Workflow\_UnregisterTask](#workflow_unregistertask)

### Workflow_HasTask

Gets whether or not the task instance is associated with the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|InstanceId|const char*|Task instance id|

Returns true if the task instance is associated with the workflow, false otherwise.

### Workflow_HasRemoteTask

Gets whether or not the remote task instance is associated with the workflow. Remote tasks are those that are run by a remote workflow engine process.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|InstanceId|const char*|Task instance id|

Returns true if the remote task instance is associated with the workflow, false otherwise.

### Workflow_HasRemoteWorkflow

Gets whether or not the remote workflow instance is associated with the workflow. Remote workflows are those that are run by a remote workflow engine process and initialated by _workflowRun_ tasks in the current workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|InstanceId|const char*|Task instance id|

Returns true if the remote workflow instance is associated with teh workflow, false otherwise.

### Workflow_FindTaskByInstanceId

Finds the task handle with the specified instance id in the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|InstanceId|const char*|Task instance id|
|TaskHandle|echandle*|Task handle|

Returns true if the task was found, false otherwise.

### Workflow_FindTaskByName

Finds the task handle with the specified name in the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Name|const char*|Task name|
|TaskHandle|echandle*|Task handle|

Returns true if the task was found, false otherwise.

### Workflow_GetParentTaskHandle

Gets the parent task handle for the specified task handle in the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|TaskHandle|echandle|Task handle|
|ParentTaskHandle|echandle*|Parent task handle|

Returns true if the task has a parent task handle, false otherwise.

### Workflow_GetParentTaskHandleByName

Gets the parent task handle with the specified name for the specified task handle in the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|TaskHandle|echandle|Task handle|
|Name|const char*|Parent task name|
|ParentTaskHandle|echandle*|Parent task handle|

Returns true if the parent task was found, false otherwise.

### Workflow_FindTaskHandler

Finds the task handler interface for the specified task type in the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Type|const char*|Task type name|
|Interface|ITask**|Task handler interface|

Returns true if found, false otherwise.

### Workflow_RegisterTaskHandler

Registers the task handler for a particular task type in the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Interface|ITask*|Task handler interface|

Returns true.

### Workflow_UnregisterTaskHandler

Unregisters the task handle for a particular task type in the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Interface|ITask*|Task handler interface|

Returns true.

### Workflow_SetStatus

Sets the "status" string for the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Status|const char*|Status string|

Returns true if successful, false otherwise.

**Notes:**

* Each workflow (and task) has a status dictionary associated with it and this function sets the "status" key of that dictionary.
* Usually the status is a localization id that the UI translate for the display language selected.

### Workflow_SetStatusString

Sets a status item in the status dictionary with a string value for the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Name|const char*|Name of the status item|
|Value|const char*|Value of the status item|

Returns true if successful, false otherwise.

```
Workflow_SetStatusString(WorkflowHandle, "specialStatus", "UI_Initializing")
```
_Status Dictionary:_
```
{
    "status": "UI_Processing",
    "specialStatus": "UI_Initializing"
}
```

### Workflow_SetStatusNumber

Sets a status item in the status dictionary with a number value for the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Name|const char*|Name of the status item|
|Value|float64|64-bit floating point integer of the status item|

Returns true if successful, false otherwise.

### Workflow_SetStatusWithDictionary

Merges and overwrites dictionary items into the status dictionary for the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Name|const char*|Name of the status item|
|DictionaryHandle|echandle|Source status dictionary handle|

Returns true.

### Workflow_CanCreateTask

Gets whether or not the workflow can create the task specified by name.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Name|const char*|Task name|

Returns true if the workflow knows about and can create the specified task, false otherwise.

### Workflow_CreateTask

Creates a task instance with the specified name in the workflow. The task name should exist in the workflow dictionary.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Name|const char*|Task name|
|DictionaryHandle|echandle|Additional task argument dictionary handle|
|ParentTaskHandle|echandle|Parent task handle or NULL|
|TaskHandle|echandle*|Handle to task that is created|

Returns true if the task is created, false otherwise.

### Workflow_CompleteCallback

Callback that is triggered when a workflow event completes.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|UserPtr|void*|User data pointer|
|DictionaryHandle|echandle|Complete info dictionary handle|

Return true.

**Notes:**

* If the event is successful, the complete info dictionary will contain "successful" boolean key set to true.

### Workflow_RunTask

Immediately runs the task specified by name in the workflow. When the task is complete, the specified complete callback is called.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Name|const char*|Task name|
|ParentTaskHandle|echandle|Parent task handle or NULL|
|UserPtr|void*|User data pointer|
|Callback|CompleteCallback|Complete callback function|

Returns true.

**Notes:**

* Using this function can cause multiple tasks to run at the same time. It is not ideal for tasks that update the UI, but can be useful for tasks that need to run immediately such as launching an executable.

### Workflow_QueueTask

Queues the task specified by name in the workflow. When the task is complete, the specified complete callback is called.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Name|const char*|Task name|
|ParentTaskHandle|echandle|Parent task handle or NULL|
|UserPtr|void*|User data pointer|
|Callback|CompleteCallback|Complete callback function|

Returns true.

**Notes:**

* The task will be run when there are no other tasks running.

### Workflow_CancelTasks

Cancels all the tasks in the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|

Returns true.

### Workflow_ClearTasks

Clears all the tasks in the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|

Returns true.

### Workflow_ClearTasksByHandle

Clears the task specified by its task handle in the workflow. The child-most task in the chain is cancelled first, and the cancellation bubbles up.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|TaskHandle|echandle|Task handle|

Returns true.

### Workflow_IsTaskRunning

Gets whether or not the task specified by name is running in the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Name|const char*|Task name|

Returns true if the task is running, false otherwise.

### Workflow_IsTaskQueued

Gets whether or not the task specified by name is queued and waiting to be run in the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Name|const char*|Task name|

Returns true if the task is queued, false otherwise.

### Workflow_IsActivated

Gets whether or not the workflow has any events that are running or ready to be run.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|

Returns true if the workflow has tasks running or ready to be run.

### Workflow_Complete

Completes the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|DictionaryHandle|echandle|Complete info dictionary handle|

Returns true.

### Workflow_Reset

Resets the workflow instance.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|

Returns true.

### Workflow_AddMacro

Adds a macro key and value to the workflow's macros list.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Key|const char*|Macro name|
|Value|const char*|Macro value|

Returns true.

### Workflow_ExpandString

Expands a string in the context of the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|String|char*|Expansion buffer|
|MaxString|int32_t|Maximum length of expansion buffer|

Returns true.

**Notes:**

*  Expands strings using the workflow's macros specified in the macro dictionary.

### Workflow_ExpandKey

Expands a macro key and value in the context of the workflow. The _ExpandKey_ function may call the _Workflow_ExpandStringCallback_ in order to evaluate certain keys in the workflow.

|Name|Type|Description|
|-|-|-|
|UserPtr|void*|User data pointer|
|Key|const char*|Macro key|
|Value|const char*|Macro key value|
|Buffer|char*|Expansion buffer|
|MaxBuffer|int32_t|Maximum length of expansion buffer|

Returns true.

### Workflow_LoadFile

Loads a workflow JSON file from disk.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Path|const char*|Path to the JSON workflow|

Returns true if successful, false otherwise.

### Workflow_LoadBuffer

Loads a workflow JSON from a memory buffer.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Buffer|const char*|JSON string buffer|
|BufferSize|int32_t|JSON string buffer length|
|Merge|int32_t|Merge boolean|

Returns true if successful, false otherwise.

**Notes:**

* When merge is enabled, it will merge the specified JSON dictionary with the current workflow's dictionary.

### Workflow_LoadDictionary

Loads a workflow from a dictionary.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|DictionaryHandle|echandle|Tasks dictionary handle|
|Merge|int32_t|Merge boolean|

**Notes:**

* When merge is enabled, it will merge the specified dictionary with the current workflow's dictionary.

### Workflow_RegisterDefaultTasks

Registers the default task handlers for the workflow engine.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|

Returns true.

### Workflow_RegisterCustomTasks

Triggers the registration of custom tasks for the workflow. The _Workflow.RegisterTaskHandlers_ notification will be fired, in which case custom interop can observer it and call _IWorkflow_RegisterTaskHandler_ to register their customer tasks.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|

Returns true.

### Workflow_UnregisterDefaultTasks

Unregisters the default task handlers for the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|

Returns true.

### Workflow_UnregisterCustomTasks

Triggers the unregistration of custom tasks for the workflow. The _Workflow.UnregisterTaskHandlers_ notification will be fired, in which case custom interop can observer it and call _IWorkflow_UnregisterTaskHandler_ to unregister their custom task types.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|

Returns true.


### Workflow_Log

Prints a message for the workflow to the debug log.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Format|const char*|Print format specifier string|
|...||Arguments for print format specifier string|

Returns true.

```
Workflow_Log(WorkflowHandle, "Hello %s", "world");
```

### Workflow_VerboseLog

Prints a message for the workflow to the debug log when verbose is enabled.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Format|const char*|Print format specifier string|
|...||Arguments for print format specifier string|

Returns true.

**Notes:**

* To turn on verbose messaging you can set call _Workflow_SetVerbose_.

### Workflow_IsGlobal

Gets whether or not the workflow is global. A workflow is global if it has no parent workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|

Returns true if the workflow is global, false otherwise.

### Workflow_SetVerbose

Enables or disables verbose logging for the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Verbose|int32_t|Enable boolean value|

Returns true.

### Workflow_IsVerbose

Gets whether or not verbose logging is enabled for the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|

Returns bool.

### Workflow_GetRemoteInstanceId

Gets the remote instance id for the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|

Returns string.

### Workflow_ExpandStringCallback

Callback used for expanding keys on the workflow with _Workflow_ExpandKey_ and _Workflow_ExpandString_.

|Name|Type|Description|
|WorkflowHandle|echandle|Workflow handle|
|UserPtr|void*|User data pointer|
|Key|const char*|Key to expand|
|Buffer|char*|Expansion buffer|
|MaxBuffer|int32_t|Maximum length of expansion buffer|

Return true if the key was expanded, false otherwise.

### Workflow_SetExpandStringCallback

Sets the string expansion callback for the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|UserPtr|void*|User data pointer|
|Callback|ExpandStringCallback|String expansion callback|

Returns true.

### Workflow_GetMacroDictionaryHandle

Gets the dictionary handle containing macros for the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|

Returns a dictionary handle.

### Workflow_GetDictionaryHandle

Gets the dictionary handle for the workflow. The workflow dictionary contains the tasks and their arguments for the entire workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|

Returns a dictionary handle.

### Workflow_GetStatusDictionaryHandle

Gets the status dictionary handle for the workflow. The status dictionary contains status items for the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|

Returns a dictionary handle.

### Workflow_GetCertStoreListHandle

Gets the list of certificate stores for the workflow. The workflow's certificate store list is loaded using the _certStoreLoad_ task.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|

Returns a dictionary handle.

### Workflow_GetInstanceId

Gets the instance id for the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|

Returns a string.

### Workflow_AddRef

Increments reference count for the workflow.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|

Returns the workflow handle.

### Workflow_Release

Decrements reference count for the workflow. When the count reaches zero, the workflow is deleted from memory.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle*|Workflow handle pointer|

Returns true.

### Workflow_RegisterTask

Macro for registering task interface. Used in conjunction with ITask_Define.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Task|const char*|Name of task class|

Returns true.

### Workflow_UnregisterTask

Macro for unregistering task interface. Used in conjunction with ITask_Define.

|Name|Type|Description|
|-|-|-|
|WorkflowHandle|echandle|Workflow handle|
|Task|const char*|Name of task class|

Returns true.
