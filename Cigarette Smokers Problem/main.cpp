#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<string>
#include<time.h>
#include<stdlib.h>

using namespace std;

string items[3] = { "Tobacco", "Matches", "Paper" };
string ingredients[2];	//pick() randomly selects from items[] and stores here

bool ingredientTobacco = false;
bool ingredientMatch = false;
bool ingredientPaper = false;

string pick(string choice){
	
	string choose;
	
	choose = items[ rand() % 3 ];
	
	if(choose == choice){
		choose = pick(choice);
	}
	return choose;
}

void makeAvailable(){
	
	if( ingredients[0] == "Tobacco" || ingredients[1] == "Tobacco" ){
		ingredientTobacco = true;
	}
	if( ingredients[0] == "Matches" || ingredients[1] == "Matches" ){
		ingredientMatch = true;
	}
	if( ingredients[0] == "Paper" || ingredients[1] == "Paper" ){
		ingredientPaper = true;
	}
	
}

//thread functions need to be a "void *" with "void * arg" as its parameter and it returns a NULL
void * agent( void * arg ){
	
	while(1){
		sleep(3);
		ingredients[0] = pick("");
		ingredients[1] = pick( ingredients[0] );

		cout << "Agent Spawned " << ingredients[0] << " and " << ingredients[1] << endl;
		makeAvailable();		
	}
	return NULL;
}

void * smokerTobacco( void * arg ){
	
	while(1){
		if( ingredientMatch && ingredientPaper ){

			ingredientMatch = false;
			ingredientPaper = false;

			cout << "Smoker TOBACCO Picked Ingredients " << endl;
			cout << "Smoker TOBACCO is Smoking!" << endl;
			cout << "\nx---------------x\n\n";
		}
	}	
	return NULL;
}

void * smokerPaper ( void * arg ){
	
	while(1){
		if( ingredientMatch && ingredientTobacco ){

			ingredientMatch = false;
			ingredientTobacco = false;

			cout << "*Smoker PAPER Picked Ingredients " << endl;
			cout << "*Smoker PAPER is Smoking!" << endl;
			cout << "\nx---------------x\n\n";
		}
	}
	return NULL;
}

void * smokerMatch( void * arg ){
	
	while(1){
		if( ingredientPaper && ingredientTobacco ){

			ingredientPaper = false;
			ingredientTobacco = false;

			cout << "Smoker MATCH Picked Ingredients " << endl;
			cout << "Smoker MATCH is Smoking!" << endl;
			cout << "\nx---------------x\n\n";
		}
	}
	
	return NULL;
}

int main(){
	
	srand( time( NULL ) );	//for random time
	
	//spawning threads
	pthread_t agentThread;
	pthread_t smokerTobaccoThread;
	pthread_t smokerPaperThread;
	pthread_t smokerMatchThread;
	
	//creating threads. pthread_create takes the name of the thread and the function
	pthread_create(&agentThread, NULL, agent, NULL);
	pthread_create(&smokerTobaccoThread, NULL, smokerTobacco, NULL);
	pthread_create(&smokerPaperThread, NULL, smokerPaper, NULL);
	pthread_create(&smokerMatchThread, NULL, smokerMatch, NULL);
	
	//pthread_join makes thread wait till they all finish their task
	pthread_join(agentThread, NULL);
	pthread_join(smokerTobaccoThread, NULL);
	pthread_join(smokerPaperThread, NULL);
	pthread_join(smokerMatchThread, NULL);
	
	return 0;
}
