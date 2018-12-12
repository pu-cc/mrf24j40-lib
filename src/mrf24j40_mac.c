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

#include "mrf24j40_mac.h"

/*
 * MLME-RESET.request
 */
void mlme_reset_req(mlme_reset_req_t *req, mlme_reset_cnf_cb_t cnf_cb)
{
	/* disassociation attempts using the MLME-DISASSOCIATE.request primitive will need to be made a priori */
	
	mlme_reset_cnf_t cnf;
	mrf24j40_set_trxstate(MRF24J40_TRX_OFF);

	/* reset MAC sublayer */
	mrf24j40_init();

	if (req->set_default_pib)
	{
		/* reset PIB to defaults*/
		mac_pib.mac_ack_wait_duration = 54;
		mac_pib.mac_assoc_permit = 0;
		mac_pib.mac_auto_request = 1;
		mac_pib.mac_bat_life_ext = 0;
		mac_pib.mac_bat_life_ext_periods = 6;
		mac_pib.mac_beacon_payload = NULL;
		mac_pib.mac_beacon_len = 0;
		mac_pib.mac_bo = 15;
		mac_pib.mac_beacon_tx_time = 0;
		mac_pib.mac_bsn = mrf24j40_rnd();
		mac_pib.mac_coord_e_addr = NULL;
		mac_pib.mac_coord_s_addr = NULL;
		mac_pib.mac_dsn = mrf24j40_rnd();
		mac_pib.mac_gts_permit = 1;
		mac_pib.mac_max_csma_backoffs = 4;
		mac_pib.mac_min_be = 3;
		mac_pib.mac_pan_id = NULL;
		mac_pib.mac_promiscuous_mode = 0;
		mac_pib.mac_rx_on_when_idle = 0;
		mac_pib.mac_s_addr = NULL;
		mac_pib.mac_so = 15;
		mac_pib.mac_transact_persist_time = 0x01f4;
	}

	cnf.status = MAC_ENUM_SUCCESS;
	cnf_cb(&cnf);
}

/*
 * MLME-RESET.confirm
 */
//mlme_reset_cnf_cb_t mlme_reset_cnf_cb(void)
//{
	//...
//}
