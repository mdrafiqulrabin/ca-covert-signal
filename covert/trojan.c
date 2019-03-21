#include "utils.h"
#include "string.h"

static char branch_status = BRANCH_DO_NOTHING;

void *trojanThread(void *argv) {
    setCPUCore(1); //set trojan thread to cpu core 1
    while (1) {
        if (branch_status == BRANCH_TAKEN) {
            t_br_taken();
        } else if (branch_status == BRANCH_NOT_TAKEN) {
            t_br_not_taken();
        } else {
            //do nothing
        }
    }
}

int main(int argc, char *argv[]) {
    setCPUCore(0); //set main thread to cpu core 0
    if (argc < 2) {
        error("Error for no message");
    }
    char *msg = argv[1]; //argv[0] is the program name
    size_t len = strlen(msg);
    if (len == 0) {
        error("Error on empty message");
    }
    printf("\nSending message: %s\n", msg);
    pthread_t t_tid;
    if (pthread_create(&t_tid, NULL, trojanThread, NULL)) {
        error("Error on creating trojan thread");
    }
    sleep(3); //fake wait to start trojanThread
    for (i = 0; i < len; i++) {
        char ch = msg[i];
        printf("\nSending char: %c\n", ch);
        for (j = 7; j >= 0; j--) {
            if (ch & (1 << j)) {
                branch_status = BRANCH_TAKEN;
                printf(" 1");
            } else {
                branch_status = BRANCH_NOT_TAKEN;
                printf(" 0");
            }
            usleep(500000); //0.5 sec
        }
        printf("\nSent char: %c\n", ch);
        branch_status = BRANCH_DO_NOTHING;
        sleep(1); //1 sec
    }
    printf("\nSent message: %s\n", msg);
    if (pthread_kill(t_tid, 0)) {
        error("Error on killing trojan thread");
    }
    return 0;
}
