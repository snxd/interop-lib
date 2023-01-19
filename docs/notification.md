## NotificationCenter

The NotificationCenter is responsible for sending and receiving notifications between native C and JavaScript. All notification observers are called back on the main UI thread.

- [NotificationCenter](#notificationcenter)
  - [NotificationCenter\_ObserverCallback](#notificationcenter_observercallback)
  - [NotificationCenter\_AddObserver](#notificationcenter_addobserver)
  - [NotificationCenter\_RemoveObserver](#notificationcenter_removeobserver)
  - [NotificationCenter\_AddProcessObserver](#notificationcenter_addprocessobserver)
  - [NotificationCenter\_RemoveProcessObserver](#notificationcenter_removeprocessobserver)
  - [NotificationCenter\_AddInteropObserver](#notificationcenter_addinteropobserver)
  - [NotificationCenter\_RemoveInteropObserver](#notificationcenter_removeinteropobserver)
  - [NotificationCenter\_AddInstanceObserver](#notificationcenter_addinstanceobserver)
  - [NotificationCenter\_RemoveInstanceObserver](#notificationcenter_removeinstanceobserver)
  - [NotificationCenter\_Fire](#notificationcenter_fire)
  - [NotificationCenter\_FireWithJSON](#notificationcenter_firewithjson)
  - [NotificationCenter\_FireAfterDelay](#notificationcenter_fireafterdelay)
  - [NotificationCenter\_FireAfterDelayWithJSON](#notificationcenter_fireafterdelaywithjson)
  - [NotificationCenter\_SetVerbose](#notificationcenter_setverbose)
- [NotificationCenterInterop](#notificationcenterinterop)
  - [NotificationCenterInterop\_SetExecuteCallback](#notificationcenterinterop_setexecutecallback)
  - [NotificationCenterInterop\_GetInstanceId](#notificationcenterinterop_getinstanceid)
  - [NotificationCenterInterop\_Create](#notificationcenterinterop_create)
  - [NotificationCenterInterop\_Release](#notificationcenterinterop_release)


### NotificationCenter_ObserverCallback

Callback for when a notification observer is triggered.

|Name|Type|Description|
|-|-|-|
|UserPtr|void*|User data pointer|
|Type|const char*|Event type string|
|Notification|const char*|Event name string|
|Sender|void*|String instance id of sender|
|DictionaryHandle|echandle|Notification info Dictionary handle|

Return value is reserved and can be true.

### NotificationCenter_AddObserver

Adds a notification observer callback that gets triggered whenever the specified notification gets fired. The observer callback will get called when any sender sends a notification matching Type and Notification.

|Name|Type|Description|
|-|-|-|
|Type|const char*|Event type string|
|Notification|const char*|Event name string|
|UserPtr|void*|User data pointer|
|Callback|ObserverCallback|Observer callback that is called|

Returns true if successful, false otherwise.

### NotificationCenter_RemoveObserver

Removes a notification observer callback so that it will no longer be triggered whenever a specified notification gets fired.

|Name|Type|Description|
|-|-|-|
|Type|const char*|Event type string|
|Notification|const char*|Event name string|
|UserPtr|void*|User data pointer|
|Callback|ObserverCallback|Observer callback that was previously added|

Returns true if successful, false otherwise.

### NotificationCenter_AddProcessObserver

Adds a process observer callback that gets triggered once per process loop (see WorkflowApp_Process).

|Name|Type|Description|
|-|-|-|
|Sender|void*|String instance id of the sender|
|UserPtr|void*|User data pointer|
|Callback|ObserverCallback|Observer callback to call once per process loop|

Return true if successful, false otherwise.

### NotificationCenter_RemoveProcessObserver

Removes a process observer callback so that it no longer gets triggered once per process loop (see WorkflowApp_Process).

|Name|Type|Description|
|-|-|-|
|Sender|void*|String instance id of the sender|
|UserPtr|void*|User data pointer|
|Callback|ObserverCallback|Observer callback that was previously added|

Return true if successful, false otherwise.

### NotificationCenter_AddInteropObserver

Adds an interop observer callback that gets triggered whenever an interop instance's reference count may need to be incremented or decremented.

|Name|Type|Description|
|-|-|-|
|Sender|void*|String instance id of the sender|
|UserPtr|void*|User data pointer|
|Callback|ObserverCallback|Observer callback|

**Notes:**

* In this case the Dictionary will contain an AddRef boolean key that when true, indicates that the reference count be incremented, and when false, indicates that the reference count be decremented.

Returns true if a successful, false otherwise.

### NotificationCenter_RemoveInteropObserver

Removes an interop observer callback so that it no longer gets triggered whenever an interop instance's reference count needs to be modified.

|Name|Type|Description|
|-|-|-|
|Sender|void*|String instance id of the sender|
|UserPtr|void*|User data pointer|
|Callback|ObserverCallback|Observer callback that was previously added|

Returns true if successful, false otherwise.

### NotificationCenter_AddInstanceObserver

Adds an instance observer callback that gets triggered whenever the specified notification is called on the Sender. The observer callback will get called when the Sender sends a notification matching Type and Notification.

|Name|Type|Description|
|-|-|-|
|Type|const char*|Event type string|
|Notification|const char*|Event name string|
|Sender|void*|String instance id of the sender|
|UserPtr|void*|User data pointer|
|Callback|ObserverCallback|Observer callback|

Returns true if successful, false otherwise.

### NotificationCenter_RemoveInstanceObserver

Removes an intstance observer callback so that it no longer gets triggered whenever the specified notification is called on the Sender.

|Name|Type|Description|
|-|-|-|
|Type|const char*|Event type string|
|Notification|const char*|Event name string|
|Sender|void*|String instance id of the sender|
|UserPtr|void*|User data pointer|
|Callback|ObserverCallback|Observer callback that was previously added|

Returns true if successful, false otherwise.

### NotificationCenter_Fire

Fires a notification on the specified sender.

* Triggers all observers that are registered using AddInstanceObserver matching Type and Notification and Sender.
* Triggers all observers that are registered using AddObserver matching Type and Notification regardless of Sender.

|Name|Type|Description|
|-|-|-|
|Type|const char*|Event type string|
|Notification|const char*|Event name string|
|Sender|void*|String instance id of the sender|
|DictionaryHandle|echandle|Event info Dictionary handle|

**Notes:**

* To send to all observers matching Type and Notification, use _NOTIFICATIONCENTER_GLOBALSENDER_ as the sender.
* DictionaryHandle can be NULL if no data is to be send to the observers.

Returns true if non-global tasks running, false otherwise.

```
echandle DictionaryHandle = NULL;
Dictionary_Create(&DictionaryHandle);
Dictionary_SetInt32ByKey(DictionaryHandle, "sizeOfTray", 1020);
NotificationCenter_Fire("MyObject", "SizeChanged", InstanceId, DictionaryHandle);
Dictionary_Release(&DictionaryHandle);
```

### NotificationCenter_FireWithJSON

Fires a notification same as the Fire function except it allows for the construction of a JSON string instead of a Dictionary.

|Name|Type|Description|
|-|-|-|
|Type|const char*|Event type string|
|Notification|const char*|Event name string|
|Sender|void*|String instance id of the sender|
|Format|const char*|Sprintf formatted string|
|...||Variable arguments for sprintf formatted string|

**Notes:**

* Standard printf formatted specifiers are used.
* %js printf format specifier can be used to convert the string to use JSON escaping.

Returns true if successful, false otherwise.

```
NotificationCenter_FireWithJSON("MyObject", "SizeChanged", InstanceId, "{\"sizeOfTray\":%d}", 1020);
```
### NotificationCenter_FireAfterDelay

Fires a notification same as Fire function, but fires it after a given number of milliseconds has elapsed.

|Name|Type|Description|
|-|-|-|
|Type|const char*|Event type string|
|Notification|const char*|Event name string|
|Sender|void*|String instance id of the sender|
|DelayMS|int32_t|Number of milliseconds to wait before firing|
|DictionaryHandle|echandle|Event info Dictionary handle|

Returns true if successful, false otherwise.

```
echandle DictionaryHandle = NULL;
Dictionary_Create(&DictionaryHandle);
Dictionary_SetBooleanByKey(DictionaryHandle, "successful", Successful);
NotificationCenter_FireAfterDelay("MyObject", "Complete", InstanceId, 1000, DictionaryHandle);
Dictionary_Release(&DictionaryHandle);
```

### NotificationCenter_FireAfterDelayWithJSON

Fires a notification same as FireAfterDelay, except it allows for the construction of a JSON string instead of Dictionary.

|Name|Type|Description|
|-|-|-|
|Type|const char*|Event type string|
|Notification|const char*|Event name string|
|Sender|void*|String instance id of the sender|
|DelayMS|int32_t|Number of milliseconds to wait before firing|
|Format|const char*|Sprintf formatted string|
|...||Variable arguments for sprintf formatted string|

Returns true if successful, false otherwise.

```
NotificationCenter_FireAfterDelayWithJSON("MyObject", "Complete", InstanceId, 1000, "{\"successful\":%s}", ((Successful) ? "true": "false"));
```

### NotificationCenter_SetVerbose

Enables or disables verbose logging for the NotificationCenter.

|Name|Type|Description|
|-|-|-|
|Verbose|int32_t|Enabled boolean value|

Returns true.

```
NotificationCenter_SetVerbose(true);
```

## NotificationCenterInterop

NotificationCenterInterop objects hook into the NotificationCenter and allow for an ExecuteCallback to be whenever a notification occurs. The NotificationCenter will call the Execute callbacks for every NotificationCenterInterop object created.

### NotificationCenterInterop_SetExecuteCallback

Sets the execute callback for the NotificationCenterInterop instance.

|Name|Type|Description|
|-|-|-|
|NotificationCenterInteropHandle|echandle|NotificationCenterInterop handle|
|UserPtr|void*|User data pointer|
|Callback|InteropExecuteCallback|Interop execute callback function|

Returns true.

### NotificationCenterInterop_GetInstanceId

Gets the instance id of the NotificationCenterInterop instance.

|Name|Type|Description|
|-|-|-|
|NotificationCenterInteropHandle|echandle|NotificationCenterInterop handle|
|InstanceId|const char*|Instance id buffer|
|MaxInstanceId|int32_t|Maximum length of instance id buffer|

Returns true.

### NotificationCenterInterop_Create

Creates a new NotificationCenterInterop instance.

|Name|Type|Description|
|-|-|-|
|NotificationCenterInteropHandle|echandle*|NotificationCenterInterop handle|

Returns true.

### NotificationCenterInterop_Release

Releases/deletes a NotificationCenterInterop instance.

|Name|Type|Description|
|-|-|-|
|NotificationCenterInteropHandle|echandle*|NotificationCenterInterop handle|

Returns true.
