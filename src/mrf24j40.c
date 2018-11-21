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

/* ATTENTION These registers need to be allocated by the user! */
extern uint8_t mrf24j40_rxfifo[144];
extern uint8_t mrf24j40_txfifo[128];
extern uint8_t aes_key[16];
extern uint8_t aes_nonce[13];

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

uint8_t mrf24j40_isr_handler(void)
{
	uint8_t reg;
	uint8_t irqmsk = mrf24j40_rd_short(MRF24J40_R_INTSTAT);

	if (irqmsk & MRF24J40_IRQ_SLPIF)
	{
		/* acknowledge SLPIF: enable low current sleep mode */
		reg = mrf24j40_rd_short(MRF24J40_R_SLPACK);
		MRF24J40_SET_SLPACK(reg, 1);
		mrf24j40_wr_short(MRF24J40_R_SLPACK, reg);
	}
	if (irqmsk & MRF24J40_IRQ_WAKEIF)
	{
		/* NOTE This is an alert to the host MCU: */
		/* May be useful if the MCU is in a low current (sleep) mode */
	}
	if (irqmsk & MRF24J40_IRQ_HSYMTMRIF)
	{
		/* TODO implement timer */
	}
	if (irqmsk & MRF24J40_IRQ_SECIF)
	{
		/* TODO implement security suite */
	}
	if (irqmsk & MRF24J40_IRQ_RXIF)
	{
		mrf24j40_rd_rxfifo();
	}
	if (irqmsk & (MRF24J40_IRQ_TXG1IF | MRF24J40_IRQ_TXG2IF | MRF24J40_IRQ_TXNIF))
	{
		mrf24j40_rd_short(MRF24J40_R_TXSTAT);

		/* check if MIC error has occurred */
		reg = mrf24j40_rd_short(MRF24J40_R_RXSR);
		if (MRF24J40_GET_UPSECERR(reg))
		{
			/* write '1' to clear */
			mrf24j40_wr_short(MRF24J40_R_RXFLUSH, reg);
		}
	}

	return irqmsk;
}

void mrf24j40_init(void)
{
	/* perform hard- and software reset */
	mrf24j40_hwrst();
	mrf24j40_swrst(0x07, 0);

	/* See datasheet section 3.2: Initialization */
	mrf24j40_wr_short(MRF24J40_R_PACON2, 0x98);
	mrf24j40_wr_short(MRF24J40_R_TXSTBL, 0x95);
	mrf24j40_wr_long(MRF24J40_R_RFCON1,  0x02);
	mrf24j40_wr_long(MRF24J40_R_RFCON2,  0x80);
	mrf24j40_wr_long(MRF24J40_R_RFCON6,  0x90);
	mrf24j40_wr_long(MRF24J40_R_RFCON8,  0x10);

	/* device configuration */
	mrf24j40_cca(MRF24J40_CCA_MODE3);
	mrf24j40_rssi_fiforeq();
	mrf24j40_config_ifs();

	/* enable interrupts */
	mrf24j40_wr_short(MRF24J40_R_INTCON, 0x00); // 0x00: all

	/* set RFOPT = 0x03 */
	mrf24j40_wr_long(MRF24J40_R_RFCON0,  0x03);

	/* set transmitter power */
	mrf24j40_wr_long(MRF24J40_R_RFCON3,  0x00); // 0x00: highest / 0xF8: very poor

	/* set the rx mode */
	mrf24j40_config_rxmode(MRF24J40_RXMODE_NORMAL);
	mrf24j40_config_rxfilter(MRF24J40_RXFILTER_ALL);

	/* reset RF state machine */
	mrf24j40_swrst(0, 1);
}

void mrf24j40_cca(uint8_t mode)
{
	/* obtain current register state */
	uint8_t reg = mrf24j40_rd_long(MRF24J40_R_BBREG2);

	MRF24J40_SET_CCAMODE(reg, mode);
	mrf24j40_wr_long(MRF24J40_R_BBREG2, reg);

	if (mode & MRF24J40_CCA_MODE2)
	{
		/* no need to load register value anew */
		MRF24J40_SET_CCACSTH(reg, 0x0E); // recommended value
		mrf24j40_wr_long(MRF24J40_R_BBREG2, reg);
	}

	if (mode & MRF24J40_CCA_MODE1)
	{
		reg = mrf24j40_rd_short(MRF24J40_R_CCAEDTH);
		MRF24J40_SET_CCAEDTH(reg, 0x60); // recommended value (approx. -69 dBm)
		mrf24j40_wr_short(MRF24J40_R_CCAEDTH, reg);
	}
}

uint8_t mrf24j40_rssi_firmwreq(uint32_t len)
{
	uint8_t rssi = 0, reg;
	uint8_t restore = mrf24j40_rd_short(MRF24J40_R_BBREG6);
	uint32_t i;

	/* check if RSSI mode 2 is enabled */
	restore = MRF24J40_GET_RSSIMODE2(restore);

	for (i = 0; i < len; i++)
	{
		/* initiate RSSI calculation */
		mrf24j40_wr_short(MRF24J40_R_BBREG6, 0x80);

		/* wait until RSSI calculation is complete */
		while (mrf24j40_rd_short(MRF24J40_R_BBREG6) != 1);

		reg = mrf24j40_rd_long(MRF24J40_R_RSSI);

		if (reg > rssi) {
			rssi = reg;
		}
	}

	/* if necessary: restore RSSI mode 2 */
	if (restore) {
		mrf24j40_wr_short(MRF24J40_R_BBREG6, 0x40);
	}

	return rssi;
}

void mrf24j40_rssi_fiforeq(void)
{
	uint8_t reg = mrf24j40_rd_short(MRF24J40_R_BBREG6);

	MRF24J40_SET_RSSIMODE2(reg, 1);
	mrf24j40_wr_short(MRF24J40_R_BBREG6, reg);
}

void mrf24j40_config_ifs(void)
{
	uint8_t reg;

	/* aMinSIFSPeriod = MSIFS + RFSTBL */
	reg = mrf24j40_rd_short(MRF24J40_R_TXSTBL);
	MRF24J40_SET_MSIFS(reg, 0x05); // datasheet default: 16 us
	MRF24J40_SET_RFSTBL(reg, 0x09); // datasheet recommendation
	mrf24j40_wr_short(MRF24J40_R_TXSTBL, reg);

	/* aMinLIFSPeriod = MLFS + RFSTBL */
	reg = mrf24j40_rd_short(MRF24J40_R_TXPEND);
	MRF24J40_SET_MLIFS(reg, 0x1F); // datasheet recommendation
	mrf24j40_wr_short(MRF24J40_R_TXPEND, reg);

	/* aTurnaroundTime = TURNTIME + RFSTBL */
	reg = mrf24j40_rd_short(MRF24J40_R_TXTIME);
	MRF24J40_SET_TURNTIME(reg, 0x03); // datasheet recommendation
	mrf24j40_wr_short(MRF24J40_R_TXTIME, reg);
}

void mrf24j40_config_rxmode(uint8_t mode)
{
	uint8_t reg = mrf24j40_rd_short(MRF24J40_R_RXMCR);

	switch (mode)
	{
		case MRF24J40_RXMODE_NORMAL:
			MRF24J40_SET_ERRPKT(reg, 0);
			MRF24J40_SET_PROMI(reg, 0);
			break;

		case MRF24J40_RXMODE_ERROR:
			MRF24J40_SET_ERRPKT(reg, 1);
			MRF24J40_SET_PROMI(reg, 0);
			break;

		case MRF24J40_RXMODE_PROMISCUOUS:
			MRF24J40_SET_ERRPKT(reg, 0);
			MRF24J40_SET_PROMI(reg, 1);
			break;

		default:
			/* something has gone wrong here */
			return;
	}

	mrf24j40_wr_short(MRF24J40_R_RXMCR, reg);
}

void mrf24j40_config_rxfilter(uint8_t filter)
{
	uint8_t reg = mrf24j40_rd_short(MRF24J40_R_RXFLUSH);

	switch (filter)
	{
		case MRF24J40_RXFILTER_ALL:
			MRF24J40_SET_CMDONLY(reg, 1);
			MRF24J40_SET_DATAONLY(reg, 1);
			MRF24J40_SET_BCNONLY(reg, 1);
			break;

		case MRF24J40_RXFILTER_CMD:
			MRF24J40_SET_CMDONLY(reg, 1);
			MRF24J40_SET_DATAONLY(reg, 0);
			MRF24J40_SET_BCNONLY(reg, 0);
			break;

		case MRF24J40_RXFILTER_DATA:
			MRF24J40_SET_CMDONLY(reg, 0);
			MRF24J40_SET_DATAONLY(reg, 1);
			MRF24J40_SET_BCNONLY(reg, 0);
			break;

		case MRF24J40_RXFILTER_BEACON:
			MRF24J40_SET_CMDONLY(reg, 0);
			MRF24J40_SET_DATAONLY(reg, 0);
			MRF24J40_SET_BCNONLY(reg, 1);
			break;

		default:
			/* something has gone wrong here */
			return;
	}

	mrf24j40_wr_short(MRF24J40_R_RXFLUSH, reg);
}

void mrf24j40_set_addr(uint8_t *e_addr, uint8_t *s_addr, uint8_t *pan_id)
{
	/* program the associated coordinator's 64-bit extended address */
	mrf24j40_wr_long(MRF24J40_R_ASSOEADR0, e_addr[0]); /* 0..7 */
	mrf24j40_wr_long(MRF24J40_R_ASSOEADR1, e_addr[1]);
	mrf24j40_wr_long(MRF24J40_R_ASSOEADR2, e_addr[2]);
	mrf24j40_wr_long(MRF24J40_R_ASSOEADR3, e_addr[3]);
	mrf24j40_wr_long(MRF24J40_R_ASSOEADR4, e_addr[4]);
	mrf24j40_wr_long(MRF24J40_R_ASSOEADR5, e_addr[5]);
	mrf24j40_wr_long(MRF24J40_R_ASSOEADR6, e_addr[6]);
	mrf24j40_wr_long(MRF24J40_R_ASSOEADR7, e_addr[7]);

	/* program the associated coordinator's 16-bit short address */
	mrf24j40_wr_long(MRF24J40_R_ASSOSADR0, s_addr[0]); /* 0..7 */
	mrf24j40_wr_long(MRF24J40_R_ASSOSADR1, s_addr[1]);

	/* program source pan id */
	mrf24j40_wr_short(MRF24J40_R_PANIDL, pan_id[0]); /* 0..7 */
	mrf24j40_wr_short(MRF24J40_R_PANIDH, pan_id[1]);
}

void mrf24j40_set_channel(uint8_t ch)
{
	uint8_t reg;

	reg = mrf24j40_rd_long(MRF24J40_R_RFCON0);
	MRF24J40_SET_CHANNEL(reg, ch);
	mrf24j40_wr_long(MRF24J40_R_RFCON0, reg);

	/* reset the RF state machine */
	mrf24j40_swrst(0, 1);
}

void mrf24j40_set_txpower(uint8_t txpwr)
{
	mrf24j40_wr_long(MRF24J40_R_RFCON3, (txpwr << 3));
}

void mrf24j40_config_timed_sleep(uint8_t ext_clk)
{
	uint8_t reg;

	/* enable sleep clock generation */
	reg = mrf24j40_rd_long(MRF24J40_R_SLPCON0);
	MRF24J40_SET_SLPCLKEN(reg, 0); // 0: enabled
	mrf24j40_wr_long(MRF24J40_R_SLPCON0, reg);

	/* frequency can be further divided */
	reg = mrf24j40_rd_long(MRF24J40_R_SLPCON1);
	MRF24J40_SET_CLKOUTEN(reg, 0); // 0: enable CLKOUT pin 26 (discontinued)
	MRF24J40_SET_SLPCLKDIV(reg, (ext_clk ? 0x00 : 0x01));
	mrf24j40_wr_long(MRF24J40_R_SLPCON1, reg);

	/* select clock source */
	reg = mrf24j40_rd_long(MRF24J40_R_RFCON7);
	MRF24J40_SET_SLPCLKSEL(reg, (ext_clk ? 0x01 : 0x02));
	mrf24j40_wr_long(MRF24J40_R_RFCON7, reg);

	/* sleep clock calibration */
	reg = mrf24j40_rd_long(MRF24J40_R_SLPCAL2);
	MRF24J40_SET_SLPCALEN(reg, 1);
	mrf24j40_wr_long(MRF24J40_R_SLPCAL2, reg);

	do {
		reg = mrf24j40_rd_long(MRF24J40_R_SLPCAL2);
	} while (reg != 0x80);

	/* program sleep mode counters */
	reg = mrf24j40_rd_short(MRF24J40_R_SLPACK);
	MRF24J40_SET_WAKECNTL(reg, (ext_clk ? 0x42 : 0xC8));
	mrf24j40_wr_short(MRF24J40_R_SLPACK, reg);

	reg = mrf24j40_rd_short(MRF24J40_R_RFCTL);
	MRF24J40_SET_WAKECNTH(reg, 0);
	mrf24j40_wr_short(MRF24J40_R_RFCTL, reg);

	mrf24j40_wr_long(MRF24J40_R_WAKETIMEL, (ext_clk ? 0x45 : 0xD2));
	mrf24j40_wr_long(MRF24J40_R_WAKETIMEH, 0);
}

uint8_t mrf24j40_rd_rxfifo(void)
{
	uint8_t len, reg = 0;

	/* disable receiving packets off air */
	MRF24J40_SET_RXDECINV(reg, 1);
	mrf24j40_wr_short(MRF24J40_R_BBREG1, reg);

	/* get RXFIFO frame length */
	len = mrf24j40_rd_long(MRF24J40_RX_FIFO);

	if (len > MRF24J40_RX_FIFO_LEN) {
		len = MRF24J40_RX_FIFO_LEN;
	}

	/* read FIFO in burst mode */
	mrf24j40_rd_fifo(MRF24J40_RX_FIFO + 1, mrf24j40_rxfifo, len + 4); // + 4: fcs(2) + lqi + rssi

	/* enable receiving packets */
	mrf24j40_wr_short(MRF24J40_R_BBREG1, 0);

	return len;
}

void mrf24j40_wr_txfifo(uint16_t fifo, uint8_t *buf, uint8_t hdr_len, uint8_t buf_len)
{
	uint8_t reg;

	/* header and frame length */
	mrf24j40_wr_long(fifo, hdr_len);
	mrf24j40_wr_long(fifo + 1, buf_len);

	/* write fifo in burst mode */
	mrf24j40_wr_fifo(fifo + 2, buf, buf_len);

	/* trigger the packet tranmsission */
	switch (fifo) {
		case MRF24J40_TXNFIFO:
			reg = mrf24j40_rd_short(MRF24J40_R_TXNCON);
			MRF24J40_SET_TXNTRIG(reg, 1);
			mrf24j40_wr_short(MRF24J40_R_TXNCON, reg);
			break;

		case MRF24J40_TXBFIFO:
			/* NOTE only single shot, TXBFIFO will be flushed? */
			reg = mrf24j40_rd_short(MRF24J40_R_TXBCON0);
			MRF24J40_SET_TXBTRIG(reg, 1);
			mrf24j40_wr_short(MRF24J40_R_TXBCON0, reg);
			break;

		case MRF24J40_TXG1FIFO:
			reg = mrf24j40_rd_short(MRF24J40_R_TXG1CON);
			MRF24J40_SET_TXGTRIG(reg, 1);
			mrf24j40_wr_short(MRF24J40_R_TXG1CON, reg);
			break;

		case MRF24J40_TXG2FIFO:
			reg = mrf24j40_rd_short(MRF24J40_R_TXG2CON);
			MRF24J40_SET_TXGTRIG(reg, 1);
			mrf24j40_wr_short(MRF24J40_R_TXG2CON, reg);
			break;

		default:
			/* something has gone wrong here */
			return;
	}
}