//Supplementary functions for echo_s_functions.c
//Written by Logan Padon and James Speights

#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
#include <errno.h>

//socket for log communication
int log_fd;

//addr for log server
struct sockaddr_in remote;

void error(const char *msg) {
     perror(msg);
     exit(1);
}

void doStuffTCP(int fd, char buff[], int buff_len) {
  int n;
  bzero(buff,buff_len);
  if ((n = read(fd,buff,buff_len-1)) < 0)
       error("ERROR reading from socket");

  printf("Got message: %s", buff);
  //echo msg
  write(fd, buff, n);
  close(fd);

  //log
  log_data(&buff, n);
}

void doStuffUDP(int fd, char buff[], int buff_len) {
  struct sockaddr_in remote;
  int len, length;
  len = sizeof(remote);
  bzero(buff,buff_len);
  length = recvfrom(fd, buff, buff_len - 1, 0, (struct sockaddr *)&remote, &len);
  buff[length] = '\0';
  printf("Got message: %s", buff);

  //echo msg
  sendto(fd,buff,length,0,(struct sockaddr *)&remote,len);

  //log
  log_data(&buff, length);
}

void init_log(char *name) {
  struct hostent *log_server;
  log_server = gethostbyname(name);
  if (log_server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
  }
     printf ("enter in a port  # ");
        scanf ("%d",&righe);
  int PORT = %d;
  bzero((char *) &remote, sizeof(remote));
  remote.sin_family = AF_INET;
  bcopy((char *)log_server->h_addr,
       (char *)&remote.sin_addr.s_addr,
       log_server->h_length);
  remote.sin_port = htons(PORT);
  log_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (bind(log_fd, (struct remote *) &remote, sizeof(remote)) < 0)
      error("ERROR on binding");
}

//logs the data to the log server
void log_data(char buff[], int length){
  printf("seding data");
  sendto(log_fd, buff, length-1, 0, (struct sockaddr *)&remote, sizeof(remote));
  printf("data sent");
}

//waits with no hang to prevent zombie processes
void SigCatcher(int n) {
     wait3(NULL,WNOHANG,NULL);
}
