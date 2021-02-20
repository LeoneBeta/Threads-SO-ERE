/*Utilizando Threads para calcular a série de Fibonacci, o usuário fornece um númeor inteiro positivo para o 
tamanho da sequência, o processo filho gera os números da série e os envia para o processo pai os printar 
na tela.*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
    int number;
    int *sequence;
}TFibonacci;

void* generateNumber(void *ptrFib){
    int i;
    TFibonacci *ptr;
    ptr = (TFibonacci*) ptrFib;
 
    ptr->sequence[0] = 0;
    ptr->sequence[1] = 1;
    for(i=2;i<=ptr->number;i++){
        ptr->sequence[i] = ptr->sequence[i-1] + ptr->sequence[i-2];
    }
    pthread_exit(NULL);
}

void* printResult(void *number){
    pthread_t threadGenerate_id;
    void *thread_return;
    int threadGen, i ,*n;
    TFibonacci fib, *ptrFib;
    ptrFib = &fib;
    n = (int*) number;
    
    //Cria vetor dinamico do tamano fornecido
    fib.sequence = (int*)malloc((*n)*sizeof(int));
    fib.number = *n;

    threadGen = pthread_create(&threadGenerate_id, NULL,generateNumber,(void *)(ptrFib));
    if(threadGen != 0){
        printf ("Erro na Criação da Thread\n");
        exit(EXIT_FAILURE);
    }

    threadGen = pthread_join(threadGenerate_id,&thread_return);

    for(i=0;i<=*n;i++){
        printf("\n%d\n",fib.sequence[i]);
    }
    free(fib.sequence);
    pthread_exit(NULL);
}

int start(){
    pthread_t threadPrint_id;
    void *thread_return;
    int threadPri, number;

    printf("\nForneça um valor inteiro positivo: ");
    scanf("%d",&number);

    //Cria uma Thread passando o número fornecido
    threadPri = pthread_create(&threadPrint_id, NULL,printResult,(void *)(&number));
    if(threadPri != 0){
        printf ("Erro na Criação da Thread \n");
        exit(EXIT_FAILURE);
    }

    threadPri = pthread_join(threadPrint_id,&thread_return);

    return 0;
}

int main(){
    return start();
}