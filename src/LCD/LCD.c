#include "LCD.h"

// Global Variables
unsigned char written_characters_counter = 0;

// Prototypes
void LCDResetDataPins(void);
unsigned char LCDSetEnablePin(unsigned char value);
void LCDWriteCharacter(char character);

void LCDInit(void){
	LCD_CONTROL_DIRECTION_REGISTER |= (1 << LCD_VSS_PIN | 1 << LCD_VDD_PIN | 1 << LCD_VE_PIN | 1 << LCD_EN_PIN | 1 << LCD_RW_PIN | 1 << LCD_RS_PIN);
	LCD_DATA_DIRECTION_REGISTER = 0xFF;

	LCD_CONTROL_PORT_REGISTER &= ~(1 << LCD_VSS_PIN | 1 << LCD_EN_PIN | 1 << LCD_RW_PIN | 1 << LCD_RS_PIN);
	LCD_CONTROL_PORT_REGISTER |= (1 << LCD_VDD_PIN | 1 << LCD_VE_PIN);

	LCDSendCommand(LCD_ENTRY_MODE_COMMAND);
	LCDSendCommand(LCD_DISPLAY_ON_CURSOR_BLINKING_COMMAND);
	LCDSendCommand(LCD_8BIT_MODE_TWO_LINES_5X7_MATRIX_COMMAND);
}
unsigned char LCDIsBusy(void){
	LCDResetDataPins();
	
	LCDSwitchMode(LCD_READ_COMMAND_MODE);
	return !((LCD_DATA_PIN_REGISTER & (1 << LCD_D7_PIN)) >> LCD_D7_PIN);
}
unsigned char LCDSwitchMode(unsigned char mode){
	switch (mode)
	{
		case LCD_READ_COMMAND_MODE:
			LCD_CONTROL_PORT_REGISTER &= ~(1 << LCD_RS_PIN);
			LCD_CONTROL_PORT_REGISTER |= 1 << LCD_RW_PIN;
			return 1;
		case LCD_WRITE_COMMAND_MODE:
			LCD_CONTROL_PORT_REGISTER &= ~(1 << LCD_RS_PIN | 1 << LCD_RW_PIN);
			return 1;
		case LCD_WRITE_CHARACTER_MODE:
			LCD_CONTROL_PORT_REGISTER |= 1 << LCD_RS_PIN;
			LCD_CONTROL_PORT_REGISTER &= ~(1 << LCD_RW_PIN);
			return 1;
		default:
			return 0;
	}
}
unsigned char LCDMoveCursor(unsigned char row, unsigned char column){
	unsigned char command = 0;
	if(row >= LCD_NUMBER_OF_ROWS || column >= LCD_NUMBER_OF_CHARACTERS_PER_ROW)
		return 0;
	switch(row){
		case 0:
			command += (0x80 + column);
			break;
		case 1:
			command += (0xC0 + column);
			break;
	}
	LCDSendCommand(command);
	return 1;
}
void LCDClear(void){
	LCDSendCommand(LCD_CLEAR_DISPLAY_COMMAND);
}
void LCDRefresh(void){
	LCDSetEnablePin(0);
	_delay_ms(50);
	LCDSetEnablePin(1);
	written_characters_counter = 0;
}
void LCDWriteCharacter(char character){
	while(LCDIsBusy());
	LCDSwitchMode(LCD_WRITE_CHARACTER_MODE);
	LCDResetDataPins();
	LCD_DATA_PORT_REGISTER = ((character&0xFF) << LCD_D0_PIN);
	LCDRefresh();
	written_characters_counter++;
}
void LCDWriteString(char* word){
	unsigned int count = 0;
	
	while(*word != '\0'){	
		count++;
		LCDWriteCharacter(*(word++));

	}
}
void LCDWriteInteger(int number){
	char string_buffer[10];
	sprintf(string_buffer,"%d",number);
	LCDWriteString(string_buffer);
}
void LCDWriteFloat(float number){
	char string_buffer[13];
	sprintf(string_buffer,"%4.02f",number);
	LCDWriteString(string_buffer);
}
void LCDSendCommand(unsigned char command){
	while(LCDIsBusy());
	LCDSwitchMode(LCD_WRITE_COMMAND_MODE);
	LCDResetDataPins();
	LCD_DATA_PORT_REGISTER |= (command << LCD_D0_PIN);
	LCDRefresh();
}

// Helper Functions
void LCDResetDataPins(void){
	LCD_DATA_DIRECTION_REGISTER &= ~(
	1 << LCD_D0_PIN |
	1 << LCD_D1_PIN |
	1 << LCD_D2_PIN |
	1 << LCD_D3_PIN |
	1 << LCD_D4_PIN |
	1 << LCD_D5_PIN |
	1 << LCD_D6_PIN |
	1 << LCD_D7_PIN
	);
}
unsigned char LCDSetEnablePin(unsigned char value){
	if(value > 1) return 0;
	if(value == 0)
	LCD_CONTROL_PORT_REGISTER &= ~(1 << LCD_EN_PIN);
	else
	LCD_CONTROL_PORT_REGISTER |= 1 << LCD_EN_PIN;
	return 1;
}