#include "tcp_client.h"
#include<iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include "winsock2.h"
#include <sstream>
#include <vector>

#pragma comment(lib,"ws2_32.lib")//���ÿ��ļ�
using namespace std;



tcp_client::tcp_client(string& plc_addr, int& plc_port)
{
    this->plc_addr = plc_addr;
    this->plc_port = plc_port;
}

vector<string> split2(const string& strs, const char& delim) {
    vector<string> res;
    if (strs == "") return res;
    stringstream sstr(strs);
    string token;
    while (getline(sstr, token, delim))
    {
        res.push_back(token);
    }

    return res;
}


int tcp_client::main_process(char &send_megs, float& angle, float& X_Distance, float& Y_Distance)
{
    //�����׽���
    WSADATA wsaData;
    memset(buff, 0, sizeof(buff));
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("��ʼ��Winsockʧ��");
        return 0;
    }

    SOCKADDR_IN addrSrv;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(plc_port);//�˿ں�
    addrSrv.sin_addr.S_un.S_addr = inet_addr(plc_addr.c_str());//IP��ַ

    //�����׽���
    SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
    if (SOCKET_ERROR == sockClient) {
        printf("Socket() error:%d", WSAGetLastError());
        return 0;
    }
    //�������������������
    if (connect(sockClient, (struct  sockaddr*)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET) {
        printf("����ʧ��:%d", WSAGetLastError());
        return 0;
    }
    else
    {
            //��������
            send_buff[0] = send_megs;
            send(sockClient, send_buff, sizeof(send_buff), 0);
            
            //��������
            recv(sockClient, recv_buff, sizeof(recv_buff), 0);
            string recv_to_string(recv_buff);
            vector<string> res2 = split2(recv_to_string, ',');
        
            X_Distance = std::stof(res2[0]);
            Y_Distance = std::stof(res2[1]);
            angle = std::stof(res2[2]);
          
         
    }

    //�ر��׽���
    closesocket(sockClient);
    WSACleanup();//�ͷų�ʼ��Ws2_32.dll���������Դ��
    //system("pause");//����Ļ����
    return 0;
}
