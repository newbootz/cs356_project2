#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
/*


*/




/*used for validating length and id, make sure
it only consists of digits*/
int valid_num(char *num)
{
	int i =0;
    while (num[i] != '\0') {
        if (num[i] >= '0' && num[i] <= '9')
            i++;
        else
        	return 0;
    }
    return 1;
}

void parse(char* mesg, int n)
{
	char str[1000];
	char packet_host[1000];
	

	//printf("%d BYTES\n",n);
	//printf("-------------------------------------------------------\n");
            mesg[n] = 0;
            // printf("Received the following:\n");
            // printf("%s",mesg);
			while (sscanf(mesg, "%s", str)!=EOF)
			{
				mesg = mesg + strlen(str);
				// if(!strcmp(str,"Host:") )
				// {
				// 	sscanf(mesg,"%s",packet_host);
				// 	printf("%s",packet_host);
				// }
				printf("%s",str);
			}
			//printf("%s",packet_host);
    //printf("-------------------------------------------------------\n");

}
int main ( int argc, char *argv[] )
{


	int listenfd,connfd,n;
   struct sockaddr_in servaddr,cliaddr;
   socklen_t clilen;
   pid_t     childpid;
   char mesg[1000];

int port_number;
int valid_flags=0;
int i;
/*get port number and verbose flag, check for errors*/
/*still have to implement verbose flag(1 or 0) */
if(argc != 3)
	{
		printf("Arguments are incorrect, example:(./bad-proxy -p 8080)\n");
		return 0;
	}
	for(i = 0; i < argc; ++i)
	{
		if(argv[i][0] == '-')
		{
			switch(argv[i][1])
			{
				case 'p':
					if(!valid_num(argv[i+1])){printf("Invalid Port Number, example:(./bad-proxy -p 8080)\n"); return 0;}
					port_number = atoi(argv[i+1]);
					if(port_number <= 0){printf("Invalid Port Number, example:(./bad-proxy -p 8080)\n");
						return 0;}
					printf("Port number: %d\n", port_number);
					valid_flags = 1;
					break;
				default:
					printf("unrecognized flag: %s, example: (./bad-proxy -p 8080)\n", argv[i]);
					return 0;
				
			}
		}
	}
	if(!valid_flags)
	{
		printf("unrecognized flag %s, example: (./bad-proxy -p 8080)\n", argv[1]);
		return 0;
	}


/*listen on the specified port*/

   listenfd=socket(AF_INET,SOCK_STREAM,0);

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   servaddr.sin_port=htons(port_number);
   if(bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
   {
   		printf("Failed to bind to port %d\n",port_number);
		return 0;
   }

   listen(listenfd,1024);
/*listen for a connection*/
   for(;;)
   {
      clilen=sizeof(cliaddr);
      connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);
      /*for this connection, listen for any incoming packets*/
      if ((childpid = fork()) == 0)
      {
         close (listenfd);
         for(;;)
         {
            n = recvfrom(connfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&clilen);
            // mesg[n] = 0;
            parse(mesg,n);
            sendto(connfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
            
         }
         
      }
      close(connfd);
   }
   return 0;
}