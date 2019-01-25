/*
 * IEEE 802.15.4-2003 MAC sublayer service implementation
 *
 * Copyright (C) 2017, 2018 Patrick Urban <patrick.urban@web.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _MRF24J40_MAC_H
#define _MRF24J40_MAC_H

#include "mrf24j40.h"

#define PHY_MAX_PHY_PACKET_SIZE		127

/* MAC sublayer constants */
#define MAC_BASE_SLOT_DURATION		60
#define MAC_NUM_SUPERFRAME_SLOTS	16
#define MAC_BASE_SUPERFRAME_DURATION	(MAC_BASE_SLOT_DURATION * MAC_NUM_SUPERFRAME_SLOTS)
#define MAC_MAX_BACKOFF_EXPONENT	5
#define MAC_MAX_BEACON_OVERHEAD		75
#define MAC_MAX_BEACON_PAYLOAD_LENGTH	(PHY_MAX_PHY_PACKET_SIZE - MAC_MAX_BEACON_OVERHEAD)
#define MAC_GTS_DESC_PERSISTENCE_TIME	4
#define MAC_MAX_FRAME_OVERHEAD		25
#define MAC_MAX_FRAME_RESPONSE_TIME	1220
#define MAC_MAX_FRAME_RETRIES		3
#define MAC_MAX_LOST_BEACONS		4
#define MAC_MAX_MAC_FRAME_SIZE		(PHY_MAX_PHY_PACKET_SIZE - MAC_MAX_FRAME_OVERHEAD)
#define MAC_MAX_SIFS_FRAME_SIZE		18
#define MAC_MIN_CAP_LENGTH		440
#define MAC_MIN_LIFS_PERIOD		40
#define MAC_MIN_SIFS_PERIOD		12
#define MAC_RESPONSE_WAIT_TIME		(32 * MAC_BASE_SUPERFRAME_DURATION)
#define MAC_UNIT_BACKOFF_PERIOD		20

typedef enum {
	MAC_ENUM_SUCCESS = 0,
	/* 0x01 - 0xDF: reserved */
	/* 0x80 - 0xDF: reserved */
	MAC_ENUM_BEACON_LOSS = 0xE0,
	MAC_ENUM_CHANNEL_ACCESS_FAILURE,
	MAC_ENUM_DENIED,
	MAC_ENUM_DISABLE_TRX_FAILURE,
	MAC_ENUM_FAILED_SECURITY_CHECK,
	MAC_ENUM_FRAME_TOO_LONG,
	MAC_ENUM_INVALID_GTS,
	MAC_ENUM_INVALID_HANDLE,
	MAC_ENUM_INVALID_PARAMETER,
	MAC_ENUM_NO_ACK,
	MAC_ENUM_NO_BEACON,
	MAC_ENUM_NO_DATA,
	MAC_ENUM_NO_SHORT_ADDRESS,
	MAC_ENUM_OUT_OF_CAP,
	MAC_ENUM_PAN_ID_CONFLICT,
	MAC_ENUM_REALIGNMENT,
	MAC_ENUM_TRANSACTION_EXPIRED,
	MAC_ENUM_TRANSACTION_OVERFLOW,
	MAC_ENUM_TX_ACTIVE,
	MAC_ENUM_UNAVAILABLE_KEY,
	MAC_ENUM_UNSUPPORTED_ATTRIBUTE
} mac_enum_e;

typedef enum {
	MAC_ASSOC_SUCCESS = 0,
	MAC_ASSOC_PAN_AT_CAPACITY,
	MAC_ASSOC_PAN_ACCESS_DENIED
	/* 0x03 – 0x7F: reserved */
	/* 0x80 – 0xFF: reserved for MAC primitive enumeration values */
} mac_assoc_status_e;

/*
 * MCPS-SAP primitives: (*) optional for an RFD
 *
 * 1) MCPS-DATA (req, cnf, ind)
 * 2) MCPS-PURGE (req*, cnf*)
 */

/*
 * MCPS-DATA.indication
 */
typedef struct {
	uint8_t src_addr_mode;
	uint8_t *src_pan_id;
	uint8_t *src_addr;
	uint8_t dst_addr_mode;
	uint8_t *dst_pan_id;
	uint8_t *dst_addr;
	uint8_t msdu_len;
	uint8_t *msdu;
	uint8_t mpdu_link_quality;
	uint8_t security_use;
	uint8_t acl_entry;
} mcps_data_ind_t;

void mcps_data_ind(mcps_data_ind_t *ind);

/*
 * MCPS-DATA.confirm
 */
typedef struct {
	uint8_t msdu_hndl;
	mac_enum_e status;
} mcps_data_cnf_t;

typedef void (* mcps_data_cnf_cb_t)(void);

mcps_data_cnf_cb_t mcps_data_cnf_cb(void);

/*
 * MCPS-DATA.request
 */
typedef struct {
	uint8_t src_addr_mode;
	uint8_t *src_pan_id;
	uint8_t *src_addr;
	uint8_t dst_addr_mode;
	uint8_t *dst_pan_id;
	uint8_t *dst_addr;
	uint8_t msdu_len;
	uint8_t *msdu;
	uint8_t msdu_hndl;
	uint8_t tx_options;
} mcps_data_req_t;

void mcps_data_req(mcps_data_req_t *req, mcps_data_cnf_cb_t cnf_cb);

/*
 * MCPS-PURGE.confirm
 */
typedef struct {
	uint8_t msdu_hndl;
	mac_enum_e status;
} mcps_purge_cnf_t;

typedef void (* mcps_purge_cnf_cb_t)(void);

mcps_purge_cnf_cb_t mcps_purge_cnf_cb(void);

/*
 * MCPS-PURGE.request
 */
typedef struct {
	uint8_t msdu_hndl;
} mcps_purge_req_t;

void mcps_purge_req(mcps_purge_req_t *req, mcps_purge_cnf_cb_t cnf_cb);

/*
 * MLME-SAP primitives: (*) optional for an RFD
 *
 * 1)  MLME-ASSOCIATE (req, cnf, ind*, rsp*)
 * 7)  MLME-RESET (req, cnf)
 */

/*
 * MLME-ASSOCIATE.response
 */

typedef struct {
	uint8_t *dev_addr;
	uint8_t *assoc_s_addr;
	mac_assoc_status_e status;
	uint8_t securtiy_en;
} mlme_associate_rsp_t;

typedef void (* mlme_associate_rsp_cb_t)(void);

mlme_associate_rsp_cb_t mlme_associate_rsp_cb(void);

/*
 * MLME-ASSOCIATE.indication
 */

typedef struct {
	uint8_t *dev_addr;
	uint8_t cap_info;
	uint8_t securtiy_use;
	uint8_t acl_entry;
} mlme_associate_ind_t;

void mlme_associate_ind(mlme_associate_ind_t *ind, mlme_associate_rsp_cb_t rsp_cb);

/*
 * MLME-ASSOCIATE.confirm
 */
typedef struct {
	uint8_t *assoc_s_addr;
	mac_enum_e status;
} mlme_associate_cnf_t;

typedef void (* mlme_associate_cnf_cb_t)(void);

mlme_associate_cnf_cb_t mlme_associate_cnf_cb(void);

/*
 * MLME-ASSOCIATE.request
 */
typedef struct {
	uint8_t logical_channel;
	uint8_t coord_addr_mode;
	uint8_t coord_pan_id;
	uint8_t *coord_addr;
	uint8_t cap_info;
	uint8_t securtiy_en;
} mlme_associate_req_t;

void mlme_associate_req(mlme_associate_req_t *req, mlme_associate_cnf_cb_t cnf_cb);

/*
 * MLME-RESET.confirm
 */
typedef struct {
	mac_enum_e status;
} mlme_reset_cnf_t;

typedef void (* mlme_reset_cnf_cb_t)(mlme_reset_cnf_t *);

mlme_reset_cnf_cb_t mlme_reset_cnf_cb(mlme_reset_cnf_t cnf);

/*
 * MLME-RESET.request
 */
typedef struct {
	uint8_t set_default_pib;
} mlme_reset_req_t;

void mlme_reset_req(mlme_reset_req_t *req, mlme_reset_cnf_cb_t cnf_cb);

/*
 * MAC PIB (PAN information base)
 */
struct mac_pib_d
{
	uint8_t mac_ack_wait_duration;
	uint8_t mac_assoc_permit;
	uint8_t mac_auto_request;
	uint8_t mac_bat_life_ext;
	uint8_t mac_bat_life_ext_periods;
	uint8_t *mac_beacon_payload;
	uint8_t mac_beacon_len;
	uint8_t mac_bo;
	uint32_t mac_beacon_tx_time;
	uint8_t mac_bsn;
	uint8_t *mac_coord_e_addr;
	uint8_t *mac_coord_s_addr;
	uint8_t mac_dsn;
	uint8_t mac_gts_permit;
	uint8_t mac_max_csma_backoffs;
	uint8_t mac_min_be;
	uint8_t *mac_pan_id;
	uint8_t mac_promiscuous_mode;
	uint8_t mac_rx_on_when_idle;
	uint8_t *mac_s_addr;
	uint8_t mac_so;
	uint16_t mac_transact_persist_time;

	/* ACL */
	//acldesc_t mac_acl_entry_descr;
	//uint8_t mac_acl_entry_descr_size;

	/* securtiy suite */
	//uint8_t mac_default_security;
	//uint8_t mac_default_security_mat_len;
	//uint8_t *mac_default_security_mat;
	//uint8_t mac_default_security_suite;
	//uint8_t mac_security_mode;
} mac_pib;

#endif //_MRF24J40_MAC_H
