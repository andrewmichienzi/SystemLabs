#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>

#define MAXLINE 80
#define MAXARG 20

void background(char * datain);

/*
 * Authors: Andrew Michienzi and Vignesh Suresh
 *
 * The purpose of this code is to learn the forking process and create a simple  * 	* Unix shell 
 */
int main()
{
	struct timeval total_time;
	struct timeval previous_time = {tv_sec:0, tv_usec:0};
	struct timeval time_diff;
	long previous_ics = 0;
  	//fgets adds a new line to the end of a string
  	char *quit;
	quit = "quit";
	printf("\nMax number of characters:\t%d\n", MAXLINE);
	printf("Max number of args:\t\t%d\n", MAXARG);
	printf("To Quit, simply type: quit\n");
 	while(1){
  		char *datain;
  		datain = malloc(MAXLINE);
		//Creating cursor
  		printf("\n");
  		printf(">>");
  		fgets(datain, MAXLINE, stdin);
		//if datain is empty
		if(!strcmp("\n", datain)){
			free(datain);
			continue;
		}

		//Remove new line at end from fgets
		datain = strtok(datain, "\n");
  		//Quit if correct input
 		if(!strcmp(quit, datain)){
    			free(datain);
    			exit(0);
  		}
  		pid_t pid;
  		int status;
		//Fork and Failure catch
  		if((pid=fork())<0){
    			perror("fork failure");
    			free(datain);
				free(quit);
    			exit(1);
  		}
    		//Child. Execute and catch failure
  		if(pid==0){
			background(datain);
  		}
    		//Parent
  		else{
    		wait(&status);
			
			//Find CPU usage time
			struct rusage usage;
			int sec, usec;
			long ics;
			getrusage(RUSAGE_CHILDREN, &usage);

			//Find time
			total_time = usage.ru_utime;
			timersub(&total_time, &previous_time, &time_diff);
			sec = time_diff.tv_sec;
			usec = time_diff.tv_usec;
			previous_time.tv_sec = total_time.tv_sec;
			previous_time.tv_usec = total_time.tv_usec;
			printf("\nUsage time:\t%ds, %dus", sec, usec);
 			
			//Find involuntary context switches
			ics = usage.ru_nivcsw - previous_ics;
			printf("\nICS:\t\t%ld\n", ics);
			previous_ics = usage.ru_nivcsw;
		}	
		free(datain);
	}
	free(quit);
  	return (0);
}

void background(char * datain)
{
	  	char* command[MAXARG];	
  		int i = 0;
  		command[i] = strtok(datain, " ");
		do{
			i++;
			command[i] = strtok(NULL, " ");
		}while(command[i]);
    		execvp(command[0], &command[0]);
      		perror("\nCommand not found");
      		free(datain);
      		exit(1);	
} 

