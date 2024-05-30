#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct ans{
	int l;
	int h;
	int max_sum;
};

ans maxsubarraybf(int a[], int n, int& count){
	ans results;
	results.max_sum = -1000;
	for (int i = 1; i<=n; i++){
		int sum = 0; 
		for (int j = i; j<=n; j++){
			count++;
			sum += a[j];
			if (sum > (results.max_sum)){
				results.max_sum = sum;
				results.l = i; 
				results.h = j;
			}
		}
	}
	return results;
}

ans findmaxcrosssubarray(int a[], int l, int m, int h, int& count){
	int leftsum = -1000;
	int sum = 0;
	ans results; 
	for (int i = m; i>=l; i--){
		count++;
		sum += a[i];
		if (sum > leftsum){
			leftsum = sum;
			results.l = i;
		}
	}
	int rightsum = -1000;
	sum = 0; 
	for (int j = m+1; j<=h; j++){
		count++;
		sum += a[j];
		if (sum > rightsum){
			rightsum = sum; 
			results.h = j;
		}
	}
	results.max_sum = leftsum + rightsum;
	return results;
}

ans findmaxsubarray(int a[], int l, int h, int& count){
	ans results; 
	ans lresults;
	ans rresults;
	ans cresults;	
	if (l == h){
		results.l = l; 
		results.h = h; 
		results.max_sum = a[l];
		return results;
	}
	else{
		int m = (l + h)/2; 
		lresults = findmaxsubarray(a, l, m, count);
		rresults = findmaxsubarray(a, m+1, h, count);
		cresults = findmaxcrosssubarray(a, l, m, h, count);
		if (lresults.max_sum >= rresults.max_sum and lresults.max_sum >= cresults.max_sum)
			return lresults;
		else if (rresults.max_sum >= lresults.max_sum and rresults.max_sum >= cresults.max_sum)
			return rresults;
		else return cresults; 
	}
}
main(){
	ans results; 
	ofstream fout("input.txt");
	srand((long int)clock());
	int n;
	cout<<"Enter the number of elements: ";
	cin>>n; 
	for (int i = 0; i<n; i++){
		int num = rand()%30;
		if (rand()%2 == 0) fout<<-1*num<< "\t";
		else fout<<num<<"\t";
	}
	fout.close();
	
	ifstream fin("input.txt");
	int a[n];
	for (int i = 1; i<=n; i++) fin>>a[i];
	int count = 0;
	results = maxsubarraybf(a,n,count);
	cout<<"The number of iterations (B.F): "<<count<<endl; 
	count = 0;
	results = findmaxsubarray(a,1,n,count);	
	cout<<"The number of iterations (D.C): "<<count<<endl;
}
	
