#include"../common/header.h"
#include"../common/declaration.h"
#include"../common/datastruct.h"

void signal_handler(int arg){

#ifdef DEBUG
	printf("\n Begin : %s : %s ",__FILE__,__func__);
#endif
	printf("\n signal generated ");
	
/*	if (unlink(del->fifo) == -1) {
        	perror("unlink");
        	fptr[0]((void*)"FAILURE");
    	}
    	printf("FIFO '%s' unlinked (removed) successfully.\n", fifoName);

	close((*del->pipe+0));
	close((*del->pipe+1));

	if (msgctl(del->msgid, IPC_RMID, NULL) == -1) {
        	perror("msgctl");
        	fptr[0]((void*)"FAILURE");
    	}
    	printf("Message queue deleted successfully.\n");

	if (shmctl(del->shmid, IPC_RMID, NULL) == -1) {
        	perror("shmctl");
     		exit(1);
    	}
    	printf("Shared memory segment deleted successfully.\n");
*/
	fptr[0]((void*)"SUCCESS");
#ifdef DEBUG
	printf("\n End : %s : %s ",__FILE__,__func__);
#endif



}


