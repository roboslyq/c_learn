//
// Created by luo.yongqian on 2020/4/30.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
/**
 * 功能介绍：
      连接函数connect是属于client端的操作函数，其目的是向服务器端发送连接请求，这也是从客户端发起TCP三次握手请求的开始，服务器端的协议族，网络地址以及端口都会填充到connect函数的serv_addr地址当中。当connect返回0时说明已经connect成功，返回值是-1时，表示connect失败。
    参数说明：
      connect的第一个参数是socket创建的文件描述符；第二个参数是一个structsockaddr类型的指针，这个参数中设置的是要连接的目标服务器的协议族，网络地址以及端口号；第三个参数表示第二个参数内容的大小，与accept不同，这个值不是一个指针。
 * @param argc
 * @param argv
 * @return
 */
int main(int argc,char *argv[])
{
    int sockfd,numbytes;
    char buf[BUFSIZ];
    struct sockaddr_in their_addr;
    printf("break!");
    while((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1);
    printf("We get the sockfd~\n");
    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(8000);
    their_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bzero(&(their_addr.sin_zero), 8);
//    （5）客户端请求连接函数： intconnect(int sock_fd, struct sockaddr *serv_addr,int addrlen);
    while(connect(sockfd,(struct sockaddr*)&their_addr,sizeof(struct sockaddr)) == -1);
    printf("Get the Server~Cheers!\n");
    numbytes = recv(sockfd, buf, BUFSIZ,0);//接收服务器端信息
    buf[numbytes]='\0';
    printf("%s",buf);
    while(1)
    {
        printf("Entersome thing:");
        scanf("%s",buf);
        numbytes = send(sockfd, buf, strlen(buf), 0);
        numbytes=recv(sockfd,buf,BUFSIZ,0);
        buf[numbytes]='\0';
        printf("received:%s\n",buf);
    }
//    close(sockfd);
    return 0;
}