#ifndef LCD_H_
#define LCD_H_

// Dependencies
#include <avr/io.h>
#include <util/delay.h>

// LCD Properties
#define LCD_NUMBER_OF_CHARACTERS_PER_ROW	16
#define LCD_NUMBER_OF_ROWS					2


// LCD PINS
#define LCD_CONTROL_DIRECTION_REGISTER		DDRA
#define LCD_CONTROL_PORT_REGISTER			PORTA
#define LCD_CONTROL_PIN_REGISTER			PINA

#define LCD_DATA_DIRECTION_REGISTER			DDRB
#define LCD_DATA_PORT_REGISTER				PORTB
#define LCD_DATA_PIN_REGISTER				PINB


// LCD PIN NUMBERS
#define LCD_VSS_PIN					0
#define LCD_VDD_PIN					1
#define LCD_VE_PIN					2
#define LCD_RS_PIN					3
#define LCD_RW_PIN					4
#define LCD_EN_PIN					5

#define LCD_BACKLIGHT_ANODE_PIN		6
#define LCD_BACKLIGHT_CATHODE_PIN	7

#define LCD_D0_PIN					0
#define LCD_D1_PIN					1
#define LCD_D2_PIN					2
#define LCD_D3_PIN					3
#define LCD_D4_PIN					4
#define LCD_D5_PIN					5
#define LCD_D6_PIN					6
#define LCD_D7_PIN					7


// LCD MODES
#define LCD_READ_COMMAND_MODE		0
#define LCD_WRITE_COMMAND_MODE		1
#define LCD_WRITE_CHARACTER_MODE	2

// LCD COMMANDS
#define LCD_8BIT_MODE_ONE_LINE_5X7_MATRIX_COMMAND		0x30
#define LCD_8BIT_MODE_TWO_LINES_5X7_MATRIX_COMMAND		0x38
#define LCD_4BIT_MODE_ONE_LINE_5X7_MATRIX_COMMAND		0x20
#define LCD_4BIT_MODE_TWO_LINES_5X7_MATRIX_COMMAND		0x28
#define LCD_ENTRY_MODE_COMMAND							0x06
#define LCD_DISPLAY_OFF_CURSOR_OFF_COMMAND				0x08
#define LCD_DISPLAY_ON_CURSOR_ON_COMMAND				0x0E
#define LCD_DISPLAY_ON_CURSOR_OFF_COMMAND				0x0C
#define LCD_DISPLAY_ON_CURSOR_BLINKING_COMMAND			0x0F
#define LCD_SHIFT_DISPLAY_LEFT_COMMAND					0x18
#define LCD_SHIFT_DISPLAY_RIGHT_COMMAND					0x1C
#define LCD_MOVE_CURSOR_LEFT_BY_ONE_CHARACTER_COMMAND	0x10
#define LCD_MOVE_CURSOR_RIGHT_BY_ONE_CHARACTER_COMMAND	0x14
#define LCD_CLEAR_DISPLAY_COMMAND						0x01
#define LCD_ACTIVATE_SECOND_LINE_COMMAND				0x3C


void LCDInit(void);
unsigned char LCDIsBusy(void);
unsigned char LCDSwitchMode(unsigned char mode);
unsigned char LCDMoveCursor(unsigned char row, unsigned char column);
void LCDClear(void);
void LCDRefresh(void);
void LCDWriteString(char* word);
void LCDWriteInteger(int number);
void LCDWriteFloat(float number);
void LCDSendCommand(unsigned char command);


#endif /* LCD_H_ */