#include"../common/header.h"
#include"../common/declaration.h"
#include"../common/datastruct.h"



int main(){

#ifdef DEBUG
	printf("\n Begin : %s : %s ",__FILE__,__func__);
#endif
	pthread_t process_request;
	Infra *infra;
	signal(SIGINT,signal_handler);
	init();
	
	infra = fptr[1]((void*)infra); // create infra is called
	size_t num_thread = 0;
    	//process_request = (pthread_t*)malloc((num_thread)*sizeof(pthread_t));
	//if(process_request == NULL){
	//	perror("malloc thread");
	//	fptr[0]((void*)"FAILURE");
	//}
#ifdef DEBUG
        printf("\n =============================================  \n");
#endif

	while(1){
		//fptr[3]((void*)infra);
		sem_wait(infra->pr_sem);
		printf("\n thread created %ld \n",num_thread);
	        pthread_create(&process_request, NULL,fptr[3],(void*)infra);
		num_thread++;
	//	process_request = realloc(process_request,num_thread*sizeof(pthread_t));
	//	if(process_request == NULL){
	//		perror("relloc thread");
        //      	fptr[0]((void*)"FAILURE");
        //		}
	}
	
#ifdef DEBUG
	printf("\n End : %s : %s ",__FILE__,__func__);
#endif
return 0;
}


