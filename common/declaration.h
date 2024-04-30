#ifndef NOF
#define NOF 5
#endif
#define DEBUG 1

extern void signal_handler(int arg);
extern void* process_request(void*);
extern void* delete_infra(void *arg);
extern void* create_infra(void* arg);
extern void* exitserver(void*); // exit from the server
				//
extern void* (*fptr[NOF])(void*); // function pointer
extern void init(void);
extern sem_t process_req_sem;
