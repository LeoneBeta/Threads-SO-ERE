/*Programa Multithread para calcular as potências de 2 elevado a n, onde n varia de 0 a 10, uma thread
calcula a potência, enquanto a outra soma os resultados das potencias.*/

/*O programa consta com um erro, após efetur as tarefas necessárias, a thread Calc finaliza sua execução,
assim passando a vez para a Thread Sum, e a finalizando. O erro constando no programa, é que em algumas
execuções ele não passa a ultima vez pela Thread Sum, assim não somando o último resultado, ficando com o 
resultado de 1023, ao invés de 2047*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

typedef struct{
    int n;
    long int sum;
    int result;
    int control;
    pthread_t threadSum_id, threadCalc_id;
}StructCalc;

void* calcPower(void *ptrStruct){
    StructCalc *ptr;
    ptr = (StructCalc*) ptrStruct;

    while(ptr->n <= 10){
        if(ptr->control == 0){
            ptr->result = pow(2,ptr->n);
            ptr->control = 1;
            sched_yield();
            ptr->n++;
        }else
            sched_yield();
    }
    printf("\nFinaliza a Thread Calc\n");
    pthread_exit(NULL);
}

void* sumPower(void *ptrStruct){
    StructCalc *ptr;
    ptr = (StructCalc*) ptrStruct;
    while(ptr->n <= 10){
        if(ptr->control == 1){
            ptr->sum += ptr->result;
            ptr->control = 0;
            sched_yield();
        }else
            sched_yield();
    }
    printf("\nFinaliza a Thread Sum\n");
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

    str.threadCalc_id = threadCalc_id;
    str.threadSum_id = threadSum_id;

    pthread_join(threadCalc_id,thread_return);
    pthread_join(threadSum_id,thread_return);

    printf("Resultado: %ld\n",str.sum);
}

int main(){
    return start();
}