#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file

int32_t* reg; // Array of 32 32-bit registers

void init_regs();
bool interpret(char* instr);
void write_read_demo();
void print_tokens(char* instr, char** theword);
int get_instr_length(char*, char);
bool equals(char*, char*);
int get_instr_name(char*);
void add_instr(char*, char*, char*);
void addi_instr(char*, char*, char*);
void and_instr(char*, char*, char*);
void or_instr(char*, char*, char*);
void xor_instr(char*, char*, char*);
/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void and_instr(char* rd, char* r1, char* r2){
	rd++;
	r1++;
	r2++;
	reg[atoi(rd)] = (atoi(r1) && atoi(r2));

}//end and

void or_instr(char* rd, char* r1, char* r2){
	rd++;
	r1++;
	r2++;
	reg[atoi(rd)] = (atoi(r1) || atoi(r2));
}//end or

void xor_instr(char* rd, char* r1, char* r2){
	rd++;
	r1++;
	r2++;

	reg[atoi(rd)] = (atoi(r1) ^ atoi(r2));


}//end xor

void addi_instr(char* rd, char* r1, char* im){
	rd++;
	r1++;
	
	reg[atoi(rd)] = reg[atoi(r1)] + atoi(im);

}//end adii


void add_instr(char* rd, char* r1, char* r2){
	rd++;
	r1++;
	r2++;
	
	//printf("rd: %c\nr1: %c\nr2: %c\n", *rd, *r1, *r2);
	
	reg[atoi(rd)] = reg[atoi(r1)] + reg[atoi(r2)];
	//reg[rd] = reg[r1] + reg[r2];

}//end add



int get_instr_name(char* instr){
	//If all comparisons fail then return 0
 	char sw[3] = "SW";
        char* swp = sw;

        char lw[3] = "LW";
        char* lwp = lw;

        char add[4] = "ADD";
        char* addp = add;

        char addi[5] = "ADDI";
        char* addip = addi;

	char and[4] = "AND";
	char* andp = and;

	char or[3] = "OR";
	char* orp = or;

	char xor[4] = "XOR";
	char* xorp = xor;

	//1:sw, 2:lw, 3:add, 4:addi, 5:and, 6:or, 7:xor, 0:DNE
	int store = equals(instr, swp);
	if(store){
		return 1;
	}

	int load = equals(instr, lwp);
	if(load){
		return 2;
	}

	int addition = equals(instr, addp);
	if(addition){
		return 3;
	}

	int immediate = equals(instr, addip);
	if(immediate){
		return 4;
	}
	int anded = equals(instr, andp);
	if(anded){
		return 5;
	}

	int ord = equals(instr, orp);
	if(ord){
		return 6;
	}
	
	int xord = equals(instr, xorp);
	if(xord){
		return 7;
	}

	return 0;
	//printf("Determine if equal: %d\n", store);
	

}//end get_instr_name


bool equals(char* a, char* b){
	int alength = get_instr_length(a, '\0');
	int blength = get_instr_length(b, '\0');

	//printf("alength: %d\n", alength);
	//printf("blength: %d\n", blength);

	if(!(alength == blength)){
		//printf("Incorrect\n");
		return false;
	}//end if

	while(!(*a == '\0')){
		//printf("In equals function comparing %c to %c\n", *a, *b);
		if(!(*a == *b)){
			return false;
		}
		a++;
		b++;
	}//end while

	return true;
}//end function



int get_instr_length(char* instr, char terminator){
	//printf("We are in the function\n");
	int thelength = 0;
	while(!(*instr == terminator)){
		//printf("%c\n", *instr);
		thelength++;
		instr++;
	}//end while
	return thelength;

}// length


void print_tokens(char* instr, char** theword){

	int totaldelim = 0;
        while(!(*instr == '\0')){
		//printf("In the while\n");
		if(*instr == ','){
			totaldelim++;
		}
		instr++;

        }//end while
	//printf("Reached the end of the while in print tokens\n");

    for(int j = 0; j < totaldelim+1; j++){
        printf("Tokens[%d] = %s\n", j, theword[j]);
    }//end for

}//end print tokens


void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}



/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */

bool interpret(char* instr){
	
	//int newlength = get_instr_length(*instr);
	

	char** tokeninstr = tokenize(instr, ',');

	print_tokens(instr, tokeninstr);

	
	int the_name = get_instr_name(tokeninstr[0]);

	//printf("%d\n", the_name);
	switch(the_name){
		case 1:
			printf("SW\n");
			break;
		case 2:
			printf("LW\n");
			break;
		case 3:
			printf("ADD\n");
			add_instr(tokeninstr[1], tokeninstr[2], tokeninstr[3]);
			break;
		case 4:
			printf("ADDI\n");
			addi_instr(tokeninstr[1], tokeninstr[2], tokeninstr[3]);
			break;
		case 5:
			printf("AND\n");
			and_instr(tokeninstr[1], tokeninstr[2], tokeninstr[3]);
			break;
		case 6:
			printf("OR\n");
			or_instr(tokeninstr[1], tokeninstr[2], tokeninstr[3]);
			break;
		case 7:
			printf("XOR\n");
			xor_instr(tokeninstr[1], tokeninstr[2], tokeninstr[3]);
			break;
		default:
			printf("Not Valid\n");


	}//end switch

	return true;
}


/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */

void write_read_demo(){
	int32_t data_to_write = 0xFFF; // equal to 4095
	int32_t address = 0x98; // equal to 152
	char* mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	if(write == (int32_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}

/**
 * Prints all 32 registers in column-format
 */
void print_regs(){
	int col_size = 10;
	for(int i = 0; i < 8; i++){
		printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);
		printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);
		printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);
		printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);
	}
}

/**
 * Your code goes in the main
 *
 */
int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

	print_regs();

	// Below is a sample program to a write-read. Overwrite this with your own code.
	//write_read_demo();

	printf(" RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\nEnter 'EOF' character to end program\n");

	printf("Delimiter: ,\n");
	char* instruction = malloc(1000 * sizeof(char));
	bool is_null = false;
	// fgets() returns null if EOF is reached.
	is_null = fgets(instruction, 1000, stdin) == NULL;
	while(!is_null){
		//This should replace the \n and fix the error
		//instruction[get_instr_length(instruction)] = '\0';
		//printf("Before interpret\n");
		if(*instruction == '\n'){
			printf("EMPTY\n");
			break;
		}




		//int lentester = get_instr_length(instruction);
		
		instruction[get_instr_length(instruction, '\n')] = '\0';
		//printf("Len tester: %d\n", lentester);
		//instruction[lentester] = '\0';
		interpret(instruction);
		printf("\n");
		print_regs();
		printf("\n");

		is_null = fgets(instruction, 1000, stdin) == NULL;
	}

	printf("Good bye!\n");

	return 0;
}
