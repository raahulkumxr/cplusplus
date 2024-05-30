#include <iostream>
using namespace std;
struct activity{
	int start;
	int finish;
};

void greedy_activity_selector(activity arr[], int n, int& i, activity results[]){
	results[i] = arr[0];
	int k = 0;
	for (int m=1; m<n; m++){
		if (arr[m].start >= arr[k].finish){
			i += 1;
			results[i] = arr[m];
			k = m;
		}
	}
}

void recursive_activity_selector(activity arr[], int k, int n, int& i, activity results[]){
	int m = k+1; 
	results[0] = arr[0];
	while (m < n and arr[m].start < arr[k].finish) m = m+1;
	if (m<n){
		i += 1;
		results[i] = arr[m];
		recursive_activity_selector(arr, m, n, i, results);
	}
}
int main(){
	activity arr[5];
	activity a[5];
	activity b[5];
	int k = 0;
	cout<<"Enter the activity start time and finish time:\n";
	for (int i=0; i<5; i++){
		cout<<"Start time "<<i<<": ";
		cin>>arr[i].start;
		cout<<"Finish time "<<i<<": ";
		cin>>arr[i].finish;
	}
	recursive_activity_selector(arr, 0, 5, k, a);
	cout<<"The mutually compatible activities using R.A.S are: "<<endl;
	for (int i=0; i<k; i++) cout<<"("<<a[i].start<<", "<<a[i].finish<<")"<<endl;

	k = 0;
	greedy_activity_selector(arr, 5, k, b);
	cout<<"The mutually compatible activities using G.A.S are: "<<endl;
	for (int i=0; i<k; i++) cout<<"("<<b[i].start<<", "<<b[i].finish<<")"<<endl;
}


