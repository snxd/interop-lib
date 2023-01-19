## Interop

Interop shared libraries must `export` the following functions.

### Interop_CreateInstance

Called to create an instance of a type of object.

|Name|Type|Description|
|-|-|-|
|TypeName|const char*|Name/type of the object to create. Passed from JavaScript host function `interop.createInstance`.|
|InstanceId|char*|Guid string of the object.|
|InstanceIdLength|int32_t|Max size available to fill guid string.|
|ExecuteUserPtr|void*|Reserved|
|Execute|Interop_ExecuteCallback|Reserved|
|InvokeInstance|Interop_InvokeInstanceCallback*|Pointer to object's invoke function which is called whenever a method needs to be invoked on the object.|
|ReleaseInstance|Interop_ReleaseInstanceCallback*|Pointer to object's release function which is called when the object needs to be released.|
|ProcessInstance|Interop_ProcessInstanceCallback*|Pointer to object's process function which is called once per tick.|
|UserPtr|void**|User data pass to each instance callback|

Return true if successfully, false otherwise.

```c
bool Interop_CreateInstance(const char *TypeName, char *InstanceId, int32_t InstanceIdLength, void *ExecuteUserPtr,
                            Interop_ExecuteCallback Execute, Interop_InvokeInstanceCallback *InvokeInstance,
                            Interop_ReleaseInstanceCallback *ReleaseInstance,
                            Interop_ProcessInstanceCallback *ProcessInstance, void **UserPtr) {
    void *Context;

    if (strcmp(TypeName, "SSN.Simple") == 0) {
        Simple_Create(&Context);
        Simple_GetInstanceId(Context, InstanceId, InstanceIdLength);

        *InvokeInstance = Simple_Invoke;
        *ReleaseInstance = Simple_Release;
        *ProcessInstance = NULL;

        // Uncomment this line in if you want the process call
        // *ProcessInstance = Simple_Process;

        *UserPtr = Context;
        return true;
    }
    return false;
                            }
```

### Interop_SetOverride

Called to provide function callbacks for DIRECT client functions.

|Name|Type|Description|
|-|-|-|
|Key|const char*|Name of the client function.|
|Value|void*|Pointer to the function.|

Return true if successfully, false otherwise.

### Interop_SetOption

Called whenever a client configuration option changes.

|Name|Type|Description|
|-|-|-|
|Key|const char*|Name of the option.|
|Value|void*|Value of the option.|

Return true if successfully, false otherwise.

### Interop_Load

Called whenever the interop library loads.

Return true if successfully, false otherwise.

### Interop_Unload

Called whenever the interop library unloads.

Return true if successfully, false otherwise.
