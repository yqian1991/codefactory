#include <iostream>

using namespace std;

double byteToDouble(char *str)
{

	long long dbl = 0;

	for(int i=0;i<63;i++)
	{
	    cout<<str[i]-'0'<<"\n";
		dbl += (str[i]-'0');
		cout<<dbl<<"\n";
		dbl <<= 1;//multiple by 2
		cout<<dbl<<"\n";
		cout<<"--------"<<"\n";
	}
	//cout<<"end for cycle"<<"\n";
	cout<<dbl<<"\n";
	cout<<(str[63]-'0')<<"\n";
	dbl +=(str[63]-'0');
	double* db = (double*)&dbl;
	return *db;
}

int main()
{
    double data=0.0;
    char *str="0100000001011001000000000000000000000000000000000000000000000000";
    char *str1="0100000011100010110000011100110101010101010101010101010101010101";
    data=byteToDouble(str);
    cout<<data;
    return 0;
}
