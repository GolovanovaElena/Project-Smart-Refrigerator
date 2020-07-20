#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char message_1[]="success\n";
char buf_1[sizeof(message_1)];

int main(int argc, char *argv[]){
	int server, sock, client, sock2, text;
	struct sockaddr_in addr;
	char buf[1024]/*to_save[1024]*/;
	
		//emulator
	server=socket(AF_INET, SOCK_STREAM, 0);
	
	if (server<0){
		perror("socket problem");
		exit(1);	
	}
	
	addr.sin_family=AF_INET; //семейство адресов
	addr.sin_port=htons(3425); // номер порта (из хоста в сетевой)
	addr.sin_addr.s_addr=htonl(INADDR_ANY); //IP-адрес
	
	if(bind(server,(struct sockaddr*)&addr, sizeof(addr))<0){ //связывание сокета с адресом
		perror("problem address");
		exit(2);
	}
	listen(server, 2); //ожидание запросов со стороны клиента
	while(1){
		sock=accept(server, NULL, NULL); //обслуживание 
		if(sock<0){
			perror("problem accept");
			exit(3);
		}
		while(1){
			text=recv(sock, buf, 1024, 0);
			if (text<=0)
				break;
				//to_save=*buf;
			send(sock, message_1, sizeof(message_1), 0);
		}
		}
		
		//send(sock, buf, sizeof(buf), 0);
		shutdown(sock,SHUT_RDWR);
		shutdown(server,SHUT_RDWR);
		const char on = 1;
		setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)); 
		setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)); 
	
	        //shop
	   /*  client=socket(AF_INET, SOCK_STREAM, 0);
	if (client<0){
		perror("socket problem");
		exit(1);	
	}
	
	addr.sin_family=AF_INET; //семейство адресов
	addr.sin_port=htons(3425); // номер порта (из хоста в сетевой)
	addr.sin_addr.s_addr=htonl(INADDR_LOOPBACK); //IP-адрес
	
	if (connect(client, (struct sockaddr *)&addr, sizeof(addr))<0){ //установление соединения с сервером
		perror("connect problem");
		exit(2);		
	}
	send(sock2, buf, sizeof(buf), 0);
	printf("%s\n",buf);
 	close(client);	
 	*/   
	
	return 0;
}
