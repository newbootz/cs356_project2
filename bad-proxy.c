#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include<errno.h>
/*flag for verbose mode
verbose mode will print GET requests received and if 'Google' 
has been found in the body of the response*/
int verbose = 0;
/*This function detects if we have received
a request for tamu.edu*/
int tamuCheck(char * mesg, int n)
{
    char tamu[1000] = "www.tamu.edu";
    char* ret;

<<<<<<< HEAD
    ret = strstr(mesg, tamu);
    if(ret != NULL)
    {
        return 1;   
    }

    return 0;
}
/* used for printing out error
messages to stdout*/
void error(char* msg)
{
perror(msg);
exit(0);
}
=======
static int verbose = 0;
>>>>>>> c84c20d5f31a236aaeec5c43cdb54c6422e5e88f

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

int main(int argc,char* argv[])
{
<<<<<<< HEAD
    /*google flag used to print google found message only once per response*/
    int google_flag = 0;
    /*used to set up the connection with host*/
    pid_t pid;
    struct sockaddr_in addr_in,cli_addr,serv_addr;
    struct hostent* host;
    int sockfd,newsockfd;
    /*verbose mode flag*/
    int verbose_val = 0;
=======
	char str[1000];
	char packet_host[1000];
	char host_name[1000] = "Host: ";
	char port_number[100] = ":";
	char ip[100];
	char* ret;
	char* pn;
	char str_pn[100];
	printf("-------------------------------------------------------\n");
	printf("%s\n",mesg);
	
	ret = strstr(mesg, host_name);
	if(ret != NULL)
	{
		sscanf(((char*)ret+6), "%s", str);
	 	pn = strstr(str, port_number);
	 	if(pn != NULL)
	 	{
	 		int pn_len = -1;
	 		sscanf(((char*)pn), "%s+1", str_pn);
	 		pn_len = strlen(str_pn);
	 		str[strlen(str)-pn_len] = 0;
	 		//printf("New hostname is  %s\n", str);


	 	}
		char* ip = hostname_to_ip(str);
		if(ip != NULL)
		{
			if(pn == NULL)
			{
				printf("%s resolved to %s\n" , str , ip);
			}
			else
			{

				printf("%s resolved to %s   port_number %s\n" , str , ip, str_pn);
			}
			
		}
		else
		{
			printf("error resolving IP\n");
		}
		
	   		 
		//printf("%s\n",str );

	}
	printf("-------------------------------------------------------\n");

}

int tamuCheck(char * mesg, int n)
{
	char tamu[1000] = "www.tamu.edu";
	char* ret;

	ret = strstr(mesg, tamu);
	if(ret != NULL)
	{
		return 1;	
	}

	return 0;
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
	int verbose_val;

/*get port number and verbose flag, check for errors*/
if(argc < 3 || argc > 5)
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
				case 'v':
					if(!valid_num(argv[i+1])){printf("Invalid Argument for Verbose Flag. example (./bad-proxy -p 8080 -v 1)\n"); return 0;}
					verbose_val = atoi(argv[i+1]);
					if(verbose_val > 1 || verbose_val < 0){printf("Invalid Argument for Verbose Flag. Use -v 1 or -v 0\n"); return 0;}
					verbose = verbose_val;
					printf("Verbose: %d\n", verbose_val);
					valid_flags = 1;
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
>>>>>>> c84c20d5f31a236aaeec5c43cdb54c6422e5e88f

    int port_number;
    int p =0;
    int i;
    char* response;
    /*detecting errors with arguments*/
    if(argc < 3 || argc > 5)
    {
        printf("Arguments are incorrect, example:(./bad-proxy -p 8080)\n");
        return 0;
    }
    /*parse the arguments given to program*/
    for(i = 0; i < argc; ++i)
    {
        if(argv[i][0] == '-')
        {
            switch(argv[i][1])
            {
                /*port number flag set*/
                case 'p':
                {
                    if(!valid_num(argv[i+1])){printf("Invalid Port Number, example:(./bad-proxy -p 8080)\n"); return 0;}
                    port_number = atoi(argv[i+1]);
                    if(port_number <= 0){printf("Invalid Port Number, example:(./bad-proxy -p 8080)\n");
                        return 0;}
                    printf("Port number: %d\n", port_number);
                    p = 1;
                    break;
                } 
                /*verbose mode flag set*/  
                case 'v':
                {
                    if(!valid_num(argv[i+1])){printf("Invalid Argument for Verbose Flag. example (./bad-proxy -p 8080 -v 1)\n"); return 0;}
                    verbose_val = atoi(argv[i+1]);
                    if(verbose_val > 1 || verbose_val < 0){printf("Invalid Argument for Verbose Flag. Use -v 1 or -v 0\n"); return 0;}
                    verbose = verbose_val;
                    printf("Verbose: %d\n", verbose_val);
                    break;
                }
                default :
                {
                    printf("unrecognized flag: %s, example: (./bad-proxy -p 8080)\n", argv[i]);
                    return 0;
                }
            }
        }
    }
    if(p == 0)
    {
        printf("Incorrect Arguments, example: (./bad-proxy -p 8080)\n");
        return 0;
    }
      
    /*set up socket to listen for requests*/   
    bzero((char*)&serv_addr,sizeof(serv_addr));
    bzero((char*)&cli_addr, sizeof(cli_addr));
       
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(port_number);
    serv_addr.sin_addr.s_addr=INADDR_ANY;
       
      
    sockfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd<0)
        error("Problem in initializing socket");
       
    if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
        error("Error on binding");
      
    /*listening for any client requests*/
    listen(sockfd,50);
    int clilen=sizeof(cli_addr);
      
     
     /*accepting a new request from a client*/
    accepting:
     /*reset the google flag and accept the connection request*/
    google_flag = 0; 
    newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clilen);
       
    if(newsockfd<0)
    error("Problem in accepting connection");
    /*fork a new process to handle this client*/
    pid=fork();
    if(pid==0)
    {
    /*parse the request*/
    struct sockaddr_in host_addr;
    int flag=0,newsockfd1,n,port=0,i,sockfd1;
    char buffer[510],t1[300],t2[300],t3[10];
    char* temp=NULL;
    bzero((char*)buffer,500);
    recv(newsockfd,buffer,500,0);
       
    sscanf(buffer,"%s %s %s",t1,t2,t3);
       
       /*determine HTTP version*/
    if(((strncmp(t1,"GET",3)==0))&&((strncmp(t3,"HTTP/1.1",8)==0)||(strncmp(t3,"HTTP/1.0",8)==0))&&(strncmp(t2,"http://",7)==0))
    {
        strcpy(t1,t2);
           
        flag=0;
           
        for(i=7;i<strlen(t2);i++)
        {
            if(t2[i]==':')
            {
                flag=1;
                break;
            }
        }
       
        temp=strtok(t2,"//");
        if(flag==0)
        {
            port=80;
            temp=strtok(NULL,"/");
        }
        else
        {
            temp=strtok(NULL,":");
        }
           
        sprintf(t2,"%s",temp);
        //printf("host = %s",t2);
        host=gethostbyname(t2);
           
        if(flag==1)
        {
            temp=strtok(NULL,"/");
            port=atoi(temp);
        }
       
       
    strcat(t1,"^]");
    temp=strtok(t1,"//");
    temp=strtok(NULL,"/");
    if(temp!=NULL)
    temp=strtok(NULL,"^]");
    /*end of parsing get request*/
       
    // MAYBE CHANGE HOST ADDR TO YOUTUBES FOR TAMU REDIRECT  
    /*attain information of where to send this request*/ 
    bzero((char*)&host_addr,sizeof(host_addr));
    host_addr.sin_port=htons(port);
    host_addr.sin_family=AF_INET;
    bcopy((char*)host->h_addr,(char*)&host_addr.sin_addr.s_addr,host->h_length);
       
    sockfd1=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    newsockfd1=connect(sockfd1,(struct sockaddr*)&host_addr,sizeof(struct sockaddr));
    sprintf(buffer,"\nConnected to %s  IP - %s\n",t2,inet_ntoa(host_addr.sin_addr));
    if(newsockfd1<0)
    error("Error in connecting to remote server");
       
   /*format the request*/
    bzero((char*)buffer,sizeof(buffer));

    if(temp!=NULL)
    {
        sprintf(buffer,"GET /%s %s\r\nHost: %s\r\nConnection: close\r\n\r\n",temp,t3,t2);
        if(verbose){printf("GET /%s at Host %s\n", temp, t2);}
    
    }
    else
    {
        sprintf(buffer,"GET / %s\r\nHost: %s\r\nConnection: close\r\n\r\n",t3,t2);
        if(verbose){printf("GET / %s at Host %s\n", t2, t2);}
    }
    if(strcmp(t2,"www.tamu.edu") == 0)
    {
        sprintf(buffer,"GET /watch?v=dQw4w9WgXcQ HTTP/1.0\r\nHost: www.youtube.com\r\nConnection: close\r\n\r\n");
        if(verbose){printf("GET / %s at Host %s\n", t2, t2);}
    }

    /*send the request to the host*/
     
    n=send(sockfd1,buffer,strlen(buffer),0);
  
    if(n<0)
        error("Error writing to socket");
    else
    {
        /*listen for the response from host*/
        do
        {
            bzero((char*)buffer,500);
            n=recv(sockfd1,buffer,500,0);
            if(!(n<=0))
            {
                
                /*start looking for google in the response body*/
                int start_addr = 0;
                int i;
                /*find the beginnning of the body*/
                for(i = 0; i < 500; ++i)
                {
                    if(buffer[i] == '<' && buffer[i+1] == 'h')
                    {
                        start_addr = i;
                    }
                }
                /*find if there is an instance of google in the body*/
                while(1)
                {
                      char * mod = strstr(&buffer[start_addr], "Google");
                        if(mod != NULL)
                        {
                            google_flag += 1;
                            *(mod) = 'e';
                            *(mod+1) = 'l';
                            *(mod+2) = 'g';
                            *(mod+3) = 'o';
                            *(mod+4) = 'o';
                            *(mod+5) = 'G';

                           
                        }
                        else
                        {
                            break;
                        }

<<<<<<< HEAD
                }
                /*found all instances of google, print message if there were any*/
                 if(verbose && (google_flag == 1))
                {
                    printf("Page found with Google\n");
                }
                         
                /*forward the modified response back to the client*/
                send(newsockfd,buffer,n,0);
=======
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
            	if(tamuCheck(mesg, n) == 1)
            	{
            		//redirect to : http://www.youtube.com/watch?v=dQw4w9WgXcQ
            		printf("Tamu Check works!\n");
            	}
            	//sendto(connfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
            	memset(mesg,0,sizeof(mesg));
            	n = 0;
>>>>>>> c84c20d5f31a236aaeec5c43cdb54c6422e5e88f
            }
        }while(n>0);
    }
    }
    /*bad request, give the user a message*/
    else
    {
        send(newsockfd,"400 : BAD REQUEST\nONLY HTTP REQUESTS ALLOWED",18,0);
    }
    /*close this connection after sending response*/
    close(sockfd1);
    close(newsockfd);
    close(sockfd);
    exit(0);
    }
    else
    {
    close(newsockfd);
    /*go back to accepting requests*/
    goto accepting;
    }
    return 0;
}