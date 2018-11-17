/*
 * Low-level library for the
 * Microchip MRF24J40 IEEE 802.15.4 2.4 GHz RF Transceiver
 *
 * Based on the Microchip DS39776C datasheet
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

#include "mrf24j40.h"

void mrf24j40_hwrst(void)
{
	mrf24j40_pin_ctrl(MRF24J40_RST_PIN, 0x00);
	mrf24j40_delay_us(250);
	mrf24j40_pin_ctrl(MRF24J40_RST_PIN, 0x04);
	mrf24j40_delay_ms(2);
}

void mrf24j40_swrst(uint8_t sw_rstmsk, uint8_t rfrst)
{
	uint8_t reg;

	if (sw_rstmsk)
	{
		mrf24j40_wr_short(MRF24J40_R_SOFTRST, sw_rstmsk);

		while (mrf24j40_rd_short(MRF24J40_R_SOFTRST) != 0);
	}

	if (rfrst)
	{
		reg = mrf24j40_rd_short(MRF24J40_R_RFCTL);
		MRF24J40_SET_RFRST(reg, 1);
		mrf24j40_wr_short(MRF24J40_R_RFCTL, reg);
		MRF24J40_SET_RFRST(reg, 0);
		mrf24j40_wr_short(MRF24J40_R_RFCTL, reg);

		mrf24j40_delay_us(192);
	}
}
