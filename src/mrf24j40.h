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

#ifndef _MRF24J40_H
#define _MRF24J40_H

#include "mrf24j40_regmap.h"

/* SPI r/w Interface Access */
#define MRF24J40_SPI_RD_SHORT(R)	(R = ((R & 0x3F) << 1))
#define MRF24J40_SPI_WR_SHORT(R)	(R = ((R & 0x3F) << 1) | 0x01)

#define MRF24J40_SPI_RD_LONG(R)		(R = ((R & 0x3FF) << 1) | 0x800)
#define MRF24J40_SPI_WR_LONG(R)		(R = ((R & 0x3FF) << 1) | 0x801)

/* Pin masks */
#define MRF24J40_INT_PIN		0x01
#define MRF24J40_WAK_PIN		0x02
#define MRF24J40_RST_PIN		0x04

/* Clear Channel Assessment (CCA) modes */
#define MRF24J40_CCA_MODE1		0x02 // Energy Above Threshold
#define MRF24J40_CCA_MODE2		0x01 // Carrier Sense Only
#define MRF24J40_CCA_MODE3		0x03 // Carrier Sense With Energy Above Threshold

/* Reception modes */
#define MRF24J40_RXMODE_NORMAL		0x00
#define MRF24J40_RXMODE_ERROR		0x02
#define MRF24J40_RXMODE_PROMISCUOUS	0x01

/* Reception filters */
#define MRF24J40_RXFILTER_ALL		0x00
#define MRF24J40_RXFILTER_CMD		0x04
#define MRF24J40_RXFILTER_DATA		0x02
#define MRF24J40_RXFILTER_BEACON	0x01

/*
 * ATTENTION These functions need to be implemented by the user!
 */
extern uint8_t mrf24j40_rd_short(uint8_t addr);
extern void    mrf24j40_wr_short(uint8_t addr, uint8_t data);
extern uint8_t mrf24j40_rd_long(uint16_t addr);
extern void    mrf24j40_wr_long(uint16_t addr, uint8_t data);
extern void    mrf24j40_rd_fifo(uint16_t addr, uint8_t *data, uint8_t len);
extern void    mrf24j40_wr_fifo(uint16_t addr, uint8_t *data, uint8_t len);
extern void    mrf24j40_pin_ctrl(uint8_t pin_mask, uint8_t pin_state);
extern void    mrf24j40_delay_ms(const double ms);
extern void    mrf24j40_delay_us(const double us);

/*
 * Public functions
 */
void    mrf24j40_hwrst(void);
void    mrf24j40_swrst(uint8_t sw_rstmsk, uint8_t rfrst);

void    mrf24j40_init(void);
void    mrf24j40_cca(uint8_t mode);
uint8_t mrf24j40_rssi_firmwreq(uint32_t len);
void    mrf24j40_rssi_fiforeq(void);
void    mrf24j40_config_ifs(void);
void    mrf24j40_config_rxmode(uint8_t mode);
void    mrf24j40_config_rxfilter(uint8_t mode);

#endif //_MRF24J40_H
