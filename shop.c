#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite/sqlite3.h"

char message_1[]="success\n";
char buf_1[sizeof(message_1)];

// Create a callback function  
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char *argv[]){

	/*int listener, re1, message;
	struct sockaddr_in addr;
	char buf[1024];
	listener=socket(AF_INET, SOCK_STREAM, 0);
	if (listener<0){
		perror("socket problem");
		exit(1);	
	}
	
	addr.sin_family=AF_INET; //семейство адресов
	addr.sin_port=htons(3425); // номер порта (из хоста в сетевой)
	addr.sin_addr.s_addr=htonl(INADDR_ANY); //IP-адрес
	
	if(bind(listener,(struct sockaddr*)&addr, sizeof(addr))<0){ //связывание сокета с адресом
		perror("problem address");
		exit(2);
	}
	printf("fghj");
	listen(listener, 1); //ожидание запросов со стороны клиента
	while(1){
		re1=accept(listener, NULL, NULL); //обслуживание 
		while(1){
			message=recv(re1, buf, sizeof(buf), 0);
			if (message<=0)
				break;
				//to_save=*buf;
			send(re1, message_1, sizeof(message_1), 0);
		}
		//send(re, bu, sizeof(message), 0);
		//close(listener);
	}
*/


	int key=0; 
	char text;
	int message=1; //1-milk, 2- ice-cream, 3-tomato
	
	
	sqlite3* store;	 
	int base = 0;	
	const char *sql;
	base = sqlite3_open("store.db", &store);   
    	if (base) {
    		printf("DB Open Error: "); 
        }
	
	//printf message;
	printf("Are you looking for the product in a specific store?(y/n):\n");
	scanf("%c", &text);
	switch(text)
	{
		case 'y':{
			printf("Select store:\n");
			printf("1. Eleven\n");
			printf("2. Glade\n");
			printf("3. Vegetables\n");
			scanf("%d", &key);
			if (key==1){
				if (message==1){
					sql="SELECT * FROM 'ELEVEN' WHERE TYPE='milk'";
					base = sqlite3_exec(store,  sql, callback, 0, NULL);
					}
				else if (message==2){
					sql="SELECT * FROM 'ELEVEN' WHERE TYPE='ice-creame'";
					base = sqlite3_exec(store,  sql, callback, 0, NULL);
					}
				else if (message==3){
					sql="SELECT * FROM 'ELEVEN' WHERE TYPE='tomato'";
					base = sqlite3_exec(store,  sql, callback, 0, NULL);
					}
				}	
			if (key==2){
				if (message==1){
					sql="SELECT * FROM 'GLADE' WHERE TYPE='milk'";
					base = sqlite3_exec(store,  sql, callback, 0, NULL);
					}
				else if (message==2){
					sql="SELECT * FROM 'GLADE' WHERE TYPE='ice-creame'";
					base = sqlite3_exec(store,  sql, callback, 0, NULL);
					}
				else if (message==3){
					printf("This product is not in the store\n");
					}
				}		
			if (key==3){
				if (message==1){
					printf("This product is not in the store\n");
					}
				else if (message==2){
					printf("This product is not in the store\n");
					}
				else if (message==3){
					sql="SELECT * FROM 'VEGETABLES' WHERE TYPE='tomato'";
					base = sqlite3_exec(store,  sql, callback, 0, NULL);
					}
				}		
			break;
			}
		case 'n':{
			printf("Search in all stores\n");
			if (message==1){
				printf("ELEVEN\n");
				sql="SELECT * FROM 'ELEVEN' WHERE TYPE='milk'";
				base = sqlite3_exec(store,  sql, callback, 0, NULL);
				printf("GLADE\n");
				sql="SELECT * FROM 'GLADE' WHERE TYPE='milk'";
				base = sqlite3_exec(store,  sql, callback, 0, NULL);
			}
			if (message==2){
				printf("ELEVEN\n");
				sql="SELECT * FROM 'ELEVEN' WHERE TYPE='ice-creame'";
				base = sqlite3_exec(store,  sql, callback, 0, NULL);
				printf("GLADE\n");
				sql="SELECT * FROM 'GLADE' WHERE TYPE='ice-creame'";
				base = sqlite3_exec(store,  sql, callback, 0, NULL);
			}
			if (message==3){
				printf("ELEVEN\n");
				sql="SELECT * FROM 'ELEVEN' WHERE TYPE='tomato'";
				base = sqlite3_exec(store,  sql, callback, 0, NULL);
				printf("GLADE\n");
				printf("This product is not in the store\n");
				printf("VEGETABLESE\n");
				sql="SELECT * FROM 'VEGETABLES' WHERE TYPE='tomato'";
				base = sqlite3_exec(store,  sql, callback, 0, NULL);
			}
			break;
		}
		default:
			printf("Error!\n");	
       	}
        // Close the connection
        sqlite3_close(store); 
        return (0); 
}
