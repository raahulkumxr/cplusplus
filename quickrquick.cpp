#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

void swap(int* a, int* b){
	int g = *a;
	*a = *b;
	*b = g;
}

int partition(int A[], int p, int r, int& count){
	int x = A[r];
	int i = p - 1; 
	for (int j = p; j<=r-1; j++){
		count++;
		if (A[j]<=x){
			i++;
			swap(A[i], A[j]);
		}
	}
	swap(A[i+1], A[r]); 
	return i+1;
}

void quicksort(int A[], int p, int r, int& count){
	if (p<r){
		int q = partition(A, p, r, count);
		quicksort(A, p, q - 1, count);
		quicksort(A, q + 1, r, count);
	}
}

int rpartition(int A[], int p, int r, int& count){
	int i = (rand()%(r - p + 1)) + p;
	swap(A[r], A[i]);
	return partition(A, p, r, count);
}

int rquicksort(int A[], int p, int r, int& count){
	if (p<r){
		int q = rpartition(A, p, r, count);
		rquicksort(A, p, q - 1, count);
		rquicksort(A, q + 1, r, count);
	}
}

main(){
	ofstream fout("input.txt");
	int choice;
	int choice1; 
	int n; 
	cout<<"Enter the number of elements: ";
	cin>>n;
	cout<<"1.Random\n2.Ascending\n3.Descending\n4.Equal\n";
	cin>>choice;
	srand((long int)clock());
	switch(choice){
		case 1: for(int i = 0; i<n; i++) fout<<rand()%n<<"\t";
			break;
		case 2: for(int i = 0; i<n; i++) fout<<i<<"\t";
			break;
		case 3: for(int i = n; i>0; i--) fout<<i<<"\t";
			break;
		case 4: for(int i = 0; i<n; i++) fout<<n<<"\t";
			break;
		default:cout<<"Enter the valid choice!";
	}
	fout.close();

	ifstream fin("input.txt");
	int A[n+1];
	int count = 0; 
	for (int i = 1; i<=n; i++) fin>>A[i];
	
	cout<<"Do you want quick sort(0) or rquicksort(1):  ";
	cin>>choice1;
	if (choice1 == 0) quicksort(A,1,n,count);
	else rquicksort(A, 1, n, count);
		
	cout<<"Number of elements: "<<n<<endl;
	cout<<"Number of iterations: "<<count<<endl;
}

