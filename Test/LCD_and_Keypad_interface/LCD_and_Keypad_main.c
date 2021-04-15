// for all 8051 ICs
#include<reg51.h>
// for Keyboard 4x3 (Rows x Columns)
sbit row_A = P1^0;
sbit row_B = P1^1;
sbit row_C = P1^2;
sbit row_D = P1^3;
sbit column1 = P1^4;
sbit column2 = P1^5;
sbit column3 = P1^6;


// for LCD 
sbit rs = P3^0;
sbit rw = P3^1;
sbit en = P3^2;

//Prototype
void delay(unsigned int);

void input_delay(){
	unsigned int i;
	for (i=0;i<350;i++){
		delay(100);
	}
}
void delay(unsigned int delay_value){
	unsigned int i;
	for(i=0;i<delay_value;i++);
}

void lcd_cmd(unsigned char val){
	P2 = val;
	rs = 0;
	rw = 0;
	en = 0;
	delay(150);
	en=1;
}

void lcd_data(unsigned char val){
	P2 = val;
	rs = 1;
	rw = 0;
	en = 1;
	delay(150);
	en=0;
}

void init_lcd(){
	lcd_cmd(0x38); // 5x7 matrix crystal of 2 lines 8bit-mode
	lcd_cmd(0x0c); // turning on display 
	lcd_cmd(0x01); // clear screen
	lcd_cmd(0x80); //setting cursor to 1st line 2nd pos
	delay(150);
}

void lcd_second_line(){
	lcd_cmd(0x38); // 5x7 matrix crystal of 2 lines 8bit-mode
	lcd_cmd(0xC0); //setting cursor to 1st line 2nd pos
	delay(150);
}

void print_banner(){
		lcd_data('C');
		delay(150);
		lcd_data('o');
		delay(150);
		lcd_data('d');
		delay(150);
		lcd_data('e');
		delay(150);
		lcd_data(' ');
		delay(150);
		lcd_data('b');
		delay(150);
		lcd_data('y');
		delay(150);
		lcd_data(' ');
		delay(150);
		
		// Code for second line
		lcd_second_line();//setting cursor to 2nd line 2nd pos
		delay(150);
		
		lcd_data('D');
		delay(150);
		lcd_data('h');
		delay(150);
		lcd_data('r');
		delay(150);
		lcd_data('u');
		delay(150);
		lcd_data('m');
		delay(150);
		lcd_data('i');
		delay(150);
		lcd_data('l');
		delay(150);
		lcd_data(' ');
		delay(150);
		lcd_data('M');
		delay(150);
		lcd_data('i');
		delay(150);
		lcd_data('s');
		delay(150);
		lcd_data('t');
		delay(150);
		lcd_data('r');
		delay(150);
		lcd_data('y');
		delay(150);
}
	

void init_keyboard(){
	row_A = 1;
	row_B = 1;
	row_C = 1;
	row_D = 1;
	column1 = 1;
	column2 = 1;
	column3 = 1;
}
void main(){
	P0= 0x00; // Output Declaration
	
	init_lcd();
	print_banner();
	input_delay();
	init_lcd();
	
	while(1){
		
		init_keyboard();
		// identifying the button
		// For Row A
		row_A = 0;
		if (row_A == 0){
			if(column1==0){
				lcd_data('1');
				input_delay();
			}
			if(column2==0){
				lcd_data('2');
				input_delay();
			}
			if(column3==0){
				lcd_data('3');
				input_delay();
			}
		}
		
		// For Row B
		row_A = 1;
		row_B = 0;
		if (row_B == 0){
			if(column1==0){
				lcd_data('4');
				input_delay();
			}
			if(column2==0){
				lcd_data('5');
				input_delay();
			}
			if(column3==0){
				lcd_data('6');
				input_delay();
			}
		}
		
		// For Row C
		row_B = 1;
		row_C = 0;
		if (row_C == 0){
			if(column1==0){
				lcd_data('7');
				input_delay();
			}
			if(column2==0){
				lcd_data('8');
				input_delay();
			}
			if(column3==0){
				lcd_data('9');
				input_delay();
			}
		}

		// For Row D
		row_C = 1;
		row_D = 0;
		if (row_D == 0){
			if(column1==0){
				lcd_data('*');
				input_delay();
			}
			if(column2==0){
				lcd_data('0');
				input_delay();
			}
			if(column3==0){
				lcd_data('#');
				input_delay();
			}
		}
		
	}

}