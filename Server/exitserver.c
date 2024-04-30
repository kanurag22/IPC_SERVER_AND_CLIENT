#include"../common/header.h"
#include"../common/declaration.h"
#include"../common/datastruct.h"

void* exitserver(void* arg){

#ifdef DEBUG
	printf("\n Begin : %s : %s ",__FILE__,__func__);
#endif
	if(strcmp("SUCCESS",(char*)arg) == 0){
		exit(EXIT_SUCCESS);
	}
	if(strcmp("FAILURE",(char*)arg) == 0){
		exit(EXIT_FAILURE);
	}

#ifdef DEBUG
	printf("\n End : %s : %s ",__FILE__,__func__);
#endif



}


