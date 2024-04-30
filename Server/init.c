#include"../common/header.h"
#include"../common/declaration.h"
#include"../common/datastruct.h"

void* delete_infra(void*);
void* create_infra(void*);
void* exitserver(void*);
void* process_request(void*);

void* (*fptr[NOF])(void*); 
void signal_handler(int);

sem_t process_req_sem;
sem_t *server_vendor_sem;
void init (){

#ifdef DEBUG
	printf("\n Begin : %s : %s ",__FILE__,__func__);
#endif
	fptr[0] = exitserver;
	fptr[1] = create_infra;
	fptr[2] = delete_infra;
	fptr[3] = process_request;
#ifdef DEBUG
	printf("\n End : %s : %s ",__FILE__,__func__);
#endif



}


