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
#include <stdint.h>
#include <math.h>

/* SPI r/w Interface Access */
#define MRF24J40_SPI_RD_SHORT(R)		(R = ((R & 0x3F) << 1))
#define MRF24J40_SPI_WR_SHORT(R)		(R = ((R & 0x3F) << 1) | 0x01)

#define MRF24J40_SPI_RD_LONG(R)			(R = ((R & 0x3FF) << 1) | 0x800)
#define MRF24J40_SPI_WR_LONG(R)			(R = ((R & 0x3FF) << 1) | 0x801)

/* Pin masks */
#define MRF24J40_INT_PIN			0x01
#define MRF24J40_WAK_PIN			0x02
#define MRF24J40_RST_PIN			0x04

/* Clear Channel Assessment (CCA) modes */
#define MRF24J40_CCA_MODE1			0x02 // Energy Above Threshold
#define MRF24J40_CCA_MODE2			0x01 // Carrier Sense Only
#define MRF24J40_CCA_MODE3			0x03 // Carrier Sense With Energy Above Threshold

/* Reception modes */
#define MRF24J40_RXMODE_NORMAL			0x00
#define MRF24J40_RXMODE_ERROR			0x02
#define MRF24J40_RXMODE_PROMISCUOUS		0x01

/* Reception filters */
#define MRF24J40_RXFILTER_ALL			0x00
#define MRF24J40_RXFILTER_CMD			0x04
#define MRF24J40_RXFILTER_DATA			0x02
#define MRF24J40_RXFILTER_BEACON		0x01

/* TRX states */
#define MRF24J40_TX_ON				0x01
#define MRF24J40_RX_ON				0x02
#define MRF24J40_TRX_OFF			0x03
#define MRF24J40_FORCE_TRX_OFF			0x04

/* Battery low-voltage threshold masks */
#define MRF24J40_BATTH_3V5			0x0E
#define MRF24J40_BATTH_3V3			0x0D
#define MRF24J40_BATTH_3V2			0x0C
#define MRF24J40_BATTH_3V1			0x0B
#define MRF24J40_BATTH_2V8			0x0A
#define MRF24J40_BATTH_2V7			0x09
#define MRF24J40_BATTH_2V6			0x08
#define MRF24J40_BATTH_2V5			0x07
#define MRF24J40_BATTH_UNDEF			0x06

/* Security suites */
#define MRF24J40_SECURITY_NONE			0x00
#define MRF24J40_SECURITY_AES_CTR		0x01
#define MRF24J40_SECURITY_AES_CCM128		0x02
#define MRF24J40_SECURITY_AES_CCM64		0x03
#define MRF24J40_SECURITY_AES_CCM32		0x04
#define MRF24J40_SECURITY_AES_CBC_MAC128	0x05
#define MRF24J40_SECURITY_AES_CBC_MAC64		0x06
#define MRF24J40_SECURITY_AES_CBC_MAC32		0x07

/*
 * ATTENTION These functions need to be implemented by the user!
 */
extern uint8_t mrf24j40_rd_short(uint8_t addr) __attribute__((weak));
extern void    mrf24j40_wr_short(uint8_t addr, uint8_t data) __attribute__((weak));
extern uint8_t mrf24j40_rd_long(uint16_t addr) __attribute__((weak));
extern void    mrf24j40_wr_long(uint16_t addr, uint8_t data) __attribute__((weak));
extern void    mrf24j40_rd_fifo(uint16_t addr, uint8_t *data, uint8_t len) __attribute__((weak));
extern void    mrf24j40_wr_fifo(uint16_t addr, uint8_t *data, uint8_t len) __attribute__((weak));
extern void    mrf24j40_pin_ctrl(uint8_t pin_mask, uint8_t pin_state) __attribute__((weak));
extern void    mrf24j40_delay_ms(const double ms) __attribute__((weak));
extern void    mrf24j40_delay_us(const double us) __attribute__((weak));
extern uint8_t mrf24j40_rnd(void) __attribute__((weak));


/*
 * Public functions
 */
void    mrf24j40_hwrst(void);
void    mrf24j40_swrst(uint8_t sw_rstmsk, uint8_t rfrst);

uint8_t mrf24j40_isr_handler(void);
void    mrf24j40_init(void);
void    mrf24j40_config(uint8_t pan_coord, uint8_t bo, uint8_t so, uint8_t hdr_len, uint8_t buf_len);

void    mrf24j40_cca(uint8_t mode);
uint8_t mrf24j40_rssi_firmwreq(uint32_t len);
void    mrf24j40_rssi_fiforeq(void);
void    mrf24j40_config_csmaca(uint8_t slotted);
void    mrf24j40_config_ifs(void);
void    mrf24j40_config_rxmode(uint8_t mode);
void    mrf24j40_config_rxfilter(uint8_t mode);

void    mrf24j40_set_addr(uint8_t *e_addr, uint8_t *s_addr, uint8_t *pan_id);
void    mrf24j40_set_channel(uint8_t ch);
void    mrf24j40_set_txpower(uint8_t txpwr);
void    mrf24j40_set_trxstate(uint8_t state);

void    mrf24j40_config_timed_sleep(uint8_t ext_clk);

uint8_t mrf24j40_rd_rxfifo(void);
void    mrf24j40_wr_txfifo(uint16_t fifo, uint8_t *buf, uint8_t hdr_len, uint8_t buf_len);

void    mrf24j40_config_mac_timer(uint16_t ticks);

void mrf24j40_encrypt_mac(uint16_t fifo, uint8_t suite, uint8_t *key);
void mrf24j40_decrypt_mac(uint8_t suite, uint8_t *key);

void    mrf24j40_config_batmon(uint8_t threshold);
uint8_t mrf24j40_battery_status(void);

#endif //_MRF24J40_H
