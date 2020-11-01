/*
	Manos Chatzakis - chatzakis@ics.forth.gr
	Restaurant take away simulation using threads.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

/*The number of costumers*/
#define N 20

/*Create the threads periodically to test the facebook attribute*/
#define FB_TEST 1

/*Include stoppage time for the cook to get the meal ready*/
#define COOK_STOPPAGE 0

sem_t call_inside;
sem_t order;
sem_t order_ready;
sem_t cust_left;

int active_customers = 0;

/*Simulates the customer behavior*/
void *customer(void *arg);

/*Simulates the chef behavior*/
void *chef(void *arg); 

int main(){

	int i,t1,t2;

	pthread_t chef_thread;
	pthread_t customer_thread[N];
	
	sem_init(&order_ready,0,0);
	sem_init(&order,0,0);
	sem_init(&call_inside,0,0);
	sem_init(&cust_left,0,0);

	t1 = pthread_create(&chef_thread, NULL, chef, NULL);

	for(i=0; i<N; i++){
		t2 = pthread_create(&customer_thread[i], NULL, customer, NULL);
		active_customers++;
		if(FB_TEST && (i+1)%3 == 0) sleep(10);
	}

	for(i=0; i<N; i++){
		pthread_join(customer_thread[i],NULL);	
	}
	
	pthread_join(chef_thread,NULL);
	
	sem_destroy(&order_ready);
	sem_destroy(&order);
	sem_destroy(&call_inside);
	sem_destroy(&cust_left);

	return 0;
}

/*Simulates the customer behavior*/
void *customer(void *arg){
	
	/*Wait for the chef to call you inside*/
	sem_wait(&call_inside);

	/*Place your order*/
	printf("CUSTOMER: Ordered.\n");
	sem_post(&order);

	/*Wait for your order to be cooked*/
	sem_wait(&order_ready);

	/*Leave the restaurant when your order is ready*/
	printf("CUSTOMER: Left.\n");
	printf("----------\n");
	active_customers--;
	sem_post(&cust_left);

	pthread_exit(NULL);
}

/*Simulates the chef behavior*/
void *chef(void *arg){
	
	int counter = 0;
	
	printf("Procedure is ready to commence.\n");
	printf("----------\n");

	while(counter<N){

		/*If there are no active customers check your facebook*/
		if(active_customers == 0){
			printf("CHEF: On facebook.\n");
			printf("----------\n");
		}

		/*If customer is waiting, call him inside*/
		sem_post(&call_inside);

		/*Wait for the customer to give his order*/
		sem_wait(&order);

		/*Cook the order*/
		if(COOK_STOPPAGE) sleep(2);
		printf("CHEF: Order is ready.\n");
		
		/*When the order is ready call the corresponding customer to recieve*/
		sem_post(&order_ready);

		/*Wait for the customer to exit the place to call the next one*/
		sem_wait(&cust_left);

		counter++;	
	}
	
	printf("Procedure ended.\n");

	pthread_exit(NULL);
}
