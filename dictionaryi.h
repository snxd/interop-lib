#pragma once

/*********************************************************************/

#define IDICTIONARY_KEYRAW_MAX      (120)
#define IDICTIONARY_KEY_MAX         (IDICTIONARY_KEYRAW_MAX - 1)
#define IDICTIONARY_PATH_MAX        (4096)

#define IDICTIONARY_TYPE_UNKNOWN    (0)
#define IDICTIONARY_TYPE_NULL       (1)
#define IDICTIONARY_TYPE_BOOLEAN    (2)
#define IDICTIONARY_TYPE_INT        (3)
#define IDICTIONARY_TYPE_FLOAT      (4)
#define IDICTIONARY_TYPE_STRING     (5)
#define IDICTIONARY_TYPE_LIST       (6)
#define IDICTIONARY_TYPE_DICTIONARY (7)

/*********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************/

typedef bool (*IDictionary_ItemFilterCallback)(echandle dictionary_handle, void *user_ptr,
                                               echandle source_dictionary_handle, echandle source_item_handle);
typedef bool (*IDictionary_ItemRemoveCallback)(echandle handle, echandle item_handle, void *user_ptr, const char *path);
typedef bool (*IDictionary_ItemKeyChangeCallback)(echandle handle, echandle item_handle, void *user_ptr,
                                                  const char *path, const char *old_key);
typedef bool (*IDictionary_ItemValueChangeCallback)(echandle handle, echandle item_handle, void *user_ptr,
                                                    const char *path, const char *old_value, int32_t old_value_length);

/*********************************************************************/

typedef struct IDictionaryVtbl {
    bool (*get_parent)(echandle handle, echandle *parent_dictionary_handle, echandle *parent_item_handle);
    bool (*add)(echandle handle, const char *key, echandle *item_handle);
    bool (*add_null)(echandle handle, const char *key, echandle *item_handle);
    bool (*add_string)(echandle handle, const char *key, const char *value, echandle *item_handle);
    bool (*add_int)(echandle handle, const char *key, int64_t value, echandle *item_handle);
    bool (*add_float)(echandle handle, const char *key, float64_t value, echandle *item_handle);
    bool (*add_boolean)(echandle handle, const char *key, bool value, echandle *item_handle);
    bool (*add_list)(echandle handle, const char *key, echandle *list_handle, echandle *item_handle);
    bool (*add_dictionary)(echandle handle, const char *key, echandle *dict_handle, echandle *item_handle);
    bool (*insert)(echandle handle, echandle prev_item_handle, const char *key, echandle *item_handle);
    bool (*remove)(echandle handle, echandle *item_handle);

    bool (*convert_from_string)(echandle handle, const char *value, int32_t max_value, char key_value_separator,
                                char item_separator);
    bool (*convert_to_string)(echandle handle, char *value, int32_t max_value, char key_value_separator,
                              char item_separator);

    bool (*contains_key)(echandle handle, const char *key);
    bool (*ensure_index)(echandle handle, int32_t index, echandle *item_handle);
    bool (*ensure_list_by_index)(echandle handle, int32_t index, echandle *item_handle,
                                 echandle *item_dictionary_handle);
    bool (*ensure_dictionary_by_index)(echandle handle, int32_t index, echandle *item_handle,
                                       echandle *item_dictionary_handle);
    bool (*ensure_key)(echandle handle, const char *key, echandle *item_handle);
    bool (*ensure_list)(echandle handle, const char *key, echandle *item_handle, echandle *item_dictionary_handle);
    bool (*ensure_dictionary)(echandle handle, const char *key, echandle *item_handle,
                              echandle *item_dictionary_handle);

    bool (*get_type_by_key)(echandle handle, const char *key, int32_t *type);
    bool (*set_string_by_key)(echandle handle, const char *key, const char *string);
    bool (*get_string_by_key)(echandle handle, const char *key, char *string, int32_t max_string);
    bool (*set_string_by_key_v)(echandle handle, const char *key, const char *string, va_list argument_list);
    bool (*get_string_ptr_by_key)(echandle handle, const char *key, const char **string_ptr);
    bool (*get_buffer_ptr_by_key)(echandle handle, const char *key, const char **buffer_ptr, int32_t *buffer_length);
    bool (*set_int_by_key)(echandle handle, const char *key, int64_t value);
    bool (*get_int32_by_key)(echandle handle, const char *key, int32_t *value);
    bool (*get_int64_by_key)(echandle handle, const char *key, int64_t *value);
    bool (*set_float_by_key)(echandle handle, const char *key, float64_t value);
    bool (*get_float_by_key)(echandle handle, const char *key, float64_t *value);
    bool (*set_boolean_by_key)(echandle handle, const char *key, bool value);
    bool (*get_boolean_by_key)(echandle handle, const char *key, bool *value);
    bool (*get_list_by_index)(echandle handle, int32_t index, echandle *item_dictionary_handle);
    bool (*get_dictionary_by_index)(echandle handle, int32_t index, echandle *item_dictionary_handle);
    bool (*get_list_by_key)(echandle handle, const char *key, echandle *item_dictionary_handle);
    bool (*get_dictionary_by_key)(echandle handle, const char *key, echandle *item_dictionary_handle);
    bool (*remove_by_key)(echandle handle, const char *key);

    bool (*item_get_path)(echandle handle, echandle item_handle, echandle top_dictionary_handle, char *path,
                          int32_t max_path);
    bool (*item_is_container)(echandle handle, echandle item_handle);
    bool (*item_is_null)(echandle handle, echandle item_handle);
    bool (*item_get_index)(echandle handle, echandle item_handle, int32_t *index);
    bool (*item_set_type)(echandle handle, echandle item_handle, int32_t type);
    int32_t (*item_get_type)(echandle handle, echandle item_handle);
    bool (*item_compare_type)(echandle handle, echandle item_handle, int32_t type);
    bool (*item_set_key)(echandle handle, echandle item_handle, const char *key);
    bool (*item_set_key_length)(echandle handle, echandle item_handle, const char *key, int32_t key_length);
    bool (*item_get_key)(echandle handle, echandle item_handle, char *key, int32_t max_key);
    bool (*item_get_key_ptr)(echandle handle, echandle item_handle, const char **key_ptr);
    bool (*item_set_string)(echandle handle, echandle item_handle, const char *string);
    bool (*item_set_string_v)(echandle handle, echandle item_handle, const char *string, va_list argument_list);
    bool (*item_get_string)(echandle handle, echandle item_handle, char *string, int32_t max_string);
    bool (*item_get_string_ptr)(echandle handle, echandle item_handle, const char **string_ptr);
    bool (*item_set_buffer)(echandle handle, echandle item_handle, const char *buffer, int32_t buffer_length);
    bool (*item_get_buffer_ptr)(echandle handle, echandle item_handle, const char **buffer_ptr, int32_t *buffer_length);
    bool (*item_set_float)(echandle handle, echandle item_handle, float64_t value);
    bool (*item_get_float)(echandle handle, echandle item_handle, float64_t *value);
    bool (*item_set_int)(echandle handle, echandle item_handle, int64_t value);
    bool (*item_get_int32)(echandle handle, echandle item_handle, int32_t *value);
    bool (*item_get_int64)(echandle handle, echandle item_handle, int64_t *value);
    bool (*item_set_boolean)(echandle handle, echandle item_handle, bool value);
    bool (*item_get_boolean)(echandle handle, echandle item_handle, bool *value);
    bool (*item_set_null)(echandle handle, echandle item_handle);
    bool (*item_get_dictionary_handle)(echandle handle, echandle item_handle, echandle *dict_handle);
    bool (*item_find_by_path)(echandle handle, const char *path, echandle *item_dictionary_handle,
                              echandle *item_handle);
    bool (*item_find_by_key)(echandle handle, const char *key, echandle start_item_handle, echandle *item_handle);
    bool (*item_find_by_buffer)(echandle handle, const char *buffer, int32_t buffer_length, echandle start_item_handle,
                                echandle *item_handle);
    bool (*item_find_by_index)(echandle handle, int32_t index, echandle start_item_handle, echandle *item_handle);
    bool (*item_get_next)(echandle handle, echandle item_handle, echandle *next_item_handle);
    bool (*item_get_prev)(echandle handle, echandle item_handle, echandle *prev_item_handle);
    bool (*item_get_first)(echandle handle, echandle *item_handle);
    bool (*item_get_last)(echandle handle, echandle *item_handle);
    int32_t (*item_get_count)(echandle handle);

    FORMAT(2, 3)
    bool (*log)(echandle handle, const char *format, ...);
    FORMAT(3, 4)
    bool (*log_tabbed)(echandle handle, int32_t depth, const char *format, ...);
    bool (*set_log_callback)(echandle handle, echandle log_handle, Generic_LogCallback callback);
    bool (*get_log_callback)(echandle handle, echandle *log_handle, Generic_LogCallback *callback);

    bool (*sync)(echandle target_dictionary_handle, echandle source_dictionary_handle, void *filter_user_ptr,
                 IDictionary_ItemFilterCallback filter_callback);
    bool (*sync_at)(echandle target_dictionary_handle, echandle source_dictionary_handle, echandle source_item_handle,
                    void *filter_user_ptr, IDictionary_ItemFilterCallback filter_callback);
    bool (*remove_missing)(echandle target_dictionary_handle, echandle source_dictionary_handle);

    bool (*merge)(echandle target_dictionary_handle, echandle source_dictionary_handle, int32_t flags);
    bool (*merge_at)(echandle target_dictionary_handle, echandle source_dictionary_handle, echandle source_item_handle,
                     int32_t flags);
    echandle (*skip_root)(echandle handle);
    bool (*reset)(echandle handle);
    bool (*dump)(echandle handle);

    bool (*set_case_sensitive)(echandle handle, bool case_sensitive);
    bool (*get_case_sensitive)(echandle handle);
    bool (*set_allow_duplicates)(echandle handle, bool allow_duplicates);
    bool (*get_allow_duplicates)(echandle handle);

    bool (*set_item_remove_callback)(echandle handle, void *user_ptr, IDictionary_ItemRemoveCallback callback);
    bool (*get_item_remove_callback)(echandle handle, void **user_ptr, IDictionary_ItemRemoveCallback *callback);
    bool (*set_item_key_change_callback)(echandle handle, void *user_ptr, IDictionary_ItemKeyChangeCallback callback);
    bool (*get_item_key_change_callback)(echandle handle, void **user_ptr, IDictionary_ItemKeyChangeCallback *callback);
    bool (*set_item_value_change_callback)(echandle handle, void *user_ptr,
                                           IDictionary_ItemValueChangeCallback callback);
    bool (*get_item_value_change_callback)(echandle handle, void **user_ptr,
                                           IDictionary_ItemValueChangeCallback *callback);

    bool (*merge_item)(echandle target_dictionary_handle, echandle *target_prev_item_handle,
                       echandle source_dictionary_handle, echandle source_item_handle, int32_t flags);
    bool (*set_string_by_key_print)(echandle handle, const char *key, const char *string, ...);
    bool (*item_set_string_print)(echandle handle, echandle item_handle, const char *string, ...);

    bool (*set_string_by_path)(echandle handle, const char *path, const char *string);
    bool (*get_string_by_path)(echandle handle, const char *path, char *string, int32_t max_string);
    bool (*get_buffer_ptr_by_path)(echandle handle, const char *path, const char **buffer_ptr, int32_t *buffer_length);
    bool (*set_int_by_path)(echandle handle, const char *path, int64_t value);
    bool (*get_int32_by_path)(echandle handle, const char *path, int32_t *value);
    bool (*get_int64_by_path)(echandle handle, const char *path, int64_t *value);
    bool (*set_float_by_path)(echandle handle, const char *path, float64_t value);
    bool (*get_float_by_path)(echandle handle, const char *path, float64_t *value);
    bool (*set_boolean_by_path)(echandle handle, const char *path, bool value);
    bool (*get_boolean_by_path)(echandle handle, const char *path, bool *value);
    echandle (*skip_root_container)(echandle handle);
    bool (*item_set_private)(echandle handle, echandle item_handle, bool enabled);
    bool (*item_is_private)(echandle handle, echandle item_handle);
    bool (*set_private_keys)(echandle handle, bool private_keys);
    bool (*get_private_keys)(echandle handle);

    echandle (*add_ref)(echandle handle);
    int32_t (*release)(echandle *dictionary_handle);

    bool (*ensure_dictionary_by_path)(echandle handle, const char *path, echandle *item_dictionary_handle);
    bool (*contains_path)(echandle handle, const char *path);

    bool (*get_string_ptr_by_path)(echandle handle, const char *path, const char **string_ptr);
    bool (*contains_string)(echandle handle, const char *string);
    bool (*remove_by_string)(echandle handle, const char *string);

    bool (*get_dictionary_by_path)(echandle handle, const char *path, echandle *item_dictionary_handle);
} IDictionaryVtbl;

/*********************************************************************/

#define IDictionary_GetParent(handle, parent_dictionary_handle, parent_item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_parent(handle, parent_dictionary_handle, parent_item_handle)
#define IDictionary_Add(handle, key, item_handle) Class_VtblCast(handle, IDictionaryVtbl)->add(handle, key, item_handle)
#define IDictionary_AddNull(handle, key, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->add_null(handle, key, item_handle)
#define IDictionary_AddString(handle, key, value, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->add_string(handle, key, value, item_handle)
#define IDictionary_AddInt(handle, key, value, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->add_int(handle, key, value, item_handle)
#define IDictionary_AddFloat(handle, key, value, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->add_float(handle, key, value, item_handle)
#define IDictionary_AddBoolean(handle, key, value, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->add_boolean(handle, key, value, item_handle)
#define IDictionary_AddList(handle, key, list_handle, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->add_list(handle, key, list_handle, item_handle)
#define IDictionary_AddDictionary(handle, key, dict_handle, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->add_dictionary(handle, key, dict_handle, item_handle)
#define IDictionary_Insert(handle, prev_item_handle, key, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->insert(handle, prev_item_handle, key, item_handle)
#define IDictionary_Remove(handle, item_handle) Class_VtblCast(handle, IDictionaryVtbl)->remove(handle, item_handle)

#define IDictionary_ConvertFromString(handle, value, max_value, key_value_separator, item_separator) \
    Class_VtblCast(handle, IDictionaryVtbl)                                                          \
        ->convert_from_string(handle, value, max_value, key_value_separator, item_separator)
#define IDictionary_ConvertToString(handle, value, max_value, key_value_separator, item_separator) \
    Class_VtblCast(handle, IDictionaryVtbl)                                                        \
        ->convert_to_string(handle, value, max_value, key_value_separator, item_separator)

#define IDictionary_ContainsKey(handle, key) Class_VtblCast(handle, IDictionaryVtbl)->contains_key(handle, key)
#define IDictionary_ContainsString(handle, string) \
    Class_VtblCast(handle, IDictionaryVtbl)->contains_string(handle, string)
#define IDictionary_ContainsPath(handle, path) Class_VtblCast(handle, IDictionaryVtbl)->contains_path(handle, path)
#define IDictionary_EnsureIndex(handle, index, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->ensure_index(handle, index, item_handle)
#define IDictionary_EnsureKey(handle, key, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->ensure_key(handle, key, item_handle)
#define IDictionary_EnsureList(handle, key, item_handle, item_dictionary_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->ensure_list(handle, key, item_handle, item_dictionary_handle)
#define IDictionary_EnsureListByIndex(handle, index, item_handle, item_dictionary_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->ensure_list_by_index(handle, index, item_handle, item_dictionary_handle)
#define IDictionary_EnsureDictionary(handle, key, item_handle, item_dictionary_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->ensure_dictionary(handle, key, item_handle, item_dictionary_handle)
#define IDictionary_EnsureDictionaryByPath(handle, path, item_dictionary_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->ensure_dictionary_by_path(handle, path, item_dictionary_handle)
#define IDictionary_EnsureDictionaryByIndex(handle, index, item_handle, item_dictionary_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)                                                     \
        ->ensure_dictionary_by_index(handle, index, item_handle, item_dictionary_handle)
#define IDictionary_GetTypeByKey(handle, key, type) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_type_by_key(handle, key, type)
#define IDictionary_SetStringByKey(handle, key, string) \
    Class_VtblCast(handle, IDictionaryVtbl)->set_string_by_key(handle, key, string)
#define IDictionary_SetStringByKeyPrint(handle, key, string, ...) \
    Class_VtblCast(handle, IDictionaryVtbl)->set_string_by_key_print(handle, key, string, __VA_ARGS__)
#define IDictionary_GetStringByKey(handle, key, string, max_string) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_string_by_key(handle, key, string, max_string)
#define IDictionary_SetStringByPath(handle, path, string) \
    Class_VtblCast(handle, IDictionaryVtbl)->set_string_by_path(handle, path, string)
#define IDictionary_GetStringByPath(handle, path, string, max_string) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_string_by_path(handle, path, string, max_string)
#define IDictionary_SetStringByKeyV(handle, key, string, argument_list) \
    Class_VtblCast(handle, IDictionaryVtbl)->set_string_by_key_v(handle, key, string, argument_list)
#define IDictionary_GetStringPtrByKey(handle, key, string_ptr) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_string_ptr_by_key(handle, key, string_ptr)
#define IDictionary_GetStringPtrByPath(handle, path, string_ptr) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_string_ptr_by_path(handle, path, string_ptr)
#define IDictionary_GetBufferPtrByKey(handle, key, buffer_ptr, buffer_length) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_buffer_ptr_by_key(handle, key, buffer_ptr, buffer_length)
#define IDictionary_GetBufferPtrByPath(handle, path, buffer_ptr, buffer_length) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_buffer_ptr_by_path(handle, path, buffer_ptr, buffer_length)
#define IDictionary_SetIntByKey(handle, key, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->set_int_by_key(handle, key, value)
#define IDictionary_SetIntByPath(handle, path, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->set_int_by_path(handle, path, value)
#define IDictionary_GetInt32ByKey(handle, key, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_int32_by_key(handle, key, value)
#define IDictionary_GetInt32ByPath(handle, path, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_int32_by_path(handle, path, value)
#define IDictionary_GetInt64ByKey(handle, key, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_int64_by_key(handle, key, value)
#define IDictionary_GetInt64ByPath(handle, path, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_int64_by_path(handle, path, value)
#define IDictionary_SetFloatByKey(handle, key, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->set_float_by_key(handle, key, value)
#define IDictionary_SetFloatByPath(handle, path, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->set_float_by_path(handle, path, value)
#define IDictionary_GetFloatByKey(handle, key, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_float_by_key(handle, key, value)
#define IDictionary_GetFloatByPath(handle, path, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_float_by_path(handle, path, value)
#define IDictionary_SetBooleanByKey(handle, key, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->set_boolean_by_key(handle, key, value)
#define IDictionary_SetBooleanByPath(handle, path, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->set_boolean_by_path(handle, path, value)
#define IDictionary_GetBooleanByKey(handle, key, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_boolean_by_key(handle, key, value)
#define IDictionary_GetBooleanByPath(handle, path, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_boolean_by_path(handle, path, value)
#define IDictionary_GetListByIndex(handle, index, item_dictionary_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_list_by_index(handle, index, item_dictionary_handle)
#define IDictionary_GetListByKey(handle, key, item_dictionary_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_list_by_key(handle, key, item_dictionary_handle)
#define IDictionary_GetDictionaryByIndex(handle, index, item_dictionary_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_dictionary_by_index(handle, index, item_dictionary_handle)
#define IDictionary_GetDictionaryByKey(handle, key, item_dictionary_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_dictionary_by_key(handle, key, item_dictionary_handle)
#define IDictionary_GetDictionaryByPath(handle, path, item_dictionary_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_dictionary_by_path(handle, path, item_dictionary_handle)
#define IDictionary_RemoveByKey(handle, key) Class_VtblCast(handle, IDictionaryVtbl)->remove_by_key(handle, key)
#define IDictionary_RemoveByString(handle, string) \
    Class_VtblCast(handle, IDictionaryVtbl)->remove_by_string(handle, string)

#define IDictionary_ItemGetPath(handle, item_handle, top_dictionary_handle, path, max_path) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_get_path(handle, item_handle, top_dictionary_handle, path, max_path)
#define IDictionary_ItemIsContainer(handle, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_is_container(handle, item_handle)
#define IDictionary_ItemIsNull(handle, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_is_null(handle, item_handle)
#define IDictionary_ItemIsPrivate(handle, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_is_private(handle, item_handle)
#define IDictionary_ItemGetIndex(handle, item_handle, index) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_get_index(handle, item_handle, index)
#define IDictionary_ItemSetType(handle, item_handle, type) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_set_type(handle, item_handle, type)
#define IDictionary_ItemGetType(handle, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_get_type(handle, item_handle)
#define IDictionary_ItemCompareType(handle, item_handle, type) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_compare_type(handle, item_handle, type)
#define IDictionary_ItemSetKey(handle, item_handle, key) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_set_key(handle, item_handle, key)
#define IDictionary_ItemSetKeyLength(handle, item_handle, key, key_length) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_set_key_length(handle, item_handle, key, key_length)
#define IDictionary_ItemGetKey(handle, item_handle, key, max_key) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_get_key(handle, item_handle, key, max_key)
#define IDictionary_ItemGetKeyPtr(handle, item_handle, keyPtr) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_get_key_ptr(handle, item_handle, keyPtr)
#define IDictionary_ItemSetString(handle, item_handle, string) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_set_string(handle, item_handle, string)
#define IDictionary_ItemSetStringPrint(handle, item_handle, string, ...) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_set_string_print(handle, item_handle, string, __VA_ARGS__)
#define IDictionary_ItemSetStringV(handle, item_handle, string, argument_list) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_set_string_v(handle, item_handle, string, argument_list)
#define IDictionary_ItemGetString(handle, item_handle, string, max_string) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_get_string(handle, item_handle, string, max_string)
#define IDictionary_ItemGetStringPtr(handle, item_handle, string_ptr) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_get_string_ptr(handle, item_handle, string_ptr)
#define IDictionary_ItemSetBuffer(handle, item_handle, buffer, buffer_length) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_set_buffer(handle, item_handle, buffer, buffer_length)
#define IDictionary_ItemGetBufferPtr(handle, item_handle, buffer_ptr, buffer_length) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_get_buffer_ptr(handle, item_handle, buffer_ptr, buffer_length)
#define IDictionary_ItemSetFloat(handle, item_handle, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_set_float(handle, item_handle, value)
#define IDictionary_ItemGetFloat(handle, item_handle, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_get_float(handle, item_handle, value)
#define IDictionary_ItemSetInt(handle, item_handle, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_set_int(handle, item_handle, value)
#define IDictionary_ItemGetInt32(handle, item_handle, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_get_int32(handle, item_handle, value)
#define IDictionary_ItemGetInt64(handle, item_handle, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_get_int64(handle, item_handle, value)
#define IDictionary_ItemSetBoolean(handle, item_handle, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_set_boolean(handle, item_handle, value)
#define IDictionary_ItemGetBoolean(handle, item_handle, value) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_get_boolean(handle, item_handle, value)
#define IDictionary_ItemSetPrivate(handle, item_handle, enabled) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_set_private(handle, item_handle, enabled)
#define IDictionary_ItemSetNull(handle, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_set_null(handle, item_handle)
#define IDictionary_ItemGetDictionaryHandle(handle, item_handle, dict_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_get_dictionary_handle(handle, item_handle, dict_handle)
#define IDictionary_ItemFindByPath(handle, path, item_dictionary_handle, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_find_by_path(handle, path, item_dictionary_handle, item_handle)
#define IDictionary_ItemFindByKey(handle, key, start_item_handle, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_find_by_key(handle, key, start_item_handle, item_handle)
#define IDictionary_ItemFindByBuffer(handle, buffer, buffer_length, start_item_handle, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)                                                         \
        ->item_find_by_buffer(handle, buffer, buffer_length, start_item_handle, item_handle)
#define IDictionary_ItemFindByIndex(handle, index, start_item_handle, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_find_by_index(handle, index, start_item_handle, item_handle)
#define IDictionary_ItemGetNext(handle, item_handle, next_item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_get_next(handle, item_handle, next_item_handle)
#define IDictionary_ItemGetPrev(handle, item_handle, prev_item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_get_prev(handle, item_handle, prev_item_handle)
#define IDictionary_ItemGetFirst(handle, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_get_first(handle, item_handle)
#define IDictionary_ItemGetLast(handle, item_handle) \
    Class_VtblCast(handle, IDictionaryVtbl)->item_get_last(handle, item_handle)
#define IDictionary_ItemGetCount(handle)     Class_VtblCast(handle, IDictionaryVtbl)->item_get_count(handle)

#define IDictionary_Log(handle, format, ...) Class_VtblCast(handle, IDictionaryVtbl)->log(handle, format, __VA_ARGS__)
#define IDictionary_LogTabbed(handle, depth, format, ...) \
    Class_VtblCast(handle, IDictionaryVtbl)->log_tabbed(handle, depth, format, __VA_ARGS__)
#define IDictionary_SetLogCallback(handle, log_handle, callback) \
    Class_VtblCast(handle, IDictionaryVtbl)->set_log_callback(handle, log_handle, callback)
#define IDictionary_GetLogCallback(handle, log_handle, callback) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_log_callback(handle, log_handle, callback)

#define IDictionary_Sync(target_dictionary_handle, source_dictionary_handle, filter_user_ptr, filter_callback) \
    Class_VtblCast(target_dictionary_handle, IDictionaryVtbl)                                                  \
        ->sync(target_dictionary_handle, source_dictionary_handle, filter_user_ptr, filter_callback)
#define IDictionary_SyncAt(target_dictionary_handle, source_dictionary_handle, source_item_handle, filter_user_ptr, \
                           filter_callback)                                                                         \
    Class_VtblCast(target_dictionary_handle, IDictionaryVtbl)                                                       \
        ->sync_at(target_dictionary_handle, source_dictionary_handle, source_item_handle, filter_user_ptr,          \
                  filter_callback)
#define IDictionary_RemoveMissing(target_dictionary_handle, source_dictionary_handle) \
    Class_VtblCast(target_dictionary_handle, IDictionaryVtbl)                         \
        ->remove_missing(target_dictionary_handle, source_dictionary_handle)
#define IDictionary_Merge(target_dictionary_handle, source_dictionary_handle, flags) \
    Class_VtblCast(target_dictionary_handle, IDictionaryVtbl)                        \
        ->merge(target_dictionary_handle, source_dictionary_handle, flags)
#define IDictionary_MergeAt(target_dictionary_handle, source_dictionary_handle, source_item_handle, flags) \
    Class_VtblCast(target_dictionary_handle, IDictionaryVtbl)                                              \
        ->merge_at(target_dictionary_handle, source_dictionary_handle, source_item_handle, flags)
#define IDictionary_MergeItem(target_dictionary_handle, target_prev_item_handle, source_dictionary_handle,            \
                              source_item_handle, flags)                                                              \
    Class_VtblCast(target_dictionary_handle, IDictionaryVtbl)                                                         \
        ->merge_item(target_dictionary_handle, target_prev_item_handle, source_dictionary_handle, source_item_handle, \
                     flags)
#define IDictionary_SkipRoot(handle)          Class_VtblCast(handle, IDictionaryVtbl)->skip_root(handle)
#define IDictionary_SkipRootContainer(handle) Class_VtblCast(handle, IDictionaryVtbl)->skip_root_container(handle)
#define IDictionary_Reset(handle)             Class_VtblCast(handle, IDictionaryVtbl)->reset(handle)
#define IDictionary_Dump(handle)              Class_VtblCast(handle, IDictionaryVtbl)->dump(handle)

#define IDictionary_SetCaseSensitive(handle, case_sensitive) \
    Class_VtblCast(handle, IDictionaryVtbl)->set_case_sensitive(handle, case_sensitive)
#define IDictionary_GetCaseSensitive(handle) Class_VtblCast(handle, IDictionaryVtbl)->get_case_sensitive(handle)
#define IDictionary_SetPrivateKeys(handle, private_keys) \
    Class_VtblCast(handle, IDictionaryVtbl)->set_private_keys(handle, private_keys)
#define IDictionary_GetPrivateKeys(handle) Class_VtblCast(handle, IDictionaryVtbl)->get_private_keys(handle)
#define IDictionary_SetAllowDuplicates(handle, allow_duplicates) \
    Class_VtblCast(handle, IDictionaryVtbl)->set_allow_duplicates(handle, allow_duplicates)
#define IDictionary_GetAllowDuplicates(handle) Class_VtblCast(handle, IDictionaryVtbl)->get_allow_duplicates(handle)

#define IDictionary_SetItemRemoveCallback(handle, user_ptr, callback) \
    Class_VtblCast(handle, IDictionaryVtbl)->set_item_remove_callback(handle, user_ptr, callback)
#define IDictionary_GetItemRemoveCallback(handle, user_ptr, callback) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_item_remove_callback(handle, user_ptr, callback)
#define IDictionary_SetItemKeyChangeCallback(handle, user_ptr, callback) \
    Class_VtblCast(handle, IDictionaryVtbl)->set_item_key_change_callback(handle, user_ptr, callback)
#define IDictionary_GetItemKeyChangeCallback(handle, user_ptr, callback) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_item_key_change_callback(handle, user_ptr, callback)
#define IDictionary_SetItemValueChangeCallback(handle, user_ptr, callback) \
    Class_VtblCast(handle, IDictionaryVtbl)->set_item_value_change_callback(handle, user_ptr, callback)
#define IDictionary_GetItemValueChangeCallback(handle, user_ptr, callback) \
    Class_VtblCast(handle, IDictionaryVtbl)->get_item_value_change_callback(handle, user_ptr, callback)

#define IDictionary_Create()        Dictionary_Create()
#define IDictionary_AddRef(handle)  Dictionary_AddRef(handle)
#define IDictionary_Release(handle) Dictionary_Release(handle)

/*********************************************************************/

#ifdef __cplusplus
}
#endif
