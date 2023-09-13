#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
//#include <conio.h>
//#include <ctime>

using namespace std;
struct record1
{
	char a[30];
	short int b;
	char c[22];
	char d[10];
};

int main()
{
	setlocale(LC_CTYPE, "Russian");
	FILE *fp;
	fp=fopen("testBase2.dat", "rb");
	record1 mas[4000]={0};
	int i=0,sum=0;
	int ch[10];
	i=fread((record1 *)mas, sizeof(record1), 4000, fp);
	cout<<i<<endl;
    i=0;
	while((i++)<4000)
	{
		//getchar();
		cout<<mas[i].a<<mas[i].b<<mas[i].c<<mas[i].d<<endl;
        cout<< "qq" <<endl;
	};
	cout<<sizeof(record1)<<endl;
	
    //getch();
	return 0;
};
