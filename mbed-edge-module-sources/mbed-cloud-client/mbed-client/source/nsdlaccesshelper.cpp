/*
 * Copyright (c) 2015 ARM Limited. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "include/nsdlaccesshelper.h"
#include "include/m2mnsdlinterface.h"
#include "sn_nsdl_lib.h"
#include "sn_grs.h"
#include <stdlib.h>

#ifdef TRACE_COAP_PACKAGE
#define TRACE_GROUP "NSDLAccessHelper"
#include "mbed-trace/mbed_trace.h"
#include "sn_grs.h"
#include "sn_coap_header.h"
#endif

// callback function for NSDL library to call into
uint8_t __nsdl_c_callback(struct nsdl_s *nsdl_handle,
                          sn_coap_hdr_s *received_coap_ptr,
                          sn_nsdl_addr_s *address,
                          sn_nsdl_capab_e nsdl_capab)
{
    uint8_t status = 0;
    M2MNsdlInterface *interface = (M2MNsdlInterface*)sn_nsdl_get_context(nsdl_handle);
    if(interface) {
        status = interface->resource_callback(nsdl_handle,
                                              received_coap_ptr,
                                              address, nsdl_capab);
    }
    return status;
}

void* __nsdl_c_memory_alloc(uint16_t size)
{
    if(size)
        return malloc(size);
    else
        return 0;
}

void __nsdl_c_memory_free(void *ptr)
{
    if(ptr)
        free(ptr);
}


#ifdef TRACE_COAP_PACKAGE
static void trace_coap_header(const char *prefix, sn_coap_hdr_s *header)
{
    if(header->options_list_ptr) {
        if(header->options_list_ptr->uri_query_ptr) {
            tr_debug("%s: query: '%.*s'\n", prefix, header->options_list_ptr->uri_query_len, header->options_list_ptr->uri_query_ptr);
        }
    }

    if(header->payload_len) {
        tr_debug("%s: payload: '%.*s'\n", prefix, header->payload_len, header->payload_ptr);
    }
}

static void trace_coap_message(const char *prefix, struct nsdl_s * nsdl_handle, uint8_t *data_ptr, uint16_t data_len)
{
    coap_version_e version = COAP_VERSION_1;
    sn_coap_hdr_s *header = sn_coap_parser(nsdl_handle->grs->coap, data_len, data_ptr, &version);

    trace_coap_header(prefix, header);
    sn_coap_parser_release_allocated_coap_msg_mem(nsdl_handle->grs->coap, header);
}
#endif

uint8_t __nsdl_c_send_to_server(struct nsdl_s * nsdl_handle,
                                sn_nsdl_capab_e protocol,
                                uint8_t *data_ptr,
                                uint16_t data_len,
                                sn_nsdl_addr_s *address_ptr)
{
#ifdef TRACE_COAP_PACKAGE
    trace_coap_message("nsdl_c_send_to_server", nsdl_handle, data_ptr, data_len);
#endif
    uint8_t status = 0;
    M2MNsdlInterface *interface = (M2MNsdlInterface*)sn_nsdl_get_context(nsdl_handle);
#if defined(FEA_TRACE_SUPPORT) || MBED_CONF_MBED_TRACE_ENABLE || MBED_EDGE_BUILD_CFG_MBED_TRACE || (defined(MBED_EDGE_BUILD_CFG) && !defined(NDEBUG))
    coap_version_e version = COAP_VERSION_UNKNOWN;
    sn_coap_hdr_s *header = sn_coap_parser(nsdl_handle->grs->coap, data_len, data_ptr, &version);
    sn_nsdl_print_coap_data(header, true);
    sn_coap_parser_release_allocated_coap_msg_mem(nsdl_handle->grs->coap, header);
#endif
    if(interface) {
        status = interface->send_to_server_callback(nsdl_handle,
                                                           protocol, data_ptr,
                                                           data_len, address_ptr);
    }
    return status;
}

uint8_t __nsdl_c_received_from_server(struct nsdl_s * nsdl_handle,
                                      sn_coap_hdr_s *coap_header,
                                      sn_nsdl_addr_s *address_ptr)
{
    uint8_t status = 0;
    M2MNsdlInterface *interface = (M2MNsdlInterface*)sn_nsdl_get_context(nsdl_handle);
#ifdef TRACE_COAP_PACKAGE
    trace_coap_header("__nsdl_c_received_from_server", coap_header);
#endif
    if(interface) {
        status = interface->received_from_server_callback(nsdl_handle,
                                                          coap_header,
                                                          address_ptr);
    }
    return status;
}

uint8_t __nsdl_c_auto_obs_token(struct nsdl_s *nsdl_handle, const char *path, uint8_t *token)
{
    M2MNsdlInterface *interface = (M2MNsdlInterface*)sn_nsdl_get_context(nsdl_handle);
    if(interface) {
        return interface->find_auto_obs_token(path, token);
    }
    return 0;
}

void* __socket_malloc( void * context, size_t size)
{
    (void) context;
    return malloc(size);
}

void __socket_free(void * context, void * ptr)
{
    (void) context;
    free(ptr);
}

