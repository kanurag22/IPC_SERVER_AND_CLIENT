#include"../common/header.h"
#include"../common/declaration.h"
#include"../common/datastruct.h"

void* process_request(void* arg){
#ifdef DEBUG
	printf("\n Begin : %s : %s ",__FILE__,__func__);
#endif
	Infra *infra;
	Request *req;
	ssize_t bytes_read,bytes_write;
	char ret;
	int fd;
	pid_t id;
	char rpfd[10],sshmid[10];
	Result *res;

	infra = (Infra*)arg;
	req = (Request*) malloc(sizeof(Request));
	if(req == NULL){
		perror("Request Malloc");
		fptr[0]((void*)"FALIURE");
	}
#ifdef DEBUG_1
	printf("\n size of req = %ld size of Request = %ld \n",sizeof(req),sizeof(Request));
#endif

	///////// opening the fifo to recieve the message in the que ///////
	fd = open(infra->fifo,O_RDONLY);
		if (fd == -1) {
        		perror("open");
        		fptr[0]((void*)"FAILURE");
    		}
	bytes_read = read(fd,(void*)req, sizeof(Request));
    		if (bytes_read <= 0) {
        		perror("read Request");
        		fptr[0]((void*)"FAILURE");
    		}
	close(fd);
	sem_post(infra->pr_sem);

#ifdef DEBUG
    	printf("\n Received FIFO  size = %ld pid = %d val1 = %d val2 = %d  operator = %c \n",bytes_read,req->pid,req->val1,req->val2,req->oper);
#endif


	////////////////////// now the value are in server and server has to call the appropriate vendor for the calculation ///////
	
	ret = req->oper;
	sprintf(rpfd,"%d",(*infra->pipe+0));
	sprintf(sshmid,"%d",infra->shmid);
	

	id = fork();
			
	switch(id){
		case -1:
			perror("fork");
			fptr[0]((void*)"FAILURE");
			break;
		case 0:
			switch(ret){
				case'+':
					execl("./adder","adder",rpfd,sshmid,NULL);
                			perror("execl adder");
					break;
				case '-':
                    			execl("./adder","adder",rpfd,sshmid,NULL);
                			perror("execl adder");
                   			 break;
                		case '*':
					execl("./sadder","adder",rpfd,sshmid,NULL);
                			perror("execl adder");
					break;
		                case '/':
               			 	execl("./divisor","divisor",rpfd,sshmid,NULL);
                   			 perror("execl subtractor");
					break;
		                case '%':
					execl("./modulor","modulor",rpfd,sshmid,NULL);
                			perror("execl subtractor");
                    			break;
                		default:
                    			printf("\n wrong choice =  %c \n",req->oper);
				
			}
		default:
			bytes_write = write(*(infra->pipe+1),req,sizeof(Request));
			if(bytes_write == -1){
				perror("write reqesut error");
				fptr[0]((void*)"FAILURE");
			}
			wait(NULL);
		///////////////////////////////////////// now getting the result from the shared memory and putting it message que /////////
			res = (Result*)shmat(infra->shmid,(void*)0, 0);
			if(res == (Result*)(-1)){
				perror("shmat");
				fptr[0]((void*)"FAILURE");
			}
	
#ifdef DEBUG
	printf(" \n Getting the result from shared memory Result = %f cpid = %ld \n",res->result,res->cpid);
#endif
	printf("\n msgid = %d \n",infra->msgid);

#ifdef DEBUG
	printf("\n data send on msg queue is =  %f  type %ld \n",res->result,res->cpid);
#endif

		if(msgsnd(infra->msgid,res,sizeof(Result),0) == -1 ){
				perror("msgsnd");
				fptr[0]((void*)"FAILURE");
			}
		}

		if (shmdt(res) == -1) {
                                perror("shmdt");
                                exit(1);
                        }


#ifdef DEBUG
	printf("\n End : %s : %s \n",__FILE__,__func__);
#endif

	return (void*)arg;

}


