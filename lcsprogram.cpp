#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <cstring>
using namespace std;
struct results{
	int c[31][31];
	char b[31][31];
};

results lcsbottomup(char X[], char Y[], int& count, int n){
	results ans; 
	for (int i = 0; i<=n; i++)
		ans.c[0][i] = 0;
	for (int i = 0; i<=n; i++)
		ans.c[i][0] = 0;
	for (int i = 1; i<=n; i++){
		for (int j = 1; j<=n; j++){
			count += 1;
			if (X[i] == Y[j]){
				ans.c[i][j] = ans.c[i-1][j-1] + 1;
				ans.b[i][j] = '\\';
			}
			else if (ans.c[i-1][j] >= ans.c[i][j-1]){
				ans.c[i][j] = ans.c[i-1][j];
				ans.b[i][j] = '|';
			}
			else{
				ans.c[i][j] = ans.c[i][j-1];
				ans.b[i][j] = '-';
			}
		}
	}
	return ans; 
} 

void printlcs(char X[], results ans, int i, int j){
	if (i == 0 or j == 0)
		return;
	if (ans.b[i][j] == '\\'){
		printlcs(X, ans, i - 1, j - 1);
		cout<< X[i];
	}
	else if (ans.b[i][j] == '|') printlcs(X, ans, i - 1, j);
	else printlcs(X, ans, i, j - 1);
}

int lcstopdown(char X[], char Y[], results ans, int i, int j, int& count){
	if (ans.c[i][j] >= 0) return ans.c[i][j];
	count += 1; 
	if (i == 0 or j ==0){
		ans.c[i][j] = 0;
		return ans.c[i][j];
	}
	if (X[i] == Y[j]){
		ans.c[i][j] = lcstopdown(X, Y, ans, i-1, j-1, count) + 1;
		ans.b[i][j] = '\\';
	}
	else{
		int t1 = lcstopdown(X, Y, ans, i-1, j, count);
		int t2 = lcstopdown (X, Y, ans, i, j-1, count);
		if (t1>=t2){
			ans.c[i][j] = t1; 
			ans.b[i][j] = '|';
		}
		else{
			ans.c[i][j] = t2;
			ans.b[i][j] = '-';
		}
	}
	return ans.c[i][j];
}

int divideconquer(char X[], char Y[], int i, int j, int& count){
	count += 1; 
	if (i == 0 or j ==0) return 0;
	if (X[i] == Y[j]) return divideconquer(X, Y, i-1, j-1, count) + 1;
	else{
		int t1 = divideconquer(X, Y, i-1, j, count);
		int t2 = divideconquer (X, Y, i, j-1, count);
		if (t1>=t2) return t1;
		else return t2;
	}
}

int main(){
	char S[] = {'A', 'B', 'C'};
	ofstream fout("input.txt");
	int n;
	cout<<"Enter the size of the strings: ";
	cin>>n;

	for (int i = 0; i<n; i++)
		fout<< S[rand()%3];
	fout<<endl; 
	for (int i = 0; i<n; i++)
		fout<<S[rand()%3];
	fout.close();
	
	char X[n+1];
	char Y[n+1];
	results ans2; 
	for (int i = 1; i<=n; i++){
		for (int j = 1; j<=n; j++)
		ans2.c[i][j] = -1;
	}
	ifstream fin("input.txt");
	for (int i = 1; i<=n; i++)
		fin>>X[i];
	for (int i = 1; i<=n; i++)
		fin>>Y[i];
	fin.close();

	int count = 0;
	cout<<"LCS-BU: ";
	results answer = lcsbottomup(X, Y, count,n);
	printlcs(X, answer, n, n);
	cout<<"\nInput Size: "<<n;
	cout<<"\nNumber of Iterations: "<<count<<endl;	

	count = 0; 
	cout<<"LCS-TD: ";
	int ans = lcstopdown(X, Y, ans2, n, n, count);
	cout<<"\nInput Size: "<<n;
	cout<<"\nNumber of iterations: "<<count<<endl;  

	count = 0; 
	cout<<"LCS-DC: ";
	ans = divideconquer(X, Y, n, n, count);
	cout<<"\nInput Size: "<<n;
	cout<<"\nNumber of iterations: "<<count<<endl;  
}

