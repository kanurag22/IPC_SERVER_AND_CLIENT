#ifndef DEBUG
#define DEBUG
#endif

#ifndef REQFIFO
#define REQFIFO "./reqFifo"
#endif

#ifndef MSGQKEY
#define MSGQKEY  1111
#endif

#ifndef SHMKEY
#define SHMKEY  2222
#endif

typedef struct{
	int *pipe;    /* Infra struct for pipe fifo message que and sheared memory */
	char *fifo;
	int msgid;
	int shmid;
	sem_t *pr_sem;
	sem_t *adder_sem;
}Infra;


typedef struct{
	long cpid;
	float result;
}Result;

typedef struct{
	char oper;
	pid_t pid;
	int val1;
	int val2;
}Request;
