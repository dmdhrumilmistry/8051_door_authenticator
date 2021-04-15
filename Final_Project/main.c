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


// Door 
sbit op = P1^7;

//Prototype declarations
void delay(unsigned int);
void print_string(char *string, unsigned int n);

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

unsigned char get_key_pressed(unsigned char key1,unsigned char key2,unsigned char key3){
	unsigned char ch = ' ';
	if(column1==0){
		//print_string(&key1,1);
		input_delay();
		ch = key1;
	}
	if(column2==0){
		//print_string(&key2,1);
		input_delay();
		ch = key2;
	}
	if(column3==0){
		//print_string(&key3,1);
		input_delay();
		ch =  key3;
	}
	return ch;
}

unsigned char get_char(){
	init_keyboard();
		// identifying the button
		// For Row A
		row_A = 0;
		if (row_A == 0){
			return get_key_pressed('1','2','3');
		}
		
		// For Row B
		row_A = 1;
		row_B = 0;
		if (row_B == 0){
			return get_key_pressed('4','5','6');
		}
		
		// For Row C
		row_B = 1;
		row_C = 0;
		if (row_C == 0){
			return get_key_pressed('7','8','9');
		}

		// For Row D
		row_C = 1;
		row_D = 0;
		if (row_D == 0){
			return get_key_pressed('*','0','#');
		}
		
		return ' ';
	}

	void prompt_user(){
		init_lcd();
		print_string("Enter password: ",1);
		input_delay();
		delay(1000);
	}
// Functions for Strings
unsigned int str_len(unsigned char *string){
	unsigned int length = 0;
	while(string[length]!='\0'){
		length++;
	}
	return length;
}

void print_string(unsigned char *string, unsigned int n){
	unsigned int i;
	// init_lcd();
	if (n==2)
		lcd_second_line();
	for(i=0;i<str_len(string);i++){
			lcd_data(string[i]);
		delay(1200);
	}
}

unsigned char* str_join(unsigned char *str1, unsigned char *str2){
	unsigned int i = 0;
	unsigned char new_str[17];
	unsigned int len = str_len(str1) + str_len(str1);
	
	for(i = 0; i<str_len(str1); i++){
		new_str[i] = str1[i];
	}
	
	for(i = str_len(str1) + 1; i<len; i++){
		new_str[i] = str2[i];
	}
	new_str[i] = '\0';
	
	return new_str;
}

int str_cmp( unsigned char *str1, unsigned char *str2){
	unsigned int len = str_len(str1);
	unsigned int i = 0;
	
	while(str1[i]==str2[i] && i<len){
		i++;
	}
	
	if (len==i)
		return 1;
	return 0;
}
	
void print_stars(int n){
	int i = 0;
	lcd_cmd(0x01);	//clear screen
	lcd_cmd(0x80);
	for (i=0;i<n;i++){
		lcd_data('*');
	}
}

// Main Function
void main(){
	// Declarations
	unsigned char code_by[] = "Code By";
	unsigned char credits[] = "Dhrumil Mistry";
	//char prompt[] = "Enter pin : ";
	unsigned char default_password[] = "123";
	unsigned char pass_entered[4];
	unsigned char pass;
	unsigned int pass_len = 1;
	unsigned int len;
	unsigned int n = len = str_len(default_password);
	unsigned int index = 0;
	P0= 0x00; // Output Declaration
	op = 0;
	
	init_lcd();
	print_string(code_by,1);
	input_delay();
	
	print_string(credits,2);
	input_delay();
	
	prompt_user();
	init_lcd();
	
	// Repeating Code
	do{
		//input_delay();
		pass = get_char();
	
		delay(12000);
		if(pass != ' '){
			n--;
			pass_entered[index] = pass;
			print_stars(len-n);
			index++;
		}
		else{
			print_string('*',1);
			delay(1000);
		}
	}while(n>0);
	
	init_lcd();
	
	if( str_cmp(pass_entered,default_password) == 1){
			op = 1;
			init_lcd();
			//print_string(str_join("Password : ",pass_entered), 1);
			print_string("USER",1);
			print_string("Authenticated",2);
		
			input_delay();
			delay(65535);
			delay(65535);
		}
		else{
			prompt_user();
		}
	
	delay(65535);
	delay(65535);
}