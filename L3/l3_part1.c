#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

FILE *logFile;
sigset_t block_mask;
void signal_handler(int signo, siginfo_t *si, void *ucontext);

int main() {
    logFile = fopen("./log.txt", "a+t");
    printf("start with PID %i\n", getpid());
    fprintf(logFile, "start with PID %i\n", getpid());
    fflush(logFile);
    struct sigaction action;
    action.sa_handler = NULL;
    action.sa_sigaction = signal_handler;
    action.sa_mask = block_mask;
    action.sa_flags = SA_RESETHAND & SA_SIGINFO;
    struct sigaction oldHandler;
    sigaction(SIGHUP, &action, &oldHandler);

    while (1) {
        sleep(5);
        fprintf(logFile, "idle\n");
        fflush(logFile);
    }
    exit(EXIT_SUCCESS);
}

void signal_handler(int signo, siginfo_t *si, void *ucontext) {
    printf("receive signal");
    fprintf(logFile, "signal number %i\n", si->si_signo);
    fprintf(logFile, "signal code %i\n", si->si_code);
    fprintf(logFile, "errno association %i\n", si->si_errno);
    fprintf(logFile, "sending process %i\n", si->si_pid);
    fprintf(logFile, "sender's ruid %i\n", si->si_uid);
    fprintf(logFile, "exit value %i\n", si->si_status);
    fprintf(logFile, "band event for SIGPOLL %ld\n", si->si_band);
    fflush(logFile);
}
