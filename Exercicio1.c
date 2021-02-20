/*Programa cria uma arvore de processos, cada processo pai deve aguardar a conclusão de todos os processos
filhos para encerrar sua execução*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void * threadA(void *arg);
void * threadB(void *arg);
void * threadC(void *arg);
void * threadD(void *arg);
void * threadE(void *arg);
void * threadF(void *arg);

int main(char *argv[]){
	pthread_t thread_A_id;
	void * thread_res;
	int threadAresult;
	
	//Criando a Thread A
	threadAresult = pthread_create (&thread_A_id, NULL, threadA, (void*)("Processo A Executando\n"));
    //Verificando se a Thread A foi criada
    if(threadAresult != 0){
        printf ("Erro na Criação da Thread A\n");
        exit(EXIT_FAILURE);
    }

	//Executando a thread A
	threadAresult = pthread_join (thread_A_id, &thread_res);
	return 0;
}

//Thread A executa assim executando as threads B e C
void * threadA(void *arg){
    pthread_t thread_B_id;
    pthread_t thread_C_id;
    void * thread_res;
    int threadBresult,threadCresult;

	printf("\n%s", (char *)arg);

    threadBresult = pthread_create(&thread_B_id, NULL, threadB, (void*)("Processo B Executando\n"));
    //Verificando se a Thread B foi criada
    if(threadBresult != 0){
        printf ("Erro na Criação da Thread B\n");
        exit(EXIT_FAILURE);
    }

    threadCresult = pthread_create(&thread_C_id, NULL, threadC, (void*)("Processo C Executando\n"));
    //Verificando se a Thread C foi criada
    if(threadCresult != 0){
        printf ("Erro na Criação da Thread C\n");
        exit(EXIT_FAILURE);
    }


    threadBresult = pthread_join(thread_B_id, &thread_res);
    threadCresult = pthread_join(thread_C_id, &thread_res);

    printf("\nProcesso A Finalizado\n");
	pthread_exit(arg);
}

//Thread B executa assim executando as threads D, E e F
void * threadB(void *arg){
    pthread_t thread_D_id;
    pthread_t thread_E_id;
    pthread_t thread_F_id;
    void * thread_res;
    int threadDresult,threadEresult,threadFresult;

	printf("\n%s", (char *)arg);

    threadDresult = pthread_create (&thread_D_id, NULL, threadD, (void*)("Processo D Executando\n"));
    //Verificando se a Thread D foi criada
    if(threadDresult != 0){
        printf ("Erro na Criação da Thread C\n");
        exit(EXIT_FAILURE);
    }
    threadEresult = pthread_create (&thread_E_id, NULL, threadE, (void*)("Processo E Executando\n"));
    //Verificando se a Thread E foi criada
    if(threadEresult != 0){
        printf ("Erro na Criação da Thread C\n");
        exit(EXIT_FAILURE);
    }
    threadFresult = pthread_create (&thread_F_id, NULL, threadF, (void*)("Processo F Executando\n"));
    //Verificando se a Thread F foi criada
    if(threadFresult != 0){
        printf ("Erro na Criação da Thread C\n");
        exit(EXIT_FAILURE);
    }
    
    threadDresult = pthread_join(thread_D_id, &thread_res);
    threadEresult = pthread_join(thread_E_id, &thread_res);
    threadFresult = pthread_join(thread_F_id, &thread_res);


    printf("\nProcesso B Finalizado\n");
	pthread_exit(arg);
}

//Thread C executa 
void * threadC(void *arg){
    printf("\n%s", (char *)arg);
    printf("\nProcesso C Finalizado\n");
	pthread_exit(arg);
}

//Thread D executa
void * threadD(void *arg){
    printf("\n%s", (char *)arg);
    printf("\nProcesso D Finalizado\n");
	pthread_exit(arg);
}

//Thread E executa
void * threadE(void *arg){
    printf("\n%s", (char *)arg);
    printf("\nProcesso E Finalizado\n");
	pthread_exit(arg);
}

//Thread F executa
void * threadF(void *arg){
    printf("\n%s", (char *)arg);
    printf("\nProcesso F Finalizado\n");
	pthread_exit(arg);
}