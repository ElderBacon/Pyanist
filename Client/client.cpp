#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define serverIP "127.0.0.1"

using namespace std;
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " image.jpg" << endl; // argv[0]是程序名
        return -1;
    }

    //创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));        //每个字节都用0填充
    serv_addr.sin_family = AF_INET;                  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr(serverIP); //具体的IP地址
    serv_addr.sin_port = htons(1234);                //端口
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    cout << "connect success" << endl;

    //向服务器发送数据
    char str[] = "Hello World!";
    write(sock, str, sizeof(str));
    //关闭套接字
    close(sock);

    //读取服务器传回的数据
    char buffer[40];
    read(sock, buffer, sizeof(buffer) - 1);

    printf("Message form server: %s\n", buffer);

    //关闭套接字
    close(sock);
    return 0;
}