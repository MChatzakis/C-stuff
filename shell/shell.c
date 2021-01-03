/*
    @author: Manos Chatzakis || chatzakis@ics.forth.gr
    This shell supports pipeline command execution and redirection.
*/
#define _GNU_SOURCE
#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <signal.h>
#include <fcntl.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SHORTCUTS 1 /*Enable this to use shortcuts*/
#define DEBUG 0 /*Enable this for debugging*/

#define TRUE 1

#define MAX_INPUT 1024
#define MAX_TOKENS 512

#define MAX_COMMANDS 100
#define MAX_ARGS 100

#define ENABLE_D_PATH 1
#define D_PATH "/bin/"
#define D_PATH_2 "/usr/bin/"

#define PIPE  ">"
#define RD_FL "|"
#define WR_FL "||"
#define AP_FL "|||"

/*Abstract structure for a linux command*/
typedef struct command{
    char *args[MAX_ARGS];
    int args_size;
    int file_input;
    int file_output;
    int append; 
}command;

/*This structs hold default terminal settings*/
struct termios default_atr;

/*When program starts, only parent is running*/
int child_running = 0;

/*Parse the input using " "*/
int tokenize(char *input,char **tokens);

/*Prints the prompt to get new command*/
void type_prompt();

/*Initializes the structures with null values*/
void clear_containers(char *input,char **tokens,command *commands);

/*Saves the input*/
void read_input(char *input);

/*Saves input using getchar*/
int read_chars(char *input);

/*Initializes the command array*/
void initialize_commands(char **tokens,command *commands);

/*Prints the commands*/
void print_commands_debug(command *commands,int commands_num);

/*Prints the tokens*/
void print_tokens_debug(char **tokens);

/*Executes the commands*/
void execute(command *commands,int pipes);

/*Creates the CTRL H and CTRL S, Q shortcuts*/
void create_shortcuts();

/*Erases the shortcut settings from terminal*/
void reset_terminal();

/*Prints shell attributes*/
void print_info();

/*Suspends execution only for child process upon interruption*/
void signal_han(int sig);

/*Run the shell*/
int main(void){

    char input[MAX_INPUT];
    char* tokens[MAX_TOKENS];
    
    command commands[MAX_COMMANDS];

    int pipes = 0;

    if(SHORTCUTS){
    	tcgetattr(STDIN_FILENO, &default_atr);
		create_shortcuts();
		signal(SIGINT, signal_han);
		/*Reset terminal settings upon exiting*/
		atexit(reset_terminal); 
    }

    //print_info();

    while(TRUE){
        
        type_prompt();

        /*Initialize structures with NULL*/
        clear_containers(input,tokens,commands);
        
        /*On error, 0 is returned*/
        if(!read_chars(input)){
        	continue;
        }

        pipes = tokenize(input,tokens);
        
        /*Run exit,info or cd or commands included in command PATH*/
        if(pipes == 0 && strcmp(tokens[0],"exit") == 0){
            exit(0);
        }else if(pipes == 0 && strcmp(tokens[0],"cd") == 0){
            chdir(tokens[1]);
        }else if(pipes == 0 && strcmp(tokens[0],"info") == 0){
        	print_info();
        }
        else{
            initialize_commands(tokens,commands);
            if(DEBUG){
                print_tokens_debug(tokens);
                print_commands_debug(commands,(pipes+1));
            }
            execute(commands,pipes);
        }
    }
    return 0;    
}

/*Executes the commands*/
void execute(command *commands,int pipes){
	int pipeline[pipes][2];
	int i,k,status,fd,commands_number = pipes + 1;
	pid_t pid;
	char cmd[100]; 
    FILE *fp;
    
    for(i=0; i<pipes; i++){
		pipe(pipeline[i]);
	}

	for(i=0; i<commands_number; i++){

		pid = fork();

		if(pid < 0){
			perror("Error forking\n");
			exit(EXIT_FAILURE);
		}
        
		if(pid == 0){

			//child_running = 0;
			if(SHORTCUTS){
				signal(SIGINT,signal_han);
			}

			/*Write output on pipe or file*/
			if(commands[i].file_output < 0 && i != commands_number - 1){ 
                if(dup2(pipeline[i][1],1)<0){
					perror("Could not redirect output");
					exit(EXIT_FAILURE);
				} 
			}else if(commands[i].file_output >= 0){
                if(commands[i].append){
                	//fd = open(commands[i].args[commands[i].file_output],O_APPEND);
                    fp = fopen(commands[i].args[commands[i].file_output],"a+");
                }else{
                	//fd = open(commands[i].args[commands[i].file_output],O_WRONLY);
                    fp = fopen(commands[i].args[commands[i].file_output],"w+"); /*May change to w+?*/
                }

                /*Convert file pointer to file descriptor*/
                fd = fileno(fp);

                if(fd < 0){
                    perror("Could not open file");
                    exit(EXIT_FAILURE);
                }

                commands[i].args[commands[i].file_output] = NULL;

                if(dup2(fd,1)<1){
                    perror("Could not redirect output");
                    exit(EXIT_FAILURE);
                }

                fclose(fp);
            }

			if(commands[i].file_input < 0 && i != 0){
                if(dup2(pipeline[i-1][0],0)<0){
					perror("Error taking input");
					exit(EXIT_FAILURE);
				}
			}else if(commands[i].file_input >= 0){
                fd = open(commands[i].args[commands[i].file_input],O_RDONLY);
                if(fd < 0){
                    perror("Error taking input");
					exit(EXIT_FAILURE);
                }

                commands[i].args[commands[i].file_input] = NULL;

                if(dup2(fd,0)<0){
                    perror("Could not take input for command");
					exit(EXIT_FAILURE);
                }
            }

			for(k = 0; k<pipes; k++){
				close(pipeline[k][0]);
				close(pipeline[k][1]);
			}

			/*You may need to disable this part: Compatibility tested on UBUNTU 20.04 LTS and CSD Debian*/
			if(ENABLE_D_PATH){
            	strcpy(cmd,D_PATH);
            	if(strstr(commands[i].args[0],D_PATH) != NULL){
                	strcpy(cmd,commands[i].args[0]);
            	}else{
                	strcat(cmd,commands[i].args[0]);
                	/*check if the path is ok*/
                	if(access(cmd, F_OK) == -1){ /* file does not exist */
                		strcpy(cmd,D_PATH_2);
                		strcat(cmd,commands[i].args[0]);	
                	}
            	}
            }else{
           		strcpy(cmd,commands[i].args[0]);
            }

			if(execve(cmd, commands[i].args,0) < 0){
                perror("Error executing command");
				exit(EXIT_FAILURE);
            }
		}
	}

	//child_running = 0;

	for(i = 0; i < pipes; i++){
        close(pipeline[i][0]);
        close(pipeline[i][1]);
    }

    for(i = 0; i < commands_number; i++){
    	wait(&status);
    }

    /*
		The rest of the code is the ctrl S and Q shortcuts.
		The code was buggy, it did it's job (stty -ixon was used)
		Uncomment to try this (dont forget to comment the above for loop)
    */
    /*struct termios edited_atr;
	tcgetattr(STDIN_FILENO, &edited_atr);
	char c;
	edited_atr.c_lflag &= ~(ICANON | ISIG);
    
    for(i = 0; i < commands_number; i++){
        while(waitpid(-1,&status,WNOHANG) == 0){
        
        	//Use SIGCHLD to return EOF to father
        	if((c = getchar()) == (('s') & 0x1f)){
        		//send sigstop
        		kill(-1,SIGSTOP);
        	}
        	else if(c == (('q') & 0x1f)){
        		//send sigcont
        		kill(-1,SIGCONT);
        	}
        }
    }

    edited_atr.c_lflag &= (ICANON);*/
}

/*Parse the input using " "*/
int tokenize(char *input,char **tokenized){
    char * curr_token = strtok(input," ");
    int i = 0,pipes = 0;
    while(curr_token){
        tokenized[i++] = curr_token;
        if(strcmp(curr_token,PIPE) == 0){
            pipes++;
        }
        curr_token = strtok(NULL," ");
    }
    return pipes;
}

/*Initializes the command array*/
void initialize_commands(char ** tokens,command *commands){    
    int i=0; //current token
    int j=0; //current command
    int k=0; //current command arg

    /*By default, the command echo hello > 1.txt > 2.txt
    will create the files 1.txt and 2.txt, but hello will be written
    only in 2.txt. Here we declare the following pointer to create
    those files upon command initilization to usu them later.*/
    FILE* fp;

    while(tokens[i]!=NULL && i<MAX_TOKENS && j<MAX_COMMANDS){
        
        if(strcmp(PIPE,tokens[i]) == 0){
            /*When a pipe occurs, a new command should start.*/
            commands[j].args_size = k;
            /*Start new command and reinit arg counter*/
            j++; 
            k=0; 
        }else if(strcmp(RD_FL,tokens[i]) == 0){
            if(!(tokens[i+1]!=NULL && i+1<MAX_TOKENS)){
                printf("Error on redirection.\n");
                return;
            } 
            if(commands[j].file_input > 0){
                commands[j].args[commands[j].file_input] = tokens[++i];
            }
            else{
                commands[j].file_input = k;
                commands[j].args[k] = tokens[++i];
                k++;
            }
        }else if(strcmp(WR_FL,tokens[i]) == 0){
            if(!(tokens[i+1]!=NULL && i+1<MAX_TOKENS)){
                printf("Error on redirection.\n");
                return;
            }
            if(commands[j].file_output >= 0){
                commands[j].args[commands[j].file_output] = tokens[++i];
                commands[j].append = 0; //check again

            }else{
                commands[j].file_output = k;
                commands[j].append = 0;
                commands[j].args[k] = tokens[++i];
                k++;
            }

            fp = fopen(commands[j].args[commands[j].file_output],"w+");
            fclose(fp);

        }else if(strcmp(AP_FL,tokens[i]) == 0){
            if(!(tokens[i+1]!=NULL && i+1<MAX_TOKENS)){
                printf("Error on redirection.\n");
                return;
            }
            if(commands[j].file_output >= 0){
                commands[j].args[commands[j].file_output] = tokens[++i];
            }else{
                commands[j].file_output = k;
                commands[j].args[k] = tokens[++i];
                k++;
            }
            
            commands[j].append = 1;
            fp = fopen(commands[j].args[commands[j].file_output],"a");
            fclose(fp);
        }else{
            // printf("Adding token[%d]: %s to command[%d] to pos[%d]\n",i,tokens[i],j,k);
            commands[j].args[k] = tokens[i];
            k++;   
        }

        i++;
    }
    commands[j].args_size = k; // Last command.
}

/*Prints the commands*/
void print_commands_debug(command *commands,int commands_num){
    int i=0;
    printf("Total number of commands is : %d\n",commands_num);
    for(i=0; i<commands_num; i++){
        printf("Command[%d] with total arguments %d, file_input: %d, file_output: %d and append: %d\n",i,commands[i].args_size,commands[i].file_input,commands[i].file_output,commands[i].append);
        int j=0;
        /*This is not so beautiful, but cool for debug*/
        while(commands[i].args[j] != NULL){
            printf("    arg[%d]:%s \n",j,commands[i].args[j]);
            j++;
        }
        /*This one is better, but for know its dangerous to lose bugs*/ /*
        for(j=0; j<commands[i].args_size; j++){
            printf("    arg[%d]:%s \n",j,commands[i].args[j]);
        }*/
        //printf("Commant with mode %d\n",commands[i].mode);
    }
}

/*Prints the prompt to get new command*/
void type_prompt(){
    char dir[500] ;
    getcwd(dir, sizeof(dir));  
    printf("\033[1;35m"); //[1;36m //[0;35m
    printf("[shMC][%s][%s]~$",getenv("USER"),dir);
    printf("\033[0m"); 
}

/*Saves the input*/
void read_input(char *input){
    fgets(input,MAX_INPUT,stdin);
    input[strlen(input)-1] = '\0';
}

/*Prints the tokens*/
void print_tokens_debug(char **tokens){
    int i = 0;
    while(tokens[i]!=NULL && i<MAX_TOKENS) {
        printf("Token[%d] = %s\n",i,tokens[i]);
        i++;
    }
}

/*Initializes the structures with null values*/
void clear_containers(char *input,char **tokens,command *commands){
    int i = 0;
    int j = 0;
    for(i=0; i<MAX_INPUT; i++){
        input[i] = '\0';
    }

    for(i=0; i<MAX_COMMANDS; i++){
        commands[i].args_size = -1;
        commands[i].file_input = -1;
        commands[i].file_output = -1;
        commands[i].append = -1;
        for(j=0; j<MAX_ARGS; j++){
            commands[i].args[j] = NULL;
        }
    }

    for(i=0; i<MAX_TOKENS; i++){
        tokens[i] = NULL;
    }
}

/*Saves input using getchar*/
int read_chars(char *input){
	int c,counter = 0;
	while((c = getchar()) != '\n'){
		if(counter == MAX_INPUT) break;
		input[counter] = c;
		counter++;
	}
	if(counter == 0) return 0;
	return 1;
}

/*Prints shell attributes*/
void print_info(){
	printf("******************************************************************************\n");
	printf("* CS345 - Assignment 1: A simple linux shell.                                *\n");
	printf("* Creator: Manos Chatzakis, chatzakis@ics.forth.gr                           *\n");
	printf("* Using shortcuts: %d.                                                        *\n",SHORTCUTS);
	printf("* Using default PATH(%s): %d.                                              *\n",D_PATH,ENABLE_D_PATH);
	printf("* Default path is tested on UBUNTU 20.04 LTS.                                *\n");
	printf("* Disable or reset default PATH for other distros.                           *\n");	
	printf("* This shell supports simple command execution, pipes and redirection.       *\n");
	printf("* It also supports CTRL H, CTRL C, CTRL S and CTRL Q shortcuts.              *\n");
	printf("******************************************************************************\n");
}

/*Erases the shortcut settings from terminal*/
void reset_terminal(){
	//Set default attributes
 	tcsetattr(STDIN_FILENO, TCSAFLUSH, &default_atr);
}

/*Creates the CTRL H and CTRL S, Q shortcuts*/
void create_shortcuts(){

	struct termios edited_atr;
	
	tcgetattr(STDIN_FILENO, &edited_atr);
  	
  	/*CTRL H has ascii code 8*/
  	edited_atr.c_cc[VERASE] = 8; 
  	
  	/*Disable CTRL C*/
  	//edited_atr.c_lflag &= ~(ICANON | ISIG);

  	/*Enable CTRL S and CTRL Q*/
  	edited_atr.c_iflag &= ~(IXON);
  	tcsetattr(STDIN_FILENO, TCSAFLUSH, &edited_atr);
}

/*Suspends execution only for child process upon interruption*/
void signal_han(int sig){
	/*pid_t pid;
	if(child_running){
		pid = getpid();
		kill(pid,sig);
	}*/
	return;
}
