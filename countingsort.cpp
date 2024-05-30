#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
using namespace std;
int countsort(int a[], int b[], int n, int k){
	int c[k];
	int count = 0;
	for (int i = 0; i<k; i++){
		count = count+1;
		c[i] = 0;
	}
	for (int j = 1; j<=n; j++){
		count = count+1;
		c[a[j]] = c[a[j]]+1;
	}
	for (int i = 1; i<=k; i++){
		count = count+1;
		c[i] = c[i-1] + c[i];
	}
	for (int j = n; j>0; j--){
		count = count+1;
		b[c[a[j]]] = a[j];
		c[a[j]] = c[a[j]]-1;
	}

	return count; 
}
		

main(){
	ofstream fout("input.txt");
	int n; 
	srand((long int)clock());
	cout<<"Enter the number of elements: ";
	cin>>n;
	
	for (int i = 0; i<n; i++)
		fout<<rand()%(n/2)<<"\t";
	fout.close();
	
	ifstream fin("input.txt");
	int a[n];
	for (int i = 1; i<=n; i++)
		fin>>a[i];
	fin.close();
	
	int b[n];
	int count = countsort(a,b,n,n/2);
	cout<<"Number of iterations for "<<n<<" inputs is: "<<count<<endl;
	
}
