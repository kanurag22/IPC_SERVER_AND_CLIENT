#include"../common/header.h"
#include"../common/declaration.h"
#include"../common/datastruct.h"

void* create_infra(void* arg){

#ifdef DEBUG
	printf("\n Begin : %s : %s ",__FILE__,__func__);
#endif

///////////////////// malloc of infra structure ////////////////////
	Infra *infra;
    	infra = (Infra*)malloc(sizeof(Infra));
        if(infra == NULL){
            perror("infra malloc");
            fptr[0]((void*)"FAILURE");
            }
	memset(infra,'\0',sizeof(infra));

///////////////// creating pipe ////////////////////////
	infra->pipe = (int*)malloc(sizeof(int)*2);
	if(!infra->pipe){
		perror("malloc of pipe");
		free(infra);
		fptr[0]((void*)"failure");
	}

	if(pipe(infra->pipe) == -1){
		perror("pipe");
		free(infra->pipe);
		free(infra);
		fptr[0]((void*)"FAILURE");
	}

#ifdef DEBUG
        printf("\n pipe has been created : %d %d",*(infra->pipe+0),*(infra->pipe+1));
#endif

///////////////// creating fifo ///////////////////////

	if( access(REQFIFO,F_OK) == -1){
		if(mkfifo(REQFIFO, 0666) == -1){
			perror("mkfifo");
			close(*(infra->pipe+0));
			close(*(infra->pipe+1));
			free(infra->pipe);
			free(infra);
			fptr[0]((void*)"FAILURE");
			}

		infra->fifo = (char*)malloc(20);
		if(!infra->fifo){
			perror("malloc fifo");
			close(*(infra->pipe+0));
			close(*(infra->pipe+1));
			free(infra->pipe);
			free(infra);
			fptr[0]((void*)"FAILURE");
		}
		memset(infra->fifo,'\0',20);
		strcpy(infra->fifo,REQFIFO);
#ifdef DEBUG
        printf("\n Fifo has been created : %s",infra->fifo);
#endif
	}
	else{
		
#ifdef DEBUG
        printf("\n Fifo is already created :");
#endif
	}
///////////////// creating message queue///////////////////////
	
	infra->msgid = msgget(MSGQKEY, IPC_CREAT | 0666);
	if(infra->msgid == -1){
		perror("msgget");
		system("unlink REQFIFO");
		close(*(infra->pipe+0));
		close(*(infra->pipe+1));
		free(infra->pipe);
		free(infra);	
		fptr[0]((void*)"FAILURE");
		}
#ifdef DEBUG
        printf("\n message queue has been created : %d",infra->msgid);
#endif

///////////////// creating shared memory //////////////////////
	
	infra->shmid = shmget(SHMKEY,sizeof(Result),IPC_CREAT | 0666);
	if(infra->shmid == -1){
		perror("shmget");
		msgctl(infra->msgid,IPC_RMID,NULL);
    	system("unlink REQFIFO");
        close(*(infra->pipe+0));
		close(*(infra->pipe+1));
        free(infra->pipe);
        free(infra);
		fptr[0]((void*)"FAILURE");
	}

#ifdef DEBUG
        printf("\n shared memory has been created :");
#endif
/*               attaching the created shared memory       */
	char *shared_memory = (char*)shmat(infra->shmid,(void *)0,0);
	if(shared_memory == (char *)(-1)){
			perror("shmat");
			fptr[0]((void*)"FAILURE");
			}
#ifdef DEBUG
        printf("\n shared memory has been attached :");
#endif

//////////////////////  semaphore creating for process request only //////////////////////////////
		infra->pr_sem = (sem_t*)malloc(sizeof(sem_t));
		if(!infra->pr_sem){
			perror("malloc semaphore");
			fptr[0]((void*)"FAILURE");
		}

		if (sem_init(infra->pr_sem, 0, 1) == -1) {
        		perror("Semaphore initialization error");
        		exit(EXIT_FAILURE);
    		}

///////////////////////////////////////////////////////////////////////
#ifdef DEBUG
        printf("\n semaphore has been created :");
#endif		
#ifdef DEBUG

		printf("\n fifo_name = %s  fd[0] = %d fd[1] = %d  shmkey = %d msg key = %d \n",infra->fifo,*(infra->pipe+0),*(infra->pipe+1),infra->shmid,infra->msgid);
#endif
//////////////////////////////////////////////////////////////////////////////////
#ifdef DEBUG
	printf("\n End : %s : %s ",__FILE__,__func__);
#endif

	return (void*)infra;

}


