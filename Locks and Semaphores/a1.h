/* Michael Woo
 *masc0995
 *February 26, 2013
 *Professor Leonard
 *CS 570, Spring 2013
 *Assignment 1, Creating threads and using semaphores
 *a1.h
 */

#ifndef HEADER_FILE
#define HEADER_FILE


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 
#include <time.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

void *post(void *threadid);
void handleFork();
void prompt();
sem_t sem;

#endif
