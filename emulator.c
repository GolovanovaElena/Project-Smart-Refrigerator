#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char message_1[]="milk is over";
char message_2[]="ice-cream is over";
char message_3[]="tomatoes are over";
char buf_1[sizeof(message_1)];
char buf_2[sizeof(message_2)];
char buf_3[sizeof(message_3)];


int main(int argc, char *argv[]){
	int sock, random;
	struct sockaddr_in addr;
	char answer[1024];
	
	srand(time(NULL));
	random=rand()%(1-3+1)+1;
	printf("%d\n", random);	
	
	sock=socket(AF_INET, SOCK_STREAM, 0); //домен - интернет; тип - способ передачи данных - с предварительной установкой соединения; протокол - определяется однозначно по домену и типу
	if (sock<0){
		perror("socket problem");
		exit(1);	
	}
	
	addr.sin_family=AF_INET;
	addr.sin_port=htons(3425);
	addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK);
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr))<0){ //установление соединения с сервером
		perror("connect problem");
		exit(2);		
	}
	
	if (random==1){
		send(sock, message_1, sizeof(message_1), 0);
		printf("%s\n", message_1);
		}
	else if (random==2){
		send(sock, message_2, sizeof(message_3), 0);
		printf("%s\n", message_2);
		}	
	else if(random==3){
		send(sock, message_3, sizeof(message_3), 0);
		printf("%s\n", message_3);
		}
	recv(sock, answer, sizeof(answer), 0);
	printf("%s", answer);
	shutdown(sock,SHUT_RDWR);
	const char on = 1; 
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)); 
	return 0;
}
