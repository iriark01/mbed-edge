// ----------------------------------------------------------------------------
// Copyright 2016-2017 ARM Ltd.
//
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------------------------------------------------------

#ifndef ARM_UC_HUB_STATE_MACHINE_H
#define ARM_UC_HUB_STATE_MACHINE_H

#include <stdint.h>


/**
 * States in the Update Hub.
 */
typedef enum {
    ARM_UC_HUB_STATE_UNINITIALIZED,
    ARM_UC_HUB_STATE_INITIALIZED,
    ARM_UC_HUB_STATE_GET_ACTIVE_FIRMWARE_DETAILS,
    ARM_UC_HUB_STATE_REPORT_ACTIVE_HASH,
    ARM_UC_HUB_STATE_REPORT_ACTIVE_VERSION,
    ARM_UC_HUB_STATE_GET_INSTALLER_DETAILS,
    ARM_UC_HUB_STATE_REPORT_INSTALLER_DETAILS,
    ARM_UC_HUB_STATE_CHECK_OEM_MODE_RESET,
    ARM_UC_HUB_STATE_GET_STORED_FIRMWARE_DETAILS,
    ARM_UC_HUB_STATE_STORED_FIRMWARE_DETAILS_OK,
    ARM_UC_HUB_STATE_STORED_FIRMWARE_DETAILS_ERROR,
    ARM_UC_HUB_STATE_IDLE,
    ARM_UC_HUB_STATE_NOTIFIED,
    ARM_UC_HUB_STATE_CERT_STORED,
    ARM_UC_HUB_STATE_MANIFEST_FETCHED,
    ARM_UC_HUB_STATE_MANIFEST_COMPLETE,
    ARM_UC_HUB_STATE_CHECK_VERSION,
    ARM_UC_HUB_STATE_PREPARE_FIRMWARE_SETUP,
    ARM_UC_HUB_STATE_REQUEST_DOWNLOAD_AUTHORIZATION,
    ARM_UC_HUB_STATE_WAIT_FOR_DOWNLOAD_AUTHORIZATION,
    ARM_UC_HUB_STATE_DOWNLOAD_AUTHORIZED,
    ARM_UC_HUB_STATE_SETUP_FIRMWARE,
    ARM_UC_HUB_STATE_FETCH_FIRST_FRAGMENT,
    ARM_UC_HUB_STATE_STORE_AND_DOWNLOAD,
    ARM_UC_HUB_STATE_WAIT_FOR_STORAGE,
    ARM_UC_HUB_STATE_WAIT_FOR_NETWORK,
    ARM_UC_HUB_STATE_STORE_LAST_FRAGMENT,
    ARM_UC_HUB_STATE_FINALIZE_STORAGE,
    ARM_UC_HUB_STATE_STORAGE_FINALIZED,
    ARM_UC_HUB_STATE_WAIT_FOR_INSTALL_AUTHORIZATION,
    ARM_UC_HUB_STATE_INSTALL_AUTHORIZED,
    ARM_UC_HUB_STATE_ACTIVATE_FIRMWARE,
    ARM_UC_HUB_STATE_REBOOT,
    ARM_UC_HUB_STATE_ERROR_FIRMWARE_MANAGER,
    ARM_UC_HUB_STATE_ERROR_MANIFEST_MANAGER,
    ARM_UC_HUB_STATE_ERROR_SOURCE_MANAGER,
    ARM_UC_HUB_STATE_ERROR_CONTROL_CENTER,
    ARM_UC_HUB_STATE_ERROR_UNKNOWN,
} arm_uc_hub_state_t;

/**
 * @brief Read internal state.
 * @return State
 */
arm_uc_hub_state_t ARM_UC_HUB_getState(void);

/**
 * @brief Set internal state.
 * @details Setting the state will perform actions related to that state.
 *
 * @param state New state.
 */
void ARM_UC_HUB_setState(arm_uc_hub_state_t state);

/**
 * @brief Set callback function for when the Update Client is initialized.
 *
 * @param callback Function pointer.
 */
void ARM_UC_HUB_setInitializationCallback(void (*callback)(int32_t));

#endif // ARM_UC_HUB_STATE_MACHINE_H
