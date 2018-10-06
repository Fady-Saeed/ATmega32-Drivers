#include "LCD.h"

void LCDRunTests(void){
	LCDInit();
	
	LCDWriteString("Test LCD");
	_delay_ms(1000);
	LCDClear();
	
	
	LCDWriteInteger(98765);
	_delay_ms(1000);
	LCDClear();
	
	
	LCDWriteInteger(-98765);
	_delay_ms(1000);
	LCDClear();
	
	LCDWriteFloat(98765.892);
	LCDClear();
	_delay_ms(1000);
	
	LCDWriteFloat(-98765.892);
	_delay_ms(1000);
	LCDClear();
}