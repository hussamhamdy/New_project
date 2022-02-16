/*
 * MCP.c
 *
 *  Created on: Feb 16, 2022
 *      Author: Hussam Hamdy
 */

#include "stm32f1xx_hal.h"

#include "MCP.h"



uint8_t readBuffer[14];


uint8_t MCP2515_U8ReadRegister(uint8_t address){
	uint8_t regVal ;
	uint8_t dummy ;
	HAL_GPIO_WritePin(CsPort, CsPIN, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi, INST_READ, &dummy, 1, Timeout);
	HAL_SPI_TransmitReceive(hspi, &address, &dummy, 1, Timeout);
	HAL_SPI_TransmitReceive(hspi, 0, &regVal, 1, Timeout);
	HAL_GPIO_WritePin(CsPort, CsPIN, GPIO_PIN_SET);
	return regVal ;
}

void MCP2515_voidWriteRegister(uint8_t address , uint8_t value){

	uint8_t dummy ;
	HAL_GPIO_WritePin(CsPort, CsPIN, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi, INST_WRITE, &dummy, 1, Timeout);
	HAL_SPI_TransmitReceive(hspi, &address, &dummy, 1, Timeout);
	HAL_SPI_TransmitReceive(hspi, &value, &dummy, 1, Timeout);
	HAL_GPIO_WritePin(CsPort, CsPIN, GPIO_PIN_SET);

}

void MCP2515_voidSetBitTiming(uint8_t cnf1Value, uint8_t cnf2Value, uint8_t cnf3Value)
{
	MCP2515_voidWriteRegister(CNF1, cnf1Value);
	MCP2515_voidWriteRegister(CNF2, cnf2Value);
	MCP2515_voidWriteRegister(CNF3, cnf3Value);
}

void MCP2515_voidReset(void){

	uint8_t dummy ;
	HAL_GPIO_WritePin(CsPort, CsPIN, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi, INST_RESET, &dummy, 1, Timeout);
	HAL_GPIO_WritePin(CsPort, CsPIN, GPIO_PIN_SET);

}

void MCP2515_voidChangeBits(uint8_t address ,uint8_t mask, uint8_t value){

	uint8_t dummy ;
	HAL_GPIO_WritePin(CsPort, CsPIN, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi, INST_BIT_MODIFY, &dummy, 1, Timeout);
	HAL_SPI_TransmitReceive(hspi, &address, &dummy, 1, Timeout);
	HAL_SPI_TransmitReceive(hspi, &mask, &dummy, 1, Timeout);
	HAL_SPI_TransmitReceive(hspi, &value, &dummy, 1, Timeout);
	HAL_GPIO_WritePin(CsPort, CsPIN, GPIO_PIN_SET);

}

void MCP2515_voidSetMode(uint8_t mode){
	MCP2515_voidChangeBits(CANCTRL, 0xE0, mode<<5);
	while((MCP2515_U8ReadRegister(CANSTAT)>>5) != mode);
}

void MCP2515_voidSetRollover(uint8_t value){
	MCP2515_voidChangeBits(RXB0CTRL, 1<<BUKT, value<<BUKT);

}

void MCP2515_voidsetMask(uint8_t maskaddress , uint32_t maskvalue , uint8_t extended){

	uint8_t dummy ;
	uint8_t value ;
	HAL_GPIO_WritePin(CsPort, CsPIN, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi, INST_WRITE, &dummy, 1, Timeout);
	HAL_SPI_TransmitReceive(hspi, &maskaddress, &dummy, 1, Timeout);
	if(extended){
	value = ((uint8_t) (maskvalue >> 3)) ;
	HAL_SPI_TransmitReceive(hspi, &value, &dummy, 1, Timeout);
	value = ((uint8_t) (maskvalue << 5) | (1<<3) | (uint8_t)(maskvalue>>27)) ;
	HAL_SPI_TransmitReceive(hspi, &value, &dummy, 1, Timeout);
	value = ((uint8_t) (maskvalue >> 19)) ;
	HAL_SPI_TransmitReceive(hspi, &value, &dummy, 1, Timeout);
	value = ((uint8_t) (maskvalue >> 11)) ;
	HAL_SPI_TransmitReceive(hspi, &value, &dummy, 1, Timeout);
	}
	else{
		value = ((uint8_t) (maskvalue >> 3)) ;
			HAL_SPI_TransmitReceive(hspi, &value, &dummy, 1, Timeout);
			value = ((uint8_t) (maskvalue << 5)) ;
			HAL_SPI_TransmitReceive(hspi, &value, &dummy, 1, Timeout);
	}
	HAL_GPIO_WritePin(CsPort, CsPIN, GPIO_PIN_SET);
}

void MCP2515_voidReciveInit(void){
	MCP2515_voidReset();
	MCP2515_voidWriteRegister(CANCTRL, 0x84);
	while((MCP2515_U8ReadRegister(CANSTAT)>>5) != MCP2515_MODE_CONFG);
	MCP2515_voidSetBitTiming((2<<6), (1<<7)|(6<<3)|(1), (5));
	MCP2515_voidsetMask(RXM0SIDH, 0x0000000, 1);
	MCP2515_voidsetMask(RXM1SIDH, 0x0000000, 1);
	MCP2515_voidSetRollover(1);

	MCP2515_voidWriteRegister(CANINTE, 1<<RX0IE);
	MCP2515_voidSetMode(MCP2515_MODE_NORMAL);
}

void MCP2515_voidRecieveCANmsg(void){
	uint8_t dummy ;
		HAL_GPIO_WritePin(CsPort, CsPIN, GPIO_PIN_RESET);
		HAL_SPI_TransmitReceive(hspi, INST_READ, &dummy, 1, Timeout);
		HAL_SPI_TransmitReceive(hspi, RXB0CTRL, &dummy, 1, Timeout);


		for(uint8_t i = 0 ; i<14 ; i++){

			HAL_SPI_TransmitReceive(hspi, &value, &dummy, 1, Timeout);
		}
		HAL_GPIO_WritePin(CsPort, CsPIN, GPIO_PIN_SET);
}
