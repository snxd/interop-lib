## Dictionary <!-- omit in toc -->

The Dictionary class and its interface are used to store structured data.

* Dictionaries contains key/value pair items.
* Dictionaries can contain items of the following types: null, boolean, int64, float64, string, list and dictionary.
* Dictionaries inherit the following settings from their parents: case-sensitivity, allowing duplicates, and string pooling.

**Important:**

Use `Dictionary_Create` and `Dictionary_Delete` to create and delete dictionaries. Then use the corresponding `IDictionary` interface function to call the `Dictionary` function referenced below.

- [DICTIONARY\_TYPE](#dictionary_type)
- [DICTIONARY\_MERGE](#dictionary_merge)
- [Dictionary\_GetParent](#dictionary_getparent)
- [Dictionary\_Add](#dictionary_add)
- [Dictionary\_AddNull](#dictionary_addnull)
- [Dictionary\_AddString](#dictionary_addstring)
- [Dictionary\_AddInt32](#dictionary_addint32)
- [Dictionary\_AddInt64](#dictionary_addint64)
- [Dictionary\_AddFloat64](#dictionary_addfloat64)
- [Dictionary\_AddBoolean](#dictionary_addboolean)
- [Dictionary\_AddList](#dictionary_addlist)
- [Dictionary\_AddDictionary](#dictionary_adddictionary)
- [Dictionary\_Append](#dictionary_append)
- [Dictionary\_Insert](#dictionary_insert)
- [Dictionary\_Remove](#dictionary_remove)
- [Dictionary\_ConvertFromString](#dictionary_convertfromstring)
- [Dictionary\_ConvertToString](#dictionary_converttostring)
- [Dictionary\_ContainsKey](#dictionary_containskey)
- [Dictionary\_EnsureIndex](#dictionary_ensureindex)
- [Dictionary\_EnsureKey](#dictionary_ensurekey)
- [Dictionary\_EnsureList](#dictionary_ensurelist)
- [Dictionary\_EnsureListIndex](#dictionary_ensurelistindex)
- [Dictionary\_EnsureDictionary](#dictionary_ensuredictionary)
- [Dictionary\_EnsureDictionaryByPath](#dictionary_ensuredictionarybypath)
- [Dictionary\_EnsureDictionaryByIndex](#dictionary_ensuredictionarybyindex)
- [Dictionary\_GetTypeByKey](#dictionary_gettypebykey)
- [Dictionary\_SetStringByKey](#dictionary_setstringbykey)
- [Dictionary\_SetStringByKeyV](#dictionary_setstringbykeyv)
- [Dictionary\_SetStringByKeyPrint](#dictionary_setstringbykeyprint)
- [Dictionary\_GetStringByKey](#dictionary_getstringbykey)
- [Dictionary\_SetStringByPath](#dictionary_setstringbypath)
- [Dictionary\_GetStringByPath](#dictionary_getstringbypath)
- [Dictionary\_GetStringPtrByKey](#dictionary_getstringptrbykey)
- [Dictionary\_GetBufferPtrByKey](#dictionary_getbufferptrbykey)
- [Dictionary\_GetBufferPtrByPath](#dictionary_getbufferptrbypath)
- [Dictionary\_SetInt32ByKey](#dictionary_setint32bykey)
- [Dictionary\_SetInt32ByPath](#dictionary_setint32bypath)
- [Dictionary\_GetInt32ByKey](#dictionary_getint32bykey)
- [Dictionary\_GetInt32ByPath](#dictionary_getint32bypath)
- [Dictionary\_SetInt64ByKey](#dictionary_setint64bykey)
- [Dictionary\_SetInt64ByPath](#dictionary_setint64bypath)
- [Dictionary\_GetInt64ByKey](#dictionary_getint64bykey)
- [Dictionary\_GetInt64ByPath](#dictionary_getint64bypath)
- [Dictionary\_SetFloat64ByKey](#dictionary_setfloat64bykey)
- [Dictionary\_SetFloat64ByPath](#dictionary_setfloat64bypath)
- [Dictionary\_GetFloat64ByKey](#dictionary_getfloat64bykey)
- [Dictionary\_GetFloat64ByPath](#dictionary_getfloat64bypath)
- [Dictionary\_SetBooleanByKey](#dictionary_setbooleanbykey)
- [Dictionary\_SetBooleanByPath](#dictionary_setbooleanbypath)
- [Dictionary\_GetBooleanByKey](#dictionary_getbooleanbykey)
- [Dictionary\_GetBooleanByPath](#dictionary_getbooleanbypath)
- [Dictionary\_GetListByIndex](#dictionary_getlistbyindex)
- [Dictionary\_GetDictionaryByIndex](#dictionary_getdictionarybyindex)
- [Dictionary\_GetListByKey](#dictionary_getlistbykey)
- [Dictionary\_GetDictionaryByKey](#dictionary_getdictionarybykey)
- [Dictionary\_RemoveByKey](#dictionary_removebykey)
- [Dictionary\_ItemGetPath](#dictionary_itemgetpath)
- [Dictionary\_ItemIsContainer](#dictionary_itemiscontainer)
- [Dictionary\_ItemIsNull](#dictionary_itemisnull)
- [Dictionary\_ItemGetIndex](#dictionary_itemgetindex)
- [Dictionary\_ItemSetType](#dictionary_itemsettype)
- [Dictionary\_ItemGetType](#dictionary_itemgettype)
- [Dictionary\_ItemCompareType](#dictionary_itemcomparetype)
- [Dictionary\_ItemSetKey](#dictionary_itemsetkey)
- [Dictionary\_ItemSetKeyLength](#dictionary_itemsetkeylength)
- [Dictionary\_ItemGetKey](#dictionary_itemgetkey)
- [Dictionary\_ItemGetKeyPtr](#dictionary_itemgetkeyptr)
- [Dictionary\_ItemSetString](#dictionary_itemsetstring)
- [Dictionary\_ItemSetStringPrint](#dictionary_itemsetstringprint)
- [Dictionary\_ItemSetStringV](#dictionary_itemsetstringv)
- [Dictionary\_ItemGetString](#dictionary_itemgetstring)
- [Dictionary\_ItemGetStringPtr](#dictionary_itemgetstringptr)
- [Dictionary\_ItemSetBuffer](#dictionary_itemsetbuffer)
- [Dictionary\_ItemGetBufferPtr](#dictionary_itemgetbufferptr)
- [Dictionary\_ItemSetFloat64](#dictionary_itemsetfloat64)
- [Dictionary\_ItemGetFloat64](#dictionary_itemgetfloat64)
- [Dictionary\_ItemSetInt32](#dictionary_itemsetint32)
- [Dictionary\_ItemGetInt32](#dictionary_itemgetint32)
- [Dictionary\_ItemSetInt64](#dictionary_itemsetint64)
- [Dictionary\_ItemGetInt64](#dictionary_itemgetint64)
- [Dictionary\_ItemSetBoolean](#dictionary_itemsetboolean)
- [Dictionary\_ItemGetBoolean](#dictionary_itemgetboolean)
- [Dictionary\_ItemSetNull](#dictionary_itemsetnull)
- [Dictionary\_ItemGetDictionaryHandle](#dictionary_itemgetdictionaryhandle)
- [Dictionary\_ItemFindByPath](#dictionary_itemfindbypath)
- [Dictionary\_ItemFindByKey](#dictionary_itemfindbykey)
- [Dictionary\_ItemFindByBuffer](#dictionary_itemfindbybuffer)
- [Dictionary\_ItemFindByIndex](#dictionary_itemfindbyindex)
- [Dictionary\_ItemGetNext](#dictionary_itemgetnext)
- [Dictionary\_ItemGetPrev](#dictionary_itemgetprev)
- [Dictionary\_ItemGetFirst](#dictionary_itemgetfirst)
- [Dictionary\_ItemGetLast](#dictionary_itemgetlast)
- [Dictionary\_ItemGetCount](#dictionary_itemgetcount)
- [Dictionary\_Log](#dictionary_log)
- [Dictionary\_LogTabbed](#dictionary_logtabbed)
- [Dictionary\_ItemFilterCallback](#dictionary_itemfiltercallback)
- [Dictionary\_Sync](#dictionary_sync)
- [Dictionary\_SyncAt](#dictionary_syncat)
- [Dictionary\_RemoveMissing](#dictionary_removemissing)
- [Dictionary\_Merge](#dictionary_merge-1)
- [Dictionary\_MergeAt](#dictionary_mergeat)
- [Dictionary\_MergeItem](#dictionary_mergeitem)
- [Dictionary\_SkipRoot](#dictionary_skiproot)
- [Dictionary\_SkipRootContainer](#dictionary_skiprootcontainer)
- [Dictionary\_Reset](#dictionary_reset)
- [Dictionary\_Dump](#dictionary_dump)
- [Dictionary\_SetCaseSensitive](#dictionary_setcasesensitive)
- [Dictionary\_GetCaseSensitive](#dictionary_getcasesensitive)
- [Dictionary\_SetAllowDuplicates](#dictionary_setallowduplicates)
- [Dictionary\_GetAllowDuplicates](#dictionary_getallowduplicates)
- [Dictionary\_ItemRemoveCallback](#dictionary_itemremovecallback)
- [Dictionary\_SetItemRemoveCallback](#dictionary_setitemremovecallback)
- [Dictionary\_GetItemRemoveCallback](#dictionary_getitemremovecallback)
- [Dictionary\_ItemKeyChangeCallback](#dictionary_itemkeychangecallback)
- [Dictionary\_SetItemKeyChangeCallback](#dictionary_setitemkeychangecallback)
- [Dictionary\_GetItemKeyChangeCallback](#dictionary_getitemkeychangecallback)
- [Dictionary\_ItemValueChangeCallback](#dictionary_itemvaluechangecallback)
- [Dictionary\_SetItemValueChangeCallback](#dictionary_setitemvaluechangecallback)
- [Dictionary\_GetItemValueChangeCallback](#dictionary_getitemvaluechangecallback)
- [Dictionary\_TranslateType](#dictionary_translatetype)
- [Dictionary\_PathGetKey](#dictionary_pathgetkey)
- [Dictionary\_PathSkipRoot](#dictionary_pathskiproot)
- [Dictionary\_PathGetParent](#dictionary_pathgetparent)
- [Dictionary\_PathHasParent](#dictionary_pathhasparent)
- [Dictionary\_Create](#dictionary_create)
- [Dictionary\_AddRef](#dictionary_addref)
- [Dictionary\_Release](#dictionary_release)


### DICTIONARY_TYPE

These values indicate the type of an item.

|Name|Value|Description|
|-|-|-|
|UNKNOWN|0|Not specified|
|BOOLEAN|1|Boolean value, true = 1, false = 0|
|INT64|2|64-bit integer|
|FLOAT64|3|64-bit floating point integer|
|STRING|4|UTF8 character buffer|
|LIST|5|Items containing no key|
|DICTIONARY|6|Key/value pairs|

**Notes:**

* 32-bit integers are stored internally as 64-bit integers

### DICTIONARY_MERGE

These values indicate how items will be merged when copying from one dictionary into another.

|Name|Value|Description|
|-|-|-|
|OVERWRITE|0x01|Existing items will be overwritten|
|INSERT|0x02|New items will be inserted at the beginning|
|APPEND|0x04|New items will be appended to the end|

### Dictionary_GetParent

Gets a child dictionary's parent instance along with the associated item in the parent where the child dictionary can be found.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Child dictionary handle|
|ParentDictionaryHandle|echandle*|Parent dictionary handle|
|ParentItemHandle|echandle*|Item handle in parent dictionary where child dictionary can be found.|

Returns true if child dictionary has a parent, false otherwise.

### Dictionary_Add

Adds an item to the dictionary with a key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Key string|
|ItemHandle|echandle*|Item handle that is created|

**Notes:**

* The item added to the dictionary is not assigned a type unless Dictionary_ItemSetType is called.
* New items added using this function are appended on to the backend of the list of items in the dictionary (also see Dictionary_Append).

Returns true if added successfully, false otherwise.

### Dictionary_AddNull

Adds a null typed item to the dictionary with a key.
```json
{ "myKey": null }
```
|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Key string|
|ItemHandle|echandle*|Item handle that is created|

Returns true if added successfully, false otherwise.

### Dictionary_AddString

Adds a string typed item to the dictionary with a key and value.
```json
{ "myKey": "myValue" }
```
|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Key string|
|Value|const char*|Value string|
|ItemHandle|echandle*|Item handle that is created|

Returns true if added successfully, false otherwise.

### Dictionary_AddInt32

Adds a 32-bit integer typed item to the dictionary with a key and value.
```json
{ "myTraySize": 1020 }
```

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Key string|
|Value|int32_t|32-bit integer value|
|ItemHandle|echandle*|Item handle that is created|

Returns true if added successfully, false otherwise.

### Dictionary_AddInt64

Adds a 64-bit integer typed item to the dictionary with a key and value.
```json
{ "myTraySize": 1061208000 }
```

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Key string|
|Value|int64|64-bit integer value|
|ItemHandle|echandle*|Item handle that is created|

Returns true if added successfully, false otherwise.

### Dictionary_AddFloat64

Adds a 64-bit floating integer typed item to the dictionary with a key and value.
```json
{ "myTraySize": 1020.0 }
```
|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Key string|
|Value|float64|64-bit floating integer value|
|ItemHandle|echandle*|Item handle that is created|

Returns true if added successfully, false otherwise.

### Dictionary_AddBoolean

Adds a boolean typed item to the dictionary with a key and value.
```json
{ "isEnabled": false }
```
|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Key string|
|Value|int32_t|Boolean value (0 or 1)|
|ItemHandle|echandle*|Item handle that is created|

Returns true if added successfully, false otherwise.

### Dictionary_AddList

Adds a list typed item to the dictionary with a key.
```json
{ "myList": [ ] }
```
|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Key string|
|ListHandle|echandle*|Handle for created list Dictionary|
|ItemHandle|echandle*|Item handle that is created in dictionary|

**Notes:**

* Lists are Dictionary instances whose items contain no keys - only values.

Returns true if added successfully, false otherwise.

### Dictionary_AddDictionary

Adds a dictionary typed item to the dictionary with a key.
```json
{ "myObject": { } }
```
|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Key string|
|DictHandle|echandle*|Handle for created dictionary|
|ItemHandle|echandle*|Item handle that is created in dictionary|

Returns true if added successfully, false otherwise.

### Dictionary_Append

Appends a new item to the dictionary. The function operates the same as Dictionary_Add.

### Dictionary_Insert

Inserts a new item in the dictionary. The item will be inserted after the item indicated by PrevItemHandle.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|PrevItemHandle|echandle|Previous item handle|
|Key|const char*|Key string|
|ItemHandle|echandle*|Item handle that is created in dictionary|

Returns true if successful, false otherwise.

### Dictionary_Remove

Removes an item from the dictionary given it's handle.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Handle of item to remove|

Returns true if removed successfully, false otherwise.

### Dictionary_ConvertFromString

Loads a key/value pair string into the dictionary.

_Input String_
```
key1=value1;key2=value2
```
_Output Structure_
```json
{ "key1": "value1", "key2": "value2" }
```

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Value|char*|String to convert|
|MaxValue|int32_t|Maximum length of string to convert|
|KeyValueSeparator|char|Character that separators keys from values (ie: =)|
|ItemSeparator|char|Character that separators items from each other (ie: ;)|

Returns true if successful, false otherwise.

### Dictionary_ConvertToString

Converts a dictionary into a key/value pair string.

_Input Structure_
```json
{ "key1": "value1", "key2": "value2" }
```
_Output String_
```
key1=value1;key2=value2;
```

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Value|char*|Conversion string buffer|
|MaxValue|int32_t|Maximum length of conversion string buffer|
|KeyValueSeparator|char|Character that separators keys from values (ie: =)|
|ItemSeparator|char|Character that separators items from each other (ie: ;)|

Returns true if successful, false otherwise.

### Dictionary_ContainsKey

Gets whether or not the dictionary contains an item with the specified key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Key to search for|

Returns true if dictionary contains key, false otherwise.

### Dictionary_EnsureIndex

Ensures that the specified item by index exists in the dictionary. If the item at the specified does not exist, it will be created.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Index|int32_t|Index of item to retrieve|
|ItemHandle|echandle*|Item handle at the specified index|

Returns true if successful, false otherwise.

**Notes:**

* This function will create empty non-typed items until the index is addressable at which point it will return the item at the specified index.

### Dictionary_EnsureKey

Ensures that an item exists for the key. If the item does not exist, it an empty non-typed item be created with the specified key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Key of item to ensure exists|
|ItemHandle|echandle*|Item handle at the specified index|

Returns true if successful, false otherwise.

### Dictionary_EnsureList

Ensures that a list typed item exists for the key. If the item does not exist, it will be created.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item to ensure exists|
|ItemHandle|echandle*|Item handle that was created|
|ItemDictionaryHandle|echandle*|Handle to the list dictionary for the key|

Returns true if successful, false otherwise.

### Dictionary_EnsureListIndex

Ensures that the specified item by index exists in the dictionary and ensures that it is a list typed item. If the item at the specified does not exist, it will be created.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Index|int32_t|Index of item to retrieve|
|ItemHandle|echandle*|Item handle at the specified index|
|ItemDictionaryHandle|echandle*|Handle to the list dictionary|

Returns true if successful, false otherwise.

**Notes:**

* This function will create empty items until the index is addressable at which point it will return the item at the specified index.

### Dictionary_EnsureDictionary

Ensures that a dictionary typed item exists for the key. If the item does not exist, it will be created.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item to ensure exists|
|ItemHandle|echandle*|Item handle that was created|
|ItemDictionaryHandle|echandle*|Handle to the dictionary for the key|

Returns true if successful, false otherwise.

### Dictionary_EnsureDictionaryByPath

Ensures that the path specified exists in the dictionary. If the path does not exist, it will be created.

_Input Path_
```
myKey.mySubKey
```
_Search Structure_
```json
{ "myKey": { "mySubKey": { "hello": "world" } } }
```

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Path|const char*|Path to ensure it exists (ie: myKey.mySubKey)|
|ItemDictionaryHandle|echandle*|Handle to the list dictionary|

Returns true if successful, false otherwise.

**Notes:**

* This function will create empty dictionaries until the path specified is addressable at which point it will return the last dictionary created.

### Dictionary_EnsureDictionaryByIndex

Ensures that the specified item by index exists in the dictionary and ensures that it is a dictionary typed item. If the item at the specified index does not exist, it will be created.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Index|int32_t|Index of item to retrieve|
|ItemHandle|echandle*|Item handle at the specified index|
|ItemDictionaryHandle|echandle*|Handle to the dictionary at the index|

Returns true if successful, false otherwise.

**Notes:**

* This function will create empty non-typed items until the index is addressable at which point it will return the item at the specified index.

### Dictionary_GetTypeByKey

Gets the type of the item specified by the key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|
|Type|int32_t*|Type of the item (see DICTIONARY_TYPE)|

Returns true if item exists, false otherwise.

### Dictionary_SetStringByKey

Sets the string for an item specified by key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|
|String|const char*|Value string|

Returns true if successful, false otherwise.

### Dictionary_SetStringByKeyV

Sets the string using a formatted specifier and variable argument list for an item specified by key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|
|String|const char*|Value string with sprintf format specifiers|
|ArgumentList|va_list|Variable argument list for sprintf|

Returns true if successful, false otherwise.

### Dictionary_SetStringByKeyPrint

Sets the string using a formatted specifier for an item specified by key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|
|String|const char*|Value string with sprintf format specifiers|
|...||Variable arguments for sprintf|

Returns true if successful, false otherwise.

### Dictionary_GetStringByKey

Gets the string for an item specified by key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|
|String|char*|Value string buffer|
|MaxString|int32_t|Maximum length of value string buffer|

Returns true if item exists, false otherwise.

### Dictionary_SetStringByPath

Sets the string for an item specified by path.

_Input Path and Value_
```
f1.f2.key1=val1
```
_Output Structure_
```json
{ "f1": { "f2": { "key1": "val1" } } }
```

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Path|const char*|Location of item (ie: f1.f2.key1)|
|String|const char*|Value string (ie: val1)|

Returns true if successful, false otherwise.

### Dictionary_GetStringByPath

Gets the string for an item specified by path.

_Input Path_
```
f1.f2.key1
```
_Input Structure_
```json
{ "f1": { "f2": { "key1": "val1" } } }
```
_Expected Value_
```
val1
```

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Path|const char*|Location of item (ie: f1.f2.string)|
|String|char*|Value string|
|MaxString|int32_t|Maximum length of value string buffer|

Returns true if item exists, false otherwise.

### Dictionary_GetStringPtrByKey

Gets the pointer to the string for an item specified by key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|
|StringPtr|const char**|Value string pointer|

Returns true if item exists, false otherwise.

### Dictionary_GetBufferPtrByKey

Gets the raw memory buffer pointer for an item specified by key. The memory buffer is null-terminated.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|
|BufferPtr|const char**|Buffer pointer|
|BufferLength|int32_t*|Buffer pointer length|

Returns true if item exists, false otherwise.

### Dictionary_GetBufferPtrByPath

Gets the raw memory buffer pointer for an item specified by path. The memory buffer is null-terminated.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Path|const char*|Location of item|
|BufferPtr|const char**|Buffer pointer|
|BufferLength|int32_t*|Buffer pointer length|

Returns true if item exists, false otherwise.

### Dictionary_SetInt32ByKey

Sets the 32-bit integer value for an item specified by key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|
|Value|int32_t|32-bit integer value|

Returns true if successful, false otherwise.

### Dictionary_SetInt32ByPath

Sets the 32-bit integer value for an item specified by path.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Path|const char*|Location of item|
|Value|int32_t|32-bit integer value|

Returns true if successful, false otherwise.

### Dictionary_GetInt32ByKey

Gets the 32-bit integer value for an item specified by key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|
|Value|int32_t*|32-bit integer value|

Returns true if successful, false otherwise.

### Dictionary_GetInt32ByPath

Gets the 32-bit integer value for an item specified by path.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Path|const char*|Location of item|
|Value|int32_t*|32-bit integer value|

Returns true if successful, false otherwise.

### Dictionary_SetInt64ByKey

Sets the 64-bit integer value for an item specified by key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|
|Value|int64|64-bit integer value|

Returns true if successful, false otherwise.

### Dictionary_SetInt64ByPath

Sets the 64-bit integer value for an item specified by path.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Path|const char*|Location of item|
|Value|int64|64-bit integer value|

Returns true if successful, false otherwise.

### Dictionary_GetInt64ByKey

Gets the 64-bit integer value for an item specified by key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|
|Value|int64*|64-bit integer value|

Returns true if successful, false otherwise.

### Dictionary_GetInt64ByPath

Gets the 64-bit integer value for an item specified by path.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Path|const char*|Location of item|
|Value|int64*|64-bit integer value|

Returns true if successful, false otherwise.

### Dictionary_SetFloat64ByKey

Sets the 64-bit floating point integer value for an item specified by key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|
|Value|float64|64-bit floating point integer value|

Returns true if successful, false otherwise.

### Dictionary_SetFloat64ByPath

Sets the 64-bit floating point integer value for an item specified by path.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Path|const char*|Location of item|
|Value|float64|64-bit floating point integer value|

Returns true if successful, false otherwise.

### Dictionary_GetFloat64ByKey

Gets the 64-bit floating point integer value for an item specified by key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|
|Value|float64*|64-bit floating point integer value|

Returns true if successful, false otherwise.

### Dictionary_GetFloat64ByPath

Gets the 64-bit floating point integer value for an item specified by path.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Path|const char*|Location of item|
|Value|float64*|64-bit floating point integer value|

Returns true if successful, false otherwise.

### Dictionary_SetBooleanByKey

Sets the boolean value for an item specified by key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|
|Value|int32_t|Boolean value|

Returns true if successful, false otherwise.

### Dictionary_SetBooleanByPath

Sets the boolean value for an item specified by path.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Path|const char*|Location of item|
|Value|int32_t|Boolean value|

Returns true if successful, false otherwise.

### Dictionary_GetBooleanByKey

Gets the boolean value for an item specified by key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|
|Value|int32_t*|Boolean value|

Returns true if successful, false otherwise.

### Dictionary_GetBooleanByPath

Gets the boolean value for an item specified by path.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Path|const char*|Location of item|
|Value|int32_t*|Boolean value|

Returns true if successful, false otherwise.

### Dictionary_GetListByIndex

Gets the list at the specified index.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Index|int32_t|Index of item|
|ItemDictionaryHandle|echandle*|List dictionary handle|

Returns true if item exists at index and is a list, false otherwise.

### Dictionary_GetDictionaryByIndex

Gets the dictionary at the specified index.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Index|int32_t|Index of item|
|ItemDictionaryHandle|echandle*|Dictionary handle for item|

Returns true if item exists at index and is a dictionary, false otherwise.

### Dictionary_GetListByKey

Gets the list at the specified key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|
|ItemDictionaryHandle|echandle*|List dictionary handle|

Returns true if item exists with key and is a list, false otherwise.

### Dictionary_GetDictionaryByKey

Gets the dictionary at the specified key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|
|ItemDictionaryHandle|echandle*|Dictionary handle for item|

Returns true if item exists with key and is a dictionary, false otherwise.

### Dictionary_RemoveByKey

Remove an item specified by key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|

Returns true if removed successfully, false otherwise.

### Dictionary_ItemGetPath

Gets a path for a dictionary item.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|TopDictionaryHandle|echandle|Dictionary handle to stop at|
|Path|char*|Path buffer|
|MaxPath|int32_t|Maximum length of path buffer|

Returns true if successfully, false otherwise.

### Dictionary_ItemIsContainer

Gets whether or not the item is a list or dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|

Returns true if the item is a list or dictionary, false otherwise.

### Dictionary_ItemIsNull

Gets whether or not the item is null typed.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|

Returns true if the item is null typed, false otherwise.

### Dictionary_ItemGetIndex

Gets the index of the item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|Index|int32_t*|Index of item|

Returns true if successful, false otherwise.

### Dictionary_ItemSetType

Sets the type of an item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|Type|int32_t|Type of the item (See DICTIONARY_TYPE)|

Returns true if successful, false otherwise.

**Notes:**

* Changing the type of a dictionary item will cause its value to be reset.

### Dictionary_ItemGetType

Gets the type of an item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|Type|int32_t*|Type of the item (See DICTIONARY_TYPE)|

Returns true if successful, false otherwise.

### Dictionary_ItemCompareType

Determine if an item in the dictionary is of a particular type.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|Type|int32_t|Type to check (See DICTIONARY_TYPE)|

Returns true if the item's type matches the Type specified, false otherwise.

### Dictionary_ItemSetKey

Sets the key of the item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|Key|const char*|Name of item|

Returns true if successful, false otherwise.

### Dictionary_ItemSetKeyLength

Sets the key of the item in the dictionary. Copies the key name up to the length specified.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|Key|const char*|Name of item|
|KeyLength|int32_t|Number of bytes in the name to copy|

Returns true if successful, false otherwise.

### Dictionary_ItemGetKey

Gets the key of the item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|Key|char*|Key buffer|
|MaxKey|int32_t|Maximum length of key buffer|

Returns true if successful, false otherwise.

### Dictionary_ItemGetKeyPtr

Gets a pointer to the key of the item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|KeyPtr|const char**|Pointer to key string|

Returns true if successful, false otherwise.

### Dictionary_ItemSetString

Sets the string of the item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|String|const char*|Value string|

Returns true if successful, false otherwise.

### Dictionary_ItemSetStringPrint

Sets the string of the item in the dictionary using a print format specifier.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|String|const char*|Value string with print format specifiers|
|...||Arguments for print format specifier|

Returns true if successful, false otherwise.

### Dictionary_ItemSetStringV

Sets the string of the item in the dictionary using a print format specifier and variable argument list.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|String|const char*|Value string with print format specifiers|
|ArgumentList|va_list|Variable argument list for print format specifier|

Returns true if successful, false otherwise.

### Dictionary_ItemGetString

Gets the string of the item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|String|char*|Value string buffer|
|MaxString|int32_t|Maximum length of value string buffer|

Returns true if successful, false otherwise.

### Dictionary_ItemGetStringPtr

Gets a pointer to the string of the item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|StringPtr|const char**|Value string pointer|

Returns true if successful, false otherwise.

### Dictionary_ItemSetBuffer

Copies the raw memory buffer for the item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|Buffer|const char*|Buffer to copy|
|BufferLength|int32_t|Bytes to copy|

Returns true if successful, false otherwise.

**Notes:**

* Each item in the dictionary has a raw memory buffer associated with it. This function will copy bytes from the buffer supplied into the raw memory buffer for the item.
* For boolean typed items, the buffer supplied will be parsed for the boolean value and set appropriately.
* For null typed items, this function does nothing.

### Dictionary_ItemGetBufferPtr

Gets a pointer to the raw memory buffer for the item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|BufferPtr|const char**|Buffer pointer|
|BufferLength|int32_t*|Buffer length|

Returns true if successful, false otherwise.

**Notes:**

* The buffer pointer always points to a memory allocation that is null-terminated.
* BufferLength argument can be NULL if the length of the buffer is not needed.

### Dictionary_ItemSetFloat64

Sets the 64-bit floating point integer value for the item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|Value|float64|64-bit floating point integer value|

Returns true.

### Dictionary_ItemGetFloat64

Gets the 64-bit floating point integer value for the item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|Value|float64*|64-bit floating point integer value|

Returns true if item is typed a 64-bit floating point integer or 64-bit integer, false otherwise.

**Notes:**

* If the item is 64-bit integer typed, the returned value will be a casted 64-bit floating point integer.

### Dictionary_ItemSetInt32

Sets the 32-bit integer value for the item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|Value|int32_t|32-bit integer value|

Returns true.

### Dictionary_ItemGetInt32

Gets the 32-bit integer value for the item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|Value|int32_t*|32-bit integer value|

Returns true if item is a typed 64-bit integer or 64-bit floating point integer, false otherwise.

**Notes:**

* If the item is 64-bit integer typed or 64-bit floating point integer typed, the returned value will be a casted 32-bit integer.

### Dictionary_ItemSetInt64

Sets the 64-bit integer value for the item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|Value|int64|64-bit integer value|

Returns true.

### Dictionary_ItemGetInt64

Gets the 64-bit integer value for the item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|Value|int64*|64-bit integer value|

Returns true if item is a typed 64-bit integer or 64-bit floating point integer, false otherwise.

**Notes:**

* If the item is 64-bit floating point integer typed, the returned value will be a casted 64-bit integer.

### Dictionary_ItemSetBoolean

Sets the boolean value for the item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|Value|int32_t|Boolean value|

Returns true.

### Dictionary_ItemGetBoolean

Gets the boolean value for the item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|Value|int32_t*|Boolean value|

Returns true if item is boolean typed, false otherwise.

### Dictionary_ItemSetNull

Returns true.

### Dictionary_ItemGetDictionaryHandle

Gets the item's dictionary handle if the item is dictionary typed.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Item handle|
|DictHandle|echandle*|Item dictionary handle|

Returns true if the item is dictionary typed, false otherwise.

### Dictionary_ItemFindByPath

Finds an item in the dictionary by path.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Path|const char*|Location of item|
|ItemDictionaryHandle|echandle*|Handle to immediately dictionary where item is found|
|ItemHandle|echandle*|Handle to item that was found|

Returns true if the item was found, false otherwise.

### Dictionary_ItemFindByKey

Finds an item in the dictionary by key.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Key|const char*|Name of item|
|StartItemHandle|echandle|Handle to item to start search at or NULL|
|ItemHandle|echandle*|Handle to item if found|

Returns true if the item was found, false otherwise.

### Dictionary_ItemFindByBuffer

Finds an item in the dictionary by value buffer. Searches every item's value buffer to find a match.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Buffer|const char*|Value buffer|
|BufferLength|int32_t|Value buffer length|
|StartItemHandle|echandle|Handle to item to start search at or NULL|
|ItemHandle|echandle*|Handle to item if found|

Returns true if the item was found, false otherwise.

### Dictionary_ItemFindByIndex

Finds an item in the dictionary by index.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Index|int32_t|Index of item|
|StartItemHandle|echandle|Handle to item to start search at or NULL|
|ItemHandle|echandle*|Handle to item if found|

Returns true if the item was found, false otherwise.

### Dictionary_ItemGetNext

Gets the next item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Current item handle|
|NextItemHandle|echandle*|Next item handle|

Returns true if successful, false otherwise.

### Dictionary_ItemGetPrev

Gets the previous item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Current item handle|
|PrevItemHandle|echandle*|Previous item handle|

Returns true if successful, false otherwise.

### Dictionary_ItemGetFirst

Gets the first item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle*|First item handle|

Returns true if successful, false otherwise.

### Dictionary_ItemGetLast

Gets the last item in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle*|Last item handle|

Returns true if successful, false otherwise.

### Dictionary_ItemGetCount

Gets the number of items in the dictionary. Does not traverse dictionary or list items.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemCount|int32_t*|Number of items|

Returns true.

### Dictionary_Log

Prints a message for the dictionary that is written to the debug log.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Format|const char*|String print format specifier|
|...||Arguments for print format specifier|

Returns true.

### Dictionary_LogTabbed

Prints an indented message for the dictionary that is written to the debug log.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|Depth|int32_t|Number of tabs|
|Format|const char*|String print format specifier|
|...||Arguments for print format specifier|

Returns true.

### Dictionary_ItemFilterCallback

TODO

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|UserPtr|void*|User data pointer|
|SourceDictionaryHandle|echandle|Source dictionary handle|
|SourceItemHandle|echandle|Source item handle|

### Dictionary_Sync

TODO

|Name|Type|Description|
|-|-|-|
|TargetDictionaryHandle|echandle|Target dictionary handle|
|SourceDictionaryHandle|echandle|Source dictionary handle|
|FilterUserPtr|void*|User data pointer|
|FilterCallback|ItemFilterCallback|Callback function|

### Dictionary_SyncAt

TODO

|Name|Type|Description|
|-|-|-|
|TargetDictionaryHandle|echandle|Target dictionary handle|
|SourceDictionaryHandle|echandle|Source dictionary handle|
|SourceItemHandle|echandle|Source item handle|
|FilterUserPtr|void*|User data pointer|
|FilterCallback|ItemFilterCallback|Callback function|

### Dictionary_RemoveMissing

Removes any items in the target dictionary which don't exist by key in the source dictionary key list.

|Name|Type|Description|
|-|-|-|
|TargetDictionaryHandle|echandle|Target dictionary handle|
|SourceDictionaryHandle|echandle|Source dictionary list handle containing list of valid keys|

Returns true.

### Dictionary_Merge

Merges the items from one dictionary into another. The overwrite argument determines if the source dictionary's items will overwrite existing items in the target dictionary or not.

|Name|Type|Description|
|-|-|-|
|TargetDictionaryHandle|echandle|Target dictionary handle|
|SourceDictionaryHandle|echandle|Source dictionary handle|
|OverwriteExisting|int32_t|Overwrite existing items|

Returns true.

### Dictionary_MergeAt

Merges the items from one dictionary into another, starting at a particular item in the source dictionary.

|Name|Type|Description|
|-|-|-|
|TargetDictionaryHandle|echandle|Target dictionary handle|
|SourceDictionaryHandle|echandle|Source dictionary handle|
|SourceItemHandle|echandle|Item to start at when copying|
|Flags|int32_t|Merge flags (See DICTIONARY_MERGE)|

Returns true.

### Dictionary_MergeItem

Merges a particular item from one dictionary into another.

|Name|Type|Description|
|-|-|-|
|TargetDictionaryHandle|echandle|Target dictionary handle|
|SourceDictionaryHandle|echandle|Source dictionary handle|
|SourceItemHandle|echandle|Item to copy|
|Flags|int32_t|Merge flags (See DICTIONARY_MERGE)|

Returns true.

### Dictionary_SkipRoot

Skips the root dictionary or list. If the dictionary is a dictionary container it will return the inner dictionary handle, otherwise it will return itself.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|DataDictionaryHandle|echandle*|Unrooted dictionary handle|

Returns true.

### Dictionary_SkipRootContainer

Skips the root dictionary or list. If the dictionary is a dictionary _or list_ container it will return the inner dictionary handle, otherwise it will return itself.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|DataDictionaryHandle|echandle*|Unrooted dictionary handle|

Returns true.

### Dictionary_Reset

Resets the contents of the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|

Returns true.

### Dictionary_Dump

Prints the contents of the dictionary to the debug log.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|

Returns true.

### Dictionary_SetCaseSensitive

Sets the case-sensitivity of the dictionary. Setting this value to true will cause searches for keys to be case-sensitive.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|CaseSensitive|int32_t|Boolean value|

Returns true.

### Dictionary_GetCaseSensitive

Gets the case-sensitivity of the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|CaseSensitive|int32_t*|Boolean value|

Returns true.

### Dictionary_SetAllowDuplicates

Sets duplicates to be allowed in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|AllowDuplicates|int32_t|Boolean value|

Returns true.

### Dictionary_GetAllowDuplicates

Gets whether or not duplicates are allowed in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|AllowDuplicates|int32_t*|Boolean value|

Returns true.

### Dictionary_ItemRemoveCallback

Callback that is called whenever an item is removed from a dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Handle to the item being removed|
|UserPtr|void*|User data pointer|
|Path|const char*|Full path to the item being removed|

Returns true.

### Dictionary_SetItemRemoveCallback

Sets the callback that gets triggered when an item is removed from the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|UserPtr|void*|User data pointer|
|Callback|ItemRemoveCallback|Callback function|

Returns true.

### Dictionary_GetItemRemoveCallback

Gets the callback that gets triggered when an item is removed from the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|UserPtr|void**|User data pointer|
|Callback|ItemRemoveCallback*|Callback function|

Returns true.

### Dictionary_ItemKeyChangeCallback

Callback that is called whenever an item's key is changed in a dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Handle to the item changed|
|UserPtr|void*|User data pointer|
|Path|const char*|Full path to the item changed|
|OldKey|const char*|Previous name of the item|

Returns true.

### Dictionary_SetItemKeyChangeCallback

Sets the callback that gets triggered when an item's key is changed in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|UserPtr|void*|User data pointer|
|Callback|ItemKeyChangeCallback|Callback function|

Returns true.

### Dictionary_GetItemKeyChangeCallback

Gets the callback that gets triggered when an item's key is changed in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|UserPtr|void**|User data pointer|
|Callback|ItemKeyChangeCallback*|Callback function|

Returns true.

### Dictionary_ItemValueChangeCallback

Callback that is called whenever an item's value is changed in a dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|ItemHandle|echandle|Handle to the item changed|
|UserPtr|void*|User data pointer|
|Path|const char*|Full path to the item changed|
|OldValue|const char*|Previous value of item|
|OldValueLength|int32_t|Length of previous value of item|

Returns true.

### Dictionary_SetItemValueChangeCallback

Sets the callback that gets triggered when an item's value is changed in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|UserPtr|void*|User data pointer|
|Callback|ItemValueChangeCallback|Callback function|

Returns true.

### Dictionary_GetItemValueChangeCallback

Gets the callback that gets triggered when an item's value is changed in the dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|
|UserPtr|void**|User data pointer|
|Callback|ItemValueChangeCallback*|Callback function|

Returns true.

### Dictionary_TranslateType

Translates a dictionary item type value into a string.

|Name|Type|Description|
|-|-|-|
|Type|int32_t|Item type (See DICTIONARY_TYPE)|

Returns the string of the type.

### Dictionary_PathGetKey

Gets the key for a item path.

_Input Path_
```
f1.f2.key1
```
_Search Structure_
```json
{ "f1": { "f2": { "key1": "val1" } } }
```
_Expected Key_
```
key1
```

|Name|Type|Description|
|-|-|-|
|Path|const char*|Item path|
|Key|char*|Key buffer|
|MaxKey|int32_t|Maximum length of key buffer|

Returns true if successful, false otherwise.

### Dictionary_PathSkipRoot

Skips the first item in a path.

_Input Path_
```
f1.f2.key1
```
_Expected Output Path_
```
f2.key1
````

|Name|Type|Description|
|-|-|-|
|Path|const char*|Item path|
|ChildPath|char*|Child path buffer|
|MaxChildPath|int32_t|Maximum length of child path buffer|

Returns true if successful, false otherwise.

### Dictionary_PathGetParent

Gets the parent path.

_Input Paths and Expected Output Paths_
```
f1.f2.key1 >> f1.f2
f1.f2 >> f1
```

|Name|Type|Description|
|-|-|-|
|Path|const char*|Item path|
|Parent|char*|Parent path buffer|
|MaxParent|int32_t|Maximum length of parent path buffer|

Returns true if successful, false otherwise.

### Dictionary_PathHasParent

Gets whether or not the path has a parent.

_Path Inputs and Expected Outputs_
```
f1.f2.key1 >> true
f1 >> false
key1 >> false
```

|Name|Type|Description|
|-|-|-|
|Path|const char*|Item path|

Returns true if item has parent, false otherwise.

### Dictionary_Create

Creates a new instance of a dictionary.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle*|Dictionary handle|

Returns true.

### Dictionary_AddRef

Increments the reference count of the dictionary by one.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle|Dictionary handle|

Returns handle to the dictionary instance.

### Dictionary_Release

Releases an instance of a dictionary when its reference count reaches zero. Decrements the reference count of the dictionary by one.

|Name|Type|Description|
|-|-|-|
|DictionaryHandle|echandle*|Dictionary handle|

Returns true.
