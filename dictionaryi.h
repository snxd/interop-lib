#ifndef _DICTIONARY_INTERFACE_H_
#define _DICTIONARY_INTERFACE_H_

/*********************************************************************/

#define IDICTIONARY_KEYRAW_MAX      (120)
#define IDICTIONARY_KEY_MAX         (IDICTIONARY_KEYRAW_MAX - 1)
#define IDICTIONARY_PATH_MAX        (4096)

#define IDICTIONARY_TYPE_UNKNOWN    (0)
#define IDICTIONARY_TYPE_NULL       (1)
#define IDICTIONARY_TYPE_BOOLEAN    (2)
#define IDICTIONARY_TYPE_INT64      (3)
#define IDICTIONARY_TYPE_FLOAT64    (4)
#define IDICTIONARY_TYPE_STRING     (5)
#define IDICTIONARY_TYPE_LIST       (6)
#define IDICTIONARY_TYPE_DICTIONARY (7)

/*********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************/

typedef int32 (*IDictionary_ItemFilterCallback)(echandle DictionaryHandle, void *UserPtr, echandle SourceDictionaryHandle, echandle SourceItemHandle);
typedef int32 (*IDictionary_ItemRemoveCallback)(echandle DictionaryHandle, echandle ItemHandle, void *UserPtr, char *Path);
typedef int32 (*IDictionary_ItemKeyChangeCallback)(echandle DictionaryHandle, echandle ItemHandle, void *UserPtr, char *Path, char *OldKey);
typedef int32 (*IDictionary_ItemValueChangeCallback)(echandle DictionaryHandle, echandle ItemHandle, void *UserPtr, char *Path, char *OldValue, int32 OldValueLength);

/*********************************************************************/

typedef struct IDictionaryVtbl {
    int32 (*GetParent)(echandle DictionaryHandle, echandle *ParentDictionaryHandle, echandle *ParentItemHandle);
    int32 (*Add)(echandle DictionaryHandle, char *Key, echandle *ItemHandle);
    int32 (*AddNull)(echandle DictionaryHandle, char *Key, echandle *ItemHandle);
    int32 (*AddString)(echandle DictionaryHandle, char *Key, char *Value, echandle *ItemHandle);
    int32 (*AddInt32)(echandle DictionaryHandle, char *Key, int32 Value, echandle *ItemHandle);
    int32 (*AddInt64)(echandle DictionaryHandle, char *Key, int64 Value, echandle *ItemHandle);
    int32 (*AddFloat64)(echandle DictionaryHandle, char *Key, float64 Value, echandle *ItemHandle);
    int32 (*AddBoolean)(echandle DictionaryHandle, char *Key, int32 Value, echandle *ItemHandle);
    int32 (*AddList)(echandle DictionaryHandle, char *Key, echandle *ListHandle, echandle *ItemHandle);
    int32 (*AddDictionary)(echandle DictionaryHandle, char *Key, echandle *DictHandle, echandle *ItemHandle);
    int32 (*Append)(echandle DictionaryHandle, char *Key, echandle *ItemHandle);
    int32 (*Insert)(echandle DictionaryHandle, echandle PrevItemHandle, char *Key, echandle *ItemHandle);
    int32 (*Remove)(echandle DictionaryHandle, echandle *ItemHandle);

    int32 (*ConvertFromString)(echandle DictionaryHandle, char *Value, int32 MaxValue, char KeyValueSeparator, char ItemSeparator);
    int32 (*ConvertToString)(echandle DictionaryHandle, char *Value, int32 MaxValue, char KeyValueSeparator, char ItemSeparator);

    int32 (*ContainsKey)(echandle DictionaryHandle, char *Key);
    int32 (*EnsureIndex)(echandle DictionaryHandle, int32 Index, echandle *ItemHandle);
    int32 (*EnsureListByIndex)(echandle DictionaryHandle, int32 Index, echandle *ItemHandle, echandle *ItemDictionaryHandle);
    int32 (*EnsureDictionaryByIndex)(echandle DictionaryHandle, int32 Index, echandle *ItemHandle, echandle *ItemDictionaryHandle);
    int32 (*EnsureKey)(echandle DictionaryHandle, char *Key, echandle *ItemHandle);
    int32 (*EnsureList)(echandle DictionaryHandle, char *Key, echandle *ItemHandle, echandle *ItemDictionaryHandle);
    int32 (*EnsureDictionary)(echandle DictionaryHandle, char *Key, echandle *ItemHandle, echandle *ItemDictionaryHandle);
    int32 (*GetTypeByKey)(echandle DictionaryHandle, char *Key, int32 *Type);
    int32 (*SetStringByKey)(echandle DictionaryHandle, char *Key, char *String);
    int32 (*GetStringByKey)(echandle DictionaryHandle, char *Key, char *String, int32 MaxString);
    int32 (*SetStringByKeyV)(echandle DictionaryHandle, char *Key, char *String, va_list ArgumentList);
    int32 (*GetStringPtrByKey)(echandle DictionaryHandle, char *Key, char **StringPtr);
    int32 (*GetBufferPtrByKey)(echandle DictionaryHandle, char *Key, char **BufferPtr, int32 *BufferLength);
    int32 (*SetInt32ByKey)(echandle DictionaryHandle, char *Key, int32 Value);
    int32 (*GetInt32ByKey)(echandle DictionaryHandle, char *Key, int32 *Value);
    int32 (*SetInt64ByKey)(echandle DictionaryHandle, char *Key, int64 Value);
    int32 (*GetInt64ByKey)(echandle DictionaryHandle, char *Key, int64 *Value);
    int32 (*SetFloat64ByKey)(echandle DictionaryHandle, char *Key, float64 Value);
    int32 (*GetFloat64ByKey)(echandle DictionaryHandle, char *Key, float64 *Value);
    int32 (*SetBooleanByKey)(echandle DictionaryHandle, char *Key, int32 Value);
    int32 (*GetBooleanByKey)(echandle DictionaryHandle, char *Key, int32 *Value);
    int32 (*GetListByIndex)(echandle DictionaryHandle, int32 Index, echandle *ItemDictionaryHandle);
    int32 (*GetDictionaryByIndex)(echandle DictionaryHandle, int32 Index, echandle *ItemDictionaryHandle);
    int32 (*GetListByKey)(echandle DictionaryHandle, char *Key, echandle *ItemDictionaryHandle);
    int32 (*GetDictionaryByKey)(echandle DictionaryHandle, char *Key, echandle *ItemDictionaryHandle);
    int32 (*RemoveByKey)(echandle DictionaryHandle, char *Key);

    int32 (*ItemGetPath)(echandle DictionaryHandle, echandle ItemHandle, echandle TopDictionaryHandle, char *Path, int32 MaxPath);
    int32 (*ItemIsContainer)(echandle DictionaryHandle, echandle ItemHandle);
    int32 (*ItemIsNull)(echandle DictionaryHandle, echandle ItemHandle);
    int32 (*ItemGetIndex)(echandle DictionaryHandle, echandle ItemHandle, int32 *Index);
    int32 (*ItemSetType)(echandle DictionaryHandle, echandle ItemHandle, int32 Type);
    int32 (*ItemGetType)(echandle DictionaryHandle, echandle ItemHandle, int32 *Type);
    int32 (*ItemCompareType)(echandle DictionaryHandle, echandle ItemHandle, int32 Type);
    int32 (*ItemSetKey)(echandle DictionaryHandle, echandle ItemHandle, char *Key);
    int32 (*ItemSetKeyLength)(echandle DictionaryHandle, echandle ItemHandle, char *Key, int32 KeyLength);
    int32 (*ItemGetKey)(echandle DictionaryHandle, echandle ItemHandle, char *Key, int32 MaxKey);
    int32 (*ItemGetKeyPtr)(echandle DictionaryHandle, echandle ItemHandle, char **KeyPtr);
    int32 (*ItemSetString)(echandle DictionaryHandle, echandle ItemHandle, char *String);
    int32 (*ItemSetStringV)(echandle DictionaryHandle, echandle ItemHandle, char *String, va_list ArgumentList);
    int32 (*ItemGetString)(echandle DictionaryHandle, echandle ItemHandle, char *String, int32 MaxString);
    int32 (*ItemGetStringPtr)(echandle DictionaryHandle, echandle ItemHandle, char **StringPtr);
    int32 (*ItemSetBuffer)(echandle DictionaryHandle, echandle ItemHandle, char *Buffer, int32 BufferLength);
    int32 (*ItemGetBufferPtr)(echandle DictionaryHandle, echandle ItemHandle, char **BufferPtr, int32 *BufferLength);
    int32 (*ItemSetFloat64)(echandle DictionaryHandle, echandle ItemHandle, float64 Value);
    int32 (*ItemGetFloat64)(echandle DictionaryHandle, echandle ItemHandle, float64 *Value);
    int32 (*ItemSetInt32)(echandle DictionaryHandle, echandle ItemHandle, int32 Value);
    int32 (*ItemGetInt32)(echandle DictionaryHandle, echandle ItemHandle, int32 *Value);
    int32 (*ItemSetInt64)(echandle DictionaryHandle, echandle ItemHandle, int64 Value);
    int32 (*ItemGetInt64)(echandle DictionaryHandle, echandle ItemHandle, int64 *Value);
    int32 (*ItemSetBoolean)(echandle DictionaryHandle, echandle ItemHandle, int32 Value);
    int32 (*ItemGetBoolean)(echandle DictionaryHandle, echandle ItemHandle, int32 *Value);
    int32 (*ItemSetNull)(echandle DictionaryHandle, echandle ItemHandle);
    int32 (*ItemGetDictionaryHandle)(echandle DictionaryHandle, echandle ItemHandle, echandle *DictHandle);
    int32 (*ItemFindByPath)(echandle DictionaryHandle, char *Path, echandle *ItemDictionaryHandle, echandle *ItemHandle);
    int32 (*ItemFindByKey)(echandle DictionaryHandle, char *Key, echandle StartItemHandle, echandle *ItemHandle);
    int32 (*ItemFindByBuffer)(echandle DictionaryHandle, char *Buffer, int32 BufferLength, echandle StartItemHandle, echandle *ItemHandle);
    int32 (*ItemFindByIndex)(echandle DictionaryHandle, int32 Index, echandle StartItemHandle, echandle *ItemHandle);
    int32 (*ItemGetNext)(echandle DictionaryHandle, echandle ItemHandle, echandle *NextItemHandle);
    int32 (*ItemGetPrev)(echandle DictionaryHandle, echandle ItemHandle, echandle *PrevItemHandle);
    int32 (*ItemGetFirst)(echandle DictionaryHandle, echandle *ItemHandle);
    int32 (*ItemGetLast)(echandle DictionaryHandle, echandle *ItemHandle);
    int32 (*ItemGetCount)(echandle DictionaryHandle, int32 *ItemCount);

    int32 (*Print)(echandle DictionaryHandle, char *Format, ...);
    int32 (*PrintTabbed)(echandle DictionaryHandle, int32 Depth, char *Format, ...);
    int32 (*SetPrintCallback)(echandle DictionaryHandle, echandle PrintHandle, Generic_PrintCallback Callback);
    int32 (*GetPrintCallback)(echandle DictionaryHandle, echandle *PrintHandle, Generic_PrintCallback *Callback);

    int32 (*Sync)(echandle TargetDictionaryHandle, echandle SourceDictionaryHandle, void *FilterUserPtr, IDictionary_ItemFilterCallback FilterCallback);
    int32 (*SyncAt)(echandle TargetDictionaryHandle, echandle SourceDictionaryHandle, echandle SourceItemHandle, void *FilterUserPtr, IDictionary_ItemFilterCallback FilterCallback);
    int32 (*RemoveMissing)(echandle TargetDictionaryHandle, echandle SourceDictionaryHandle);

    int32 (*Merge)(echandle TargetDictionaryHandle, echandle SourceDictionaryHandle, int32 OverwriteExisting);
    int32 (*MergeAt)(echandle TargetDictionaryHandle, echandle SourceDictionaryHandle, echandle SourceItemHandle, int32 Flags);
    int32 (*SkipRoot)(echandle DictionaryHandle, echandle *DataDictionaryHandle);
    int32 (*Reset)(echandle DictionaryHandle);
    int32 (*Dump)(echandle DictionaryHandle);

    int32 (*SetCaseSensitive)(echandle DictionaryHandle, int32 CaseSensitive);
    int32 (*GetCaseSensitive)(echandle DictionaryHandle, int32 *CaseSensitive);
    int32 (*SetAllowDuplicates)(echandle DictionaryHandle, int32 AllowDuplicates);
    int32 (*GetAllowDuplicates)(echandle DictionaryHandle, int32 *AllowDuplicates);
    int32 (*SetStringPool)(echandle DictionaryHandle, int32 StringPool);
    int32 (*GetStringPool)(echandle DictionaryHandle, int32 *StringPool);
    int32 (*SetPoolChunkSize)(echandle DictionaryHandle, int32 ChunkSize);

    int32 (*SetItemRemoveCallback)(echandle DictionaryHandle, void *UserPtr, IDictionary_ItemRemoveCallback Callback);
    int32 (*GetItemRemoveCallback)(echandle DictionaryHandle, void **UserPtr, IDictionary_ItemRemoveCallback *Callback);
    int32 (*SetItemKeyChangeCallback)(echandle DictionaryHandle, void *UserPtr, IDictionary_ItemKeyChangeCallback Callback);
    int32 (*GetItemKeyChangeCallback)(echandle DictionaryHandle, void **UserPtr, IDictionary_ItemKeyChangeCallback *Callback);
    int32 (*SetItemValueChangeCallback)(echandle DictionaryHandle, void *UserPtr, IDictionary_ItemValueChangeCallback Callback);
    int32 (*GetItemValueChangeCallback)(echandle DictionaryHandle, void **UserPtr, IDictionary_ItemValueChangeCallback *Callback);

    // 5.2
    int32 (*MergeItem)(echandle TargetDictionaryHandle, echandle SourceDictionaryHandle, echandle SourceItemHandle, int32 Flags);
    int32 (*SetStringByKeyPrint)(echandle DictionaryHandle, char *Key, char *String, ...);
    int32 (*ItemSetStringPrint)(echandle DictionaryHandle, echandle ItemHandle, char *String, ...);
    int32 (*SetStringByPath)(echandle DictionaryHandle, char *Path, char *String);
    int32 (*GetStringByPath)(echandle DictionaryHandle, char *Path, char *String, int32 MaxString);
    int32 (*GetBufferPtrByPath)(echandle DictionaryHandle, char *Path, char **BufferPtr, int32 *BufferLength);
    int32 (*SetInt32ByPath)(echandle DictionaryHandle, char *Path, int32 Value);
    int32 (*GetInt32ByPath)(echandle DictionaryHandle, char *Path, int32 *Value);
    int32 (*SetInt64ByPath)(echandle DictionaryHandle, char *Path, int64 Value);
    int32 (*GetInt64ByPath)(echandle DictionaryHandle, char *Path, int64 *Value);
    int32 (*SetFloat64ByPath)(echandle DictionaryHandle, char *Path, float64 Value);
    int32 (*GetFloat64ByPath)(echandle DictionaryHandle, char *Path, float64 *Value);
    int32 (*SetBooleanByPath)(echandle DictionaryHandle, char *Path, int32 Value);
    int32 (*GetBooleanByPath)(echandle DictionaryHandle, char *Path, int32 *Value);
    int32 (*SkipRootContainer)(echandle DictionaryHandle, echandle *DataDictionaryHandle);
} IDictionaryVtbl;

/*********************************************************************/

#define IDictionary_GetParent(DictionaryHandle, ParentDictionaryHandle, ParentItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetParent(DictionaryHandle, ParentDictionaryHandle, ParentItemHandle)
#define IDictionary_Add(DictionaryHandle, Key, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->Add(DictionaryHandle, Key, ItemHandle)
#define IDictionary_AddNull(DictionaryHandle, Key, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->AddNull(DictionaryHandle, Key, ItemHandle)
#define IDictionary_AddString(DictionaryHandle, Key, Value, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->AddString(DictionaryHandle, Key, Value, ItemHandle)
#define IDictionary_AddInt32(DictionaryHandle, Key, Value, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->AddInt32(DictionaryHandle, Key, Value, ItemHandle)
#define IDictionary_AddInt64(DictionaryHandle, Key, Value, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->AddInt64(DictionaryHandle, Key, Value, ItemHandle)
#define IDictionary_AddFloat64(DictionaryHandle, Key, Value, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->AddFloat64(DictionaryHandle, Key, Value, ItemHandle)
#define IDictionary_AddBoolean(DictionaryHandle, Key, Value, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->AddBoolean(DictionaryHandle, Key, Value, ItemHandle)
#define IDictionary_AddList(DictionaryHandle, Key, ListHandle, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->AddList(DictionaryHandle, Key, ListHandle, ItemHandle)
#define IDictionary_AddDictionary(DictionaryHandle, Key, DictHandle, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->AddDictionary(DictionaryHandle, Key, DictHandle, ItemHandle)
#define IDictionary_Append(DictionaryHandle, Key, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->Append(DictionaryHandle, Key, ItemHandle)
#define IDictionary_Insert(DictionaryHandle, PrevItemHandle, Key, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->Insert(DictionaryHandle, PrevItemHandle, Key, ItemHandle)
#define IDictionary_Remove(DictionaryHandle, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->Remove(DictionaryHandle, ItemHandle)

#define IDictionary_ConvertFromString(DictionaryHandle, Value, MaxValue, KeyValueSeparator, ItemSeparator) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ConvertFromString(DictionaryHandle, Value, MaxValue, KeyValueSeparator, ItemSeparator)
#define IDictionary_ConvertToString(DictionaryHandle, Value, MaxValue, KeyValueSeparator, ItemSeparator) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ConvertToString(DictionaryHandle, Value, MaxValue, KeyValueSeparator, ItemSeparator)

#define IDictionary_ContainsKey(DictionaryHandle, Key) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ContainsKey(DictionaryHandle, Key)
#define IDictionary_EnsureIndex(DictionaryHandle, Index, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->EnsureIndex(DictionaryHandle, Index, ItemHandle)
#define IDictionary_EnsureListByIndex(DictionaryHandle, Index, ItemHandle, ItemDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->EnsureListByIndex(DictionaryHandle, Index, ItemHandle, ItemDictionaryHandle)
#define IDictionary_EnsureDictionaryByIndex(DictionaryHandle, Index, ItemHandle, ItemDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->EnsureDictionaryByIndex(DictionaryHandle, Index, ItemHandle, ItemDictionaryHandle)
#define IDictionary_EnsureKey(DictionaryHandle, Key, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->EnsureKey(DictionaryHandle, Key, ItemHandle)
#define IDictionary_EnsureList(DictionaryHandle, Key, ItemHandle, ItemDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->EnsureList(DictionaryHandle, Key, ItemHandle, ItemDictionaryHandle)
#define IDictionary_EnsureDictionary(DictionaryHandle, Key, ItemHandle, ItemDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->EnsureDictionary(DictionaryHandle, Key, ItemHandle, ItemDictionaryHandle)
#define IDictionary_GetTypeByKey(DictionaryHandle, Key, Type) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetTypeByKey(DictionaryHandle, Key, Type)
#define IDictionary_SetStringByKey(DictionaryHandle, Key, String) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetStringByKey(DictionaryHandle, Key, String)
#define IDictionary_SetStringByPath(DictionaryHandle, Path, String) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetStringByPath(DictionaryHandle, Path, String)
#define IDictionary_SetStringByKeyPrint(DictionaryHandle, Key, String, ...) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetStringByKeyPrint(DictionaryHandle, Key, String, __VA_ARGS__)
#define IDictionary_GetStringByKey(DictionaryHandle, Key, String, MaxString) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetStringByKey(DictionaryHandle, Key, String, MaxString)
#define IDictionary_GetStringByPath(DictionaryHandle, Path, String, MaxString) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetStringByPath(DictionaryHandle, Path, String, MaxString)
#define IDictionary_SetStringByKeyV(DictionaryHandle, Key, String, ArgumentList) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetStringByKeyV(DictionaryHandle, Key, String, ArgumentList)
#define IDictionary_GetStringPtrByKey(DictionaryHandle, Key, StringPtr) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetStringPtrByKey(DictionaryHandle, Key, StringPtr)
#define IDictionary_GetBufferPtrByKey(DictionaryHandle, Key, BufferPtr, BufferLength) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetBufferPtrByKey(DictionaryHandle, Key, BufferPtr, BufferLength)
#define IDictionary_GetBufferPtrByPath(DictionaryHandle, Path, BufferPtr, BufferLength) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetBufferPtrByPath(DictionaryHandle, Path, BufferPtr, BufferLength)
#define IDictionary_SetInt32ByKey(DictionaryHandle, Key, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetInt32ByKey(DictionaryHandle, Key, Value)
#define IDictionary_SetInt32ByPath(DictionaryHandle, Path, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetInt32ByPath(DictionaryHandle, Path, Value)
#define IDictionary_GetInt32ByKey(DictionaryHandle, Key, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetInt32ByKey(DictionaryHandle, Key, Value)
#define IDictionary_GetInt32ByPath(DictionaryHandle, Path, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetInt32ByPath(DictionaryHandle, Path, Value)
#define IDictionary_SetInt64ByKey(DictionaryHandle, Key, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetInt64ByKey(DictionaryHandle, Key, Value)
#define IDictionary_SetInt64ByPath(DictionaryHandle, Path, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetInt64ByPath(DictionaryHandle, Path, Value)
#define IDictionary_GetInt64ByKey(DictionaryHandle, Key, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetInt64ByKey(DictionaryHandle, Key, Value)
#define IDictionary_GetInt64ByPath(DictionaryHandle, Key, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetInt64ByPath(DictionaryHandle, Path, Value)
#define IDictionary_SetFloat64ByKey(DictionaryHandle, Key, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetFloat64ByKey(DictionaryHandle, Key, Value)
#define IDictionary_SetFloat64ByPath(DictionaryHandle, Path, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetFloat64ByPath(DictionaryHandle, Path, Value)
#define IDictionary_GetFloat64ByKey(DictionaryHandle, Key, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetFloat64ByKey(DictionaryHandle, Key, Value)
#define IDictionary_GetFloat64ByPath(DictionaryHandle, Path, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetFloat64ByPath(DictionaryHandle, Path, Value)
#define IDictionary_SetBooleanByKey(DictionaryHandle, Key, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetBooleanByKey(DictionaryHandle, Key, Value)
#define IDictionary_SetBooleanByPath(DictionaryHandle, Path, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetBooleanByPath(DictionaryHandle, Path, Value)
#define IDictionary_GetBooleanByKey(DictionaryHandle, Key, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetBooleanByKey(DictionaryHandle, Key, Value)
#define IDictionary_GetBooleanByPath(DictionaryHandle, Path, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetBooleanByPath(DictionaryHandle, Path, Value)
#define IDictionary_GetListByIndex(DictionaryHandle, Index, ItemDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetListByIndex(DictionaryHandle, Index, ItemDictionaryHandle)
#define IDictionary_GetDictionaryByIndex(DictionaryHandle, Index, ItemDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetDictionaryByIndex(DictionaryHandle, Index, ItemDictionaryHandle)
#define IDictionary_GetListByKey(DictionaryHandle, Key, ItemDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetListByKey(DictionaryHandle, Key, ItemDictionaryHandle)
#define IDictionary_GetDictionaryByKey(DictionaryHandle, Key, ItemDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetDictionaryByKey(DictionaryHandle, Key, ItemDictionaryHandle)
#define IDictionary_RemoveByKey(DictionaryHandle, Key) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->RemoveByKey(DictionaryHandle, Key)

#define IDictionary_ItemGetPath(DictionaryHandle, ItemHandle, TopDictionaryHandle, Path, MaxPath) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetPath(DictionaryHandle, ItemHandle, TopDictionaryHandle, Path, MaxPath)
#define IDictionary_ItemIsContainer(DictionaryHandle, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetPath(DictionaryHandle, ItemHandle)
#define IDictionary_ItemIsNull(DictionaryHandle, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemIsNull(DictionaryHandle, ItemHandle)
#define IDictionary_ItemGetIndex(DictionaryHandle, ItemHandle, Index) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetIndex(DictionaryHandle, ItemHandle, Index)
#define IDictionary_ItemSetType(DictionaryHandle, ItemHandle, Type) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemSetType(DictionaryHandle, ItemHandle, Type)
#define IDictionary_ItemGetType(DictionaryHandle, ItemHandle, Type) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetType(DictionaryHandle, ItemHandle, Type)
#define IDictionary_ItemCompareType(DictionaryHandle, ItemHandle, Type) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemCompareType(DictionaryHandle, ItemHandle, Type)
#define IDictionary_ItemSetKey(DictionaryHandle, ItemHandle, Key) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemSetKey(DictionaryHandle, ItemHandle, Key)
#define IDictionary_ItemSetKeyLength(DictionaryHandle, ItemHandle, Key, KeyLength) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemSetKeyLength(DictionaryHandle, ItemHandle, Key, KeyLength)
#define IDictionary_ItemGetKey(DictionaryHandle, ItemHandle, Key, MaxKey) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetKey(DictionaryHandle, ItemHandle, Key, MaxKey)
#define IDictionary_ItemGetKeyPtr(DictionaryHandle, ItemHandle, KeyPtr) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetKeyPtr(DictionaryHandle, ItemHandle, KeyPtr)
#define IDictionary_ItemSetString(DictionaryHandle, ItemHandle, String) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemSetString(DictionaryHandle, ItemHandle, String)
#define IDictionary_ItemSetStringPrint(DictionaryHandle, ItemHandle, String, ...) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemSetStringPrint(DictionaryHandle, ItemHandle, String, __VA_ARGS__)
#define IDictionary_ItemSetStringV(DictionaryHandle, ItemHandle, String, ArgumentList) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemSetStringV(DictionaryHandle, ItemHandle, String, ArgumentList)
#define IDictionary_ItemGetString(DictionaryHandle, ItemHandle, String, MaxString) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetString(DictionaryHandle, ItemHandle, String, MaxString)
#define IDictionary_ItemGetStringPtr(DictionaryHandle, ItemHandle, StringPtr) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetStringPtr(DictionaryHandle, ItemHandle, StringPtr)
#define IDictionary_ItemSetBuffer(DictionaryHandle, ItemHandle, Buffer, BufferLength) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemSetBuffer(DictionaryHandle, ItemHandle, Buffer, BufferLength)
#define IDictionary_ItemGetBufferPtr(DictionaryHandle, ItemHandle, BufferPtr, BufferLength) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetBufferPtr(DictionaryHandle, ItemHandle, BufferPtr, BufferLength)
#define IDictionary_ItemSetFloat64(DictionaryHandle, ItemHandle, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemSetFloat64(DictionaryHandle, ItemHandle, Value)
#define IDictionary_ItemGetFloat64(DictionaryHandle, ItemHandle, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetFloat64(DictionaryHandle, ItemHandle, Value)
#define IDictionary_ItemSetInt32(DictionaryHandle, ItemHandle, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemSetInt32(DictionaryHandle, ItemHandle, Value)
#define IDictionary_ItemGetInt32(DictionaryHandle, ItemHandle, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetInt32(DictionaryHandle, ItemHandle, Value)
#define IDictionary_ItemSetInt64(DictionaryHandle, ItemHandle, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemSetInt64(DictionaryHandle, ItemHandle, Value)
#define IDictionary_ItemGetInt64(DictionaryHandle, ItemHandle, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetInt64(DictionaryHandle, ItemHandle, Value)
#define IDictionary_ItemSetBoolean(DictionaryHandle, ItemHandle, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemSetBoolean(DictionaryHandle, ItemHandle, Value)
#define IDictionary_ItemGetBoolean(DictionaryHandle, ItemHandle, Value) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetBoolean(DictionaryHandle, ItemHandle, Value)
#define IDictionary_ItemSetNull(DictionaryHandle, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemSetNull(DictionaryHandle, ItemHandle)
#define IDictionary_ItemGetDictionaryHandle(DictionaryHandle, ItemHandle, DictHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetDictionaryHandle(DictionaryHandle, ItemHandle, DictHandle)
#define IDictionary_ItemFindByPath(DictionaryHandle, Path, ItemDictionaryHandle, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemFindByPath(DictionaryHandle, Path, ItemDictionaryHandle, ItemHandle)
#define IDictionary_ItemFindByKey(DictionaryHandle, Key, StartItemHandle, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemFindByKey(DictionaryHandle, Key, StartItemHandle, ItemHandle)
#define IDictionary_ItemFindByBuffer(DictionaryHandle, Buffer, BufferLength, StartItemHandle, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemFindByBuffer(DictionaryHandle, Buffer, BufferLength, StartItemHandle, ItemHandle)
#define IDictionary_ItemFindByIndex(DictionaryHandle, Index, BufferLength, StartItemHandle, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemFindByIndex(DictionaryHandle, Index, BufferLength, StartItemHandle, ItemHandle)
#define IDictionary_ItemGetNext(DictionaryHandle, ItemHandle, NextItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetNext(DictionaryHandle, ItemHandle, NextItemHandle)
#define IDictionary_ItemGetPrev(DictionaryHandle, ItemHandle, PrevItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetPrev(DictionaryHandle, ItemHandle, PrevItemHandle)
#define IDictionary_ItemGetFirst(DictionaryHandle, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetFirst(DictionaryHandle, ItemHandle)
#define IDictionary_ItemGetLast(DictionaryHandle, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetLast(DictionaryHandle, ItemHandle)
#define IDictionary_ItemGetCount(DictionaryHandle, ItemCount) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetCount(DictionaryHandle, ItemCount)

#define IDictionary_Print(DictionaryHandle, Format, ...) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->Print(DictionaryHandle, Format, __VA_ARGS__)
#define IDictionary_PrintTabbed(DictionaryHandle, Depth, Format, ...) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->PrintTabbed(DictionaryHandle, Depth, Format, __VA_ARGS__)
#define IDictionary_SetPrintCallback(DictionaryHandle, PrintHandle, Callback) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetPrintCallback(DictionaryHandle, PrintHandle, Callback)
#define IDictionary_GetPrintCallback(DictionaryHandle, PrintHandle, Callback) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetPrintCallback(DictionaryHandle, PrintHandle, Callback)

#define IDictionary_Sync(TargetDictionaryHandle, SourceDictionaryHandle, FilterUserPtr, FilterCallback) \
    Class_VtblCast(TargetDictionaryHandle, IDictionaryVtbl)->Sync(TargetDictionaryHandle, SourceDictionaryHandle, FilterUserPtr, FilterCallback)
#define IDictionary_SyncAt(TargetDictionaryHandle, SourceDictionaryHandle, SourceItemHandle, FilterUserPtr, FilterCallback) \
    Class_VtblCast(TargetDictionaryHandle, IDictionaryVtbl)->SyncAt(TargetDictionaryHandle, SourceDictionaryHandle, SourceItemHandle, FilterUserPtr, FilterCallback)
#define IDictionary_RemoveMissing(TargetDictionaryHandle, SourceDictionaryHandle) \
    Class_VtblCast(TargetDictionaryHandle, IDictionaryVtbl)->RemoveMissing(TargetDictionaryHandle, SourceDictionaryHandle)
#define IDictionary_Merge(TargetDictionaryHandle, SourceDictionaryHandle, OverwriteExisting) \
    Class_VtblCast(TargetDictionaryHandle, IDictionaryVtbl)->Merge(TargetDictionaryHandle, SourceDictionaryHandle, OverwriteExisting)
#define IDictionary_MergeAt(TargetDictionaryHandle, SourceDictionaryHandle, SourceItemHandle, Flags) \
    Class_VtblCast(TargetDictionaryHandle, IDictionaryVtbl)->MergeAt(TargetDictionaryHandle, SourceDictionaryHandle, SourceItemHandle, Flags)
#define IDictionary_MergeItem(TargetDictionaryHandle, SourceDictionaryHandle, SourceItemHandle, Flags) \
    Class_VtblCast(TargetDictionaryHandle, IDictionaryVtbl)->MergeItem(TargetDictionaryHandle, SourceDictionaryHandle, SourceItemHandle, Flags)
#define IDictionary_SkipRoot(DictionaryHandle, DataDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SkipRoot(DictionaryHandle, DataDictionaryHandle)
#define IDictionary_SkipRootContainer(DictionaryHandle, DataDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SkipRootContainer(DictionaryHandle, DataDictionaryHandle)
#define IDictionary_Reset(DictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->Reset(DictionaryHandle)
#define IDictionary_Dump(DictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->Dump(DictionaryHandle)

#define IDictionary_SetCaseSensitive(DictionaryHandle, CaseSensitive) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetCaseSensitive(DictionaryHandle, CaseSensitive)
#define IDictionary_GetCaseSensitive(DictionaryHandle, CaseSensitive) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetCaseSensitive(DictionaryHandle, CaseSensitive)
#define IDictionary_SetAllowDuplicates(DictionaryHandle, AllowDuplicates) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetAllowDuplicates(DictionaryHandle, AllowDuplicates)
#define IDictionary_GetAllowDuplicates(DictionaryHandle, AllowDuplicates) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetAllowDuplicatese(DictionaryHandle, AllowDuplicates)
#define IDictionary_SetStringPool(DictionaryHandle, StringPool) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetStringPool(DictionaryHandle, StringPool)
#define IDictionary_GetStringPool(DictionaryHandle, StringPool) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetStringPoole(DictionaryHandle, StringPool)
#define IDictionary_SetPoolChunkSize(DictionaryHandle, PoolChunkSize) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetPoolChunkSize(DictionaryHandle, PoolChunkSize)

#define IDictionary_SetItemRemoveCallback(DictionaryHandle, UserPtr, Callback) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetItemRemoveCallback(DictionaryHandle, UserPtr, Callback)
#define IDictionary_GetItemRemoveCallback(DictionaryHandle, UserPtr, Callback) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetItemRemoveCallback(DictionaryHandle, UserPtr, Callback)
#define IDictionary_SetItemKeyChangeCallback(DictionaryHandle, UserPtr, Callback) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetItemKeyChangeCallback(DictionaryHandle, UserPtr, Callback)
#define IDictionary_GetItemKeyChangeCallback(DictionaryHandle, UserPtr, Callback) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetItemKeyChangeCallback(DictionaryHandle, UserPtr, Callback)
#define IDictionary_SetItemValueChangeCallback(DictionaryHandle, UserPtr, Callback) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetItemValueChangeCallback(DictionaryHandle, UserPtr, Callback)
#define IDictionary_GetItemValueChangeCallback(DictionaryHandle, UserPtr, Callback) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetItemValueChangeCallback(DictionaryHandle, UserPtr, Callback)
#define IDictionary_Create(DictionaryHandle) \
    Dictionary_Create(DictionaryHandle)
#define IDictionary_Delete(DictionaryHandle) \
    Dictionary_Delete(DictionaryHandle)

/*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
