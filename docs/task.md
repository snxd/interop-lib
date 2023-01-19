## Task <!-- omit in toc -->

Tasks perform a specific action depending on the task type. These functions and the associated task interface `ITask` are used to set and retrieve information for a particular task instance.

- [Task\_RequireArgument](#task_requireargument)
- [Task\_SubAction\_Null](#task_subaction_null)
- [Task\_SubAction\_Complete](#task_subaction_complete)
- [Task\_IsCompleted](#task_iscompleted)
- [Task\_IsCancelled](#task_iscancelled)
- [Task\_GetType](#task_gettype)
- [Task\_GetTimeElapsed](#task_gettimeelapsed)
- [Task\_SetName](#task_setname)
- [Task\_GetName](#task_getname)
- [Task\_GetNamePtr](#task_getnameptr)
- [Task\_HasArgument](#task_hasargument)
- [Task\_GetArgumentPtr](#task_getargumentptr)
- [Task\_GetArgumentType](#task_getargumenttype)
- [Task\_GetStringArgument](#task_getstringargument)
- [Task\_GetMultiStringArgument](#task_getmultistringargument)
- [Task\_GetBooleanArgument](#task_getbooleanargument)
- [Task\_GetNumberArgument](#task_getnumberargument)
- [Task\_GetDictionaryArgument](#task_getdictionaryargument)
- [Task\_GetCertStoreListArgument](#task_getcertstorelistargument)
- [Task\_SetStatus](#task_setstatus)
- [Task\_SetStatusString](#task_setstatusstring)
- [Task\_SetStatusNumber](#task_setstatusnumber)
- [Task\_SetStatusWithDictionary](#task_setstatuswithdictionary)
- [Task\_SetProgress](#task_setprogress)
- [Task\_SetPrintIdentifier](#task_setprintidentifier)
- [Task\_CompleteCallback](#task_completecallback)
- [Task\_RunSubAction](#task_runsubaction)
- [Task\_RunSubTask](#task_runsubtask)
- [Task\_Start](#task_start)
- [Task\_Complete](#task_complete)
- [Task\_Cancel](#task_cancel)
- [Task\_Dump](#task_dump)
- [Task\_Print](#task_print)
- [Task\_VPrint](#task_vprint)
- [Task\_VerbosePrint](#task_verboseprint)
- [Task\_ExpandString](#task_expandstring)
- [Task\_ExpandKey](#task_expandkey)
- [Task\_ExpandDictionary](#task_expanddictionary)
- [EVALUATEPATH\_OBJECT](#evaluatepath_object)
- [Task\_EvaluatePathToObject](#task_evaluatepathtoobject)
- [Task\_RequestCompleteCallback](#task_requestcompletecallback)
- [Task\_RequestURL](#task_requesturl)
- [Task\_AuthenticateCallback](#task_authenticatecallback)
- [Task\_DecodeJSON](#task_decodejson)
- [Task\_LoadFromDictionary](#task_loadfromdictionary)
- [Task\_HasError](#task_haserror)
- [Task\_HasWarning](#task_haswarning)
- [Task\_GetErrorCount](#task_geterrorcount)
- [Task\_GetWarningCount](#task_getwarningcount)
- [Task\_AddError](#task_adderror)
- [Task\_AddErrorFromMap](#task_adderrorfrommap)
- [Task\_AddErrorFromDictionary](#task_adderrorfromdictionary)
- [Task\_GetError](#task_geterror)
- [Task\_GetErrorPtr](#task_geterrorptr)
- [Task\_AddWarning](#task_addwarning)
- [Task\_AddWarningFromDictionary](#task_addwarningfromdictionary)
- [Task\_GetWarning](#task_getwarning)
- [Task\_GetWarningPtr](#task_getwarningptr)
- [Task\_ClearErrors](#task_clearerrors)
- [Task\_ClearWarnings](#task_clearwarnings)
- [Task\_SetVerbose](#task_setverbose)
- [Task\_GetVerbose](#task_getverbose)
- [Task\_SetDelayedCancel](#task_setdelayedcancel)
- [Task\_GetDelayedCancel](#task_getdelayedcancel)
- [Task\_GetWorkflowHandle](#task_getworkflowhandle)
- [Task\_GetDictionaryHandle](#task_getdictionaryhandle)
- [Task\_GetStatusDictionaryHandle](#task_getstatusdictionaryhandle)
- [Task\_GetCertStoreListHandle](#task_getcertstorelisthandle)
- [Task\_SetDefaultCertStore](#task_setdefaultcertstore)
- [Task\_GetDefaultCertStore](#task_getdefaultcertstore)
- [Task\_ExpandStringCallback](#task_expandstringcallback)
- [Task\_SetExpandStringCallback](#task_setexpandstringcallback)
- [Task\_GetExpandStringCallback](#task_getexpandstringcallback)
- [Task\_SetAuthenticateCallback](#task_setauthenticatecallback)
- [Task\_GetAuthenticateCallback](#task_getauthenticatecallback)
- [Task\_GetInstanceId](#task_getinstanceid)
- [Task\_AddRef](#task_addref)
- [Task\_Release](#task_release)


### Task_RequireArgument

Macro that can be used to check if a required argument is not specified for a task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Name|const char*|Argument name|

Returns true for the function and adds missing argument error to the task if the argument does not exist.

### Task_SubAction_Null

SubAction function callback that does nothing.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|UserPtr|void*|User data pointer|
|DictionaryHandle|echandle|Subaction dictionary handle|

Return true.

### Task_SubAction_Complete

SubAction function callback that completes the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|UserPtr|void*|User data pointer|
|DictionaryHandle|echandle|Subaction dictionary handle|

Return true.

### Task_IsCompleted

Gets whether or not the task has been completed.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|

Returns true if the task has been completed, false otherwise.

### Task_IsCancelled

Gets whether or not the task has been cancelled.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|

Returns true if the task has been cancelled, false otherwise.

### Task_GetType

Gets a string containing the task's type.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|

Returns a string pointer that contains the task's type.

### Task_GetTimeElapsed

Gets the amount of seconds elapsed while the task was running.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|ElapsedTime|float64*|Second elapsed|

Returns true.

### Task_SetName

Sets the name for the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Name|const char*|Name of task|

Returns true.

### Task_GetName

Gets the name of the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Name|char*|Name buffer|
|MaxName|int32_t|Maximum length of name buffer|

Returns true.

### Task_GetNamePtr

Gets a string pointer to the name of the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|NamePtr|const char**|Name buffer pointer|

Returns true.

### Task_HasArgument

Gets whether or not the task has an argument by name.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Name|const char*|Argument name|

Returns true if that task has the argument specified, false otherwise.

### Task_GetArgumentPtr

Gets the value string of an argument in the task by name.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Name|const char*|Argument name|
|ValuePtr|const char**|Argument value string|

Returns true if successful, false otherwise.

### Task_GetArgumentType

Gets the dictionary type of an argument in the task by name.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Name|const char*|Argument name|
|Type|int32_t*|Argument dictionary type (See DICTIONARY_TYPE)|

Returns true if successful, false otherwise.

### Task_GetStringArgument

Gets the expanded string value of an argument in the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Name|const char*|Argument name|
|Value|char*|Argument value buffer|
|MaxValue|int32_t|Maximum length of argument value buffer|

Returns true if argument exists, false otherwise.

### Task_GetMultiStringArgument

Gets the expanded string value of an argument in the task. If the argument is a list, then it returns a double-quoted string expanded value of each item in the list separated by a space.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Name|const char*|Argument name|
|Value|char*|Argument value buffer|
|MaxValue|int32_t|Maximum length of argument value buffer|

Returns true if argument exists, false otherwise.

_Task_
```json
"runMyTask": {
    "type": "myTask",
    "value": [ "-arg1=test", "--arg2=test3" ]
}
```
_Code_
```c
char Value[1024] = { 0 };
Task_GetMultiStringArgument(TaskHandle, "value", Value, Element_Count(Value));
```
_Result_
```bash
"--arg1=test" "--arg2=test3"
```

### Task_GetBooleanArgument

Gets the boolean value of an argument in the task by name.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Name|const char*|Argument name|
|Value|int32_t*|Boolean value|

Returns true if the argument exists, false otherwise.

**Notes:**

* The value of the argument is expanded before its boolean value is parsed.

### Task_GetNumberArgument

Gets the 64-bit floating integer value of an argument in the task by name.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Name|const char*|Argument name|
|Value|float64*|64-bit floating integer value|

Returns true if the argument exists, false otherwise.

**Notes:**

* The value of the argument is expanded before its 64-bit floating point integer value is parsed.

### Task_GetDictionaryArgument

Copies the dictionary value for an argument in the task by name.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Name|const char*|Argument name|
|TargetDictionaryHandle|echandle|Dictionary handle to copy argument into|

Returns true if the argument exists, false otherwise.

**Notes:**

* If the value of the argument is a dictionary, the argument's dictionary is copied into _TargetDictionaryHandle_.
* If the value of the argument is a list, it will copy each item in the list as a new item in the _TargetDictionaryHandle_ with the key being the _Name_ parameter and the value being the list value.
* If the value of the argument is a string, it is expanded first, and then JSON decoded and copied into _TargetDictionaryHandle_.

### Task_GetCertStoreListArgument

Get list of certificate stores specified in a certificate store list argument for the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Name|const char*|Argument name|
|Default|const char*|Default certificate store name|
|CertStoreListHandle|Target dictionary containing certificate store list|

Returns true if the argument exists, FALSe otherwise.

### Task_SetStatus

Sets the "status" string for the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Status|const char*|Status string|

Returns true if successful, false otherwise.

**Notes:**

* Each task has a status dictionary associated with it and this function sets the "status" key of that dictionary.
* Usually the status is a localization id that the UI translate for the display language selected.

### Task_SetStatusString

Sets a status item in the status dictionary with a string value for the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Name|const char*|Name of the status item|
|Value|const char*|Value of the status item|

Returns true if successful, false otherwise.

```c
Task_SetStatusString(TaskHandle, "trayStatus", "UI_Initializing")
```
_Status Dictionary:_
```json
{
    "status": "UI_Processing",
    "trayStatus": "UI_Initializing"
}
```

### Task_SetStatusNumber

Sets a status item in the status dictionary with a number value for the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Name|const char*|Name of the status item|
|Value|float64|64-bit floating point integer of the status item|

Returns true if successful, false otherwise.

```c
Task_SetStatusString(TaskHandle, "trayProcessed", 1020)
```
_Status Dictionary:_
```json
{
    "status": "UI_Processing",
    "trayStatus": "UI_Initializing",
    "trayProcessed": 1020
}
```

### Task_SetStatusWithDictionary

Merges and overwrites dictionary items into the status dictionary for the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Name|const char*|Name of the status item|
|DictionaryHandle|echandle|Source status dictionary handle|

Returns true.

### Task_SetProgress

Sets the progress for the task. This value is added to the status dictionary for the task as the "progress" item.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Progress|float64|Progress value (0.0 - 1.0)|

Returns true.

### Task_SetPrintIdentifier

Sets a debug identifier to use when printing debug messages to the debug log for the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Identifier|const char*|Identifer string|

Returns true.

### Task_CompleteCallback

Complete callback when a task or subaction completes.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|UserPtr|void*|User data pointer|
|DictionaryHandle|echandle|Complete info dictionary handle|

Return true.

### Task_RunSubAction

Runs a task subaction and calls a callback when complete. Subactions are names of arguments in the task that reference the names of other tasks.

In the example below, _isReady_ is the name of the subaction and it references another task called _doOurThing_.

```json
"checkIfReady": {
    "type": "readyCheck",
    "path": "c:\\pathToCheck.exe",
    "isReady": "doOurThing",
    "isNotReady": "waitAndRetry"
}
```

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Name|const char*|Name of the subaction task argument (ie: isReady)|
|UserPtr|void*|User data pointer for callback|
|Callback|CompleteCallback|Task complete callback when done|

**Notes:**

* If there is an error, the task will contain an error.
* To complete the task after the subtask is run you can pass in _Task_SubAction_Complete_ as the callback and TaskHandle as the user data pointer.

### Task_RunSubTask

Runs a task with the specified name and calls a callback when complete.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Name|const char*|Name of the task to run|
|UserPtr|void*|User data pointer for callback|
|Callback|CompleteCallback|Task complete callback when done|

Returns true.

**Notes:**

* If there is an error, the task will contain an error.
* To complete the task after the subtask is run you can pass in _Task_SubAction_Complete_ as the callback and TaskHandle as the user data pointer.

### Task_Start

Starts the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|

Returns true.

### Task_Complete

Completes the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|DictionaryHandle|echandle|Task.Complete notification dictionary info handle|

Returns true.

### Task_Cancel

Cancels the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|

Returns true.

**Notes:**

* Adds a _Task_Error_Cancelled_ error to the task's error list.

### Task_Dump

Prints the task dictionary to the debug log.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|

Returns true.

### Task_Print

Prints a message for the task to the debug log.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Format|const char*|Print format specifier string|
|...||Arguments for print format specifier string|

Returns true.

```c
Task_Print(TaskHandle, "Hello %s", "world");
```

### Task_VPrint

Prints a message for the task to the debug log using a variable argument list.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Format|const char*|Print format specifier string|
|ArgumentList|va_list|Argument list for print format specifier string|

Returns true.

### Task_VerbosePrint

Prints a message for the task to the debug log when verbose is enabled.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Format|const char*|Print format specifier string|
|...||Arguments for print format specifier string|

Returns true.

**Notes:**

* To turn on verbose messaging you can set the "verbose" argument to true on the task or by calling _Task_SetVerbose_.

### Task_ExpandString

Expands a string in the context of the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|String|char*|Expansion buffer|
|MaxString|int32_t|Maximum length of expansion buffer|

Returns true.

**Notes:**

*  Expands relative task expandable strings such as _{this.status.path}_ or _{this.args.type}_.

### Task_ExpandKey

Expands a macro key and value in the context of the task. The _ExpandKey_ function may call the _Task_ExpandStringCallback_ in order to evaluate certain keys in the task.

|Name|Type|Description|
|-|-|-|
|UserPtr|void*|User data pointer|
|Key|const char*|Macro key|
|Value|const char*|Macro key value|
|Buffer|char*|Expansion buffer|
|MaxBuffer|int32_t|Maximum length of expansion buffer|

Returns true.

### Task_ExpandDictionary

Expands all the item values in the dictionary in the context of the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|DictionaryHandle|echandle|Dictionary to expand|

Returns true.

### EVALUATEPATH_OBJECT

|Name|Value|Description|
|-|-|-|
|UNKNOWN|0|Not specified|
|WORKFLOW|1|Workflow handle|
|TASK|2|Task handle|
|DICTIONARY|3|Dictionary handle|

### Task_EvaluatePathToObject

Evaluates the workflow path and tries to determine the object that the path specifies; either another task, workflow, or a dictionary.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|String|const char*|Path to the object|
|ObjectType|int32_t*|Type of the object (See EVALUATEPATH_OBJECT)|
|ObjectHandle|echandle|Handle to the object|

Returns true if successful, false otherwise.

```
this.status -> task status dictionary
this.args -> task dictionary
this -> task
this.parent -> task
this.workflow -> task's workflow
```

### Task_RequestCompleteCallback

Complete callback for when a URL has been requested.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|UserPtr|void*|User data pointer|
|BufferPtr|uint8*|Request response buffer|
|BufferSize|int32_t|Request response buffer length|
|ErrorCode|int32_t|Error code|
|ErrorCodeEx|int32_t|Extended error code|

Return true.

**Notes:**

* If the request completed successfully, then the ErrorCode is 0.

### Task_RequestURL

Requests a URL and calls a callback when the request is complete.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|URL|const char*|URL to request|
|UserPtr|void*|User data pointer|
|Callback|RequestCompleteCallback|Request complete callback|

Returns true.

### Task_AuthenticateCallback

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|UserPtr|void*|User data pointer|

Returns true to authenticate, false otherwise.

### Task_DecodeJSON

Parses a JSON string into the target dictionary. If the string is JSON web token, it will try to authenticate it. The task's authentication callback can overwrite whether or not authentication occurs.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Buffer|uint8*|JSON buffer|
|BufferSize|int32_t|JSON buffer length|
|TargetDictionaryHandle|echandle|Target dictionary handle|

Returns true if successful, false otherwise.

### Task_LoadFromDictionary

Loads the task from path in the specified source dictionary.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|DictionaryHandle|echanle|Source dictionary handle|
|Path|const char*|Path to the task in the source dictionary|

Returns true if successful, false otherwise.

### Task_HasError

Gets whether or not the task has the specified error in its task list.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Error|const char*|Error to check for in the error list|

Returns true if the error already exists in the task's error list, false otherwise.

### Task_HasWarning

Gets whether or not the task has the specified warning in its task list.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Warning|const char*|Warning to check for in the warning list|

Returns true if the warning already exists in the task's warning list, false otherwise.

### Task_GetErrorCount

Gets the number of errors in the task's error list.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|

Returns the number of errors in the task's error list, or zero if the task has no errors.

### Task_GetWarningCount

Gets the number of warnings in the task's warning list.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|

Returns the number of warnings in the task's warning list, or zero if the task has no warnings.

### Task_AddError

Adds an error to the task's error list.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Format|const char*|Print format specifier string|
|...||Arguments for print format specifier string|

Returns true.

### Task_AddErrorFromMap

Adds the error from the task's error map specified by the exit code.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|ExitCode|int32_t|Exit code to find in the _errorCodeMap_|
|DefaultExitCodeString|const char*|Default exit code string if not found in _errorCodeMap_|

Returns true.

_Task_:
```json
"myTask": {
    "type": "uberTask",
    "errorCodeMap": {
        "0": "UI_Unknown",
        "404": "UI_NotFound"
    }
}
```
_Code_:
```c
Task_AddErrorFromMap(TaskHandle, "404", "UI_WhoKnows")
```
_Result Equivalent_:
```c
Task_AddError(TaskHandle, "UI_NotFound")
```

### Task_AddErrorFromDictionary

Adds the errors specified in the dictionary list to the task's error list.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|DictionaryHandle|echandle|Error dictionary list handle|

Returns true.

### Task_GetError

Gets the error string at the specified index in the task's error list.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Index|int32_t|Error index|
|Error|char*|Error string buffer|
|MaxError|int32_t|Maximum length of error string buffer|

Returns true if index exists, false otherwise.

### Task_GetErrorPtr

Gets a error string pointer at the specified index in the task's error list.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Index|int32_t|Error index|
|ErrorPtr|const char**|Error string pointer|

Returns true if index exists, false otherwise.

### Task_AddWarning

Adds a warning to the task's warning list.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Format|const char*|Print format specifier string|
|...||Arguments for print format specifier string|

Returns true.

### Task_AddWarningFromDictionary

Adds the warnings specified in the dictionary list to the task's warning list.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|DictionaryHandle|echandle|Warning dictionary list handle|

Returns true.

### Task_GetWarning

Gets the warning string at the specified index in the task's warning list.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Index|int32_t|Warning index|
|Warning|char*|Warning string buffer|
|MaxWarning|int32_t|Maximum length of warning string buffer|

Returns true if index exists, false otherwise.

### Task_GetWarningPtr

Gets a warning string pointer at the specified index in the task's warning list.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Index|int32_t|Warning index|
|WarningPtr|const char**|Warning string pointer|

Returns true if index exists, false otherwise.

### Task_ClearErrors

Clears all errors in the task's error list.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|

Returns true.

### Task_ClearWarnings

Clears all warnings in the task's warning list.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|

Returns true.

### Task_SetVerbose

Enables or disables verbose logging for the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Verbose|int32_t|Enable boolean value|

Returns true.

### Task_GetVerbose

Gets whether or not verbose logging is enabled for the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|Verbose|int32_t*|Enable boolean value|

Returns true.

### Task_SetDelayedCancel

Sets whether or not delayed cancel is enabled on the task. When enabled, _Task_Cancel()_ will fire a _Task.Cancel_ notification in which the _Task_Error_Cancelled_ error should be added to the task's error list, and the task completed.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|DelayedCancel|int32_t|Delayed cancel enabled boolean|

Returns true.

### Task_GetDelayedCancel

Gets whether or not delayed cancel is enabled on the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|DelayedCancel|int32_t*|Delayed cancel enabled boolean|

Returns true.

### Task_GetWorkflowHandle

Gets the workflow handle for the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|WorkflowHandle|echandle*|Workflow handle|

Returns true.

### Task_GetDictionaryHandle

Gets the dictionary handle for the task. The task dictionary contains the arguments for the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|DictionaryHandle|echandle*|Argument dictionary handle|

Returns true.

### Task_GetStatusDictionaryHandle

Gets the status dictionary handle for the task. The status dictionary contains status items for the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|DictionaryHandle|echandle*|Status dictionary handle|

Returns true.

### Task_GetCertStoreListHandle

Gets the list of certificate stores for the task's "store" argument.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|CertStoreListHandle|echandle*|Certificate store dictionary list handle|

Returns true.

### Task_SetDefaultCertStore

Sets the default certificate store if "store" argument is not specified.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|DefaultCertStore|const char*|Name of default certificate store|

Returns true.

### Task_GetDefaultCertStore

Gets the default certificate store for the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|DefaultCertStore|char*|Default certificate store buffer|
|MaxDefaultCertStore|int32_t|Maximum length of default certificate store buffer|

Returns true.

### Task_ExpandStringCallback

Callback used for expanding keys on the task with _Task_ExpandKey_ and _Task_ExpandString_.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|UserPtr|void*|User data pointer|
|Key|const char*|Key to expand|
|Buffer|char*|Expansion buffer|
|MaxBuffer|int32_t|Maximum length of expansion buffer|

Return true if the key was expanded, false otherwise.

### Task_SetExpandStringCallback

Sets the string expansion callback for the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|UserPtr|void*|User data pointer|
|Callback|ExpandStringCallback|String expansion callback|

Returns true.

### Task_GetExpandStringCallback

Gets the string expansion callback for the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|UserPtr|void**|User data pointer|
|Callback|ExpandStringCallback*|String expansion callback|

Returns true.

### Task_SetAuthenticateCallback

Sets the authenticate callback to determine whether or not the task should authenticate JWT tokens.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|UserPtr|void*|User data pointer|
|Callback|AuthenticateCallback|Authenticate callback|

Returns true.

### Task_GetAuthenticateCallback

Gets the authenticate callback for the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|UserPtr|void**|User data pointer|
|Callback|AuthenticateCallback*|Authenticate callback|

Returns true.

### Task_GetInstanceId

Gets the instance id for the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|
|InstanceId|char*|Instance id string buffer|
|MaxInstanceId|int32_t|Maximum length of instance id string buffer|

Returns true.

### Task_AddRef

Increments reference count for the task.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle|Task handle|

Returns the task handle.

### Task_Release

Decrements reference count for the task. When the count reaches zero, the task is deleted from memory.

|Name|Type|Description|
|-|-|-|
|TaskHandle|echandle*|Task handle pointer|

Returns true.
