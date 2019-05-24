#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

#define CHAIRS 5
#define FALSE 0
#define TRUE 1

sem_t client;
sem_t barber;
sem_t mutex;
int waiting = 0;

void cut_hair(){
    cout << "The barber is cutting the client's hair" << endl;
    sleep(3);
}

void *barbers(void *arg) {
    
    while(TRUE){
        sem_wait(&client);      // Go to sleep if the number of clients is 0.
        sem_wait(&mutex);       // Gets access to 'waiting'.
        waiting = waiting - 1;  // Decreases from a waiting client count because it will be serviced.
        sem_post(&barber);      // A barber is now ready to cut hair.
        sem_post(&mutex);       // Free 'waiting'.
        cut_hair();             // Cuts hair.
    }
    
    pthread_exit(NULL);
}

void *clients(void *arg) {
    sem_wait(&mutex);
    /*If the amount of waiting customers is less than
    the amount of chairs means there is chairs to sit and wait.*/
    if(waiting < CHAIRS){
        cout << "Client arrived to cut hair" << endl;
        waiting = waiting + 1;
        sem_post(&client);
        sem_post(&mutex);
        sem_wait(&barber);
        cout << "The client is having his hair cut" << endl;
    }
    
    else{ // The barber is full and clients will not wait.
        sem_post(&mutex);
        cout << "The client gave up (the hall is full)" << endl;
    }
    
    pthread_exit(NULL);
}

int main(){
    sem_init(&client, TRUE, 0);
    sem_init(&barber, TRUE, 0);
    sem_init(&mutex, TRUE, 1);
    
    pthread_t b, c;
    
    pthread_create(&b, NULL, barbers, NULL); // Create the thread for barber
    
    while(TRUE){
        pthread_create(&c, NULL, clients, NULL);
        sleep(1);
        cout << "Clients waiting in the chairs: " << waiting << endl;
        sleep(1);
    }
    
    return 0;
}