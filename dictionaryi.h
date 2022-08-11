#ifndef CORE_DICTIONARYI_H_
#define CORE_DICTIONARYI_H_

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

typedef bool (*IDictionary_ItemFilterCallback)(echandle DictionaryHandle, void *UserPtr,
                                               echandle SourceDictionaryHandle, echandle SourceItemHandle);
typedef bool (*IDictionary_ItemRemoveCallback)(echandle DictionaryHandle, echandle ItemHandle, void *UserPtr,
                                               const char *Path);
typedef bool (*IDictionary_ItemKeyChangeCallback)(echandle DictionaryHandle, echandle ItemHandle, void *UserPtr,
                                                  const char *Path, const char *OldKey);
typedef bool (*IDictionary_ItemValueChangeCallback)(echandle DictionaryHandle, echandle ItemHandle, void *UserPtr,
                                                    const char *Path, const char *OldValue, int32_t OldValueLength);

/*********************************************************************/

typedef struct IDictionaryVtbl {
    bool (*GetParent)(echandle DictionaryHandle, echandle *ParentDictionaryHandle, echandle *ParentItemHandle);
    bool (*Add)(echandle DictionaryHandle, const char *Key, echandle *ItemHandle);
    bool (*AddNull)(echandle DictionaryHandle, const char *Key, echandle *ItemHandle);
    bool (*AddString)(echandle DictionaryHandle, const char *Key, const char *Value, echandle *ItemHandle);
    bool (*AddInt32)(echandle DictionaryHandle, const char *Key, int32_t Value, echandle *ItemHandle);
    bool (*AddInt64)(echandle DictionaryHandle, const char *Key, int64_t Value, echandle *ItemHandle);
    bool (*AddFloat64)(echandle DictionaryHandle, const char *Key, float64_t Value, echandle *ItemHandle);
    bool (*AddBoolean)(echandle DictionaryHandle, const char *Key, bool Value, echandle *ItemHandle);
    bool (*AddList)(echandle DictionaryHandle, const char *Key, echandle *ListHandle, echandle *ItemHandle);
    bool (*AddDictionary)(echandle DictionaryHandle, const char *Key, echandle *DictHandle, echandle *ItemHandle);
    bool (*Append)(echandle DictionaryHandle, const char *Key, echandle *ItemHandle);
    bool (*Insert)(echandle DictionaryHandle, echandle PrevItemHandle, const char *Key, echandle *ItemHandle);
    bool (*Remove)(echandle DictionaryHandle, echandle *ItemHandle);

    bool (*ConvertFromString)(echandle DictionaryHandle, const char *Value, int32_t MaxValue, char KeyValueSeparator,
                              char ItemSeparator);
    bool (*ConvertToString)(echandle DictionaryHandle, char *Value, int32_t MaxValue, char KeyValueSeparator,
                            char ItemSeparator);

    bool (*ContainsKey)(echandle DictionaryHandle, const char *Key);
    bool (*EnsureIndex)(echandle DictionaryHandle, int32_t Index, echandle *ItemHandle);
    bool (*EnsureListByIndex)(echandle DictionaryHandle, int32_t Index, echandle *ItemHandle,
                              echandle *ItemDictionaryHandle);
    bool (*EnsureDictionaryByIndex)(echandle DictionaryHandle, int32_t Index, echandle *ItemHandle,
                                    echandle *ItemDictionaryHandle);
    bool (*EnsureKey)(echandle DictionaryHandle, const char *Key, echandle *ItemHandle);
    bool (*EnsureList)(echandle DictionaryHandle, const char *Key, echandle *ItemHandle,
                       echandle *ItemDictionaryHandle);
    bool (*EnsureDictionary)(echandle DictionaryHandle, const char *Key, echandle *ItemHandle,
                             echandle *ItemDictionaryHandle);
    bool (*GetTypeByKey)(echandle DictionaryHandle, const char *Key, int32_t *Type);
    bool (*SetStringByKey)(echandle DictionaryHandle, const char *Key, const char *String);
    bool (*GetStringByKey)(echandle DictionaryHandle, const char *Key, char *String, int32_t MaxString);
    bool (*SetStringByKeyV)(echandle DictionaryHandle, const char *Key, const char *String, va_list ArgumentList);
    bool (*GetStringPtrByKey)(echandle DictionaryHandle, const char *Key, const char **StringPtr);
    bool (*GetBufferPtrByKey)(echandle DictionaryHandle, const char *Key, const char **BufferPtr,
                              int32_t *BufferLength);
    bool (*SetInt32ByKey)(echandle DictionaryHandle, const char *Key, int32_t Value);
    bool (*GetInt32ByKey)(echandle DictionaryHandle, const char *Key, int32_t *Value);
    bool (*SetInt64ByKey)(echandle DictionaryHandle, const char *Key, int64_t Value);
    bool (*GetInt64ByKey)(echandle DictionaryHandle, const char *Key, int64_t *Value);
    bool (*SetFloat64ByKey)(echandle DictionaryHandle, const char *Key, float64_t Value);
    bool (*GetFloat64ByKey)(echandle DictionaryHandle, const char *Key, float64_t *Value);
    bool (*SetBooleanByKey)(echandle DictionaryHandle, const char *Key, bool Value);
    bool (*GetBooleanByKey)(echandle DictionaryHandle, const char *Key, bool *Value);
    bool (*GetListByIndex)(echandle DictionaryHandle, int32_t Index, echandle *ItemDictionaryHandle);
    bool (*GetDictionaryByIndex)(echandle DictionaryHandle, int32_t Index, echandle *ItemDictionaryHandle);
    bool (*GetListByKey)(echandle DictionaryHandle, const char *Key, echandle *ItemDictionaryHandle);
    bool (*GetDictionaryByKey)(echandle DictionaryHandle, const char *Key, echandle *ItemDictionaryHandle);
    bool (*RemoveByKey)(echandle DictionaryHandle, const char *Key);

    bool (*ItemGetPath)(echandle DictionaryHandle, echandle ItemHandle, echandle TopDictionaryHandle, char *Path,
                        int32_t MaxPath);
    bool (*ItemIsContainer)(echandle DictionaryHandle, echandle ItemHandle);
    bool (*ItemIsNull)(echandle DictionaryHandle, echandle ItemHandle);
    bool (*ItemGetIndex)(echandle DictionaryHandle, echandle ItemHandle, int32_t *Index);
    bool (*ItemSetType)(echandle DictionaryHandle, echandle ItemHandle, int32_t Type);
    bool (*ItemGetType)(echandle DictionaryHandle, echandle ItemHandle, int32_t *Type);
    bool (*ItemCompareType)(echandle DictionaryHandle, echandle ItemHandle, int32_t Type);
    bool (*ItemSetKey)(echandle DictionaryHandle, echandle ItemHandle, const char *Key);
    bool (*ItemSetKeyLength)(echandle DictionaryHandle, echandle ItemHandle, const char *Key, int32_t KeyLength);
    bool (*ItemGetKey)(echandle DictionaryHandle, echandle ItemHandle, char *Key, int32_t MaxKey);
    bool (*ItemGetKeyPtr)(echandle DictionaryHandle, echandle ItemHandle, const char **KeyPtr);
    bool (*ItemSetString)(echandle DictionaryHandle, echandle ItemHandle, const char *String);
    bool (*ItemSetStringV)(echandle DictionaryHandle, echandle ItemHandle, const char *String, va_list ArgumentList);
    bool (*ItemGetString)(echandle DictionaryHandle, echandle ItemHandle, char *String, int32_t MaxString);
    bool (*ItemGetStringPtr)(echandle DictionaryHandle, echandle ItemHandle, const char **StringPtr);
    bool (*ItemSetBuffer)(echandle DictionaryHandle, echandle ItemHandle, const char *Buffer, int32_t BufferLength);
    bool (*ItemGetBufferPtr)(echandle DictionaryHandle, echandle ItemHandle, const char **BufferPtr,
                             int32_t *BufferLength);
    bool (*ItemSetFloat64)(echandle DictionaryHandle, echandle ItemHandle, float64_t Value);
    bool (*ItemGetFloat64)(echandle DictionaryHandle, echandle ItemHandle, float64_t *Value);
    bool (*ItemSetInt32)(echandle DictionaryHandle, echandle ItemHandle, int32_t Value);
    bool (*ItemGetInt32)(echandle DictionaryHandle, echandle ItemHandle, int32_t *Value);
    bool (*ItemSetInt64)(echandle DictionaryHandle, echandle ItemHandle, int64_t Value);
    bool (*ItemGetInt64)(echandle DictionaryHandle, echandle ItemHandle, int64_t *Value);
    bool (*ItemSetBoolean)(echandle DictionaryHandle, echandle ItemHandle, bool Value);
    bool (*ItemGetBoolean)(echandle DictionaryHandle, echandle ItemHandle, bool *Value);
    bool (*ItemSetNull)(echandle DictionaryHandle, echandle ItemHandle);
    bool (*ItemGetDictionaryHandle)(echandle DictionaryHandle, echandle ItemHandle, echandle *DictHandle);
    bool (*ItemFindByPath)(echandle DictionaryHandle, const char *Path, echandle *ItemDictionaryHandle,
                           echandle *ItemHandle);
    bool (*ItemFindByKey)(echandle DictionaryHandle, const char *Key, echandle StartItemHandle, echandle *ItemHandle);
    bool (*ItemFindByBuffer)(echandle DictionaryHandle, const char *Buffer, int32_t BufferLength,
                             echandle StartItemHandle, echandle *ItemHandle);
    bool (*ItemFindByIndex)(echandle DictionaryHandle, int32_t Index, echandle StartItemHandle, echandle *ItemHandle);
    bool (*ItemGetNext)(echandle DictionaryHandle, echandle ItemHandle, echandle *NextItemHandle);
    bool (*ItemGetPrev)(echandle DictionaryHandle, echandle ItemHandle, echandle *PrevItemHandle);
    bool (*ItemGetFirst)(echandle DictionaryHandle, echandle *ItemHandle);
    bool (*ItemGetLast)(echandle DictionaryHandle, echandle *ItemHandle);
    bool (*ItemGetCount)(echandle DictionaryHandle, int32_t *ItemCount);

    bool (*Print)(echandle DictionaryHandle, const char *Format, ...);
    bool (*PrintTabbed)(echandle DictionaryHandle, int32_t Depth, const char *Format, ...);
    bool (*SetPrintCallback)(echandle DictionaryHandle, echandle PrintHandle, Generic_PrintCallback Callback);
    bool (*GetPrintCallback)(echandle DictionaryHandle, echandle *PrintHandle, Generic_PrintCallback *Callback);

    bool (*Sync)(echandle TargetDictionaryHandle, echandle SourceDictionaryHandle, void *FilterUserPtr,
                 IDictionary_ItemFilterCallback FilterCallback);
    bool (*SyncAt)(echandle TargetDictionaryHandle, echandle SourceDictionaryHandle, echandle SourceItemHandle,
                   void *FilterUserPtr, IDictionary_ItemFilterCallback FilterCallback);
    bool (*RemoveMissing)(echandle TargetDictionaryHandle, echandle SourceDictionaryHandle);

    bool (*Merge)(echandle TargetDictionaryHandle, echandle SourceDictionaryHandle, int32_t OverwriteExisting);
    bool (*MergeAt)(echandle TargetDictionaryHandle, echandle SourceDictionaryHandle, echandle SourceItemHandle,
                    int32_t Flags);
    bool (*SkipRoot)(echandle DictionaryHandle, echandle *DataDictionaryHandle);
    bool (*Reset)(echandle DictionaryHandle);
    bool (*Dump)(echandle DictionaryHandle);

    bool (*SetCaseSensitive)(echandle DictionaryHandle, bool CaseSensitive);
    bool (*GetCaseSensitive)(echandle DictionaryHandle, bool *CaseSensitive);
    bool (*SetAllowDuplicates)(echandle DictionaryHandle, bool AllowDuplicates);
    bool (*GetAllowDuplicates)(echandle DictionaryHandle, bool *AllowDuplicates);
    bool (*SetStringPool)(echandle DictionaryHandle, bool StringPool);
    bool (*GetStringPool)(echandle DictionaryHandle, bool *StringPool);
    bool (*SetPoolChunkSize)(echandle DictionaryHandle, int32_t ChunkSize);

    bool (*SetItemRemoveCallback)(echandle DictionaryHandle, void *UserPtr, IDictionary_ItemRemoveCallback Callback);
    bool (*GetItemRemoveCallback)(echandle DictionaryHandle, void **UserPtr, IDictionary_ItemRemoveCallback *Callback);
    bool (*SetItemKeyChangeCallback)(echandle DictionaryHandle, void *UserPtr,
                                     IDictionary_ItemKeyChangeCallback Callback);
    bool (*GetItemKeyChangeCallback)(echandle DictionaryHandle, void **UserPtr,
                                     IDictionary_ItemKeyChangeCallback *Callback);
    bool (*SetItemValueChangeCallback)(echandle DictionaryHandle, void *UserPtr,
                                       IDictionary_ItemValueChangeCallback Callback);
    bool (*GetItemValueChangeCallback)(echandle DictionaryHandle, void **UserPtr,
                                       IDictionary_ItemValueChangeCallback *Callback);

    bool (*MergeItem)(echandle TargetDictionaryHandle, echandle SourceDictionaryHandle, echandle SourceItemHandle,
                      int32_t Flags);
    bool (*SetStringByKeyPrint)(echandle DictionaryHandle, const char *Key, const char *String, ...);
    bool (*ItemSetStringPrint)(echandle DictionaryHandle, echandle ItemHandle, const char *String, ...);
    bool (*SetStringByPath)(echandle DictionaryHandle, const char *Path, const char *String);
    bool (*GetStringByPath)(echandle DictionaryHandle, const char *Path, char *String, int32_t MaxString);
    bool (*GetBufferPtrByPath)(echandle DictionaryHandle, const char *Path, const char **BufferPtr,
                               int32_t *BufferLength);
    bool (*SetInt32ByPath)(echandle DictionaryHandle, const char *Path, int32_t Value);
    bool (*GetInt32ByPath)(echandle DictionaryHandle, const char *Path, int32_t *Value);
    bool (*SetInt64ByPath)(echandle DictionaryHandle, const char *Path, int64_t Value);
    bool (*GetInt64ByPath)(echandle DictionaryHandle, const char *Path, int64_t *Value);
    bool (*SetFloat64ByPath)(echandle DictionaryHandle, const char *Path, float64_t Value);
    bool (*GetFloat64ByPath)(echandle DictionaryHandle, const char *Path, float64_t *Value);
    bool (*SetBooleanByPath)(echandle DictionaryHandle, const char *Path, bool Value);
    bool (*GetBooleanByPath)(echandle DictionaryHandle, const char *Path, bool *Value);
    bool (*SkipRootContainer)(echandle DictionaryHandle, echandle *DataDictionaryHandle);
    bool (*ItemSetPrivate)(echandle DictionaryHandle, echandle ItemHandle, bool Private);
    bool (*ItemGetPrivate)(echandle DictionaryHandle, echandle ItemHandle, bool *Private);
    bool (*SetPrivateKeys)(echandle DictionaryHandle, bool PrivateKeys);
    bool (*GetPrivateKeys)(echandle DictionaryHandle, bool *PrivateKeys);

    echandle (*AddRef)(echandle DictionaryHandle);
    int32_t (*Release)(echandle *DictionaryHandle);

    bool (*EnsureDictionaryByPath)(echandle DictionaryHandle, const char *Path, echandle *ItemDictionaryHandle);
    bool (*ContainsPath)(echandle DictionaryHandle, const char *Path);

    bool (*GetStringPtrByPath)(echandle DictionaryHandle, const char *Path, const char **StringPtr);
    bool (*ContainsString)(echandle DictionaryHandle, const char *String);
    bool (*RemoveByString)(echandle DictionaryHandle, const char *String);

    bool (*GetDictionaryByPath)(echandle DictionaryHandle, const char *Path, echandle *ItemDictionaryHandle);
} IDictionaryVtbl;

/*********************************************************************/

#define IDictionary_GetParent(DictionaryHandle, ParentDictionaryHandle, ParentItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)                                     \
        ->GetParent(DictionaryHandle, ParentDictionaryHandle, ParentItemHandle)
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
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)                                                      \
        ->ConvertFromString(DictionaryHandle, Value, MaxValue, KeyValueSeparator, ItemSeparator)
#define IDictionary_ConvertToString(DictionaryHandle, Value, MaxValue, KeyValueSeparator, ItemSeparator) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)                                                    \
        ->ConvertToString(DictionaryHandle, Value, MaxValue, KeyValueSeparator, ItemSeparator)

#define IDictionary_ContainsKey(DictionaryHandle, Key) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ContainsKey(DictionaryHandle, Key)
#define IDictionary_ContainsString(DictionaryHandle, String) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ContainsString(DictionaryHandle, String)
#define IDictionary_ContainsPath(DictionaryHandle, Path) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ContainsPath(DictionaryHandle, Path)
#define IDictionary_EnsureIndex(DictionaryHandle, Index, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->EnsureIndex(DictionaryHandle, Index, ItemHandle)
#define IDictionary_EnsureKey(DictionaryHandle, Key, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->EnsureKey(DictionaryHandle, Key, ItemHandle)
#define IDictionary_EnsureList(DictionaryHandle, Key, ItemHandle, ItemDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)                                   \
        ->EnsureList(DictionaryHandle, Key, ItemHandle, ItemDictionaryHandle)
#define IDictionary_EnsureListByIndex(DictionaryHandle, Index, ItemHandle, ItemDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)                                            \
        ->EnsureListByIndex(DictionaryHandle, Index, ItemHandle, ItemDictionaryHandle)
#define IDictionary_EnsureDictionary(DictionaryHandle, Key, ItemHandle, ItemDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)                                         \
        ->EnsureDictionary(DictionaryHandle, Key, ItemHandle, ItemDictionaryHandle)
#define IDictionary_EnsureDictionaryByPath(DictionaryHandle, Path, ItemDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)                                    \
        ->EnsureDictionaryByPath(DictionaryHandle, Path, ItemDictionaryHandle)
#define IDictionary_EnsureDictionaryByIndex(DictionaryHandle, Index, ItemHandle, ItemDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)                                                  \
        ->EnsureDictionaryByIndex(DictionaryHandle, Index, ItemHandle, ItemDictionaryHandle)
#define IDictionary_GetTypeByKey(DictionaryHandle, Key, Type) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetTypeByKey(DictionaryHandle, Key, Type)
#define IDictionary_SetStringByKey(DictionaryHandle, Key, String) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetStringByKey(DictionaryHandle, Key, String)
#define IDictionary_SetStringByKeyPrint(DictionaryHandle, Key, String, ...) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetStringByKeyPrint(DictionaryHandle, Key, String, __VA_ARGS__)
#define IDictionary_GetStringByKey(DictionaryHandle, Key, String, MaxString) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetStringByKey(DictionaryHandle, Key, String, MaxString)
#define IDictionary_SetStringByPath(DictionaryHandle, Path, String) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetStringByPath(DictionaryHandle, Path, String)
#define IDictionary_GetStringByPath(DictionaryHandle, Path, String, MaxString) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetStringByPath(DictionaryHandle, Path, String, MaxString)
#define IDictionary_SetStringByKeyV(DictionaryHandle, Key, String, ArgumentList) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetStringByKeyV(DictionaryHandle, Key, String, ArgumentList)
#define IDictionary_GetStringPtrByKey(DictionaryHandle, Key, StringPtr) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetStringPtrByKey(DictionaryHandle, Key, StringPtr)
#define IDictionary_GetStringPtrByPath(DictionaryHandle, Path, StringPtr) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetStringPtrByPath(DictionaryHandle, Path, StringPtr)
#define IDictionary_GetBufferPtrByKey(DictionaryHandle, Key, BufferPtr, BufferLength) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetBufferPtrByKey(DictionaryHandle, Key, BufferPtr, BufferLength)
#define IDictionary_GetBufferPtrByPath(DictionaryHandle, Path, BufferPtr, BufferLength) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)                                   \
        ->GetBufferPtrByPath(DictionaryHandle, Path, BufferPtr, BufferLength)
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
#define IDictionary_GetListByKey(DictionaryHandle, Key, ItemDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetListByKey(DictionaryHandle, Key, ItemDictionaryHandle)
#define IDictionary_GetDictionaryByIndex(DictionaryHandle, Index, ItemDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)                                   \
        ->GetDictionaryByIndex(DictionaryHandle, Index, ItemDictionaryHandle)
#define IDictionary_GetDictionaryByKey(DictionaryHandle, Key, ItemDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetDictionaryByKey(DictionaryHandle, Key, ItemDictionaryHandle)
#define IDictionary_GetDictionaryByPath(DictionaryHandle, Path, ItemDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetDictionaryByPath(DictionaryHandle, Path, ItemDictionaryHandle)
#define IDictionary_RemoveByKey(DictionaryHandle, Key) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->RemoveByKey(DictionaryHandle, Key)
#define IDictionary_RemoveByString(DictionaryHandle, String) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->RemoveByString(DictionaryHandle, String)

#define IDictionary_ItemGetPath(DictionaryHandle, ItemHandle, TopDictionaryHandle, Path, MaxPath) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)                                             \
        ->ItemGetPath(DictionaryHandle, ItemHandle, TopDictionaryHandle, Path, MaxPath)
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
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)                             \
        ->ItemSetStringPrint(DictionaryHandle, ItemHandle, String, __VA_ARGS__)
#define IDictionary_ItemSetStringV(DictionaryHandle, ItemHandle, String, ArgumentList) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)                                  \
        ->ItemSetStringV(DictionaryHandle, ItemHandle, String, ArgumentList)
#define IDictionary_ItemGetString(DictionaryHandle, ItemHandle, String, MaxString) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetString(DictionaryHandle, ItemHandle, String, MaxString)
#define IDictionary_ItemGetStringPtr(DictionaryHandle, ItemHandle, StringPtr) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetStringPtr(DictionaryHandle, ItemHandle, StringPtr)
#define IDictionary_ItemSetBuffer(DictionaryHandle, ItemHandle, Buffer, BufferLength) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemSetBuffer(DictionaryHandle, ItemHandle, Buffer, BufferLength)
#define IDictionary_ItemGetBufferPtr(DictionaryHandle, ItemHandle, BufferPtr, BufferLength) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)                                       \
        ->ItemGetBufferPtr(DictionaryHandle, ItemHandle, BufferPtr, BufferLength)
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
#define IDictionary_ItemSetPrivate(DictionaryHandle, ItemHandle, Private) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemSetPrivate(DictionaryHandle, ItemHandle, Private)
#define IDictionary_ItemGetPrivate(DictionaryHandle, ItemHandle, Private) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetPrivate(DictionaryHandle, ItemHandle, Private)
#define IDictionary_ItemSetNull(DictionaryHandle, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemSetNull(DictionaryHandle, ItemHandle)
#define IDictionary_ItemGetDictionaryHandle(DictionaryHandle, ItemHandle, DictHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemGetDictionaryHandle(DictionaryHandle, ItemHandle, DictHandle)
#define IDictionary_ItemFindByPath(DictionaryHandle, Path, ItemDictionaryHandle, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)                                        \
        ->ItemFindByPath(DictionaryHandle, Path, ItemDictionaryHandle, ItemHandle)
#define IDictionary_ItemFindByKey(DictionaryHandle, Key, StartItemHandle, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->ItemFindByKey(DictionaryHandle, Key, StartItemHandle, ItemHandle)
#define IDictionary_ItemFindByBuffer(DictionaryHandle, Buffer, BufferLength, StartItemHandle, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)                                                     \
        ->ItemFindByBuffer(DictionaryHandle, Buffer, BufferLength, StartItemHandle, ItemHandle)
#define IDictionary_ItemFindByIndex(DictionaryHandle, Index, BufferLength, StartItemHandle, ItemHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)                                                   \
        ->ItemFindByIndex(DictionaryHandle, Index, BufferLength, StartItemHandle, ItemHandle)
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
    Class_VtblCast(TargetDictionaryHandle, IDictionaryVtbl)                                             \
        ->Sync(TargetDictionaryHandle, SourceDictionaryHandle, FilterUserPtr, FilterCallback)
#define IDictionary_SyncAt(TargetDictionaryHandle, SourceDictionaryHandle, SourceItemHandle, FilterUserPtr, \
                           FilterCallback)                                                                  \
    Class_VtblCast(TargetDictionaryHandle, IDictionaryVtbl)                                                 \
        ->SyncAt(TargetDictionaryHandle, SourceDictionaryHandle, SourceItemHandle, FilterUserPtr, FilterCallback)
#define IDictionary_RemoveMissing(TargetDictionaryHandle, SourceDictionaryHandle) \
    Class_VtblCast(TargetDictionaryHandle, IDictionaryVtbl)                       \
        ->RemoveMissing(TargetDictionaryHandle, SourceDictionaryHandle)
#define IDictionary_Merge(TargetDictionaryHandle, SourceDictionaryHandle, Flags) \
    Class_VtblCast(TargetDictionaryHandle, IDictionaryVtbl)                      \
        ->Merge(TargetDictionaryHandle, SourceDictionaryHandle, Flags)
#define IDictionary_MergeAt(TargetDictionaryHandle, SourceDictionaryHandle, SourceItemHandle, Flags) \
    Class_VtblCast(TargetDictionaryHandle, IDictionaryVtbl)                                          \
        ->MergeAt(TargetDictionaryHandle, SourceDictionaryHandle, SourceItemHandle, Flags)
#define IDictionary_MergeItem(TargetDictionaryHandle, SourceDictionaryHandle, SourceItemHandle, Flags) \
    Class_VtblCast(TargetDictionaryHandle, IDictionaryVtbl)                                            \
        ->MergeItem(TargetDictionaryHandle, SourceDictionaryHandle, SourceItemHandle, Flags)
#define IDictionary_SkipRoot(DictionaryHandle, DataDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SkipRoot(DictionaryHandle, DataDictionaryHandle)
#define IDictionary_SkipRootContainer(DictionaryHandle, DataDictionaryHandle) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SkipRootContainer(DictionaryHandle, DataDictionaryHandle)
#define IDictionary_Reset(DictionaryHandle) Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->Reset(DictionaryHandle)
#define IDictionary_Dump(DictionaryHandle)  Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->Dump(DictionaryHandle)

#define IDictionary_SetCaseSensitive(DictionaryHandle, CaseSensitive) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetCaseSensitive(DictionaryHandle, CaseSensitive)
#define IDictionary_GetCaseSensitive(DictionaryHandle, CaseSensitive) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetCaseSensitive(DictionaryHandle, CaseSensitive)
#define IDictionary_SetPrivateKeys(DictionaryHandle, PrivateKeys) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->SetPrivateKeys(DictionaryHandle, PrivateKeys)
#define IDictionary_GetPrivateKeys(DictionaryHandle, PrivateKeys) \
    Class_VtblCast(DictionaryHandle, IDictionaryVtbl)->GetPrivateKeys(DictionaryHandle, PrivateKeys)
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

#define IDictionary_Create(DictionaryHandle)  Dictionary_Create(DictionaryHandle)
#define IDictionary_AddRef(DictionaryHandle)  Dictionary_AddRef(DictionaryHandle)
#define IDictionary_Release(DictionaryHandle) Dictionary_Release(DictionaryHandle)

/*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
