/*
 * Register definitions for the
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

#ifndef _MRF24J40_REGMAP_H
#define _MRF24J40_REGMAP_H

/*
 * FIFO Addresses
 */
#define MRF24J40_RX_FIFO			0x300
#define MRF24J40_RX_FIFO_LEN			0x8F // 144 Bytes
#define MRF24J40_TXNFIFO			0x000
#define MRF24J40_TXBFIFO			0x080
#define MRF24J40_TXG1FIFO			0x100
#define MRF24J40_TXG2FIFO			0x180
#define MRF24J40_TX_FIFO_LEN			0x7F // 128 Bytes

/*
 * Security Key Memory Addresses
 */
#define MRF24J40_KEY_RX_FIFO			0x2B0
#define MRF24J40_KEY_TX_NORMAL			0x280
#define MRF24J40_KEY_TX_GTS1			0x290
#define MRF24J40_KEY_TX_GTS2			0x2A0
#define MRF24J40_KEY_TX_BEACON			0x2A0
#define MRF24J40_KEY_LEN			0x0F  // 128 Bits

/*
 * 2-1: Receive MAC Control Register
 */
#define MRF24J40_R_RXMCR			0x00

#define MRF24J40_M_NOACKRSP			0x20 /* mask bit 5 */
	#define MRF24J40_SET_NOACKRSP(R,V)	(R = (R & (MRF24J40_M_NOACKRSP ^ 0xFF)) | ((V & 0x01) << 5))
	#define MRF24J40_GET_NOACKRSP(R)	((R & MRF24J40_M_NOACKRSP) >> 5)

#define MRF24J40_M_PANCOORD			0x08 /* mask bit 3 */
	#define MRF24J40_SET_PANCOORD(R,V)	(R = (R & (MRF24J40_M_PANCOORD ^ 0xFF)) | ((V & 0x01) << 3))
	#define MRF24J40_GET_PANCOORD(R)	((R & MRF24J40_M_PANCOORD) >> 3)

#define MRF24J40_M_COORD			0x04 /* mask bit 2 */
	#define MRF24J40_SET_COORD(R,V)		(R = (R & (MRF24J40_M_COORD ^ 0xFF)) | ((V & 0x01) << 2))
	#define MRF24J40_GET_COORD(R)		((R & MRF24J40_M_COORD) >> 2)

#define MRF24J40_M_ERRPKT			0x02 /* mask bit 1 */
	#define MRF24J40_SET_ERRPKT(R,V)	(R = (R & (MRF24J40_M_ERRPKT ^ 0xFF)) | ((V & 0x01) << 1))
	#define MRF24J40_GET_ERRPKT(R)		((R & MRF24J40_M_ERRPKT) >> 1)

#define MRF24J40_M_PROMI			0x01 /* mask bit 0 */
	#define MRF24J40_SET_PROMI(R,V)		(R = (R & (MRF24J40_M_PROMI ^ 0xFF)) | (V & 0x01))
	#define MRF24J40_GET_PROMI(R)		(R & MRF24J40_M_PROMI)

/*
 * 2-2: PAN ID Low- and High Byte Register
 */
#define MRF24J40_R_PANIDL			0x01

#define MRF24J40_M_PANIDL			0xFF /* mask bits 7..0 */
	#define MRF24J40_SET_PANIDL(R,V)	(R = (R & (MRF24J40_M_PANIDL ^ 0xFF)) | (V & 0xFF))
	#define MRF24J40_GET_PANIDL(R)		(R & MRF24J40_M_PANIDL)

#define MRF24J40_R_PANIDH			0x02

#define MRF24J40_M_PANIDH			0xFF /* mask bits 7..0 */
	#define MRF24J40_SET_PANIDH(R,V)	(R = (R & (MRF24J40_M_PANIDH ^ 0xFF)) | (V & 0xFF))
	#define MRF24J40_GET_PANIDH(R)		(R & MRF24J40_M_PANIDH)

/*
 * 2-4: Short Address Low- and High Byte Register
 */
#define MRF24J40_R_SADRL			0x03
#define MRF24J40_R_SADRH			0x04

#define MRF24J40_M_SADR				0xFF /* mask bits 7..0 */
	#define MRF24J40_SET_SADR(R,V)		(R = (R & (MRF24J40_M_SADR ^ 0xFF)) | (V & 0xFF))
	#define MRF24J40_GET_SADR(R)		(R & MRF24J40_M_SADR)

/*
 * 2-6: Extended Address Register
 */
#define MRF24J40_R_EADR0			0x05
#define MRF24J40_R_EADR1			0x06
#define MRF24J40_R_EADR2			0x07
#define MRF24J40_R_EADR3			0x08
#define MRF24J40_R_EADR4			0x08
#define MRF24J40_R_EADR5			0x0A
#define MRF24J40_R_EADR6			0x0B
#define MRF24J40_R_EADR7			0x0C

#define MRF24J40_M_EADR				0xFF /* mask bits 7..0 */
	#define MRF24J40_SET_EADR(R,V)		(R = (R & (MRF24J40_M_EADR ^ 0xFF)) | (V & 0xFF))
	#define MRF24J40_GET_EADR(R)		(R & MRF24J40_M_EADR)

/*
 * 2-14: Receive FIFO Flush Register
 */
#define MRF24J40_R_RXFLUSH			0x0D

#define MRF24J40_M_WAKEPOL			0x40 /* mask bit 6 */
	#define MRF24J40_SET_WAKEPOL(R,V)	(R = (R & (MRF24J40_M_WAKEPOL ^ 0xFF)) | ((V & 0x01) << 6))
	#define MRF24J40_GET_WAKEPOL(R)		((R & MRF24J40_M_WAKEPOL) >> 6)

#define MRF24J40_M_WAKEPAD			0x20 /* mask bit 5 */
	#define MRF24J40_SET_WAKEPAD(R,V)	(R = (R & (MRF24J40_M_WAKEPAD ^ 0xFF)) | ((V & 0x01) << 5))
	#define MRF24J40_GET_WAKEPAD(R)		((R & MRF24J40_M_WAKEPAD) >> 5)

#define MRF24J40_M_CMDONLY			0x08 /* mask bit 3 */
	#define MRF24J40_SET_CMDONLY(R,V)	(R = (R & (MRF24J40_M_CMDONLY ^ 0xFF)) | ((V & 0x01) << 3))
	#define MRF24J40_GET_CMDONLY(R)		((R & MRF24J40_M_CMDONLY) >> 3)

#define MRF24J40_M_DATAONLY			0x04 /* mask bit 2 */
	#define MRF24J40_SET_DATAONLY(R,V)	(R = (R & (MRF24J40_M_DATAONLY ^ 0xFF)) | ((V & 0x01) << 2))
	#define MRF24J40_GET_DATAONLY(R)	((R & MRF24J40_M_DATAONLY) >> 2)

#define MRF24J40_M_BCNONLY			0x02 /* mask bit 1 */
	#define MRF24J40_SET_BCNONLY(R,V)	(R = (R & (MRF24J40_M_BCNONLY ^ 0xFF)) | ((V & 0x01) << 1))
	#define MRF24J40_GET_BCNONLY(R)		((R & MRF24J40_M_BCNONLY) >> 1)

#define MRF24J40_M_RXFLUSH			0x01 /* mask bit 0 */
	#define MRF24J40_SET_RXFLUSH(R,V)	(R = (R & (MRF24J40_M_RXFLUSH ^ 0xFF)) | (V & 0x01)) // write only

/*
 * 2-15: Beacon And Superframe Order Register
 */
#define MRF24J40_R_ORDER			0x10

#define MRF24J40_M_BO				0xF0 /* mask bits 7..4 */
	#define MRF24J40_SET_BO(R,V)		(R = (R & (MRF24J40_M_BO ^ 0xFF)) | ((V & 0x0F) << 4))
	#define MRF24J40_GET_BO(R)		((R & MRF24J40_M_BCNONLY) >> 4)

#define MRF24J40_M_SO 				0x0F /* mask bits 3..0 */
	#define MRF24J40_SET_SO(R,V)		(R = (R & (MRF24J40_M_SO ^ 0xFF)) | (V & 0x0F))
	#define MRF24J40_GET_SO(R)		(R & MRF24J40_M_SO)

/*
 * 2-16: CSMA-CA Mode Control Register
 */
#define MRF24J40_R_TXMCR			0x11

#define MRF24J40_M_NOCSMA			0x80 /* mask bit 7 */
	#define MRF24J40_SET_NOCSMA(R,V)	(R = (R & (MRF24J40_M_NOCSMA ^ 0xFF)) | ((V & 0x01) << 7))
	#define MRF24J40_GET_NOCSMA(R)		((R & MRF24J40_M_NOCSMA) >> 7)

#define MRF24J40_M_BATLIFEXT			0x40 /* mask bit 6 */
	#define MRF24J40_SET_BATLIFEXT(R,V)	(R = (R & (MRF24J40_M_BATLIFEXT ^ 0xFF)) | ((V & 0x01) << 6))
	#define MRF24J40_GET_BATLIFEXT(R)	((R & MRF24J40_M_BATLIFEXT) >> 6)

#define MRF24J40_M_SLOTTED			0x20 /* mask bit 5 */
	#define MRF24J40_SET_SLOTTED(R,V)	(R = (R & (MRF24J40_M_SLOTTED ^ 0xFF)) | ((V & 0x01) << 5))
	#define MRF24J40_GET_SLOTTED(R)		((R & MRF24J40_M_SLOTTED) >> 5)

#define MRF24J40_M_MACMINBE			0x18 /* mask bits 4..3 */
	#define MRF24J40_SET_MACMINBE(R,V)	(R = (R & (MRF24J40_M_MACMINBE ^ 0xFF)) | ((V & 0x03) << 3))
	#define MRF24J40_GET_MACMINBE(R)	((R & MRF24J40_M_MACMINBE) >> 3)

#define MRF24J40_M_CSMABF			0x07 /* mask bits 2..0 */
	#define MRF24J40_SET_CSMABF(R,V)	(R = (R & (MRF24J40_M_CSMABF ^ 0xFF)) | (V & 0x07))
	#define MRF24J40_GET_CSMABF(R)		(R & MRF24J40_M_CSMABF)

/* MAC ACK Time-Out Duration Register */
#define MRF24J40_R_ACKTMOUT			0x12

#define MRF24J40_M_DRPACK			0x80 /* mask bit 7 */
	#define MRF24J40_SET_DRPACK(R,V)	(R = (R & (MRF24J40_M_DRPACK ^ 0xFF)) | ((V & 0x01) << 7))
	#define MRF24J40_GET_DRPACK(R)		((R & MRF24J40_M_DRPACK) >> 7)

#define MRF24J40_M_MAWD				0x7F /* mask bits 6..0 */
	#define MRF24J40_SET_MAWD(R,V)		(R = (R & (MRF24J40_M_MAWD ^ 0xFF)) | (V & 0x7F))
	#define MRF24J40_GET_MAWD(R)		(R & MRF24J40_M_MAWD)

/*
 * GTS1 And CAP End Slot Register
 */
#define MRF24J40_R_ESLOTG1			0x13

#define MRF24J40_M_GTS1				0xF0 /* mask bits 7..4 */
	#define MRF24J40_SET_GTS1(R,V)		(R = (R & (MRF24J40_M_GTS1 ^ 0xFF)) | ((V & 0x0F) << 4))
	#define MRF24J40_GET_GTS1(R)		((R & MRF24J40_M_GTS1) >> 4)

#define MRF24J40_M_CAP				0x0F /* mask bits 3..0 */
	#define MRF24J40_SET_CAP(R,V)		(R = (R & (MRF24J40_M_CAP ^ 0xFF)) | (V & 0x0F))
	#define MRF24J40_GET_CAP(R)		(R & MRF24J40_M_CAP)

/* Symbol Period Tick Register */
#define MRF24J40_R_SYMTICKL			0x14

#define MRF24J40_M_TICKP			0xFF /* mask bits 7..0 */
	#define MRF24J40_SET_TICKP(R,V)		(R = (R & (MRF24J40_M_TICKP ^ 0xFF)) | (V & 0xFF))
	#define MRF24J40_GET_TICKP(R)		(R & MRF24J40_M_TICKP)

#define MRF24J40_R_SYMTICKH			0x15

#define MRF24J40_M_TXONT			0xFE /* mask bits 7..1 */
	#define MRF24J40_SET_TXONT(R,V)		(R = (R & (MRF24J40_M_TXONT ^ 0xFF)) | ((V & 0x7F) << 1))
	#define MRF24J40_GET_TXONT(R)		((R & MRF24J40_M_TXONT) >> 1)

#define MRF24J40_M_TICKP8			0x03 /* mask bits 1..0 */
	#define MRF24J40_SET_TICKP8(R,V)	(R = (R & (MRF24J40_M_TICKP8 ^ 0xFF)) | (V & 0x03))
	#define MRF24J40_GET_TICKP8(R)		(R & MRF24J40_M_TICKP8)

/*
 * Power Amplifier Control Register
 */
#define MRF24J40_R_PACON0			0x16

#define MRF24J40_M_PAONT			0xFF /* mask bits 7..0 */
	#define MRF24J40_SET_PAONT(R,V)		(R = (R & (MRF24J40_M_PAONT ^ 0xFF)) | (V & 0xFF))
	#define MRF24J40_GET_PAONT(R)		(R & MRF24J40_M_PAONT)

#define MRF24J40_R_PACON1			0x17

#define MRF24J40_M_PAONTS			0x1E /* mask bits 4..1 */
	#define MRF24J40_SET_PAONTS(R,V)	(R = (R & (MRF24J40_M_PAONTS ^ 0xFF)) | ((V & 0x0F) << 1))
	#define MRF24J40_GET_PAONTS(R)		((R & MRF24J40_M_PAONTS) >> 1)

#define MRF24J40_M_PAONT8			0x01 /* mask bit 0 */
	#define MRF24J40_SET_PAONT8(R,V)	(R = (R & (MRF24J40_M_PAONT8 ^ 0xFF)) | (V & 0x01))
	#define MRF24J40_GET_PAONT8(R)		(R & MRF24J40_M_PAONT8)

#define MRF24J40_R_PACON2			0x18

#define MRF24J40_M_FIFOEN			0x80 /* mask bit 7 */
	#define MRF24J40_SET_FIFOEN(R,V)	(R = (R & (MRF24J40_M_FIFOEN ^ 0xFF)) | ((V & 0x01) << 7))
	#define MRF24J40_GET_FIFOEN(R)		((R & MRF24J40_M_FIFOEN) >> 7)

#define MRF24J40_M_TXONTS			0x3C /* mask bits 5..2 */
	#define MRF24J40_SET_TXONTS(R,V)	(R = (R & (MRF24J40_M_TXONTS ^ 0xFF)) | ((V & 0x0F) << 2))
	#define MRF24J40_GET_TXONTS(R)		((R & MRF24J40_M_TXONTS) >> 2)

#define MRF24J40_M_PACON2_TXONT			0x03 /* mask bits 1..0 */
	#define MRF24J40_SET_PACON2_TXONT(R,V)	(R = (R & (MRF24J40_M_PACON2_TXONT ^ 0xFF)) | (V & 0x03))
	#define MRF24J40_GET_PACON2_TXONT(R)	(R & MRF24J40_M_PACON2_TXONT)

/*
 * Transmit Beacon FIFO Control Register
 */
#define MRF24J40_R_TXBCON0			0x1A

#define MRF24J40_M_TXBSECEN			0x02 /* mask bit 1 */
	#define MRF24J40_SET_TXBSECEN(R,V)	(R = (R & (MRF24J40_M_TXBSECEN ^ 0xFF)) | ((V & 0x01) << 1))
	#define MRF24J40_GET_TXBSECEN(R)	((R & MRF24J40_M_TXBSECEN) >> 1)

#define MRF24J40_M_TXBTRIG			0x01 /* mask bit 0 */
	#define MRF24J40_SET_TXBTRIG(R,V)	(R = (R & (MRF24J40_M_TXBTRIG ^ 0xFF)) | (V & 0x01)) // write only

/*
 * Transmit Normal FIFO Control Register
 */
#define MRF24J40_R_TXNCON			0x1B

#define MRF24J40_M_FPSTAT			0x10 /* mask bit 4 */
	#define MRF24J40_GET_FPSTAT(R)		((R & MRF24J40_M_FPSTAT) >> 4) // read only

#define MRF24J40_M_INDIRECT			0x08 /* mask bit 3 */
	#define MRF24J40_SET_INDIRECT(R,V)	(R = (R & (MRF24J40_M_INDIRECT ^ 0xFF)) | ((V & 0x01) << 3))
	#define MRF24J40_GET_INDIRECT(R)	((R & MRF24J40_M_INDIRECT) >> 3)

#define MRF24J40_M_TXNACKREQ			0x04 /* mask bit 2 */
	#define MRF24J40_SET_TXNACKREQ(R,V)	(R = (R & (MRF24J40_M_TXNACKREQ ^ 0xFF)) | ((V & 0x01) << 2))
	#define MRF24J40_GET_TXNACKREQ(R)	((R & MRF24J40_M_TXNACKREQ) >> 2)

#define MRF24J40_M_TXNSECEN			0x02 /* mask bit 1 */
	#define MRF24J40_SET_TXNSECEN(R,V)	(R = (R & (MRF24J40_M_TXNSECEN ^ 0xFF)) | ((V & 0x01) << 1))
	#define MRF24J40_GET_TXNSECEN(R)	((R & MRF24J40_M_TXNSECEN) >> 1)

#define MRF24J40_M_TXNTRIG			0x01 /* mask bit 0 */
	#define MRF24J40_SET_TXNTRIG(R,V)	(R = (R & (MRF24J40_M_TXNTRIG ^ 0xFF)) | (V & 0x01)) // write only

/*
 * GTS1 and GTS2 FIFO Control Registers
 */
#define MRF24J40_R_TXG1CON			0x1C
#define MRF24J40_R_TXG2CON			0x1D

#define MRF24J40_M_TXGRETRY			0xC0 /* mask bits 7..6 */
	#define MRF24J40_SET_TXGRETRY(R,V)	(R = (R & (MRF24J40_M_TXGRETRY ^ 0xFF)) | ((V & 0x03) << 6))
	#define MRF24J40_GET_TXGRETRY(R)	((R & MRF24J40_M_TXGRETRY) >> 6)

#define MRF24J40_M_TXGSLOT			0x38 /* mask bits 5..3 */
	#define MRF24J40_SET_TXGSLOT(R,V)	(R = (R & (MRF24J40_M_TXGSLOT ^ 0xFF)) | ((V & 0x07) << 3))
	#define MRF24J40_GET_TXGSLOT(R)		((R & MRF24J40_M_TXGSLOT) >> 3)

#define MRF24J40_M_TXGACKREQ			0x04 /* mask bit 2 */
	#define MRF24J40_SET_TXGACKREQ(R,V)	(R = (R & (MRF24J40_M_TXGACKREQ ^ 0xFF)) | ((V & 0x01) << 2))
	#define MRF24J40_GET_TXGACKREQ(R)	((R & MRF24J40_M_TXGACKREQ) >> 2)

#define MRF24J40_M_TXGSECEN			0x02 /* mask bit 1 */
	#define MRF24J40_SET_TXGSECEN(R,V)	(R = (R & (MRF24J40_M_TXGSECEN ^ 0xFF)) | ((V & 0x01) << 1))
	#define MRF24J40_GET_TXGSECEN(R)	((R & MRF24J40_M_TXGSECEN) >> 2)

#define MRF24J40_M_TXGTRIG			0x01 /* mask bit 0 */
	#define MRF24J40_SET_TXGTRIG(R,V)	(R = (R & (MRF24J40_M_TXGTRIG ^ 0xFF)) | (V & 0x01)) // write only

/*
 * End Slot of GTS3 and GTS2 Registers
 */
#define MRF24J40_R_ESLOTG23			0x1E

#define MRF24J40_M_GTS3				0xF8 /* mask bits 7..4 */
	#define MRF24J40_SET_GTS3(R,V)		(R = (R & (MRF24J40_M_GTS3 ^ 0xFF)) | ((V & 0x1F) << 4))
	#define MRF24J40_GET_GTS3(R)		((R & MRF24J40_M_GTS3) >> 4)

#define MRF24J40_M_GTS2				0x0F /* mask bits 3..0 */
	#define MRF24J40_SET_GTS2(R,V)		(R = (R & (MRF24J40_M_GTS2 ^ 0xFF)) | (V & 0x0F))
	#define MRF24J40_GET_GTS2(R)		(R & MRF24J40_M_GTS2)

/*
 * End Slot of GTS5 and GTS4 Registers
 */
#define MRF24J40_R_ESLOTG45			0x1F

#define MRF24J40_M_GTS5				0xF8 /* mask bits 7..4 */
	#define MRF24J40_SET_GTS5(R,V)		(R = (R & (MRF24J40_M_GTS5 ^ 0xFF)) | ((V & 0x1F) << 4))
	#define MRF24J40_GET_GTS5(R)		((R & MRF24J40_M_GTS5) >> 4)

#define MRF24J40_M_GTS4				0x0F /* mask bits 3..0 */
	#define MRF24J40_SET_GTS4(R,V)		(R = (R & (MRF24J40_M_GTS4 ^ 0xFF)) | (V & 0x0F))
	#define MRF24J40_GET_GTS4(R)		(R & MRF24J40_M_GTS4)

/*
 * End Slot of GTS6 Register
 */
#define MRF24J40_R_ESLOTG67			0x20

#define MRF24J40_M_GTS6				0x0F /* mask bits 3..0 */
	#define MRF24J40_SET_GTS6(R,V)		(R = (R & (MRF24J40_M_GTS6 ^ 0xFF)) | (V & 0x0F))
	#define MRF24J40_GET_GTS6(R)		(R & MRF24J40_M_GTS6)

/*
 * TX Data Pending Register
 */
#define MRF24J40_R_TXPEND			0x21

#define MRF24J40_M_MLIFS			0xFC /* mask bits 7..2 */
	#define MRF24J40_SET_MLIFS(R,V)		(R = (R & (MRF24J40_M_MLIFS ^ 0xFF)) | ((V & 0x3F) << 2))
	#define MRF24J40_GET_MLIFS(R)		((R & MRF24J40_M_MLIFS) >> 2)

#define MRF24J40_M_GTSSWITCH			0x02 /* mask bit 1 */
	#define MRF24J40_SET_GTSSWITCH(R,V)	(R = (R & (MRF24J40_M_GTSSWITCH ^ 0xFF)) | ((V & 0x01) << 1))
	#define MRF24J40_GET_GTSSWITCH(R)	((R & MRF24J40_M_GTSSWITCH) >> 1)

#define MRF24J40_M_FPACK			0x01 /* mask bit 0 */
	#define MRF24J40_SET_FPACK(R,V)		(R = (R & (MRF24J40_M_FPACK ^ 0xFF)) | (V & 0x01))
	#define MRF24J40_GET_FPACK(R)		(R & MRF24J40_M_FPACK)

/*
 * Wake Control Register
 */
#define MRF24J40_R_WAKECON			0x22

#define MRF24J40_M_IMMWAKE			0x80 /* mask bit 7 */
	#define MRF24J40_SET_IMMWAKE(R,V)	(R = (R & (MRF24J40_M_IMMWAKE ^ 0xFF)) | ((V & 0x01) << 7))
	#define MRF24J40_GET_IMMWAKE(R)		((R & MRF24J40_M_IMMWAKE) >> 7)

#define MRF24J40_M_REGWAKE			0x40 /* mask bit 6 */
	#define MRF24J40_SET_REGWAKE(R,V)	(R = (R & (MRF24J40_M_REGWAKE ^ 0xFF)) | ((V & 0x01) << 6))
	#define MRF24J40_GET_REGWAKE(R)		((R & MRF24J40_M_REGWAKE) >> 7)

#define MRF24J40_M_INTL				0x3F /* mask bit 5..0 */
	#define MRF24J40_SET_INTL(R,V)		(R = (R & (MRF24J40_M_INTL ^ 0xFF)) | (V & 0x1F))
	#define MRF24J40_GET_INTL(R)		(R & MRF24J40_M_INTL)

/*
 * Superframe Counter Offset to Align Beacon Register
 */
#define MRF24J40_R_FRMOFFSET			0x23

#define MRF24J40_M_OFFSET			0xFF /* mask bit 7..0 */
	#define MRF24J40_SET_OFFSET(R,V)	(R = (R & (MRF24J40_M_OFFSET ^ 0xFF)) | (V & 0xFF))
	#define MRF24J40_GET_OFFSET(R)		(R & MRF24J40_M_OFFSET)

/*
 * TX MAC Status Register
 */
#define MRF24J40_R_TXSTAT			0x24

#define MRF24J40_M_TXNRETRY			0xC0 /* mask bit 7..6 */
	#define MRF24J40_GET_TXNRETRY(R)	((R & MRF24J40_M_TXNRETRY) >> 6) // read only

#define MRF24J40_M_CCAFAIL			0x20 /* mask bit 5 */
	#define MRF24J40_GET_CCAFAIL(R) 	((R & MRF24J40_M_CCAFAIL) >> 5) // read only

#define MRF24J40_M_TXG2FNT			0x10 /* mask bit 4 */
	#define MRF24J40_GET_TXG2FNT(R)		((R & MRF24J40_M_TXG2FNT) >> 4) // read only

#define MRF24J40_M_TXG1FNT			0x08 /* mask bit 3 */
	#define MRF24J40_GET_TXG1FNT(R)		((R & MRF24J40_M_TXG1FNT) >> 3) // read only

#define MRF24J40_M_TXG2STAT			0x04 /* mask bit 2 */
	#define MRF24J40_GET_TXG2STAT(R)	((R & MRF24J40_M_TXG2STAT) >> 2) // read only

#define MRF24J40_M_TXG1STAT			0x02 /* mask bit 1 */
	#define MRF24J40_GET_TXG1STAT(R)	((R & MRF24J40_M_TXG1STAT) >> 1) // read only

#define MRF24J40_M_TXNSTAT			0x01 /* mask bit 0 */
	#define MRF24J40_GET_TXNSTAT(R)		(R & MRF24J40_M_TXNSTAT) // read only

/*
 * Transmit Beacon Control Register
 */
#define MRF24J40_R_TXBCON1			0x25

#define MRF24J40_M_TXBMSK			0x80 /* mask bit 7 */
	#define MRF24J40_SET_TXBMSK(R,V)	(R = (R & (MRF24J40_M_TXBMSK ^ 0xFF)) | ((V & 0x01) << 7))
	#define MRF24J40_GET_TXBMSK(R)		((R & MRF24J40_M_TXBMSK) >> 7)

#define MRF24J40_M_WUBCN			0x40 /* mask bit 6 */
	#define MRF24J40_GET_WUBCN(R)		((R & MRF24J40_M_WUBCN) >> 6) // read only

#define MRF24J40_M_RSSINUM			0x30 /* mask bits 5..4 */
	#define MRF24J40_SET_RSSINUM(R,V)	(R = (R & (MRF24J40_M_RSSINUM ^ 0xFF)) | ((V & 0x03) << 4))
	#define MRF24J40_GET_RSSINUM(R)		((R & MRF24J40_M_RSSINUM) >> 4)

/*
 * Gated Clock Control Register
 */
#define MRF24J40_R_GATECLK			0x26

#define MRF24J40_M_GTSON			0x08 /* mask bit 3 */
	#define MRF24J40_SET_GTSON(R,V)		(R = (R & (MRF24J40_M_GTSON ^ 0xFF)) | ((V & 0x01) << 3))
	#define MRF24J40_GET_GTSON(R)		((R & MRF24J40_M_GTSON) >> 3)

/*
 * TX Turnaround Time Register
 */
#define MRF24J40_R_TXTIME			0x27

#define MRF24J40_M_TURNTIME			0xF8 /* mask bit 7..4 */
	#define MRF24J40_SET_TURNTIME(R,V)	(R = (R & (MRF24J40_M_TURNTIME ^ 0xFF)) | ((V & 0x1F) << 4))
	#define MRF24J40_GET_TURNTIME(R)	((R & MRF24J40_M_TURNTIME) >> 4)

/*
 * Half Symbol Timer Register
 */
#define MRF24J40_R_HSYMTMRL			0x28
#define MRF24J40_R_HSYMTMRH			0x29

#define MRF24J40_M_HSYMTMR			0xFF /* mask bit 7..0 */
	#define MRF24J40_SET_HSYMTMR(R,V)	(R = (R & (MRF24J40_M_HSYMTMR ^ 0xFF)) | (V & 0xFF))
	#define MRF24J40_GET_HSYMTMR(R)		(R & MRF24J40_M_HSYMTMR)

/*
 * Software Reset Register
 */
#define MRF24J40_R_SOFTRST			0x2A

#define MRF24J40_M_RSTPWR			0x04 /* mask bit 2 */
	#define MRF24J40_SET_RSTPWR(R,V)	(R = (R & (MRF24J40_M_RSTPWR ^ 0xFF)) | ((V & 0x01) << 2)) // write only

#define MRF24J40_M_RSTBB			0x02 /* mask bit 1 */
	#define MRF24J40_SET_RSTBB(R,V)		(R = (R & (MRF24J40_M_RSTBB ^ 0xFF)) | ((V & 0x01) << 1)) // write only

#define MRF24J40_M_RSTMAC			0x01 /* mask bit 0 */
	#define MRF24J40_SET_RSTMAC(R,V)	(R = (R & (MRF24J40_M_RSTMAC ^ 0xFF)) | (V & 0x01)) // write only

/*
 * Security Control Register
 */
#define MRF24J40_R_SECCON0			0x2C

#define MRF24J40_M_SECIGNORE			0x80 /* mask bit 7 */
	#define MRF24J40_SET_SECIGNORE(R,V)	(R = (R & (MRF24J40_M_SECIGNORE ^ 0xFF)) | ((V & 0x01) << 7)) // write only

#define MRF24J40_M_SECSTART			0x40 /* mask bit 6 */
	#define MRF24J40_SET_SECSTART(R,V)	(R = (R & (MRF24J40_M_SECSTART ^ 0xFF)) | ((V & 0x01) << 6)) // write only

#define MRF24J40_M_RXCIPHER			0x38 /* mask bits 5..3 */
	#define MRF24J40_SET_RXCIPHER(R,V)	(R = (R & (MRF24J40_M_RXCIPHER ^ 0xFF)) | ((V & 0x07) << 3))
	#define MRF24J40_GET_RXCIPHER(R)	((R & MRF24J40_M_RXCIPHER) >> 3)

#define MRF24J40_M_TXNCIPHER			0x07 /* mask bits 2..0 */
	#define MRF24J40_SET_TXNCIPHER(R,V)	(R = (R & (MRF24J40_M_TXNCIPHER ^ 0xFF)) | (V & 0x07))
	#define MRF24J40_GET_TXNCIPHER(R)	(R & MRF24J40_M_TXNCIPHER)

#define MRF24J40_R_SECCON1			0x2D

#define MRF24J40_M_TXBCIPHER			0x70 /* mask bits 6..4 */
	#define MRF24J40_SET_TXBCIPHER(R,V)	(R = (R & (MRF24J40_M_TXBCIPHER ^ 0xFF)) | ((V & 0x07) << 4))
	#define MRF24J40_GET_TXBCIPHER(R)	((R & MRF24J40_M_TXBCIPHER) >> 4)

#define MRF24J40_M_DISDEC			0x02 /* mask bit 1 */
	#define MRF24J40_SET_DISDEC(R,V)	(R = (R & (MRF24J40_M_DISDEC ^ 0xFF)) | ((V & 0x01) << 1))
	#define MRF24J40_GET_DISDEC(R)		((R & MRF24J40_M_DISDEC) >> 1)

#define MRF24J40_M_DISENC			0x01 /* mask bit 0 */
	#define MRF24J40_SET_DISENC(R,V)	(R = (R & (MRF24J40_M_DISENC ^ 0xFF)) | (V & 0x01))
	#define MRF24J40_GET_DISENC(R)		(R & MRF24J40_M_DISENC)

/*
 * TX Stabilization Register
 */
#define MRF24J40_R_TXSTBL			0x2E

#define MRF24J40_M_RFSTBL			0xF0 /* mask bits 7..4 */
	#define MRF24J40_SET_RFSTBL(R,V)	(R = (R & (MRF24J40_M_RFSTBL ^ 0xFF)) | ((V & 0x0F) << 4))
	#define MRF24J40_GET_RFSTBL(R)		((R & MRF24J40_M_RFSTBL) >> 4)

#define MRF24J40_M_MSIFS			0x0F /* mask bits 3..0 */
	#define MRF24J40_SET_MSIFS(R,V)		(R = (R & (MRF24J40_M_MSIFS ^ 0xFF)) | (V & 0x0F))
	#define MRF24J40_GET_MSIFS(R)		(R & MRF24J40_M_MSIFS)

/*
 * RX MAC Status Register
 */
#define MRF24J40_R_RXSR				0x30

#define MRF24J40_M_UPSECERR			0x40 /* mask bit 6 */
	#define MRF24J40_SET_UPSECERR(R,V)	(R = (R & (MRF24J40_M_UPSECERR ^ 0xFF)) | ((V & 0x01) << 6))
	#define MRF24J40_GET_UPSECERR(R)	((R & MRF24J40_M_UPSECERR) >> 6)

#define MRF24J40_M_BATIND			0x20 /* mask bit 5 */
	#define MRF24J40_GET_BATIND(R)		((R & MRF24J40_M_BATIND) >> 5) // read only

#define MRF24J40_M_SECDECERR			0x04 /* mask bit 2 */
	#define MRF24J40_GET_SECDECERR(R)	((R & MRF24J40_M_SECDECERR) >> 2) // read only

/*
 * Interrupt Status Register
 */
#define MRF24J40_R_INTSTAT			0x31

#define MRF24J40_M_SLPIF			0x80 /* mask bit 7 */
	#define MRF24J40_GET_SLPIF(R)		((R & MRF24J40_M_SLPIF) >> 7) // read to clear bit

#define MRF24J40_M_WAKEIF			0x40 /* mask bit 6 */
	#define MRF24J40_GET_WAKEIF(R)		((R & MRF24J40_M_WAKEIF) >> 6) // read to clear bit

#define MRF24J40_M_HSYMTMRIF			0x20 /* mask bit 5 */
	#define MRF24J40_GET_HSYMTMRIF(R)	((R & MRF24J40_M_HSYMTMRIF) >> 5) // read to clear bit

#define MRF24J40_M_SECIF			0x10 /* mask bit 4 */
	#define MRF24J40_GET_SECIF(R)		((R & MRF24J40_M_SECIF) >> 4) // read to clear bit

#define MRF24J40_M_RXIF				0x08 /* mask bit 3 */
	#define MRF24J40_GET_RXIF(R)		((R & MRF24J40_M_RXIF) >> 3) // read to clear bit

#define MRF24J40_M_TXG2IF			0x04 /* mask bit 2 */
	#define MRF24J40_GET_TXG2IF(R)		((R & MRF24J40_M_TXG2IF) >> 2) // read to clear bit

#define MRF24J40_M_TXG1IF			0x02 /* mask bit 1 */
	#define MRF24J40_GET_TXG1IF(R)		((R & MRF24J40_M_TXG1IF) >> 1) // read to clear bit

#define MRF24J40_M_TXNIF			0x01 /* mask bit 0 */
	#define MRF24J40_GET_TXNIF(R)		(R & MRF24J40_M_TXNIF) // read to clear bit

/*
 * Interrupt Control Register
 */
#define MRF24J40_R_INTCON			0x32

#define MRF24J40_M_SLPIE			0x80 /* mask bit 7 */
	#define MRF24J40_SET_SLPIE(R,V)		(R = (R & (MRF24J40_M_SLPIE ^ 0xFF)) | ((V & 0x01) << 7))
	#define MRF24J40_GET_SLPIE(R)		((R & MRF24J40_M_SLPIE) >> 7)

#define MRF24J40_M_WAKEIE			0x40 /* mask bit 6 */
	#define MRF24J40_SET_WAKEIE(R,V)	(R = (R & (MRF24J40_M_WAKEIE ^ 0xFF)) | ((V & 0x01) << 6))
	#define MRF24J40_GET_WAKEIE(R)		((R & MRF24J40_M_WAKEIE) >> 6)

#define MRF24J40_M_HSYMTMRIE			0x20 /* mask bit 5 */
	#define MRF24J40_SET_HSYMTMRIE(R,V)	(R = (R & (MRF24J40_M_HSYMTMRIE ^ 0xFF)) | ((V & 0x01) << 5))
	#define MRF24J40_GET_HSYMTMRIE(R)	((R & MRF24J40_M_HSYMTMRIE) >> 5)

#define MRF24J40_M_SECIE			0x10 /* mask bit 4 */
	#define MRF24J40_SET_SECIE(R,V)		(R = (R & (MRF24J40_M_SECIE ^ 0xFF)) | ((V & 0x01) << 4))
	#define MRF24J40_GET_SECIE(R)		((R & MRF24J40_M_SECIE) >> 4)

#define MRF24J40_M_RXIE				0x08 /* mask bit 3 */
	#define MRF24J40_SET_RXIE(R,V)		(R = (R & (MRF24J40_M_RXIE ^ 0xFF)) | ((V & 0x01) << 3))
	#define MRF24J40_GET_RXIE(R)		((R & MRF24J40_M_RXIE) >> 3)

#define MRF24J40_M_TXG2IE			0x04 /* mask bit 2 */
	#define MRF24J40_SET_TXG2IE(R,V)	(R = (R & (MRF24J40_M_TXG2IE ^ 0xFF)) | ((V & 0x01) << 2))
	#define MRF24J40_GET_TXG2IE(R)		((R & MRF24J40_M_TXG2IE) >> 2)

#define MRF24J40_M_TXG1IE			0x02 /* mask bit 1 */
	#define MRF24J40_SET_TXG1IE(R,V)	(R = (R & (MRF24J40_M_TXG1IE ^ 0xFF)) | ((V & 0x01) << 1))
	#define MRF24J40_GET_TXG1IE(R)		((R & MRF24J40_M_TXG1IE) >> 1)

#define MRF24J40_M_TXNIE			0x01 /* mask bit 0 */
	#define MRF24J40_SET_TXNIE(R,V)		(R = (R & (MRF24J40_M_TXNIE ^ 0xFF)) | (V & 0x01))
	#define MRF24J40_GET_TXNIE(R)		(R & MRF24J40_M_TXNIE)

/*
 * GPIO Port Register
 */
#define MRF24J40_R_GPIO				0x33

#define MRF24J40_M_GPIO5			0x20 /* mask bit 5 */
	#define MRF24J40_SET_GPIO5(R,V)		(R = (R & (MRF24J40_M_GPIO5 ^ 0xFF)) | ((V & 0x01) << 5))
	#define MRF24J40_GET_GPIO5(R)		((R & MRF24J40_M_GPIO5) >> 5)

#define MRF24J40_M_GPIO4			0x10 /* mask bit 4 */
	#define MRF24J40_SET_GPIO4(R,V)		(R = (R & (MRF24J40_M_GPIO4 ^ 0xFF)) | ((V & 0x01) << 4))
	#define MRF24J40_GET_GPIO4(R)		((R & MRF24J40_M_GPIO4) >> 4)

#define MRF24J40_M_GPIO3			0x08 /* mask bit 3 */
	#define MRF24J40_SET_GPIO3(R,V)		(R = (R & (MRF24J40_M_GPIO3 ^ 0xFF)) | ((V & 0x01) << 3))
	#define MRF24J40_GET_GPIO3(R)		((R & MRF24J40_M_GPIO3) >> 3)

#define MRF24J40_M_GPIO2			0x04 /* mask bit 2 */
	#define MRF24J40_SET_GPIO2(R,V)		(R = (R & (MRF24J40_M_GPIO2 ^ 0xFF)) | ((V & 0x01) << 2))
	#define MRF24J40_GET_GPIO2(R)		((R & MRF24J40_M_GPIO2) >> 2)

#define MRF24J40_M_GPIO1			0x02 /* mask bit 1 */
	#define MRF24J40_SET_GPIO1(R,V)		(R = (R & (MRF24J40_M_GPIO1 ^ 0xFF)) | ((V & 0x01) << 1))
	#define MRF24J40_GET_GPIO1(R)		((R & MRF24J40_M_GPIO1) >> 1)

#define MRF24J40_M_GPIO0			0x01 /* mask bit 0 */
	#define MRF24J40_SET_GPIO0(R,V)		(R = (R & (MRF24J40_M_GPIO0 ^ 0xFF)) | (V & 0x01))
	#define MRF24J40_GET_GPIO0(R)		(R & MRF24J40_M_GPIO0)

/*
 * GPIO Pin Direction Register
 */
#define MRF24J40_R_TRISGPIO			0x34

#define MRF24J40_M_TRISGP5			0x20 /* mask bit 5 */
	#define MRF24J40_SET_TRISGP5(R,V)	(R = (R & (MRF24J40_M_TRISGP5 ^ 0xFF)) | ((V & 0x01) << 5))
	#define MRF24J40_GET_TRISGP5(R)		((R & MRF24J40_M_TRISGP5) >> 5)

#define MRF24J40_M_TRISGP4			0x10 /* mask bit 4 */
	#define MRF24J40_SET_TRISGP4(R,V)	(R = (R & (MRF24J40_M_TRISGP4 ^ 0xFF)) | ((V & 0x01) << 4))
	#define MRF24J40_GET_TRISGP4(R)		((R & MRF24J40_M_TRISGP4) >> 4)

#define MRF24J40_M_TRISGP3			0x08 /* mask bit 3 */
	#define MRF24J40_SET_TRISGP3(R,V)	(R = (R & (MRF24J40_M_TRISGP3 ^ 0xFF)) | ((V & 0x01) << 3))
	#define MRF24J40_GET_TRISGP3(R)		((R & MRF24J40_M_TRISGP3) >> 3)

#define MRF24J40_M_TRISGP2			0x04 /* mask bit 2 */
	#define MRF24J40_SET_TRISGP2(R,V)	(R = (R & (MRF24J40_M_TRISGP2 ^ 0xFF)) | ((V & 0x01) << 2))
	#define MRF24J40_GET_TRISGP2(R)		((R & MRF24J40_M_TRISGP2) >> 2)

#define MRF24J40_M_TRISGP1			0x02 /* mask bit 1 */
	#define MRF24J40_SET_TRISGP1(R,V)	(R = (R & (MRF24J40_M_TRISGP1 ^ 0xFF)) | ((V & 0x01) << 1))
	#define MRF24J40_GET_TRISGP1(R)		((R & MRF24J40_M_TRISGP1) >> 1)

#define MRF24J40_M_TRISGP0			0x01 /* mask bit 0 */
	#define MRF24J40_SET_TRISGP0(R,V)	(R = (R & (MRF24J40_M_TRISGP0 ^ 0xFF)) | (V & 0x01))
	#define MRF24J40_GET_TRISGP0(R)		(R & MRF24J40_M_TRISGP0)

/*
 * Sleep Acknowledgement and Wake-Up Counter Register
 */
#define MRF24J40_R_SLPACK			0x35

#define MRF24J40_M_SLPACK			0x80 /* mask bit 7 */
	#define MRF24J40_SET_SLPACK(R,V)	(R = (R & (MRF24J40_M_SLPACK ^ 0xFF)) | ((V & 0x01) << 7)) // write only

#define MRF24J40_M_WAKECNTL			0x7F /* mask bit 6..0 */
	#define MRF24J40_SET_WAKECNTL(R,V)	(R = (R & (MRF24J40_M_WAKECNTL ^ 0xFF)) | (V & 0x7F))
	#define MRF24J40_GET_WAKECNTL(R)	(R & MRF24J40_M_WAKECNTL)

/*
 * RF Mode Control Register
 */
#define MRF24J40_R_RFCTL			0x36

#define MRF24J40_M_WAKECNTH			0x18 /* mask bit 4..3 */
	#define MRF24J40_SET_WAKECNTH(R,V)	(R = (R & (MRF24J40_M_WAKECNTH ^ 0xFF)) | ((V & 0x03) << 3))
	#define MRF24J40_GET_WAKECNTH(R)	((R & MRF24J40_M_WAKECNTH) >> 3)

#define MRF24J40_M_RFRST			0x04 /* mask bit 2 */
	#define MRF24J40_SET_RFRST(R,V)		(R = (R & (MRF24J40_M_RFRST ^ 0xFF)) | ((V & 0x01) << 2))
	#define MRF24J40_GET_RFRST(R)		((R & MRF24J40_M_RFRST) >> 2)

#define MRF24J40_M_RFTXMODE			0x02 /* mask bit 1 */
	#define MRF24J40_SET_RFTXMODE(R,V)	(R = (R & (MRF24J40_M_RFTXMODE ^ 0xFF)) | ((V & 0x01) << 1))
	#define MRF24J40_GET_RFTXMODE(R)	((R & MRF24J40_M_RFTXMODE) >> 1)

#define MRF24J40_M_RFRXMODE			0x01 /* mask bit 0 */
	#define MRF24J40_SET_RFRXMODE(R,V)	(R = (R & (MRF24J40_M_RFRXMODE ^ 0xFF)) | (V & 0x01))
	#define MRF24J40_GET_RFRXMODE(R)	(R & MRF24J40_M_RFRXMODE)

/*
 * Security Control Register
 */
#define MRF24J40_R_SECCR2			0x37

#define MRF24J40_M_UPDEC			0x80 /* mask bit 7 */
	#define MRF24J40_SET_UPDEC(R,V)		(R = (R & (MRF24J40_M_UPDEC ^ 0xFF)) | ((V & 0x01) << 7)) // write only

#define MRF24J40_M_UPENC			0x40 /* mask bit 6 */
	#define MRF24J40_SET_UPENC(R,V)		(R = (R & (MRF24J40_M_UPENC ^ 0xFF)) | ((V & 0x01) << 6)) // write only

#define MRF24J40_M_TXG2CIPHER			0x38 /* mask bits 5..3 */
	#define MRF24J40_SET_TXG2CIPHER(R,V)	(R = (R & (MRF24J40_M_TXG2CIPHER ^ 0xFF)) | ((V & 0x07) << 3))
	#define MRF24J40_GET_TXG2CIPHER(R)	((R & MRF24J40_M_TXG2CIPHER) >> 3)

#define MRF24J40_M_TXG1CIPHER			0x07 /* mask bits 2..0 */
	#define MRF24J40_SET_TXG1CIPHER(R,V)	(R = (R & (MRF24J40_M_TXG1CIPHER ^ 0xFF)) | (V & 0x07))
	#define MRF24J40_GET_TXG1CIPHER(R)	(R & MRF24J40_M_TXG1CIPHER)

/*
 * Baseband Register
 */
#define MRF24J40_R_BBREG0			0x38

#define MRF24J40_M_TURBO			0x01 /* mask bit 0 */
	#define MRF24J40_SET_TURBO(R,V)		(R = (R & (MRF24J40_M_TURBO ^ 0xFF)) | (V & 0x01))
	#define MRF24J40_GET_TURBO(R)		(R & MRF24J40_M_TURBO)

#define MRF24J40_R_BBREG1			0x39

#define MRF24J40_M_RXDECINV			0x04 /* mask bit 2 */
	#define MRF24J40_SET_RXDECINV(R,V)	(R = (R & (MRF24J40_M_RXDECINV ^ 0xFF)) | ((V & 0x01) << 2))
	#define MRF24J40_GET_RXDECINV(R)	((R & MRF24J40_M_RXDECINV) >> 2)

#define MRF24J40_R_BBREG2			0x3A

#define MRF24J40_M_CCAMODE			0xC0 /* mask bits 7..6 */
	#define MRF24J40_SET_CCAMODE(R,V)	(R = (R & (MRF24J40_M_CCAMODE ^ 0xFF)) | ((V & 0x03) << 6))
	#define MRF24J40_GET_CCAMODE(R)		((R & MRF24J40_M_CCAMODE) >> 6)

#define MRF24J40_M_CCACSTH			0x3C /* mask bits 5..2 */
	#define MRF24J40_SET_CCACSTH(R,V)	(R = (R & (MRF24J40_M_CCACSTH ^ 0xFF)) | ((V & 0x0F) << 2))
	#define MRF24J40_GET_CCACSTH(R)		((R & MRF24J40_M_CCACSTH) >> 2)

#define MRF24J40_R_BBREG3			0x3B

#define MRF24J40_M_PREVALIDTH			0xF0 /* mask bits 7..4 */
	#define MRF24J40_SET_PREVALIDTH(R,V)	(R = (R & (MRF24J40_M_PREVALIDTH ^ 0xFF)) | ((V & 0x0F) << 4))
	#define MRF24J40_GET_PREVALIDTH(R)	((R & MRF24J40_M_PREVALIDTH) >> 4)

#define MRF24J40_M_PREDETTH			0x0E /* mask bits 3..1 */
	#define MRF24J40_SET_PREDETTH(R,V)	(R = (R & (MRF24J40_M_PREDETTH ^ 0xFF)) | ((V & 0x07) << 1))
	#define MRF24J40_GET_PREDETTH(R)	((R & MRF24J40_M_PREDETTH) >> 1)

#define MRF24J40_R_BBREG4			0x3C

#define MRF24J40_M_CSTH				0xE0 /* mask bits 7..5 */
	#define MRF24J40_SET_CSTH(R,V)		(R = (R & (MRF24J40_M_CSTH ^ 0xFF)) | ((V & 0x07) << 5))
	#define MRF24J40_GET_CSTH(R)		((R & MRF24J40_M_CSTH) >> 5)

#define MRF24J40_M_PRECNT			0x1C /* mask bits 4..2 */
	#define MRF24J40_SET_PRECNT(R,V)	(R = (R & (MRF24J40_M_PRECNT ^ 0xFF)) | ((V & 0x07) << 2))
	#define MRF24J40_GET_PRECNT(R)		((R & MRF24J40_M_PRECNT) >> 2)

#define MRF24J40_R_BBREG6			0x3E

#define MRF24J40_M_RSSIMODE1			0x80 /* mask bit 7 */
	#define MRF24J40_SET_RSSIMODE1(R,V)	(R = (R & (MRF24J40_M_RSSIMODE1 ^ 0xFF)) | ((V & 0x01) << 7)) // write only

#define MRF24J40_M_RSSIMODE2			0x40 /* mask bit 6 */
	#define MRF24J40_SET_RSSIMODE2(R,V)	(R = (R & (MRF24J40_M_RSSIMODE2 ^ 0xFF)) | ((V & 0x01) << 6))
	#define MRF24J40_GET_RSSIMODE2(R)	((R & MRF24J40_M_RSSIMODE2) >> 6)

#define MRF24J40_M_RSSIRDY			0x01 /* mask bit 0 */
	#define MRF24J40_SET_RSSIRDY(R,V)	(R = (R & (MRF24J40_M_RSSIRDY ^ 0xFF)) | (V & 0x01))
	#define MRF24J40_GET_RSSIRDY(R)		(R & MRF24J40_M_RSSIRDY)

/*
 * Energy Detection Threshold for CCA Register
 */
#define MRF24J40_R_CCAEDTH			0x3F

#define MRF24J40_M_CCAEDTH			0xFF /* mask bits 7..0 */
	#define MRF24J40_SET_CCAEDTH(R,V)	(R = (R & (MRF24J40_M_CCAEDTH ^ 0xFF)) | (V & 0xFF))
	#define MRF24J40_GET_CCAEDTH(R)		(R & MRF24J40_M_CCAEDTH)

/*
 * RF Control Register
 */
#define MRF24J40_R_RFCON0			0x200

#define MRF24J40_M_CHANNEL			0xF0 /* mask bits 7..4 */
	#define MRF24J40_SET_CHANNEL(R,V)	(R = (R & (MRF24J40_M_CHANNEL ^ 0xFF)) | ((V & 0x0F) << 4))
	#define MRF24J40_GET_CHANNEL(R)		((R & MRF24J40_M_CHANNEL) >> 4)

#define MRF24J40_M_RFOPT			0x0F /* mask bits 3..0 */
	#define MRF24J40_SET_RFOPT(R,V)		(R = (R & (MRF24J40_M_RFOPT ^ 0xFF)) | (V & 0x0F))
	#define MRF24J40_GET_RFOPT(R)		(R & MRF24J40_M_RFOPT)

#define MRF24J40_R_RFCON1			0x201

#define MRF24J40_M_VCOOPT			0xFF /* mask bits 7..0 */
	#define MRF24J40_SET_VCOOPT(R,V)	(R = (R & (MRF24J40_M_VCOOPT ^ 0xFF)) | (V & 0xFF))
	#define MRF24J40_GET_VCOOPT(R)		(R & MRF24J40_M_VCOOPT)

#define MRF24J40_R_RFCON2			0x202

#define MRF24J40_M_PLLEN			0x80 /* mask bit 7 */
	#define MRF24J40_SET_PLLEN(R,V)		(R = (R & (MRF24J40_M_PLLEN ^ 0xFF)) | ((V & 0x01) << 7))
	#define MRF24J40_GET_PLLEN(R)		((R & MRF24J40_M_PLLEN) >> 7)

#define MRF24J40_R_RFCON3			0x203

#define MRF24J40_M_TXPWEL			0xC0 /* mask bits 7..6 */
	#define MRF24J40_SET_TXPWEL(R,V)	(R = (R & (MRF24J40_M_TXPWEL ^ 0xFF)) | ((V & 0x03) << 6))
	#define MRF24J40_GET_TXPWEL(R)		((R & MRF24J40_M_TXPWEL) >> 6)

#define MRF24J40_M_TXPWRS			0x38 /* mask bits 5..3 */
	#define MRF24J40_SET_TXPWRS(R,V)	(R = (R & (MRF24J40_M_TXPWRS ^ 0xFF)) | ((V & 0x07) << 3))
	#define MRF24J40_GET_TXPWRS(R)		((R & MRF24J40_M_TXPWRS) >> 3)

#define MRF24J40_R_RFCON5			0x205

#define MRF24J40_M_BATTH			0xF0 /* mask bit 7..4 */
	#define MRF24J40_SET_BATTH(R,V)		(R = (R & (MRF24J40_M_BATTH ^ 0xFF)) | ((V & 0x0F) << 4))
	#define MRF24J40_GET_BATTH(R)		((R & MRF24J40_M_BATTH) >> 4)

#define MRF24J40_R_RFCON6			0x206

#define MRF24J40_M_TXFIL			0x80 /* mask bit 7 */
	#define MRF24J40_SET_TXFIL(R,V)		(R = (R & (MRF24J40_M_TXFIL ^ 0xFF)) | ((V & 0x01) << 7))
	#define MRF24J40_GET_TXFIL(R)		((R & MRF24J40_M_TXFIL) >> 7)

#define MRF24J40_M_20MRECVR			0x10 /* mask bit 4 */
	#define MRF24J40_SET_20MRECVR(R,V)	(R = (R & (MRF24J40_M_20MRECVR ^ 0xFF)) | ((V & 0x01) << 4))
	#define MRF24J40_GET_20MRECVR(R)	((R & MRF24J40_M_20MRECVR) >> 4)

#define MRF24J40_M_BATEN			0x80 /* mask bit 3 */
	#define MRF24J40_SET_BATEN(R,V)		(R = (R & (MRF24J40_M_BATEN ^ 0xFF)) | ((V & 0x01) << 3))
	#define MRF24J40_GET_BATEN(R)		((R & MRF24J40_M_BATEN) >> 3)

#define MRF24J40_R_RFCON7			0x207

#define MRF24J40_M_SLPCLKSEL			0xC0 /* mask bits 7..6 */
	#define MRF24J40_SET_SLPCLKSEL(R,V)	(R = (R & (MRF24J40_M_SLPCLKSEL ^ 0xFF)) | ((V & 0x03) << 6))
	#define MRF24J40_GET_SLPCLKSEL(R)	((R & MRF24J40_M_SLPCLKSEL) >> 6)

#define MRF24J40_R_RFCON8			0x208

#define MRF24J40_M_RFVCO			0x10 /* mask bit 4 */
	#define MRF24J40_SET_RFVCO(R,V)		(R = (R & (MRF24J40_M_RFVCO ^ 0xFF)) | ((V & 0x01) << 4))
	#define MRF24J40_GET_RFVCO(R)		((R & MRF24J40_M_RFVCO) >> 4)

/*
 * Sleep Calibration Register
 */
#define MRF24J40_R_SLPCAL0			0x209

#define MRF24J40_M_SLPCAL0			0xFF /* mask bits 7..0 */
	#define MRF24J40_SET_SLPCAL0(R,V)	(R = (R & (MRF24J40_M_SLPCAL0 ^ 0xFF)) | (V & 0xFF))
	#define MRF24J40_GET_SLPCAL0(R)		(R & MRF24J40_M_SLPCAL0)

#define MRF24J40_R_SLPCAL1			0x20A

#define MRF24J40_M_SLPCAL1			0xFF /* mask bits 7..0 */
	#define MRF24J40_SET_SLPCAL1(R,V)	(R = (R & (MRF24J40_M_SLPCAL1 ^ 0xFF)) | (V & 0xFF))
	#define MRF24J40_GET_SLPCAL1(R)		(R & MRF24J40_M_SLPCAL1)

#define MRF24J40_R_SLPCAL2			0x20B

#define MRF24J40_M_SLPCALRDY			0x80 /* mask bit 7 */
	#define MRF24J40_SET_SLPCALRDY(R,V)	(R = (R & (MRF24J40_M_SLPCALRDY ^ 0xFF)) | ((V & 0x01) << 7))
	#define MRF24J40_GET_SLPCALRDY(R)	((R & MRF24J40_M_SLPCALRDY) >> 7)

#define MRF24J40_M_SLPCALEN			0x10 /* mask bit 4 */
	#define MRF24J40_SET_SLPCALEN(R,V)	(R = (R & (MRF24J40_M_SLPCALEN ^ 0xFF)) | ((V & 0x01) << 4))
	#define MRF24J40_GET_SLPCALEN(R)	((R & MRF24J40_M_SLPCALEN) >> 4)

#define MRF24J40_M_SLPCAL2			0x0F /* mask bits 3..0 */
	#define MRF24J40_SET_SLPCAL2(R,V)	(R = (R & (MRF24J40_M_SLPCAL2 ^ 0xFF)) | (V & 0x0F))
	#define MRF24J40_GET_SLPCAL2(R)		(R & MRF24J40_M_SLPCAL2)

/* RF State Register */
#define MRF24J40_R_RFSTATE			0x20F

#define MRF24J40_M_RFSTATE			0x07 /* mask bits 2..0 */
	#define MRF24J40_SET_RFSTATE(R,V)	(R = (R & (MRF24J40_M_RFSTATE ^ 0xFF)) | (V & 0x07))
	#define MRF24J40_GET_RFSTATE(R)		(R & MRF24J40_M_RFSTATE)

/* Averaged RSSI Value Register */
#define MRF24J40_R_RSSI				0x210

#define MRF24J40_M_RSSI				0xFF /* mask bits 7..0 */
	#define MRF24J40_SET_RSSI(R,V)		(R = (R & (MRF24J40_M_RSSI ^ 0xFF)) | (V & 0xFF))
	#define MRF24J40_GET_RSSI(R)		(R & MRF24J40_M_RSSI)

/*
 * Sleep Clock Control Register
 */
#define MRF24J40_R_SLPCON0			0x211

#define MRF24J40_M_INTEDGE			0x02 /* mask bit 1 */
	#define MRF24J40_SET_INTEDGE(R,V)	(R = (R & (MRF24J40_M_INTEDGE ^ 0xFF)) | ((V & 0x01) << 1))
	#define MRF24J40_GET_INTEDGE(R)		((R & MRF24J40_M_INTEDGE) >> 1)

#define MRF24J40_M_SLPCLKEN			0x01 /* mask bit 0 */
	#define MRF24J40_SET_SLPCLKEN(R,V)	(R = (R & (MRF24J40_M_SLPCLKEN ^ 0xFF)) | (V & 0x01))
	#define MRF24J40_GET_SLPCLKEN(R)	(R & MRF24J40_M_SLPCLKEN)

#define MRF24J40_R_SLPCON1			0x220

#define MRF24J40_M_CLKOUTEN			0x20 /* mask bit 5 */
	#define MRF24J40_SET_CLKOUTEN(R,V)	(R = (R & (MRF24J40_M_CLKOUTEN ^ 0xFF)) | ((V & 0x01) << 5))
	#define MRF24J40_GET_CLKOUTEN(R)	((R & MRF24J40_M_CLKOUTEN) >> 5)

#define MRF24J40_M_SLPCLKDIV			0x1F /* mask bits 4..0 */
	#define MRF24J40_SET_SLPCLKDIV(R,V)	(R = (R & (MRF24J40_M_SLPCLKDIV ^ 0xFF)) | (V & 0x1F))
	#define MRF24J40_GET_SLPCLKDIV(R)	(R & MRF24J40_M_SLPCLKDIV)

/*
 * Wake-Up Time Match Value Register
 */
#define MRF24J40_R_WAKETIMEL			0x222

#define MRF24J40_M_WAKETIMEL			0xFF /* mask bits 7..0 */
	#define MRF24J40_SET_WAKETIMEL(R,V)	(R = (R & (MRF24J40_M_WAKETIMEL ^ 0xFF)) | (V & 0xFF))
	#define MRF24J40_GET_WAKTEIMEL(R)	(R & MRF24J40_M_WAKETIMEL)

#define MRF24J40_R_WAKETIMEH			0x223

#define MRF24J40_M_WAKETIMEH			0x07 /* mask bits 2..0 */
	#define MRF24J40_SET_WAKETIMEH(R,V)	(R = (R & (MRF24J40_M_WAKETIMEH ^ 0xFF)) | (V & 0x07))
	#define MRF24J40_GET_WAKETIMEH(R)	(R & MRF24J40_M_WAKETIMEH)

/*
 * Remain Counter Register
 */
#define MRF24J40_R_REMCNTL			0x224
#define MRF24J40_R_REMCNTH			0x225

#define MRF24J40_M_REMCNT			0xFF /* mask bits 7..0 */
	#define MRF24J40_SET_REMCNT(R,V)	(R = (R & (MRF24J40_M_REMCNT ^ 0xFF)) | (V & 0xFF))
	#define MRF24J40_GET_REMCNT(R)		(R & MRF24J40_M_REMCNT)

/*
 * Main Counter Register
 */
#define MRF24J40_R_MAINCNT0			0x226
#define MRF24J40_R_MAINCNT1			0x227
#define MRF24J40_R_MAINCNT2			0x228
#define MRF24J40_R_MAINCNT3			0x229

#define MRF24J40_M_MAINCNT3			0x03 /* mask bits 1..0 */
	#define MRF24J40_SET_MAINCNT3(R,V)	(R = (R & (MRF24J40_M_MAINCNT3 ^ 0xFF)) | (V & 0x03))
	#define MRF24J40_GET_MAINCNT3(R)	(R & MRF24J40_M_MAINCNT3)

/*
 * Test Mode Register
 */
#define MRF24J40_R_TESTMODE			0x22F

#define MRF24J40_M_RSSIWAIT			0x18 /* mask bits 4..3 */
	#define MRF24J40_SET_RSSIWAIT(R,V)	(R = (R & (MRF24J40_M_RSSIWAIT ^ 0xFF)) | ((V & 0x03) << 3))
	#define MRF24J40_GET_RSSIWAIT(R)	((R & MRF24J40_M_RSSIWAIT) >> 3)

#define MRF24J40_M_TESTMODE			0x07 /* mask bits 2..0 */
	#define MRF24J40_SET_TESTMODE(R,V)	(R = (R & (MRF24J40_M_TESTMODE ^ 0xFF)) | (V & 0x07))
	#define MRF24J40_GET_TESTMODE(R)	(R & MRF24J40_M_TESTMODE)

/*
 * Associated Coordinator Extended Address Register
 */
#define MRF24J40_R_ASSOEADR0			0x230
#define MRF24J40_R_ASSOEADR1			0x231
#define MRF24J40_R_ASSOEADR2			0x232
#define MRF24J40_R_ASSOEADR3			0x233
#define MRF24J40_R_ASSOEADR4			0x234
#define MRF24J40_R_ASSOEADR5			0x235
#define MRF24J40_R_ASSOEADR6			0x236
#define MRF24J40_R_ASSOEADR7			0x237

#define MRF24J40_M_ASSOEADR			0xFF /* mask bits 7..0 */
	#define MRF24J40_SET_ASSOEADR(R,V)	(R = (R & (MRF24J40_M_ASSOEADR ^ 0xFF)) | (V & 0xFF))
	#define MRF24J40_GET_ASSOEADR(R)	(R & MRF24J40_M_ASSOEADR)

/*
 * Associated Coordinator Short Address Register
 */
#define MRF24J40_R_ASSOSADR0			0x238
#define MRF24J40_R_ASSOSADR1			0x239

#define MRF24J40_M_ASSOSADR			0xFF /* mask bits 7..0 */
	#define MRF24J40_SET_ASSOSADR(R,V)	(R = (R & (MRF24J40_M_ASSOSADR ^ 0xFF)) | (V & 0xFF))
	#define MRF24J40_GET_ASSOSADR(R)	(R & MRF24J40_M_ASSOSADR)

/*
 * Upper Nonce Security Register
 */
#define MRF24J40_R_UPNONCE0			0x240
#define MRF24J40_R_UPNONCE1			0x241
#define MRF24J40_R_UPNONCE2			0x242
#define MRF24J40_R_UPNONCE3			0x243
#define MRF24J40_R_UPNONCE4			0x244
#define MRF24J40_R_UPNONCE5			0x245
#define MRF24J40_R_UPNONCE6			0x246
#define MRF24J40_R_UPNONCE7			0x247
#define MRF24J40_R_UPNONCE8			0x248
#define MRF24J40_R_UPNONCE9			0x249
#define MRF24J40_R_UPNONCE10			0x24A
#define MRF24J40_R_UPNONCE11			0x24B
#define MRF24J40_R_UPNONCE12			0x24C

#define MRF24J40_M_UPNONCE			0xFF /* mask bits 7..0 */
	#define MRF24J40_SET_UPNONCE(R,V)	(R = (R & (MRF24J40_M_UPNONCE ^ 0xFF)) | (V & 0xFF))
	#define MRF24J40_GET_UPNONCE(R)		(R & MRF24J40_M_UPNONCE)

#endif //_MRF24J40_REGMAP_H
