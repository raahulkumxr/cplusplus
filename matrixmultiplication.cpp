//Matrix Chain Multiplication - Optimal Ordering
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <bits/stdc++.h>

using namespace std;

long int cnt=0;

//Matrix chain Ordering - Divide and Conquer Approach
int MatrixChainDC(int p[], int i, int j) 
{ 
    if(i == j) return 0; 
    int k; 
    int min = INT_MAX; 
    int t; 
   
    for (k = i; k < j; k++) 
    { 
    	cnt++;
        t = MatrixChainDC(p, i, k) + MatrixChainDC(p, k + 1, j) + p[i - 1] * p[k] * p[j]; 
        if (t < min) 
            min = t; 
    }
    return min; 
} 
  
//Matrix Chain Ordering - Dynamic Programming Approach
long int MatrixChainDP(int p[],int n, long int **m, int **s)
{
	int i,j,len,k;
	long int q;
	for(i=1;i<=n;i++)
		m[i][i] = 0;
		
	for(len=2;len<=n;len++)
	{
		for(i=1;i<=n-len+1;i++)
		{
			j = i+len-1;
			m[i][j] = INT_MAX; //equal to infinity
			for(k=i;k<=j-1;k++)
			{
				cnt++;
				q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
				if(q<m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}			
		}
		
	}
	return m[1][n];
}

void PrintOptimal(int **s, int i, int j)
{
	
	if(i==j)
		cout<<"A"<<i;
	else
	{
		cout<<"(";
		PrintOptimal(s,i,s[i][j]);
		PrintOptimal(s,s[i][j]+1,j);
		cout<<")";
	}
}

int main()
{
	cout<<showpoint<<setprecision(12);
	
	int n;
	int *p;

	cout<<"\nEnter n (Number of Matrices): ";
	cin>>n;
	
	
	p = new int[n+1];
	
	ofstream outf;
	ifstream inf;
	
	srand((long int)clock());
	
	//Loading numbers to input file
	outf.open("in.txt");
	for(int i=0;i<=n;i++)
	{
		outf<<"\t"<<(rand()%n)+2;
	}
	outf.close();
	
	//Reading input in array from input file
		
	inf.open("in.txt");		
	for(int i=0;i<=n;i++)
	{
		inf>>p[i];
	}
	inf.close();

	
//	int n=6;
//	int p[] = {30, 35, 15, 5, 10, 20, 25};

	cout<<"\nMatrix Chain Multiplication - Optimal Ordering";
	cout<<"\n\nInput:";
	cout<<"\n\tNumber of Matrices: "<<n;
	cout<<"\n\tMatrices Dimensions: ";
	for(int i=0;i<=n;i++)
		cout<<"\t"<<p[i];
		
	cout<<"\n\nDivide & Conquer Approach:";
	long int minDC;
	
	cnt=0;
	minDC = MatrixChainDC(p,1,n);	
	cout<<"\n\nMinumum Number of Multiplications Required: "<<minDC;
	cout<<"\nNumber of Active Operations: "<<cnt;
	
	cout<<"\n\nDynamic Programming Approach:";
	
	long int minDP;
	long int **m;
	int **s;
	
	m = new long int*[n+1];
	s = new int*[n+1];
	
	for(int i=0;i<n+1;i++)
	{
		m[i] = new long int[n+1];
		s[i] = new int[n+1];
	}
	
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			m[i][j] = -1;
			s[i][j] = -1;
		}
	}

	cnt=0;
	minDP = MatrixChainDP(p,n,m,s);
	cout<<"\n\nMinumum Number of Multiplications Required: "<<minDP;
	cout<<"\nNumber of Active Operations: "<<cnt;

	
	cout<<"\n\nOptimal Solution: ";
	PrintOptimal(s,1,n);
    cout<<endl;
	
//m Matrix
/*cout<<"\n\nM-Matrix:\n ";
for(int i=1;i<=n;i++)
{
	for(int j=1;j<=n;j++)
	{
		cout<<"\t"<<m[i][j];
	}
	cout<<"\n";
}
//m Matrix
cout<<"\n\nS-Matrix:\n ";
for(int i=1;i<=n;i++)
{
	for(int j=1;j<=n;j++)
	{
		cout<<"\t"<<s[i][j];
	}
	cout<<"\n";
}
*/


}

