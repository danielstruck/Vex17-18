#ifndef _LCD_TEMPLATE_H_
#define _LCD_TEMPLATE_H_
/*
*======================================
*						--IMPORTANT--
*
* USE #include TO IMPORT THIS TEMPLATE
*
*						--IMPORTANT--
*======================================
*/




//==========================================================================Vex LCD Commands=======================================
void setupLCD(){
	//turns on the LCD's backlight
	bLCDBacklight = true;
}
//--------------------------------Draw Numbers
void drawNum(int line, int pos, float number){//(line # [1-2], position on line [usually zero (0)], what to display)
	if(line == 0 || line == 1){
		displayLCDNumber(line, pos, number);
	}
}
void drawNum(float number){//Displays a string on the next open line
	displayNextLCDNumber(number);
}
void drawNum(int line, float number){
	if(line == 0 || line == 1){
		displayLCDNumber(line, 0, number);
	}
}
//--------------------------------Draw Strings
void drawString(int line, int pos, string words){//(line # [1-2], position on line [usually zero (0)], what to display)
	if(line == 0 || line == 1){
		displayLCDString(line, pos, words);
	}
}
void drawString(string words){//Displays a string on the next open line
	displayNextLCDString(words);
}
void drawString(int line, string words){
	if(line == 0 || line == 1){
		displayLCDString(line, 0, words);
	}
}
//--------------------------------Draw Centered Strings
void drawCString(int line, string words){
	displayLCDCenteredString(line, words);
}
//--------------------------------Clear Lines
void clearLCD(int line){//(line to clear)
	clearLCDLine(line);
}
void clearLCD(){
	clearLCDLine(0);
	clearLCDLine(1);
}
//--------------------------------Return [int] Buttons
const int inputLCDLeft = 1, inputLCDCenter = 2, inputLCDRight = 4;
int getLCDInput(){//LEFT = 1; CENTER = 2; LEFT & CENTER = 3; RIGHT = 4; LEFT & RIGHT = 5; CENTER & RIGHT = 6; ALL = 7
	return nLCDButtons;
}
void waitForLCDPress(){
	while(getLCDInput() == 0);
	wait10Msec(5);
}
void waitForLCDRelease(){
	while(getLCDInput() != 0);
	wait10Msec(5);
}

#endif // _CONTROLLER_TEMPLATE_H_
