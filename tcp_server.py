#coding:utf-8

from socket import *
from time import ctime

print("=====================视觉TCP服务器=====================");

HOST = ''  #主机号为空白表示可以使用任何可用的地址。
PORT = 21567  #端口号
BUFSIZ = 1024  #接收数据缓冲大小
ADDR = (HOST, PORT)

tcpSerSock = socket(AF_INET, SOCK_STREAM) #创建TCP服务器套接字
tcpSerSock.bind(ADDR)  #套接字与地址绑定
tcpSerSock.listen(5) #监听连接，同时连接请求的最大数目

while True:
    print('等待客户端的连接...')
    tcpCliSock, addr = tcpSerSock.accept()   #接收客户端连接请求
    print('取得连接:', addr)

    while True:
        recv_data = tcpCliSock.recv(BUFSIZ)  # 接收1024个字节
        if recv_data:
            recv_to_int = int(recv_data.decode('gbk'))
            print('接收到的数据为: ', recv_to_int)
            if(recv_to_int == 1):
                list = [0.100,0.200,0.300]
                data = ','.join(str(x) for x in list)
                tcpCliSock.send(data.encode("gbk"))
            else:
                list = [0.500,0.600,0.300]
                data = ','.join(str(x) for x in list)
                tcpCliSock.send(data.encode("gbk"))
        else:
            break

    tcpCliSock.close()  #关闭与客户端的连接
tcpSerSock.close()  #关闭服务器socket