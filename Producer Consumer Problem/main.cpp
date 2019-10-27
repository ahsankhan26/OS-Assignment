#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define bufferSize 5	// change this value only to change the buffer size

using namespace std;

sem_t buffer_mutex;		// semaphore for buffer

int count = 0;			// global variable
bool buffer[bufferSize] = {};	//boolean array to check the produced and consumed values

void * produce(void * arg);		//producer Thread function
void * consume(void * arg);		//consumer thread function

int main(){
	
	for(int i=0; i<bufferSize; i++){	
		buffer[i] = false;
	}
	
	sem_init(&buffer_mutex, 0, 1);
	
	pthread_t producerThread;
	pthread_t consumerThread;
	
	pthread_create(&producerThread, NULL, produce, NULL);
	pthread_create(&consumerThread, NULL, consume, NULL);
	
	pthread_join(producerThread, NULL);
	pthread_join(consumerThread, NULL);
	
	sem_destroy(&buffer_mutex);
	
	
	return 0;
}

void * produce(void * arg){
	
//	while(1){
		
	for(int j=0; j<3; j++){
		
		
		if(!buffer[count] && count != bufferSize){	//checks if buffer is empty
			//produce
			sem_wait(&buffer_mutex);
				buffer[count] = true;
				count++;
				cout << "Producing ..." << endl;
				sleep(2);
				cout << "Produced!" << endl;
				cout << "Buffer : ";
				for(int i=0;i<bufferSize;i++){
					 cout << buffer[i] <<"\t";
				}
				cout <<endl;
			sem_post(&buffer_mutex);
				
		}
	}
	//}
	return NULL;
}

void * consume(void * arg){		//checks if buffer is full
	
	int val;
	
	sleep(3);
	
	while(1){
		
		if(buffer[count]){
			//consume
			sem_wait(&buffer_mutex);
				buffer[count] = false;
				count--;
				cout << "Consuming ..." << endl;
				sleep(3);
				cout << "Consumed!" << endl;
				cout << "Buffer : ";
				for(int i=0;i<bufferSize;i++){
					 cout << buffer[i] <<"\t";
				}
				cout <<endl;
			sem_post(&buffer_mutex);
				
		}
	}
	return NULL;
}
