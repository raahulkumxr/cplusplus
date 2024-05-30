#include<iostream>
#include<fstream>
#include<time.h>
#include<stdlib.h>
#include<iomanip>
#include<cmath>
using namespace std;

struct node
{
	double data;
	node *next;	
};

class SList
{
	node *a;
	int size;
	public:
		SList(){
			a = nullptr;
			size = 0;
		}
		bool insertFront(double x){
			node *n;
 			n = new node;
			if(n==nullptr) return false;
			n->data = x;
			n->next = nullptr;	
			n->next = a;
			a = n;
			size++;
			return true;
		}
		bool ElementAt(int p,double &x){
			node *t = a;
			int c=1;
			while(t!=NULL)
			{
				if(c==p)
				{
					x = t->data;
					return true;
				}
		
				t = t->next;
				c++;
			}	
			return false;
		}
		void Sort(){
			node *i,*j;
			double t;
	
			i = a;
			for(i=a;i!=NULL;i=i->next)
			{
				for(j = i->next;j!=NULL;j=j->next)
				{
					if(j->data<i->data)
					{
						t = i->data;
						i->data = j->data;
						j->data = t;
					}
				}
			}
	
		}
		int GetSize(){		
			return size;
		} 
		
};


long int count=0;

void BucketSort(double a[],int n)
{
	SList *Buckets;
	Buckets = new SList[n];
	
	int bNo;
	for(int i=0;i<n;i++)
	{
		bNo = a[i]*n;
		Buckets[bNo].insertFront(a[i]);
		count++;
	}
	
	for(int i=0;i<n;i++)
	{
		count++;
		Buckets[i].Sort();
	}
	double t;
	for(int i=0,j=0;i<n;i++)
	{
		//cout<<"\nBucket Number: "<<i;
		//Buckets[i].display();
			for(int p=1;p<=Buckets[i].GetSize();p++)
			{
				count++;
				if(Buckets[i].ElementAt(p,t))
				{
					a[j++] = t;
				}
			}

	}
}
int main()
{
	
	ofstream outf;
	ifstream inf;

	//clock_t st,end;
	double etime;

	int n;
	double *a;
	
	cout<<"\nEnter n:";
	cin>>n;
	
	a = new double [n];
	
	int tmp=n-1,d=0;
	while(tmp!=0)
	{
		d++;
		tmp/=10;
	}
	
	srand((long int)clock());
	
	outf.open("in.txt");
	for(int i=0;i<n;i++)
	{
		outf<<"\t"<<(double)((rand()%n)/pow(10,d));
	}
	outf.close();
		
	inf.open("in.txt");		
	for(int i=0;i<n;i++)
	{
		inf>>a[i];
	}
	inf.close();
	
	count = 0;
	BucketSort(a,n);
	
	outf.open("BucketOut.txt");
	for(int i=0;i<n;i++)
	{
		outf<<"\t"<<a[i];
	}
	outf.close();
	
	cout<<"\nBucket Sort:";
	cout<<"\nNumber of inputs: "<<n;
	cout<<"\nNumber of iterations: "<<count;
}
