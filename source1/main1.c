//
// Created by HADDAD on 02/02/2022.
//

#include "stdio.h"
#include "pthread.h"
#define NB_THREAD 5

void * maMethode(void * _arg){

    int * id = (int *) _arg;
    printf("Hello from : %d \n", *id);

    pthread_exit(NULL);

}

int main(int argc,char **argv)
{

    pthread_t thread[NB_THREAD];

    for(int i = 0; i<NB_THREAD; i++){
        pthread_create(&thread[i],NULL, maMethode, (void *) &thread[i]);
    }

    for(int i = 0; i<NB_THREAD; i++){
        pthread_join(thread[i],NULL);
    }

    return 0;
}
