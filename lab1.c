#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <math.h>

#define NTHREADS  2 // número de threads

typedef struct {
   int index;
   int* vet;
} t_Args;

// função que a thread irá executar
void *quadrado (void *arg) {

  t_Args* argumento = (t_Args *) arg;
  for(int i = argumento->index; i < 10000; i += 3){
    argumento->vet[i] = pow(argumento->vet[i], 2);
  }
  free(arg);
  pthread_exit(NULL);
}

// funcao principal
int main(void) {
  pthread_t tid_sys[NTHREADS]; 
  int thread; 
  int vet[10000];
  t_Args* argumento;
  for(int i = 0; i < 10000; i++){
    vet[i] = i; 
  }
  for(thread=0; thread<NTHREADS; thread++) {
    argumento = malloc(sizeof(t_Args));
    argumento->vet = vet;
    argumento->index = thread + 1;
    if (pthread_create(&tid_sys[thread], NULL, quadrado, (void *)argumento)) {
      printf("ERRO: pthread_create()\n"); exit(-1);
    }
  }
  for(int i = 0; i < 10000; i += 3){
    argumento->vet[i] = pow(argumento->vet[i], 2);;
  }
  for (thread=0; thread<NTHREADS; thread++) {
    if (pthread_join(tid_sys[thread], NULL)) {
         printf("ERRO: pthread_join() \n"); exit(-1); 
    } 
  }
  for(int i = 0; i < 10000; i++){ 
    printf("%d\n", vet[i]); 
  }
  printf("Thread principal finalizada\n");

  pthread_exit(NULL);
}