#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"unistd.h"
#include"arpa/inet.h"
#include"netinet/in.h"

#define PORTA 4444
#define PORTB 5555
#define BUF_SIZE 2000
#define CLADDR_LEN 100

void main() {
 struct sockaddr_in addrA,addrB, cl_addrA,cl_addrB;
 int sockfdA, lenA, retA, newsockfdA;
 int sockfdB, lenB, retB, newsockfdB;
 char bufferA[BUF_SIZE];
 char bufferB[BUF_SIZE];
 pid_t childpidA,childpidB;
 char clientAddrA[CLADDR_LEN];
 char clientAddrB[CLADDR_LEN];

 sockfdA = socket(AF_INET, SOCK_STREAM, 0);
 sockfdB = socket(AF_INET, SOCK_STREAM, 0);
 if (sockfdA < 0) {
  printf("Error creating socketA!\n");
  exit(1);
 }
if (sockfdB < 0) {
  printf("Error creating socketB!\n");
  exit(1);
 }
 printf("Socket A & B created...\n");

 memset(&addrA, 0, sizeof(addrA));
 memset(&addrB, 0, sizeof(addrB));
 addrA.sin_family = AF_INET;
 addrA.sin_addr.s_addr = INADDR_ANY;
 addrA.sin_port = PORTA;
 addrB.sin_family = AF_INET;
 addrB.sin_addr.s_addr = INADDR_ANY;
 addrB.sin_port = PORTB;

 retA = bind(sockfdA, (struct sockaddr *) &addrA, sizeof(addrA));
 retB = bind(sockfdB, (struct sockaddr *) &addrB, sizeof(addrB));
 if (retA < 0) {
  printf("Error binding in A!\n");
  exit(1);
 }
if (retB < 0) {
  printf("Error binding in B!\n");
  exit(1);
 }
 printf("Binding done in A & B...\n");

 printf("Waiting for a connection...\n");
 listen(sockfdA, 5);
 listen(sockfdB, 5);
  lenA = sizeof(cl_addrA);
  lenB = sizeof(cl_addrB);
  newsockfdA = accept(sockfdA, (struct sockaddr *) &cl_addrA, &lenA);
  newsockfdB = accept(sockfdB, (struct sockaddr *) &cl_addrB, &lenB);
  if (newsockfdA < 0) {
   printf("Error accepting connection!\n");
   exit(1);
  }
 if (newsockfdB < 0) {
   printf("Error accepting connection!\n");
   exit(1);
  }
  printf("Connection accepted A & B...\n");

  inet_ntop(AF_INET, &(cl_addrA.sin_addr), clientAddrA, CLADDR_LEN);
  inet_ntop(AF_INET, &(cl_addrB.sin_addr), clientAddrB, CLADDR_LEN);
  childpidA = fork();
//) == 0) { //creating a child process A
//close(sockfd);

//stop listening for new connections by the main process.
//the child will continue to listen.
//the main process now handles the connected client.

   for (;;){
    if (childpidA > 0)
{
memset(bufferA, 0, BUF_SIZE);
memset(bufferB, 0, BUF_SIZE);
retA = recvfrom(newsockfdA, bufferA, BUF_SIZE, 0, (struct sockaddr *) &cl_addrA, &lenA);
if(retA < 0) {

     printf("Error receiving data!\n");

     exit(1);

    }

    printf("Received data from  A %s: %s\n", clientAddrA, bufferA);
retB = sendto(newsockfdB, bufferA, BUF_SIZE, 0, (struct sockaddr *) &cl_addrB, lenB);
 if (retB < 0) {

     printf("Error sending data!\n");

     exit(1);

    }

    printf("Sent data to  B %s: %s\n", clientAddrB, bufferA);
}

else 
{
    memset(bufferA, 0, BUF_SIZE);
    memset(bufferB, 0, BUF_SIZE);
    
    retB = recvfrom(newsockfdB, bufferB, BUF_SIZE, 0, (struct sockaddr *) &cl_addrB, &lenB);
    
    if(retB < 0) {
     printf("Error receiving data!\n");
     exit(1);
    }
    printf("Received data from B %s: %s\n", clientAddrB, bufferB);

    
    retA = sendto(newsockfdA, bufferB, BUF_SIZE, 0, (struct sockaddr *) &cl_addrA, lenA);
   
    if (retA < 0) {
     printf("Error sending data!\n");
     exit(1);
    }
    printf("Sent data to A %s: %s\n", clientAddrA, bufferB);

   }
}
//  }
  close(newsockfdA);
  close(newsockfdB);
 }
