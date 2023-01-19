## Class <!-- omit in toc -->

Provides pointer to guid string translation and visa-versa. Objects are tracked through to JavaScript using guid strings. It is important that your object contain a guid string as the first member to its structure so that the pointer to your object is easily castable to a string. For this purpose use type `ClassStruct` as the type for the first member of the structure.

- [Interop\_GenerateInstanceId](#interop_generateinstanceid)
- [Class\_ConvertFromInstanceId](#class_convertfrominstanceid)
- [Class\_ConvertToInstanceId](#class_converttoinstanceid)
- [Class\_TrackInstance](#class_trackinstance)
- [Class\_UntrackInstance](#class_untrackinstance)

### Interop_GenerateInstanceId

Generating a guid string.

|Name|Type|Description|
|-|-|-|
|String|char*|String guid buffer|
|MaxString|int32_t|Max buffer of string guid|

Returns true if successfully, false otherwise.

```c
// Declare object
typedef struct SimpleStruct {
    // Interop storage data
    ClassStruct Class;
    ...
} SimpleStruct;

// Create new object
SimpleStruct *Simple = NULL;
Simple = (SimpleStruct *)calloc(1, sizeof(SimpleStruct));
if (!Simple)
    return false;
// Assign string guid to Class.InstanceId
Interop_GenerateInstanceId(Simple->Class.InstanceId, sizeof(Simple->Class.InstanceId));
```

### Class_ConvertFromInstanceId

Gets the pointer to an object given its guid.

|Name|Type|Description|
|-|-|-|
|InstanceId|const char*|String guid|

Returns `NULL` if no pointer has been found, otherwise the pointer to the object.

**Notes:**

* To use this function you must have first called `Class_TrackInstance` after generating an instance id for the object.

### Class_ConvertToInstanceId

Gets the guid/instance id for a pointer.

|Name|Type|Description|
|-|-|-|
|Pointer|void*|Address to object|

Returns pointer to the object's guid string.

**Notes:**

* To use this function you must have first called `Class_TrackInstance` after generating an instance id for the object.

### Class_TrackInstance

Tracks a object and guid string relationship.

|Name|Type|Description|
|-|-|-|
|Pointer|void*|Address to object|
|InstanceId|const char*|Object's guid string|

Returns true if successfully, false otherwise.

### Class_UntrackInstance

Stops tracking an object and guid string relationship.

|Name|Type|Description|
|-|-|-|
|Pointer|void*|Address to object|

Returns true if successfully, false otherwise.

**Notes:**

Not removing a relationship when it is no longer in use can cause lookups to be slow.
