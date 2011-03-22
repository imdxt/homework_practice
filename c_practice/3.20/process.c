#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <signal.h>

#define SERV_PORT 31000

int main(int argc, char *argv[])
{
    pid_t pid;
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    //int client_sock;
    int sockfd,sendfd;
    struct sockaddr_in addr,servaddr, sendaddr,clientaddr;
    //socklen_t cliaddr_len;
    char buf[1024] = "0";
    char buf1[1024] = "0";
    char temp[30] = "0";
    char *p ,*e , *m;
    char *ID = argv[1];
    int n;
    int flag = 8;
    FILE *fp;
  
    bzero(&addr,sizeof(addr));
    bzero(&servaddr,sizeof(servaddr));
    bzero(&sendaddr,sizeof(sendaddr));
exec_fork:
    pid = fork();
    switch(pid)
    {
        case -1:
            perror("fork error\n");
            exit(1);

        case 0:
            while(1)
                execl("show","show",NULL);

        default:
            //flag = 1;
            while(1)
            {
                addr.sin_family = AF_INET;
                addr.sin_port = htons(30000);
                addr.sin_addr.s_addr = INADDR_ANY;
                bind(s, (struct sockaddr*)&addr, sizeof(addr));

                recv(s, buf, sizeof(buf), 0);
                p = buf;
                printf("%s\n",p);
                if((p = strstr(p,ID)) == NULL)
                {
                    continue;
                }
                e = strstr(p,"&");
                *e = 0;
                p += strlen(ID);
                switch(atoi(p))
                {
                    case 16://off
                        if(flag == 8)
                        {
                            kill(pid,SIGKILL);
                            wait();
                            flag = 7;
                        }
                        break;
                    case 13://on
                        if(flag == 7)
                        {
                            kill(pid,SIGKILL);
                            wait();
                            flag = 8;
                            goto exec_fork;
                        }
                        break;
                    case 15://发送当前状态
                        sprintf(temp,"%s1%d",ID,flag);
                        printf("%s\n",temp);
                        sendfd = socket(AF_INET,SOCK_STREAM,0);
                        sendaddr.sin_family = AF_INET;
                        sendaddr.sin_port = htons(SERV_PORT);
                        sendaddr.sin_addr.s_addr = inet_addr("10.1.14.211");

                        if(connect(sendfd,(struct sockaddr *)&sendaddr,sizeof(sendaddr)) < 0)
                        {
                            printf("Connect server failed.\n");
                            perror("COnnect");
                            exit(1);
                        }
                        write(sendfd,temp,sizeof(temp));
#if 0
                        if(bind(sendfd,(struct sockaddr *)&sendaddr,sizeof(sendaddr)) < 0)
                        {
                            printf("bind error\n");
                            exit(1);
                        }
                        else printf("bind success!!\n");
                        if(listen(sendfd,5) < 0)
                        {
                            printf("listen error\n");
                            exit(1);
                        }
                        else printf("listen success!!\n");
                        
                        cliaddr_len = sizeof(clientaddr);
                        if((client_sock = accept(sendfd,(struct sockaddr *)&clientaddr,&cliaddr_len)) < 0)
                        {
                            close(sendfd);
                            printf("accept error\n");
                            exit(1);
                        }
                        else write(client_sock,temp,sizeof(temp));
#endif
                        //close(client_sock);
                        close(sendfd);
                        printf("send temp success!!\n");
                        break;
                    case 19://文件同步
                        kill(pid,SIGKILL);
                        wait();

                        sockfd = socket(AF_INET,SOCK_STREAM,0);
                        servaddr.sin_family = AF_INET;
                        servaddr.sin_port = htons(SERV_PORT);
                        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

                        if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
                        {
                            printf("Connect server failed.\n");
                            exit(1);
                        }
                        if((fp = fopen("/home/dong/imdxt","a+")) == NULL)
                        {
                            printf("fopen file error\n");
                            exit(1);
                        }

                        while((n = read(sockfd,buf1,1024)) > 0)
                        {
                            fwrite(buf1,n,1,fp);
                        }
                        printf("save file success!\n");
                        fclose(fp);
                        close(sockfd);
                        goto exec_fork;
                        break;
                    default:
                        break;
                }
            }
    close(s);

    }

    return 0;
}
