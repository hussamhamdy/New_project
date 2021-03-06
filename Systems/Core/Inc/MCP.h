/*
 * MCP.h
 *
 *  Created on: Feb 16, 2022
 *      Author: Hussam Hamdy
 */

#ifndef INC_MCP_H_
#define INC_MCP_H_

#include "stm32f1xx_hal.h"

uint8_t MCP2515_U8ReadRegister(uint8_t address);
void MCP2515_voidWriteRegister(uint8_t address , uint8_t value);
void MCP2515_voidSetBitTiming(uint8_t cnf1Value, uint8_t cnf2Value, uint8_t cnf3Value);
void MCP2515_voidReset(void);
void MCP2515_voidChangeBits(uint8_t address ,uint8_t mask, uint8_t value);
void MCP2515_voidSetMode(uint8_t mode);
void MCP2515_voidSetRollover(uint8_t value);
void MCP2515_voidsetMask(uint8_t maskaddress , uint32_t maskvalue , uint8_t extended);
void MCP2515_voidReciveInit(void);
void MCP2515_voidRecieveCANmsg(void);

#define MCP2515_MODE_NORMAL			0x0
#define MCP2515_MODE_SLEEP			0x1
#define MCP2515_MODE_LOOPBACK		0x2
#define MCP2515_MODE_LISTEN_ONLY	0x3
#define MCP2515_MODE_CONFG			0x4



#define INST_RESET			(0xC0)
#define INST_READ			(0x03)
#define INST_WRITE			(0x02)
#define INST_RTS_TXB0		(0x81)
#define INST_RTS_TXB1		(0x82)
#define INST_RTS_TXB2		(0x84)
#define INST_READ_STATUS	(0xA0)
#define INST_RX_STATUS		(0xB0)
#define INST_BIT_MODIFY		(0x05)


#define CNF1				(0x2A)
#define CNF2				(0x29)
#define CNF3				(0x28)

#define CANCTRL				(0x0F)
#define CANSTAT				(0x0E)

#define TXB0CTRL			(0x30)

#define RXB0CTRL			(0x60)
#define RXB1CTRL			(0x70)

#define BUKT				2

#define RXM0SIDH			(0x20)
#define RXM1SIDH			(0x24)

#define CANINTE				(0x2B)
#define CANINTF				(0x2C)

#define RX0IE				0
#define RX1IE				1
#define RX0IF				0
#define RX1IF				1




#endif /* INC_MCP_H_ */
