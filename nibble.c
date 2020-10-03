#include "stm32f0xx_hal.h"
#include "cmsis_os.h"
#include "nible.h"

// Set these values to select the port and offset of the nible
#define NIBLE_PORT GPIOC
#define NIBLE_LSB 0

// Set a mark 1..7 (zero is reserved)
void sendMark(uint8_t n)
{
	taskENTER_CRITICAL();
	
	NIBLE_PORT->ODR &= ~(0x000F << NIBLE_LSB);
	NIBLE_PORT->ODR |= (0x0007 & n) << NIBLE_LSB;
	NIBLE_PORT->ODR |= (0x0007 & n) << NIBLE_LSB;
	NIBLE_PORT->ODR |= (0x0007 & n) << NIBLE_LSB;
	NIBLE_PORT->ODR &= ~(0x000F << NIBLE_LSB);
	
	taskEXIT_CRITICAL();
}

// Helper function
void sendNibble(uint8_t nib)
{
	uint16_t reg = NIBLE_PORT->IDR;
	reg &= ~(0x000F << NIBLE_LSB);
	
	// To send a zero we send two seqential values followed by zero, in this case A then F
	if((nib & 0x0F) == 0)
	{
		reg |= (uint16_t)(0x0A << NIBLE_LSB);
		NIBLE_PORT->ODR = reg;
		nib = 0x05;
	}
	
	reg |= (uint16_t)((nib & 0x0F) << NIBLE_LSB);
	NIBLE_PORT->ODR = reg;
		
	NIBLE_PORT->ODR &= ~(0x000F << NIBLE_LSB);
}

// Export a 8 bit value
void sendByte(uint8_t label, uint8_t b)
{
	taskENTER_CRITICAL();
	
	sendNibble(8+1);
	sendNibble(label);
	
	sendNibble(b >> 4);
	sendNibble(b);
	
	taskEXIT_CRITICAL();
}

// Export a 16 bit value
void sendWord(uint8_t label, uint16_t w)
{
	taskENTER_CRITICAL();
	
	sendNibble(8+2);
	sendNibble(label);
	
	for(int16_t i = 12; i >= 0; i -= 4)
		sendNibble((uint8_t)(w >> i));
	
	taskEXIT_CRITICAL();
}

// Export a 32 bit value
void sendLong(uint8_t label, uint32_t l)
{
	taskENTER_CRITICAL();
	
	sendNibble(8+4);
	sendNibble(label);
	
	for(int16_t i = 28; i >= 0; i -= 4)
		sendNibble((uint8_t)(l >> i));
	
	taskEXIT_CRITICAL();
}
