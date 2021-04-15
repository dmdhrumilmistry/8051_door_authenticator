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

//Prototype declarations
void delay(unsigned int);

// Delay Functions
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

// Functions for LCD
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

// Functions for Keyboard
void init_keyboard(){
	row_A = 1;
	row_B = 1;
	row_C = 1;
	row_D = 1;
	column1 = 1;
	column2 = 1;
	column3 = 1;
}

void print_key_pressed(unsigned char key1,unsigned char key2,unsigned char key3){
	// unsigned int line_number = 1;
	if(column1==0){
		lcd_data(key1);
		input_delay();
	}
	if(column2==0){
		lcd_data(key2);
		input_delay();
	}
	if(column3==0){
		lcd_data(key3);
		input_delay();
	}
}

// Functions for Strings
unsigned int str_len(char *string){
	unsigned int length = 0;
	while(string[length]!='\0'){
		length++;
	}
	return length;
}

void print_string(char *string, unsigned int n){
	unsigned int i;
	// init_lcd();
	if (n==2)
		lcd_second_line();
	for(i=0;i<str_len(string);i++){
			lcd_data(string[i]);
		delay(1200);
	}
}


// Main Function
void main(){
	// Declarations
	char code_by[] = "Code By";
	char credits[] = "Dhrumil Mistry";
	P0= 0x00; // Output Declaration
	
	init_lcd();
	print_string(code_by,1);
	input_delay();
	
	print_string(credits,2);
	input_delay();
	init_lcd();
	
	// Repeating Code
	while(1){
		
		init_keyboard();
		// identifying the button
		// For Row A
		row_A = 0;
		if (row_A == 0){
			print_key_pressed('1','2','3');
		}
		
		// For Row B
		row_A = 1;
		row_B = 0;
		if (row_B == 0){
			print_key_pressed('4','5','6');
		}
		
		// For Row C
		row_B = 1;
		row_C = 0;
		if (row_C == 0){
			print_key_pressed('7','8','9');
		}

		// For Row D
		row_C = 1;
		row_D = 0;
		if (row_D == 0){
			print_key_pressed('*','0','#');
		}

	}

}