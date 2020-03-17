#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

const size_t BUFF_SIZE = 1024;

int main(int argc, char *argv[]) {
    if (argc < 2){
        printf("Missing label, exit");
        exit(1);
    }
    char *label = argv[1];
    char buff[BUFF_SIZE];
    fd_set rfds;
    struct timeval tv;
    int retval,len;
    /* Ждем, пока на стандартном вводе (fd 0) что-нибудь
       появится. */
while(1){
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    retval = select(1, &rfds, NULL, NULL, &tv);
    if (retval){
	ssize_t readBytes = read(STDIN_FILENO, buff, BUFF_SIZE);
        buff[readBytes - 1] = '\0';
        printf("%s: '%s'\n", label, buff);
	break;
    }
        /* Теперь FD_ISSET(0, &rfds) вернет истинное значение. */
    else
        printf("%s: no data within five seconds.\n",label);
}
    return 0;
}
