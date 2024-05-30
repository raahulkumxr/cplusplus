#include<iostream>
#include<fstream>
#include<time.h>
#include<stdlib.h>
#include<iomanip>
#include<cmath>

using namespace std;

long int count=0;

int GetDigit(int x,int i)
{
	int d;
	x = x / pow(10,i-1);
	d = x % 10;
	return d;
}

void CountingSort(int *a, int *b, int n, int k, int d)
{
	int *c;
	
	int s;
	
	c = new int[k+1];
	
	for(int i=0;i<=k;i++)
	{
		count++;
		c[i] = 0;
	}
	
	for(int i=1;i<=n;i++)
	{
		count++;
		s = GetDigit(a[i],d);
		c[s] += 1; 
	}
	for(int i=1;i<=k;i++)
	{
		count++;
		c[i] += c[i-1];
	}
	
	for(int i=n;i>=1;i--)
	{
		count++;
		s = GetDigit(a[i],d);
		b[c[s]] = a[i];
		c[s] -= 1;
	}
		
	delete(c);
}

void RadixSort(int *a, int n, int d)
{
	int *b;
	b = new int[n+1];
	
	for(int i=1;i<=d;i++)
	{
		CountingSort(a,b,n,9,i);
		for(int j=1;j<=n;j++)
			a[j] = b[j];
	}
	
	delete(b);
}

int main()
{
	cout<<showpoint<<setprecision(12);
	
	ofstream outf;
	ifstream inf;


	int n;
	int *a;
	
	cout<<"\nEnter n:";
	cin>>n;

	int tmp=n-1,d=0;
	while(tmp!=0)
	{
		d++;
		tmp/=10;
	}
	 
	a = new int [n+1];


	srand((long int)clock());
	
	int k;
	outf.open("in.txt");
	for(int i=0;i<n;i++)
	{
		k=rand()%((int)pow(10,d));
		outf<<"\t"<<k;
	}
	outf.close();
	
		
	inf.open("in.txt");		
	for(int i=1;i<=n;i++)
	{
		inf>>a[i];
	}
	inf.close();
	count = 0;
	RadixSort(a,n,d);

	outf.open("RadixOut.txt");
	for(int i=1;i<=n;i++)
	{
		outf<<"\t"<<a[i];
	}
	outf.close();
	
	cout<<"\nRadix Sort:";
	cout<<"\nNumber of inputs: "<<n;
	cout<<"\nTotal Active Operations: "<<count;

	delete(a);

}
