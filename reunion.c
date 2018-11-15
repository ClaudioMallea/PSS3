#include <pthread.h>
#include <stdlib.h>
#include "reunion.h"



typedef struct reunion {
	int in,out,cnt;
	pthread_mutex_t m;
	pthread_cond_t cond;
   // declare acá un mutex y una condición y los contadores que
      // Ud. necesitará para resolver el problema de sincronización
} Reunion;

Reunion* nuevaReunion(){
	Reunion* r=malloc(sizeof(Reunion));

	r->in=r->out=r->cnt=0;
	pthread_mutex_init(&r->m,NULL);
	pthread_cond_init(&r->cond,NULL);
	return r;
}

void entrar(Reunion *r){
	pthread_mutex_lock(&r->m);
	r->in++;
	pthread_cond_broadcast(&r->cond);
	pthread_mutex_unlock(&r->m);



}
void concluir(Reunion *r){
	pthread_mutex_lock(&r->m);
	r->out++;
	while(r->in>r->out){
		pthread_cond_wait(&r->cond,&r->m);
	}
	
		
	pthread_cond_broadcast(&r->cond);
	pthread_mutex_unlock(&r->m);


}