/*
Information:
	File: translate.c
	Name: Manos Chatzakis
	eMail: csd4238@csd.uoc.gr
	CS-255, Assignment 1: "A translate program"

Description:
	This program takes characters from standard output written in 
	ISO 8859-7 and translates the greek ones their equal 
	english characters, according to the standard ISO 8859-1.

Compile:
	Compile using standard gcc commands, etc: 

Run:
	There are multiple ways to run this program.
	The characters are taken by std input and are translated to the std output.
	(Also tests saved in ISO 8859-7 provided in the same folder).

Notes:
	The file README.txt provided in the same folder provides more information about this assignment, written in greek.
*/

#include <stdio.h> /*Only the standard input-output library is used*/

#define OUTPUT_SIZE 256 /*The size of the ISO character array*/ 
#define OUTPUT_WIDTH 3 /*The possible size of the output, after a character is translated. The "worst" case occurs when a letter's english equal is 3 characters.*/

#define APOSTROFE '\'' /*The apostrofe(tonos) definition*/
#define D_APOSTROFE '"' /*The double apostrofe(dialitika) definition*/

/*
This enum represents the states of an FSM, designed to detect combinations of characters.
IDLE: 
	Is the state that the machine remains when the input is normal character, or the state that machine returns after printing a combination.
SEEN_letter: (letter: M,m,N,n)
	These are the states that the machine gets when the input character can make combinations.
	Such letters are M,m and N,n.
	Compinations occur when the next character after the characters described above is p or P for M or M, (when, for example mp converts to b)
	and t or T (when nt converts to d).
The actions need to made in every state based on the input are described latter in this file.	
*/
typedef enum{
	IDLE,SEEN_N,SEEN_M,SEEN_n,SEEN_m 
}state;

/*
Function that creates/initializes an array with the null character '\0'.
arr: The array that contains the mappings from the ISO 8859-7 to ISO 8859-1.
*/
void create_empty_array(char arr[OUTPUT_SIZE][OUTPUT_WIDTH]){
	int i,j;
	for(i=0; i<OUTPUT_SIZE; i++){
		for(j=0; j<OUTPUT_WIDTH; j++){
			arr[i][j] = '\0'; /*null character*/
		}
	}
}

/* 
Function that matches the greek upper characters of ISO 8859-7 to their equals after translation(mapping).
arr: The array that contains the mappings from the ISO 8859-7 to ISO 8859-1.
*/
void initialize_kefalaia(char arr[OUTPUT_SIZE][OUTPUT_WIDTH]){
	arr[193][0] = 'A';
	arr[194][0] = 'V';
	arr[195][0] = 'G';
	arr[196][0] = 'D';
	arr[197][0] = 'E';
	arr[198][0] = 'Z';
	arr[199][0] = 'H';
	arr[200][0] = '8';
	arr[201][0] = 'I';
	arr[202][0] = 'K';
	arr[203][0] = 'L';
	arr[204][0] = 'M';
	arr[205][0] = 'N';

	/*Multi-character translation*/
	arr[206][0] = 'K';
	arr[206][1] = 'S';

	arr[207][0] = 'O';
	arr[208][0] = 'P';
	arr[209][0] = 'R';
	arr[211][0] = 'S';
	arr[212][0] = 'T';
	arr[213][0] = 'Y';
	arr[214][0] = 'F';
	arr[215][0] = 'X';
	
	/*Multi-character translation*/
	arr[216][0] = 'P';
	arr[216][1] = 'S';
	
	arr[217][0] = 'W';
}

/* 
Function that matches the greek upper characters with apostrofe of ISO 8859-7 to their equals after translation.
arr: The array that contains the mappings from the ISO 8859-7 to ISO 8859-1.
*/
void initialize_kefalaia_me_tonous(char arr[OUTPUT_SIZE][OUTPUT_WIDTH]){
	/*Multi-character translation*/
	arr[182][0] = APOSTROFE;
	arr[182][1] = 'A';
	
	/*Multi-character translation*/
	arr[184][0] = APOSTROFE;
	arr[184][1] = 'E';
	
	/*Multi-character translation*/
	arr[185][0] = APOSTROFE;
	arr[185][1] = 'H';
	
	/*Multi-character translation*/
	arr[186][0] = APOSTROFE;
	arr[186][1] = 'I';
	
	/*Multi-character translation*/
	arr[188][0] = APOSTROFE;
	arr[188][1] = 'O';
	
	/*Multi-character translation*/
	arr[190][0] = APOSTROFE;
	arr[190][1] = 'Y';
	
	/*Multi-character translation*/
	arr[191][0] = APOSTROFE;
	arr[191][1] = 'W';
}

/*
Function that matches the greek uper characters with double apostrofe of ISO 8859-7 to their equals after translation.
arr: The array that contains the mappings from the ISO 8859-7 to ISO 8859-1.
*/
void initialize_kefalaia_me_dialitika(char arr[OUTPUT_SIZE][OUTPUT_WIDTH]){
	/*Multi-character translation*/
	arr[218][0] = 'I';
	arr[218][1] = D_APOSTROFE;
	
	/*Multi-character translation*/
	arr[219][0] = 'Y';
	arr[219][1] = D_APOSTROFE;
}

/*
Function that matches the greek lower characters of ISO 8859-7 to their equals after translation.
arr: The array that contains the mappings from the ISO 8859-7 to ISO 8859-1.
*/
void initialize_mikra(char arr[OUTPUT_SIZE][OUTPUT_WIDTH]){
	arr[225][0] = 'a';
	arr[226][0] = 'v';
	arr[227][0] = 'g';
	arr[228][0] = 'd';
	arr[229][0] = 'e';
	arr[230][0] = 'z';
	arr[231][0] = 'h';
	arr[232][0] = '8';
	arr[233][0] = 'i';
	arr[234][0] = 'k';
	arr[235][0] = 'l';
	arr[236][0] = 'm';
	arr[237][0] = 'n';

	/*Multi-character translation*/
	arr[238][0] = 'k';
	arr[238][1] = 's';
	
	arr[239][0] = 'o';
	arr[240][0] = 'p';
	arr[241][0] = 'r';
	arr[242][0] = 's';
	arr[243][0] = 's';
	arr[244][0] = 't';
	arr[245][0] = 'y';
	arr[246][0] = 'f';
	arr[247][0] = 'x';
	
	/*Multi-character translation*/
	arr[248][0] = 'p';
	arr[248][1] = 's';
	
	arr[249][0] = 'w';
}

/* 
Function that matches the greek lower characters with apostrofe of ISO 8859-7 to their equals after translation.
arr: The array that contains the mappings from the ISO 8859-7 to ISO 8859-1.
*/
void initialize_mikra_me_tonous(char arr[OUTPUT_SIZE][OUTPUT_WIDTH]){
	/*Multi-character translation*/
	arr[220][0] = 'a';
	arr[220][1] = APOSTROFE;  
	
	/*Multi-character translation*/
	arr[221][0] = 'e';
	arr[221][1] = APOSTROFE; 
	
	/*Multi-character translation*/
	arr[222][0] = 'h';
	arr[222][1] = APOSTROFE; 
	
	/*Multi-character translation*/
	arr[223][0] = 'i';
	arr[223][1] = APOSTROFE; 
	
	/*Multi-character translation*/
	arr[252][0] = 'o';
	arr[252][1] = APOSTROFE; 

	/*Multi-character translation*/	
	arr[253][0] = 'y';
	arr[253][1] = APOSTROFE; 
	
	/*Multi-character translation*/
	arr[254][0] = 'w';
	arr[254][1] = APOSTROFE; 
}

/* 
Function that matches the greek lower characters with double apostrofe of ISO 8859-7 to their equals after translation.
arr: The array that contains the mappings from the ISO 8859-7 to ISO 8859-1.
*/
void initialize_mikra_me_dialitika(char arr[OUTPUT_SIZE][OUTPUT_WIDTH]){
	/*Multi-character translations*/
	arr[250][0] = 'i';
	arr[250][1] = D_APOSTROFE; 

	/*Multi-character translations*/
	arr[251][0] = 'y';
	arr[251][1] = D_APOSTROFE;
}

/* 
Function that matches the greek lower characters with triple apostrofe of ISO 8859-7 to their equals after translation.
arr: The array that contains the mappings from the ISO 8859-7 to ISO 8859-1.
*/
void initialize_mikra_me_dialitika_kai_tonous(char arr[OUTPUT_SIZE][OUTPUT_WIDTH]){
	/*Multi-character translation*/
	arr[192][0] = 'i';
	arr[192][1] = APOSTROFE;
	arr[192][2] = D_APOSTROFE;
	
	/*Multi-character translation*/
	arr[224][0] = 'y';
	arr[224][1] = APOSTROFE;
	arr[224][2] = D_APOSTROFE;
}

/*
Function that matches the greek symbol "aposiopitika" to its equal on ISO 8859-1.
arr: The array that contains the mappings from the ISO 8859-7 to ISO 8859-1.
*/
void initialize_simeia_stiksis(char arr[OUTPUT_SIZE][OUTPUT_WIDTH]){
	/*Multi-character translation*/
	arr[171][0] = '<';
	arr[171][1] = '<';

	/*Multi-character translation*/
	arr[187][0] = '>';
	arr[187][1] = '>';

}

/*
Function that compines all the function that match the greek characters(mappings) to their equals to create the whole output array.
arr: The array that contains the mappings from the ISO 8859-7 to ISO 8859-1.
*/
void initialize_output(char arr[OUTPUT_SIZE][OUTPUT_WIDTH]){
	
	create_empty_array(arr); /*Empty initialization*/

	initialize_kefalaia(arr); 
	
	initialize_mikra(arr);
	
	initialize_kefalaia_me_tonous(arr);
	
	initialize_mikra_me_tonous(arr);
	
	initialize_kefalaia_me_dialitika(arr);
	
	initialize_mikra_me_dialitika(arr);

	initialize_mikra_me_dialitika_kai_tonous(arr);

	initialize_simeia_stiksis(arr);

}

/* 
Function that prints a greek character translated.
arr: The array that contains the mappings from the ISO 8859-7 to ISO 8859-1.
index: The row of the array containing the characters equal to the greek one.
*/
void print_translated_word(char arr[OUTPUT_SIZE][OUTPUT_WIDTH],int index){
	int i;
	for(i = 0; i<OUTPUT_WIDTH; i++){
		if(arr[index][i] != '\0'){ /*If the rest cells of the array contain the null character means that the demanded translated output has been printed.*/
			char c = arr[index][i];
			putchar(c); 
		}
	}
}

/* 
IGNORE THIS FUNCTION
Function to print the whole output array.
It has no proper use for the programm, it's here just for deubbuging/checking reasons.
arr: The array that contains the mappings from the ISO 8859-7 to ISO 8859-1.
*/
void print_array(char arr[OUTPUT_SIZE][OUTPUT_WIDTH]){
	int i,j;
	for(i=0; i<OUTPUT_SIZE; i++){
		printf("%d: ",i);
		for(j=0; j<OUTPUT_WIDTH; j++){
			printf("%c",arr[i][j]);
		}
		printf("\n");
	}
}

/*
This function returns if a character is greek or not, based on ISO 8859-7 numeric values of characters.
letter: the letter's numeric value on ISO 8859-7.
returns: 1(true) if the character is greek, 0(false) otherwise.
*/
int is_greek_letter(int letter){
	return (letter>=182 || (letter == 171)); /*By default, greek letters begin from index 182 of the ISO. The character "<<" is an excpetion, as it has a numeric value of 171.*/
}

/*
Translates the input or just prints it, based on if the character is greek or not.
arr: The array that contains the mappings from the ISO 8859-7 to ISO 8859-1.
c: The character's numeric value on ISO 8859-7. 
*/
void print_char(char arr[OUTPUT_SIZE][OUTPUT_WIDTH],int c){
	if(is_greek_letter(c)){
		print_translated_word(arr,c); /*The character is printed translated*/
	}
	else{
		putchar(c); /*The character is printed the same, as its a symbol or a letter supported by the default ISO*/
	}
}

/*
Function that represent the actions need to made when the FSM is in IDLE state, based on the input character.
arr: The array that contains the mappings from the ISO 8859-7 to ISO 8859-1.
c: The character's numeric value on ISO 8859-7.
returns: The next state that the FSM will get, after the input character is read.
*/
state action_IDLE(char arr[OUTPUT_SIZE][OUTPUT_WIDTH],int c){
	/*The state-handling/changing is done as described in the lecture.*/
	switch(c){
		case 204: /*M*/
			return SEEN_M;
		case 236: /*m*/
			return SEEN_m;
		case 205: /*N*/
			return SEEN_N;
		case 237: /*n*/
			return SEEN_n;
		default: /*Normal character*/
			print_char(arr,c); /*When reading a normal character combinations will not occur*/
			return IDLE;			
	}
}

/*
Function that represents the actions need to made when the FSM is in SEEN_N state, based on the input character.
arr: The array that contains the mappings from the ISO 8859-7 to ISO 8859-1.
c: The character's numeric value on ISO 8859-7.
returns: The next state that the FSM will get, after the input character is read.
*/
state action_SEEN_N(char arr[OUTPUT_SIZE][OUTPUT_WIDTH],int c){
	if(c==205){
		putchar('N');
		return SEEN_N;
	}
	else if(c==237){
		putchar('N');
		return SEEN_n;		
	}
	else if(c==204){
		putchar('N');
		return SEEN_M;
	}
	else if(c==236){
		putchar('N');
		return SEEN_m;
	}
	else if(c==212||c==244){ /*Switch statement wasn't used here due to this case*/
		putchar('D');
		return IDLE;
	}
	else{
		putchar('N');
		print_char(arr,c);
		return IDLE;
	} 
}

/*
Function that represent the actions need to made when the FSM is in SEEN_M state, based on the input character.
arr: The array that contains the mappings from the ISO 8859-7 to ISO 8859-1.
c: The character's numeric value on ISO 8859-7.
returns: The next state that the FSM will get, after the input character is read.
*/
state action_SEEN_M(char arr[OUTPUT_SIZE][OUTPUT_WIDTH],int c){
	if(c==205){
		putchar('M');
		return SEEN_N;
	}
	else if(c==237){
		putchar('M');
		return SEEN_n;		
	}
	else if(c==204){
		putchar('M');
		return SEEN_M;
	}
	else if(c==236){
		putchar('M');
		return SEEN_m;
	}
	else if(c==208||c==240){ /*Switch wasn't used here due to this case*/
		putchar('B');
		return IDLE;
	}
	else{
		putchar('M');
		print_char(arr,c);
		return IDLE;
	}
}

/*
Τhe actions need to made when the FSM is in SEEN_m state, based on the input character.
arr: The array that contains the mappings from the ISO 8859-7 to ISO 8859-1.
c: The character's numeric value on ISO 8859-7.
returns: The next state that the FSM will get, after the input character is read.
*/
state action_SEEN_m(char arr[OUTPUT_SIZE][OUTPUT_WIDTH],int c){
	if(c==205){
		putchar('m');
		return SEEN_N;
	}
	else if(c==237){
		putchar('m');
		return SEEN_n;		
	}
	else if(c==204){
		putchar('m');
		return SEEN_M;
	}
	else if(c==236){
		putchar('m');
		return SEEN_m;
	}
	else if(c==208||c==240){ /*Switch wasn't used here due to this case*/
		putchar('b');
		return IDLE;
	}
	else{
		putchar('m');
		print_char(arr,c);
		return IDLE;
	}
}

/*
Τhe actions need to made when the FSM is in SEEN_n state, based on the input character.
arr: The array that contains the mappings from the ISO 8859-7 to ISO 8859-1.
c: The character's numeric value on ISO 8859-7.
returns: The next state that the FSM will get, after the input character is read.
*/
state action_SEEN_n(char arr[OUTPUT_SIZE][OUTPUT_WIDTH],int c){
	if(c==205){
		putchar('n');
		return SEEN_N;
	}
	else if(c==237){
		putchar('n');
		return SEEN_n;		
	}
	else if(c==204){
		putchar('n');
		return SEEN_M;
	}
	else if(c==236){
		putchar('n');
		return SEEN_m;
	}
	else if(c==212||c==244){ /*Switch wasn't used here due to this case*/
		putchar('d');
		return IDLE;
	}
	else{
		putchar('n');
		print_char(arr,c);
		return IDLE;
	}
}

/*
Checks if the FSM holds a character which is not printed yet, although the input is over.
cur_state: The machines current state
*/
void print_leftovers(state cur_state){
	switch(cur_state){
		case IDLE: /*If the machine is in the IDLE state, that means that all the characters have been printed/translated normally*/
			return;
		case SEEN_M: /*In every other case, the remaining character should be printed*/
			putchar('M');
			return;
		case SEEN_N:
			putchar('N');
			return;
		case SEEN_m:
			putchar('m');
			return;
		case SEEN_n:
			putchar('n');
			return;
		default:
			return;
	}
}

/*
Execution begins here.
*/
int main(void){

	char output[OUTPUT_SIZE][OUTPUT_WIDTH]; /*Holds the equal translations of greek characters(the mapping array that holds the output).*/
	
	int c; /*The input character(c stands for "c(haracter"). Its an int as char range of value cannot hold values in the range of 0-255, as wrap-around occurs. */

	state (*ActionMenu[5])(char arr[OUTPUT_SIZE][OUTPUT_WIDTH],int c) = {action_IDLE,action_SEEN_N,action_SEEN_M,action_SEEN_n,action_SEEN_m};/*Array of pointers to functions, indexed by the state values, so as to call specific function based on the current state and the input character.*/
	
	state current_state = IDLE; /*The machine's current state. IDLE is also the beggining state of the FSM.*/

	initialize_output(output); /*Initialize the output array with the translated equal words.*/

	while((c = getchar())!=EOF){ /*While there are characters left*/
		current_state = ActionMenu[current_state](output,c); /*Based on the current state, the proper state function is called, printing the characters and updating the current state.*/
	} 

	print_leftovers(current_state); /*In case the last character is M,m,N,n and remains unprinted when the while loop ends.*/

	return 0;
	
}
