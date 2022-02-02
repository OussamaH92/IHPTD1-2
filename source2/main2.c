//
// Created by HADDAD on 02/02/2022.
//

#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "unistd.h"
#define NB_THREAD 10

struct Compte{
    int compteur;
    int objectif;
    pthread_mutex_t mutex;
};


void * compteur(void * _arg){

    struct Compte * str = (struct Compte *) _arg;
    sleep(rand()%5);

    while(1) {

        int rc;
        rc = pthread_mutex_lock(&str->mutex);
        if(rc){printf("Probleme"); EXIT_FAILURE;}

        if ((*str).compteur == (*str).objectif) {
            pthread_mutex_unlock(&str->mutex);
            pthread_exit(NULL);
        }else{
            (*str).compteur++;
            printf("Nouveau compte : %d \n",(*str).compteur);
        }

       rc =  pthread_mutex_unlock(&str->mutex);
       if(rc){printf("Probleme"); EXIT_FAILURE;}
    }

}

int main(int argc,char **argv)
{
    struct Compte cpt;
    pthread_mutex_t temp = PTHREAD_MUTEX_INITIALIZER;
    cpt.mutex = temp;
    cpt.objectif = 30;
    cpt.compteur = 0;

    pthread_t thread[NB_THREAD];

    for(int i = 0; i<NB_THREAD; i++){
        pthread_create(&thread[i],NULL, compteur, (void *) &cpt);
    }

    for(int i = 0; i<NB_THREAD; i++){
        pthread_join(thread[i],NULL);
    }

    return 0;
}
