#include "../common/header.h"
#include "../common/datastruct.h"

int main(int argc,char *argv[]){
	
	printf("\n Begin : %s : %s :\n",__FILE__,__func__);
	int rpfd,ret,shmid;
	Request *req;
	Result *res;

	printf("No of arguments passed are = %d\n ",argc);

	if(argc < 2){
		printf("Insufficient argumentd \n");
		exit(EXIT_FAILURE);
	}

	rpfd = atoi(argv[1]);
    	shmid = atoi(argv[2]);

	req = (Request*) malloc(sizeof(Request));	
	memset(req,'\0',sizeof(Request));

	printf("\n read fd = %d , shared memory key = %d ",rpfd,shmid);
	
//	close(fd[1]); //closing the writer end of the vendor
	
	ret = read(rpfd,req,sizeof(Request));
//	sem_post((sem_t *)argv[3]);
	printf("\n Received in vendor: size = %d pid = %d val1 = %d val2 = %d  operator = %c\n",ret,req->pid,req->val1,req->val2,req->oper);
	
//	close(fd[0]);
	if(req->oper == '+')
	{
		/////////////////// recived from pipe and putting it sharmed memory ////////////
		res = (Result*)malloc(sizeof(Result));
		memset(res,'\0',sizeof(Result));

		res = (Result*)shmat(shmid,(void*)0, 0);
    	
		if(res == (Result*) (-1)) {
        		perror("shmat");
        		exit(1);
    		}

		//res = (Result*) malloc(sizeof(Result));
       		//memset(res,'\0',sizeof(Result));

        	res->cpid = (long)req->pid; //putting the process id 
        	res->result = req->val1 + req->val2; 
		printf("\n Putting the result in the shared memory result = %f cpid = %ld ",res->result,res->cpid);
	}
	else{
		printf("\n Wrong vendor\n");
	}

	printf("\n End : %s : %s :\n",__FILE__,__func__);


	return 0;
}
