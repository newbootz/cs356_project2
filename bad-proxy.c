#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
/*
sources used:
http://www-01.ibm.com/support/knowledgecenter/SSB23S_1.1.0.7/com.ibm.ztpf-ztpfdf.doc_put.07/gtpc2/cpp_gethostbyname.html?cp=SSB23S_1.1.0.7%2F0-3-7-1-0-6-6
google simple tcp server
http://cboard.cprogramming.com/c-programming/165979-can%27t-get-whole-ip-address-getaddrinfo.html

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
char* hostname_to_ip(char* host)
{
			 
			struct addrinfo hints, *servinfo, *p, *curr;
			int rv;
			//printf("%s\n",host );
			memset(&hints, 0, sizeof hints);
			hints.ai_family = AF_UNSPEC; // use AF_INET6 to force IPv6
			hints.ai_socktype = SOCK_STREAM;
			//sockfd = socket(AF_UNSPEC, SOCK_STREAM, 0);
			if ((rv = getaddrinfo(host, "http", &hints, &servinfo)) != 0) {
			    //fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
			    printf("error\n");
			    //exit(1);
			    return NULL;
			}
			else
			{
				//printf("success\n");
				
				for ( curr = servinfo; curr != NULL; curr = curr->ai_next) 
				{
						
			            if (curr->ai_family == AF_INET) 
			            {
			            	//printf("AF_INET\n");
			                char addrbuf[INET_ADDRSTRLEN + 1];
			                char *addr;
			 
			                addr = inet_ntop(AF_INET, &(((struct sockaddr_in *)curr->ai_addr)->sin_addr), addrbuf, sizeof addrbuf);
			                if (addr == NULL) 
			                {
			                   	printf("error\n");
			            
			                    return NULL;
			            	}
                			printf("%s: IPv4 = %s\n", host, addr);
                			return addr;
     
 
            			} 
			            else
			            {	
			            	//printf("AF_INET6\n");
				            if (curr->ai_family == AF_INET6) 
				            {
				                char addrbuf[INET6_ADDRSTRLEN + 1];
				                char *addr;
				 
				                addr = inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)curr->ai_addr)->sin6_addr), addrbuf, sizeof addrbuf);
				                if (addr == NULL) 
				                {
				                    
				                    printf("error\n");
				                   
				                    return NULL;
				                }
				                //printf("%s: IPv6 = %s\n", host, addr);
				                return addr;
				 
				            }
				        }
				}
				//sendto(sockfd,sendline,strlen(sendline),0,(struct sockaddr *)&servinfo,sizeof(servinfo));
			}

			// // loop through all the results and connect to the first we can
			// for(p = servinfo; p != NULL; p = p->ai_next) {
			//     if ((sockfd = socket(p->ai_family, p->ai_socktype,
			//             p->ai_protocol)) == -1) {
			//         perror("socket");
			//         continue;
			//     }

			//     if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			//         close(sockfd);
			//         perror("connect");
			//         continue;
			//     }

			//     break; // if we get here, we must have connected successfully
			// }

			// if (p == NULL) {
			//     // looped off the end of the list with no connection
			//     fprintf(stderr, "failed to connect\n");
			//     exit(2);
			// }

			freeaddrinfo(servinfo); // all done with this structure
}

void parse(char* mesg, int n)
{
	char str[1000];
	char packet_host[1000];
	char host_name[1000] = "Host: ";
	char ip[100];
	char* ret;
	printf("-------------------------------------------------------\n");
	//printf("%s\n",mesg);
	
	ret = strstr(mesg, host_name);
	if(ret != NULL)
	{
		sscanf(((char*)ret+6), "%s", str);
	 
		char* ip = hostname_to_ip(str);
		if(ip != NULL)
		{
			printf("%s resolved to %s" , str , ip);
		}
		else
		{
			printf("error resolving IP\n");
		}
		
	   		 
		//printf("%s\n",str );

	}
	printf("-------------------------------------------------------\n");

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
            //printf("line 136\n");
            if(n != 0)
            {
            	mesg[n] = 0;
            	parse(mesg,n);
            	//sendto(connfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
            	memset(mesg,0,sizeof(mesg));
            	n = 0;
            }
                  
         }
         
      }
      close(connfd);
   }
   return 0;
}