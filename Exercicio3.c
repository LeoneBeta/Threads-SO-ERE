/*Programa Multithread para calcular as potências de 2 elevado a n, onde n varia de 0 a 10, uma thread
calcula a potencia, enqanto a outra soma os resultados das potencias.*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

typedef struct{
    int n;
    long int sum;
    int result;
    int control;
}StructCalc;

void* calcPower(void *ptrStruct){
    StructCalc *ptr;
    ptr = (StructCalc*) ptrStruct;

    while(ptr->n <= 10){
        if(ptr->control == 0){
            ptr->result = pow(2,ptr->n);
            ptr->control = 1;
            printf("\nCALC - Valor de N : %d",ptr->n);
            printf("\nCALC - Resultado da potencia de 2 a %d: %d",ptr->n,ptr->result);
            printf("\nCALC - Valor do controle: %d",ptr->control);
            ptr->n++;
            sched_yield();
        }else
            sched_yield();
    }
    pthread_exit(NULL);
}

void* sumPower(void *ptrStruct){
    StructCalc *ptr;
    ptr = (StructCalc*) ptrStruct;
    while(ptr->n <= 10){
        if(ptr->control == 1){
            ptr->sum += ptr->result;
            ptr->control = 0;
            printf("\nSUM - Valor de N: %d",ptr->n);
            printf("\nSUM - Valor da Soma: %ld", ptr->sum);
            printf("\nSUM - Valor do controle: %d", ptr->control);
            sched_yield();
        }else
            sched_yield();
    }
    pthread_exit(NULL);
}

int start(){
    pthread_t threadCalc_id, threadSum_id;
    void *thread_return;
    int threadCalc, threadSum, arg;
    StructCalc str, *ptrStr;
    ptrStr = &str;

    str.n = 0;
    str.sum = 0;
    str.result = 0;
    str.control = 0;

    threadCalc = pthread_create(&threadCalc_id, NULL, calcPower,(void *)(ptrStr));
    if(threadCalc != 0){
        printf("\nErro ao iniciar a Thread Calc");
        exit(EXIT_FAILURE);
    }
    threadSum = pthread_create(&threadSum_id, NULL, sumPower,(void *)(ptrStr));
    if(threadSum != 0){
        printf("Erro ao iniciar a Thread Sum");
        exit(EXIT_FAILURE);
    }

    pthread_join(threadCalc_id,thread_return);
    pthread_join(threadSum_id,thread_return);

    printf("Resultado: %ld\n",str.sum);
}

int main(){
    return start();
}