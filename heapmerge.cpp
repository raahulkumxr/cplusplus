#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
using namespace std;

void merge(int a[], int p, int q, int r, int& count){
	int n1 = q - p + 1;
	int n2 = r - q;
	int L[n1+1], R[n2+1]; 
	for (int i = 1; i<=n1; i++)
		L[i] = a[p + i - 1];
	for (int i = 1; i<=n2; i++)
		R[i] = a[q + i];
	L[n1] = 10000001;
	R[n2] = 10000001;
	int i = 1; 
	int j = 1;
	for (int k = p; k<=r; k++){
		count++;
		if (L[i]<=R[j]){
			a[k] = L[i];
			i++;
		}
		else{
			a[k] = R[j];
			j++;
		}
	}
}

void swap(int* x, int* y){
	int g =  *x;
	*x = *y; 
	*y = g;
}

void mergesort(int a[], int p, int r, int& count){
	if (p<r){
		int q = (p+r)/2;
		mergesort(a, p, q, count);
		mergesort(a, q+1, r, count);
		merge(a, p, q, r, count);
	}
}

void maxheapify(int a[], int m, int n, int& count){
	int l = 2*m;
	int r = 2*m+1;
	count = count + 1;
	int largest;
	if (l<=n and a[l]>a[m])
		largest = l;
	else largest = m;
	if (r<=n and a[r]>a[largest])
		largest = r;
	if (largest != m){
		swap(a[largest], a[m]);
		maxheapify(a, largest, n, count);
	}
}

void buildmaxheap(int a[], int n, int& count){
	for (int i = n/2; i>=1; i--)
		maxheapify(a, i, n, count);
}

void heapsort(int a[], int n, int& count){
	buildmaxheap(a, n, count);
	int f = n;
	for (int i = f ; i>=2; i--){
		swap(a[1], a[i]);
		f--;
		maxheapify(a, 1, f, count);
	}
}
		
int main(){
	ofstream fout("input.txt");
	srand((long int)clock());
	int choice;
	int programend = 0; 
	int n;
	cout<<"Enter the number of elements: ";
	cin>>n;
	cout<<"1. Random\n2. Ascending\n3. Descending\n4. Equal\n";
	cin>>choice;
	switch(choice){
		case 1: for (int i = 0; i<n; i++)
				fout<<rand()%n<<" ";
			break;
		case 2: for (int i = 0; i<n; i++)
				fout<<i<<" ";
			break;
		case 3: for(int i = n; i>0; i--)
				fout<<i<<" ";
			break;
		case 4: for(int i = 0; i<n; i++)
				fout<<n<<" ";
			break;
	}
	fout.close();
	
		ifstream fin("input.txt");
		int a[n+1];
		for (int i = 1; i<=n; i++)
			fin>>a[i];
		int count;
		cout<<"Merge Sort or Heap sort? (1/0): ";
		cin>>choice;
		if (choice == 1){
				count = 0;
				mergesort(a, 1, n, count);
				cout<<endl<<"Merge Sort"<<endl;
				cout<<"Number of elements: "<<n<<endl; 
				cout<<"Number of iterations: "<<count<<endl;	
		}
		else{
				count = 0;
				heapsort(a, n, count);
				cout<<endl<<"Heap Sort"<<endl;
				cout<<"Number of elements: "<<n<<endl; 
				cout<<"Number of iterations: "<<count<<endl;
		}
	
}
