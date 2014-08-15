#include <iostream>

using namespace std;
//parse from string to int
int Str2Int(string ch)
{
    int sum=0;
    for(int i=0; i<ch.size(); i++)
    {
        //sum = sum*10 + ch[i]-'0';
        sum=(ch[i]>='0'&&ch[i]<='9'&&sum!=-1)?sum*10+ch[i]-'0':-1;
    }
    return sum;
}
//do division without / operator
int div(const int x, const int y) {
    int left_num = x;
    int result = 0;
    while (left_num >= y) {
        int multi = 1;
        while (y * multi <= (left_num >> 1)) {
           multi = multi << 1;
        }
        result += multi;
        left_num -= y * multi;
        cout << multi << " " << left_num << " " << y << endl;
    }
    return result;
}

int main()
{
    cout <<Str2Int("234")<< endl;
    cout <<div(10, 2)<< endl;
    return 0;
}
