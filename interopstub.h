#pragma once

/*! \file interopstub.h
 * Interop exports required by the DIRECT client.
 */

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************/

typedef bool (*Interop_ExecuteCallback)(void *UserPtr, const char *InstanceId, echandle MethodDictionaryHandle,
                                        echandle ReturnDictionaryHandle);
typedef int32_t (*Interop_ReleaseInstanceCallback)(void **UserPtr);
typedef bool (*Interop_InvokeInstanceCallback)(void *UserPtr, echandle MethodDictionaryHandle,
                                               echandle ReturnDictionaryHandle);
typedef bool (*Interop_ProcessInstanceCallback)(void *UserPtr);

/*********************************************************************/

/*!
 * Called when an instance is created
 * \param TypeName type of object to be created
 * \param InstanceId id of the object to be created
 * \param InstanceIdLength maximum length of the InstanceId
 * \param ExecuteUserPtr user pointer stored with execute callback
 * \param Execute execute callback
 * \param Invoke pointer to the instance invocation callback function
 * \param Release pointer to the instance release/delete callback function
 * \param Process pointer to the instance process callback function
 * \param UserPtr pointer associated with instance id
 * \return true on success, false otherwise
 */
bool Interop_CreateInstance(const char *TypeName, char *InstanceId, int32_t InstanceIdLength, void *ExecuteUserPtr,
                            Interop_ExecuteCallback Execute, Interop_InvokeInstanceCallback *Invoke,
                            Interop_ReleaseInstanceCallback *Release, Interop_ProcessInstanceCallback *Process,
                            void **UserPtr);

/*!
 * Set an interop function to override by key
 * \param Key identifier of option
 * \param Value pointer to the function
 * \return true on success, false otherwise
 */
bool Interop_SetOverride(const char *Key, void *Value);

/*!
 * Set an interop option by key
 * \param Key identifier of option
 * \param Value value of option
 * \return true on success, false otherwise
 */
bool Interop_SetOption(const char *Key, void *Value);

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
