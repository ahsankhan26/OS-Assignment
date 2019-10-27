#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

#define chairs 5

using namespace std;

//semaphores
sem_t count_mutex;
sem_t customerCount_mutex;
sem_t isAsleep_mutex;

//global variables
int count = 0;
int customerCount = 0;
int customerNumber = 0;
bool isAsleep = true;

//thread functions
void * barber ( void * arg );
void * newCustomer ( void * arg );
void * getHairCut ( void * arg );

//functions
void waitingRoom ();
void balk ();
void goToSleep ();
void cutHair ();

//main
int main() {
	
	srand( time(0) );
	
	sem_init ( &count_mutex, 0, 1 );
	sem_init ( &customerCount_mutex, 0, 1 );
	sem_init ( &isAsleep_mutex, 0, 1 );
	
	pthread_t barberThread;
	pthread_t customerCreator;
	pthread_t customer;
	
	pthread_create ( &barberThread, NULL, barber, NULL );
	pthread_create ( &customerCreator, NULL, newCustomer, NULL );
	pthread_create ( &customer, NULL, getHairCut, NULL );
	
	pthread_join ( barberThread, NULL );
	pthread_join ( customerCreator, NULL );
	pthread_join ( customer, NULL );
	
	sem_destroy ( &count_mutex );
	sem_destroy ( &customerCount_mutex );
	sem_destroy ( &isAsleep_mutex );
	
	return 0;
}

void * barber (void * arg) {
	
	while(1){

		if(customerCount == 0) {
			goToSleep();
		}
		cutHair();
	}
	return NULL;
}

void * newCustomer(void * arg) {
	
	cout <<"\n\n";
	
	for( int i = 0; i < 10; i++ ) {
		sleep(1);
	
		sem_wait ( &count_mutex );
			count++;
			cout << "count : " << count << "\n";
		sem_post ( &count_mutex );
		
		if ( count <= chairs ) {

			if ( customerCount == 1 ) {
				sem_wait ( &customerCount_mutex );
					cout << "Customer Count : " << customerCount << "\n";
				sem_post ( &customerCount_mutex );
			}
			
			else if ( customerCount > 1 ) {
				sem_wait ( &customerCount_mutex );
					cout << "Customer Count : " << customerCount << "\n";				
					cout << "Customer " << customerCount << " is waiting \n";
				sem_post ( &customerCount_mutex );
			}

			waitingRoom();
		}
		
		else{
			balk();
		}			
	}	
	return NULL;
}

void * getHairCut ( void * arg ) {
		
	while(1) {
		
		if ( isAsleep && customerCount != 0 ) {
					
			sem_wait(&isAsleep_mutex);
				isAsleep = false;
			
				sem_wait(&customerCount_mutex);
					cout << "Customer " << customerCount << " is waking the barber \n\n";
				sem_post(&customerCount_mutex);
			
			sem_post(&isAsleep_mutex);
		}
	}
	return NULL;
}

void waitingRoom () {
	
		sem_wait(&customerCount_mutex);
			customerCount++;	
		sem_post(&customerCount_mutex);
}

void balk () {
	
	cout << "Shop is Full" << endl;
	sem_wait ( &count_mutex );
		count--;
		cout << "after balk count = " << count << endl;
	sem_post ( &count_mutex );
}

void goToSleep () {
	
	sem_wait( &isAsleep_mutex );
		isAsleep = true;
		cout << "barber is going to sleep \n\n";
	sem_post( &isAsleep_mutex );
	
	while(isAsleep == true){
		//sleep	
	}
}

void cutHair () {
	
	customerNumber++;
	
	cout << "Customer Number " << customerNumber << " is Getting a Haircut \n";
	sleep( (rand() % 10) + 1 );
	
	sem_wait ( &customerCount_mutex );
		customerCount--;
		cout << "Customer Number " << customerNumber << " is Done \n";
	sem_post ( &customerCount_mutex );
}
