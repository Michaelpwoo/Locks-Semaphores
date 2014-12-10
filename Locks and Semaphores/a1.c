/* Michael Woo
 *masc0995
 *February 26, 2013
 *Professor Leonard
 *CS 570, Spring 2013
 *Assignment 1, Creating threads and using semaphores
 *a1.c
 */
#include "a1.h"

#define NUMBER_THREADS 4

pthread_t threads[NUMBER_THREADS];


void *post(void *threadid) {

	for (int j = 0; j < 10; j++) {

		int tid = (int) threadid;
		sem_wait(&sem); //entering critical area
		FILE *fp = fopen("PTAB.txt","a+");
		fprintf(fp, "%d\n", tid);
		printf("Thread: %d\n", tid);
		fclose(fp);
		sem_post(&sem); //leaving critical area
		sleep(1);
	}
	pthread_exit((void*)threadid);

}

void prompt(){
	int run = 0;
	// Prompt for user to run program
	while (run == 0) {
		char buffer[2];
		int ch;

		printf("Do you wish to run the program thread? y/n.\n");
		fgets(buffer, sizeof(buffer), stdin);

			//prevent from buffer overflow and flush stdout if invalid input
			while (((ch = getchar()) != '\n') && (ch != EOF)){
				fflush(stdout); 
			}

		if (buffer[0]!= 'n' && buffer[0] != 'y')
			printf("Incorrect input.\nPress 'y' for yes and 'n' for no.\n");
		
		//user does not want to run program exit
		else if (buffer[0] == 'n') {
			printf("Exiting program.\n");
			exit(EXIT_SUCCESS);

		}
		else if (buffer[0] == 'y')
			run++;
	}

	printf("Program is running\n");
}


void handleFork(){
	pid_t process;

	process = fork();

	//fork failed
	if (process == -1){
		exit(EXIT_FAILURE);
	}
	//success in child process 
	if (process == 0) {
		//print id
		FILE *fp = fopen ("PTAB.txt", "w+");
		//check for error
		if(fp == NULL){
			printf("Cannot open file.\n");
			exit(EXIT_FAILURE);
		}
		fprintf(fp,"%d\n", getpid());
		fclose(fp);

		//initialize semephore
		sem_init(&sem, 0, 1);
		//creates threads
  		for (long i = 0; i < NUMBER_THREADS; i++) {
  			int creation_failed;
  			creation_failed = pthread_create(&threads[i], NULL, post, (void*) i);
  			if(creation_failed != 0) {
  				exit(EXIT_FAILURE);
  			}
  		
  		}
  		pthread_exit(NULL);
  		sem_destroy(&sem);
  
	}
	//in parent process (process > 0)
	else {
		//wait for the child process to be done
		wait(NULL);
	
	}
}

int main (){

	prompt();
	handleFork();
}

