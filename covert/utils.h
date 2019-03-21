#include <stdio.h>
#include <stdlib.h> //exit()

void error(char *msg) {
    perror(msg);
    exit(1);
}

//cpu
#define __USE_GNU
#define _GNU_SOURCE

#include <sched.h>

void setCPUCore(int core) {
    cpu_set_t set;
    CPU_ZERO(&set); //clear cpu mask
    CPU_SET(core, &set); //set cpu core
    if (sched_setaffinity(0, sizeof(cpu_set_t), &set) != 0) {
        error("ERROR on cpu set");
    }
}

//__asm__
#include "../data/asm_branch.h"

//rdtsc()
#if defined(__i386__)
static __inline__ unsigned long long rdtsc(void) {
    unsigned long long int x;
    __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}
#elif defined(__x86_64__)

static __inline__ unsigned long long rdtsc(void) {
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long long) lo) | (((unsigned long long) hi) << 32);
}

#endif

#define _OPEN_THREADS

#include <pthread.h> //pthread_create()
#include <signal.h> //pthread_kill()

#include <time.h> //time()
#include <unistd.h> //usleep()

#define BRANCH_TAKEN 1
#define BRANCH_NOT_TAKEN 0
#define BRANCH_DO_NOTHING -1

#define MAX_PROBES 200 //num of iteration
#define SEC_U 1000000 //1 sec

int i, j; //loop itr
