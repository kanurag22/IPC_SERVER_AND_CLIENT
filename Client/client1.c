#include "../common/header.h"
#include "../common/datastruct.h"


int main(){
	
	Result res;

	if(access(REQFIFO,F_OK) == -1)
        {
		printf("FIFO NOT FOUND\n");
		exit(EXIT_FAILURE);
	}

	int fd = open(REQFIFO, O_WRONLY);
    	
	if (fd == -1) {
        	perror("open");
        	exit(EXIT_FAILURE);
    	}
	
	Request *req = (Request*) malloc(sizeof(Request));

	if(req == NULL){
		perror("malloc request");
		exit(EXIT_FAILURE);
	}

	req->pid = getpid();
	req->val1 = 34;
	req->val2 = 30;
	req->oper = '+';
	///////////////////////////// putting the values in fifo ////////////////////////
	ssize_t buffer_size = write(fd,req,sizeof(Request));


	if(buffer_size == -1){
		perror("write buffer size ");
		exit(EXIT_FAILURE);
	}
	close(fd);
#ifdef DEBUG
	printf("size written  = %ld \n",buffer_size);
#endif
	////////////////////////////// getting the values from message queue /////////////
    int msgid = msgget(MSGQKEY,0666);
        if(msgid == -1){
                perror("msgget");
                exit(1);
                }
	printf("\n msg id  =  %d \n",msgid);

	if(msgrcv(msgid,&res,sizeof(Result),(long)req->pid, 0) == -1){
		perror("msgrcv");
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG
    	printf("Received: %f pid %ld\n",res.result,res.cpid);	
#endif

	

	return 0;
}
