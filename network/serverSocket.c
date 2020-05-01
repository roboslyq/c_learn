//
// Created by luo.yongqian on 2020/4/30.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/************************************************************************************************************************
1、int socket(int family,int type,int protocol)
family:
    指定使用的协议簇:AF_INET（IPv4） AF_INET6（IPv6） AF_LOCAL（UNIX协议） AF_ROUTE（路由套接字） AF_KEY（秘钥套接字）
type:
    指定使用的套接字的类型:SOCK_STREAM（字节流套接字） SOCK_DGRAM
protocol:
    如果套接字类型不是原始套接字，那么这个参数就为0
2、int bind(int sockfd, struct sockaddr *myaddr, int addrlen)
sockfd:
    socket函数返回的套接字描述符
myaddr:
    是指向本地IP地址的结构体指针
myaddrlen:
    结构长度
struct sockaddr{
    unsigned short sa_family; //通信协议类型族AF_xx
    char sa_data[14];  //14字节协议地址，包含该socket的IP地址和端口号
};
struct sockaddr_in{
    short int sin_family; //通信协议类型族
    unsigned short int sin_port; //端口号
    struct in_addr sin_addr; //IP地址
    unsigned char si_zero[8];  //填充0以保持与sockaddr结构的长度相同
};
3、int connect(int sockfd,const struct sockaddr *serv_addr,socklen_t addrlen)
sockfd:
    socket函数返回套接字描述符
serv_addr:
    服务器IP地址结构指针
addrlen:
    结构体指针的长度
4、int listen(int sockfd, int backlog)
sockfd:
    socket函数绑定bind后套接字描述符
backlog:
    设置可连接客户端的最大连接个数，当有多个客户端向服务器请求时，收到此值的影响。默认值20
5、int accept(int sockfd,struct sockaddr *cliaddr,socklen_t *addrlen)
sockfd:
    socket函数经过listen后套接字描述符
cliaddr:
    客户端套接字接口地址结构
addrlen:
    客户端地址结构长度
6、int send(int sockfd, const void *msg,int len,int flags)
7、int recv(int sockfd, void *buf,int len,unsigned int flags)
sockfd:
    socket函数的套接字描述符
msg:
    发送数据的指针
buf:
    存放接收数据的缓冲区
len:
    数据的长度，把flags设置为0
*************************************************************************************************************************/
int main(int argc, char *argv[])
{
    int fd, new_fd, struct_len, numbytes,i;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    char buff[BUFSIZ];
    // 指定使用的协议簇:AF_INET（IPv4） AF_INET6（IPv6） AF_LOCAL（UNIX协议） AF_ROUTE（路由套接字） AF_KEY（秘钥套接字）
    server_addr.sin_family = AF_INET;
    // 监听端口
    server_addr.sin_port = htons(8000);
    // 监听地址，默认是0.0.0.0
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_addr.sin_zero), 8);
    struct_len = sizeof(struct sockaddr_in);
    /**
     * 第一个参数fmmily代表一个协议族，比较熟知的就是AF_INET，PF_PACKET等；
     * 第二个参数是协议类型，常见类型是SOCK_STREAM,SOCK_DGRAM, SOCK_RAW, SOCK_PACKET等；
     * 第三个参数是具体的协议，对于标准套接字来说，其值是0，对于原始套接字来说就是具体的协议值。
     */
    //（1）创建套接字：int socket(int family, int type, intprotocol);
    fd = socket(AF_INET, SOCK_STREAM, 0);
    /**
     *
     *    主要的功能是将addrlen长度 structsockaddr类型的myaddr地址与sockfd文件描述符绑定到一起，在sockaddr中主要包含服务器端的协议族类型，
     *    网络地址和端口号等。在客户端模式中不需要使用bind函数。当bind函数返回0时，为正确绑定，返回-1，则为绑定失败。
     *
     *
     *    bind函数的第一个参数sockfd是在创建socket套接字时返回的文件描述符。
     *    bind函数的第二个参数是structsockaddr类型的数据结构，由于structsockaddr数据结构类型不方便设置，所以通常会通过对tructsockaddr_in进行地质结构设置，然后进行强制类型转换成structsockaddr类型的数据，
     */
     // (2) 套接字绑定函数： intbind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);
    while(bind(fd, (struct sockaddr *)&server_addr, struct_len) == -1);
    printf("Bind Success!\n");
    /**
     * listen的操作就是当有较多的client发起connect时，server端不能及时的处理已经建立的连接，这时就会将connect连接放在等待队列中缓存起来。
     * 这个等待队列的长度有listen中的backlog参数来设定。listen和accept函数是服务器模式特有的函数，客户端不需要这个函数。
     * 当listen运行成功时，返回0；运行失败时，返回值位-1.
     */
    //（3）监听函数：int listen(int sockfd, int backlog);
    //    sockfd是前面socket创建的文件描述符;backlog是指server端可以缓存连接的最大个数，也就是等待队列的长度。
    while(listen(fd, 10) == -1);
    printf("Listening....\n");
    printf("Ready for Accept,Waitting...\n");
    /**
     *  接受函数accept其实并不是真正的接受，而是客户端向服务器端监听端口发起的连接。
     *   对于TCP来说，accept从阻塞状态返回的时候，已经完成了三次握手的操作。Accept其实是取了一个已经处于connected状态的连接，
     *   然后把对方的协议族，网络地址以及端口都存在了client_addr中，返回一个用于操作的新的文件描述符，该文件描述符表示客户端与服务器端的连接，
     *   通过对该文件描述符操作，可以向client端发送和接收数据。同时之前socket创建的sockfd，则继续监听有没有新的连接到达本地端口。
     *   返回大于0的文件描述符则表示accept成功，否则失败。
     */
//    （4）      请求接收函数： int accept(int sockfd, structsockaddr *client_addr, socklen_t *len);
//    sockfd是socket创建的文件描述符；
//    client_addr是本地服务器端的一个structsockaddr类型的变量，用于存放新连接的协议族，网络地址以及端口号等；
//    第三个参数len是第二个参数所指内容的长度，对于TCP来说其值可以用sizeof(structsockaddr_in)来计算大小，
//    说要说明的是accept的第三个参数要是指针的形式，因为这个值是要传给协议栈使用的。
    new_fd = accept(fd, (struct sockaddr *)&client_addr, &struct_len);
    printf("Get the Client.\n");
    /**
     * 在服务器端和客户端建立连接之后是进行数据间的发送和接收，主要使用的接收函数是recv和read，
     * 发送函数是send和write。因为对于socket套接字来说，最终实际操作的是文件描述符，所以可以使用对文件进行操作的接收和发送函数对socket套接字进行操作。
     * read和write函数是文件编程里的知识，所以这里不再做多与的赘述。
     */
    numbytes = send(new_fd,"Welcome to my server\n",21,0);

    while((numbytes = recv(new_fd, buff, BUFSIZ, 0)) > 0)
    {
        buff[numbytes] = '\0';
        printf("%s\n",buff);
        if(send(new_fd,buff,numbytes,0)<0)
        {
            perror("write");
            return 1;
        }
    }
    close(new_fd);
    close(fd);
    return 0;
}