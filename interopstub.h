#pragma once

/*! \file interopstub.h
 * Interop exports required by the DIRECT client.
 */

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************/

typedef bool (*Interop_ExecuteCallback)(void *user_ptr, const char *instance_id, const char *string);
typedef int32_t (*Interop_ReleaseInstanceCallback)(void **user_ptr);
typedef bool (*Interop_InvokeInstanceCallback)(void *user_ptr, echandle method_dictionary_handle,
                                               echandle return_dictionary_handle);
typedef bool (*Interop_ProcessInstanceCallback)(void *user_ptr);

/*********************************************************************/

/*!
 * Called when an instance is created
 * \param type_name type of object to be created
 * \param instance_id id of the object to be created
 * \param instance_id_length maximum length of the InstanceId
 * \param execute_user_ptr user pointer stored with execute callback
 * \param execute execute callback
 * \param invoke_instance pointer to the instance invocation callback function
 * \param release_instance pointer to the instance release/delete callback function
 * \param process_instance pointer to the instance process callback function
 * \param user_ptr pointer associated with instance id
 * \return true on success, false otherwise
 */
bool Interop_CreateInstance(const char *type_name, char *instance_id, int32_t instance_id_length,
                            void *execute_user_ptr, Interop_ExecuteCallback execute,
                            Interop_InvokeInstanceCallback *invoke_instance,
                            Interop_ReleaseInstanceCallback *release_instance,
                            Interop_ProcessInstanceCallback *process_instance, void **user_ptr);

/*!
 * Set an interop function to override by key
 * \param key identifier of option
 * \param value pointer to the function
 * \return true on success, false otherwise
 */
bool Interop_SetOverride(const char *key, void *value);

/*!
 * Set an interop option by key
 * \param key identifier of option
 * \param value value of option
 * \return true on success, false otherwise
 */
bool Interop_SetOption(const char *key, void *value);

/*!
 * Loads interop functions
 * \return true on success, false otherwise
 */
bool Interop_Load(void);
/*!
 * Unloads interop functions
 * \return true on success, false otherwise
 */
bool Interop_Unload(void);

/*********************************************************************/

#ifdef __cplusplus
}
#endif
