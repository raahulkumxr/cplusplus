#include<iostream>
using namespace std;
class sob
{
public:
int n, d, a[100],x[100];
void create()
{
	int	r = 0;
	cout<<"Enter the number of elements: "<<endl;
	cin>>n;
	cout<<"Enter the sum: "<<endl;
	cin>>d;
	cout<<"Enter the elements: "<<endl;
	for(int i =1;i<=n;i++)
	{
	x[i]=0;
	cin>>a[i];
	r+=a[i];
	}
	sums(1,r,0);
}
void sums(int i, int r, int sum)
{
	x[i] = 1;
	if(sum+a[i]==d)
	{
		for(int j = 1;j<=i; j++)
		cout<<x[j]<<" ";
		cout<<endl;
		for(int j = 1;j<=i; j++)
		cout<<a[j]<<" ";
		cout<<endl;
	}
	if(sum+a[i]<d && sum+a[i]+r>=d)
	sums(i+1,r-a[i],sum+a[i]);
	if(sum+a[i]>d&& sum +r-a[i]>=d)
	{
		x[i]= 0;
		sums(i+1,r-a[i],sum);
	}

}
};
int main()
{
	sob s;
	s.create();
}

























