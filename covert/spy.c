#include "utils.h"

#define MAX_STATE_TIME 250000
#define COVERT_LOG_FILE "../results/cycles_times.log"

static unsigned long long start_t = 0, end_t = 0;
static pthread_mutex_t spyMutex = PTHREAD_MUTEX_INITIALIZER;
unsigned long long ref_t, diff_t;

void *spyThread(void *argv) {
    setCPUCore(1); //set spy thread to cpu core 1
    while (1) {
        pthread_mutex_lock(&spyMutex);
        start_t = rdtsc();
        s_br_taken();
        end_t = rdtsc();
        pthread_mutex_unlock(&spyMutex);
        usleep(MAX_STATE_TIME); //0.25 sec; fixed state from trojan
    }
}

int main(int argc, char *argv[]) {
    setCPUCore(0); //set main thread to cpu core 0
    pthread_mutex_init(&spyMutex, NULL);
    pthread_t s_tid;
    if (pthread_create(&s_tid, NULL, spyThread, NULL)) {
        error("Error on creating spy thread");
    }
    sleep(1); //fake wait to start spyThread
    ref_t = end_t - start_t;
    FILE *fp = fopen(COVERT_LOG_FILE, "w");
    if (fp == NULL) {
        error("Error on opening file");
    }
    fprintf(fp, "%s,%s\n", "Iterations", "Cycles"); //column name
    int itr = 0;
    while (itr < MAX_PROBES) {
        pthread_mutex_lock(&spyMutex);
        diff_t = end_t - start_t;
        while (diff_t > 0 && diff_t != ref_t) {
            printf("[%d] Cycles = %llu\n", itr, diff_t);
            fprintf(fp, "%d,%llu\n", itr, diff_t);
            ref_t = diff_t;
            itr++;
            usleep(1);
        }
        pthread_mutex_unlock(&spyMutex);
    }
    pthread_mutex_destroy(&spyMutex);
    if (pthread_kill(s_tid, 0)) {
        error("Error on killing spy thread");
    }
    return 0;
}
