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
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define UDP_PORT 30000

int get_filename(char *dir_p,char namebuf[][128])
{
    DIR *d;
    struct dirent *file;
    int len = 0;

    if(!(d = opendir(dir_p)))
    {
        printf("Error opendir %s!!!\n",dir_p);
        exit(1);
    }
    while((file = readdir(d)) != NULL)
    {
        if(strncmp(file->d_name,".",1) == 0)
            continue;
        strcpy(namebuf[len++],file->d_name);
    }

    closedir(d);
    return 0;
}

void removefiles(char* dirname)
{
    DIR* d = opendir(dirname);
    struct dirent* f;
    char buf[256];

    while((f = readdir(d)) != NULL)
    {
        if(*f->d_name == '.') continue;

        if(f->d_type == DT_DIR) // sub dir
        {
            strcpy(buf, dirname);
            strcpy(buf, "/");
            strcpy(buf, f->d_name);
            removefiles(buf);
            
        }
        else if(f->d_type == DT_REG)
        {
            strcpy(buf, dirname);
            strcat(buf, "/");
            strcat(buf, f->d_name);
            remove(buf);
        }
    }
}

int main(int argc, char *argv[])
{
    pid_t pid;
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    int sockfd,sendfd;
    struct sockaddr_in addr,servaddr, sendaddr;
    char UDP_buf[1024] = "0";
    char TCP_buf[1024] = "0";
    char temp[128] = "0";
    char PORT[30] = "0";
    char *UDP_p ,*UDP_e;
    int TCP_PORT;
    char *ID = argv[1];
    char *type_p,*filename_p,*len_p,*TCP_e;
    char namebuf[20][128];
    int i;
    int flag = 8;
    int fd;

    sprintf(PORT,"%s",ID+5);
    TCP_PORT = 30001 + atoi(PORT);
    printf("%d\n",TCP_PORT);
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
                execl("Adshow","Adshow",NULL);

        default:
            while(1)
            {
                bzero(UDP_buf,sizeof(UDP_buf));
                addr.sin_family = AF_INET;
                addr.sin_port = htons(UDP_PORT);
                addr.sin_addr.s_addr = INADDR_ANY;
                bind(s, (struct sockaddr*)&addr, sizeof(addr));

                recv(s, UDP_buf, sizeof(UDP_buf), 0);
                UDP_p = UDP_buf;
                printf("%s\n",UDP_p);
                if((UDP_p = strstr(UDP_p,ID)) == NULL)
                {
                    continue;
                }
                UDP_e = strstr(UDP_p,"&");
                *UDP_e = 0;
                UDP_p += strlen(ID);
                switch(atoi(UDP_p))
                {
                    case 16://off
                        if(flag == 8)
                        {
                            kill(pid,SIGKILL);
                            flag = 7;
                            wait(NULL);
                        }
                        break;
                    case 13://on
                        if(flag == 7)
                        {
                            kill(pid,SIGKILL);
                            flag = 8;
                            wait(NULL);
                            goto exec_fork;
                        }
                        break;
                    case 15://发送当前状态
                        bzero(temp,sizeof(temp));
                        sprintf(temp,"%s1%d",ID,flag);
                        printf("%s\n",temp);
                        sendfd = socket(AF_INET,SOCK_STREAM,0);
                        sendaddr.sin_family = AF_INET;
                        sendaddr.sin_port = htons(31000);
                        sendaddr.sin_addr.s_addr = inet_addr("10.1.14.211");

                        if(connect(sendfd,(struct sockaddr *)&sendaddr,sizeof(sendaddr)) < 0)
                        {
                            printf("Connect server failed.\n");
                            exit(1);
                        }
                        write(sendfd,temp,sizeof(temp));
                        close(sendfd);
                        printf("send temp success!!\n");
                        break;
                    case 19://文件同步
                        kill(pid,SIGKILL);
                        wait(NULL);
                        bzero(temp,sizeof(temp));
                        bzero(&namebuf,20*128*sizeof(char));

                        sockfd = socket(AF_INET,SOCK_STREAM,0);
                        servaddr.sin_family = AF_INET;
                        servaddr.sin_port = htons(TCP_PORT);
                        servaddr.sin_addr.s_addr = inet_addr("10.1.14.211");

                        if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
                        {
                            printf("Connect server failed.\n");
                            exit(1);
                        }
                        read(sockfd,TCP_buf,128);
                        
                        printf("%s\n",TCP_buf);
                        type_p = strstr(TCP_buf, "FiLeTyPe=");
                        type_p += strlen("FiLeTyPe=");
                        TCP_e = strstr(type_p,"&");
                        *TCP_e = 0;
                         
                        filename_p = strstr(TCP_e+1,"FiLeNaMe=");
                        filename_p += strlen("FiLeNaMe=");
                        TCP_e = strstr(filename_p,"&");
                        *TCP_e = 0;

                        len_p = strstr(TCP_e+1,"FiLeLeNgHt=");
                        len_p += strlen("FiLeLeNgHt=");

                        sprintf(temp,"/home/dong/ADMN4/%s/",type_p);
                        removefiles(temp);
                        //get_filename(temp,namebuf);
                        //for (i = 0; namebuf[i] != NULL; i++) 
                        //{
                        //printf("%s\n",namebuf[i]);
                        //strcat(temp,namebuf[i]);
                        //remove(temp);
                        //}
                        //printf("aaaaaaaaaaaaaaaaaaaaaaaa\n");
                        bzero(temp,sizeof(temp));
                       
                        sprintf(temp,"/home/dong/ADMN4/%s/%s",type_p,filename_p);

                        printf("%s\n",temp);
                        if((fd = open(temp,O_WRONLY|O_CREAT,0666)) == -1)
                        {
                            printf("open file error\n");
                            exit(1);
                        }

                        for (i = 0; i < atoi(len_p)/1024; i++) 
                        {
                            read(sockfd,TCP_buf,1024);
                            write(fd,TCP_buf,1024);
                        }

                        read(sockfd,TCP_buf,atoi(len_p)%1024);
                        write(fd,TCP_buf,atoi(len_p)%1024);

                        printf("save file success!\n");
                        close(fd);
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
