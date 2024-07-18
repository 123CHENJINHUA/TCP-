#include"tcp_client.h"
#include<iostream>

using namespace std;

int main()
{
	cout << "=====================TCP¿Í»§¶Ë=====================" << endl;
	string addr = "127.0.0.1";
	int port = 21567;
	tcp_client plc(addr, port);
	float angle, X_Distance, Y_Distance;
	char send_megs = 0;
	while (cin >> send_megs)
	{
		plc.main_process(send_megs, angle, X_Distance, Y_Distance);
		cout << "X_Distance: " << X_Distance << endl;
		cout << "Y_Distance: " << Y_Distance << endl;
		cout << "Angle: " << angle << endl;
	}
	

	return 0;
}