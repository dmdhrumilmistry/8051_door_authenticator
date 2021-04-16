// for all 8051 ICs
#include<reg51.h>
#include<string.h>
// for Output motor
sbit motor = P1^7;

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
void lcd_cmd(char val){
	P2 = val;
	rs = 0;
	rw = 0;
	en = 0;
	delay(150);
	en=1;
}

void lcd_data(char val){
	P2 = val;
	rs = 1;
	rw = 0;
	en = 1;
	delay(150);
	en=0;
}

void init_lcd(int line_number, int clear_flag){
	lcd_cmd(0x38); // 5x7 matrix crystal of 2 lines 8bit-mode
	lcd_cmd(0x0c); // turning on display 
	if(clear_flag == 1){
		lcd_cmd(0x01); // clear screen
	}
	if (line_number==2){
		lcd_cmd(0xC0);
	}else{
		lcd_cmd(0x80); //setting cursor to 1st line 2nd pos
	}
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

char get_key_pressed(char key1,char key2,char key3){
	char key  = ' ';
	if(column1==0){
		key = key1;
		//lcd_data(key1);
		input_delay();
		
	}
	if(column2==0){
		key = key2;
		//lcd_data(key2);
		input_delay();
	}
	if(column3==0){
		key = key3;
		//lcd_data(key3);
		input_delay();
	}
	
	return key;
}

// Functions for Strings
void print_string(char *string, unsigned int n){
	unsigned int i;
	// init_lcd();
	if (n==2)
		lcd_second_line();
	for(i=0;i<strlen(string);i++){
			lcd_data(string[i]);
		delay(1200);
	}
}


// Main Function
void main(){
	// Declarations
	char code_by[] = "Code By";
	char credits[] = "Dhrumil Mistry";
	char auth[] = "Authenticated!";
	char failed_message[] = "Wrong Pin!!";
	char prompt[] = "Enter Pin:";
	
	char password[] = "123456";
	char entered_pass[16];
	char key_pressed = ' ';
	int pass_len = 0,i;
	P0= 0x00; // Output Declaration
	// intializing output to low
	motor = 0;
	
	//setting iterations acc to pass len
	pass_len = strlen(password);
	
	init_lcd(1,1);
	print_string(code_by,1);
	input_delay();
	
	print_string(credits,2);
	input_delay();
	init_lcd(1,1);
	
	print_string(prompt,1);
	input_delay();
	init_lcd(2,0);
	// Repeating Code
	for(i=0;i<pass_len;){
		
		init_keyboard();
		// identifying the button
		// For Row A
		row_A = 0;
		if (row_A == 0){
			key_pressed = get_key_pressed('1','2','3');
			if(key_pressed != ' '){
				lcd_data(key_pressed);
				strncat(entered_pass,&key_pressed,1);
				i++;
			}
		}
		
		// For Row B
		row_A = 1;
		row_B = 0;
		if (row_B == 0){
			key_pressed = get_key_pressed('4','5','6');
			if(key_pressed != ' '){
				lcd_data(key_pressed);
				strncat(entered_pass,&key_pressed,1);
				i++;
			}
		}
		
		// For Row C
		row_B = 1;
		row_C = 0;
		if (row_C == 0){
			key_pressed = get_key_pressed('7','8','9');
			if(key_pressed != ' '){
				lcd_data(key_pressed);
				strncat(entered_pass,&key_pressed,1);
				i++;
			}
		}

		// For Row D
		row_C = 1;
		row_D = 0;
		if (row_D == 0){
			key_pressed = get_key_pressed('*','0','#');
			if(key_pressed != ' '){
				lcd_data(key_pressed);
				strncat(entered_pass,&key_pressed,1);
				i++;
			}
		}
		
	}
	
	init_lcd(1,1);
	
	if(strcmp(password, entered_pass) == 0){
		motor = 1;
		print_string(auth,1);
		input_delay();
		input_delay();
	} else{
		print_string(failed_message,1);
	}
	
	input_delay();
	input_delay();
	input_delay();

}