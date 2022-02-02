//
// Created by HADDAD on 02/02/2022.
//

#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#define NB_THREAD 10

struct Barriere{
    int compteur;
    int objectif;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};


void * barriere(void * _arg){

    struct Barriere * str = (struct Barriere *) _arg;

        int rc;
        rc = pthread_mutex_lock(&str->mutex);
        if(rc){printf("Probleme"); EXIT_FAILURE;}

        if ((*str).compteur == (*str).objectif - 1) {
            (*str).compteur++;
            printf("Nous sommes tous là, je notifie les premiers. \n");
            pthread_cond_broadcast(&str->cond);
            pthread_exit(NULL);
        }else if((*str).compteur < (*str).objectif){
            (*str).compteur++;
            printf("J'entre en attente et nous sommes %d à être arriver. \n",(*str).compteur);
            pthread_cond_wait(&str->cond,&str->mutex);
        }

        rc =  pthread_mutex_unlock(&str->mutex);
        if(rc){printf("Probleme"); EXIT_FAILURE;}

        pthread_exit(NULL);

}

int main(int argc,char **argv)
{
    struct Barriere bar;
    pthread_mutex_t temp = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t tmp = PTHREAD_COND_INITIALIZER;
    bar.mutex = temp;
    bar.objectif = NB_THREAD;
    bar.compteur = 0;
    bar.cond = tmp;

    pthread_t thread[NB_THREAD];

    for(int i = 0; i<NB_THREAD; i++){
        pthread_create(&thread[i],NULL, barriere, (void *) &bar);
    }

    for(int i = 0; i<NB_THREAD; i++){
        pthread_join(thread[i],NULL);

    }

    return 0;
}
