#include<iostream>
#include <string>
using namespace std;

class tcp_client
{
private:
	char buff[1024];
	char recv_buff[100] = { 0 };
	char send_buff[1] = { 0 };

	string plc_addr = "127.0.0.1";
	int plc_port = 21567;
public:

	tcp_client(string& plc_addr, int& plc_port);
	virtual ~tcp_client() {};

	int main_process(char &send_megs, float &angle, float &X_Distance, float &Y_Distance);
};

