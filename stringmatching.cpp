#include <iostream>
#include <cstring>
using namespace std;

int naive(string text, string pattern){
	int n = text.length();
	int m = pattern.length();
	int count = 0;
	int flag; 	
	for (int s = 0; s < n - m; s++){
 		flag = 0; 
		for (int j = 1; j <= m; j++){
			count++;
			if (pattern[j] != text[s+j]){
				flag = 1;
				break;
			}
		}
		if (flag == 0) cout<< "Pattern occurs with valid shift: "<<s<<endl;
	}
	return count;
}

int charcode(char c){
	switch(c){
		case 'A': return 1;
		case 'B': return 2;
		case 'C': return 3;
		case 'G': return 4;
		case 'T': return 5;
		case 'X': return 6;
	}
}

int preprocess(string pattern, int prime, int base){
	int m = pattern.length();	
	int count = 0;
	int p = 0;
	for (int i = 0; i <= m; i++){
		count++;
		p = (base*p + charcode(pattern[i]))%prime;
	}
	cout<< "Preprocessing count: "<<count<<endl;
	return p;		
}

int rk_matcher(string text, string pattern, int base, int prime){
	int hash = preprocess(pattern, base, prime);
	int n = text.length();
	int m = pattern.length();
	int h = 1;
	int flag;
	for (int i = 1; i < m; i++)
		h = (h*base) % prime;
	int count = 0;
	int t[n+m];
	t[0] = 0;
	for (int i = 1; i <= m; i++){
		count++;
		t[0] = (base*t[0] + charcode(text[i]))%prime;
	}
	for (int s = 0; s < n - m; s++){
		count++;
		if (hash == t[s]){
			for (int j = 1; j <= m; j++){
				count++;
				if (pattern[j] != text[s+j]){
					flag = 1;
					break;
				}
				if (flag == 0) cout<<"Print occurs with valid shift: "<<s<<endl;
			}
		}
		if (s < n - m){
			t[s+1] = (base*(t[s] - charcode(text[s+1]) * h) + charcode(text[s+m+1])) % prime;
			if (t[s+1] < 0) t[s+1] = t[s+1] % prime;
		}
	}
	return count;
}

void compute_prefix(string pattern, int pi[]){
	int m = pattern.length();
	pi[1] = 0;
	int k = 0; 
	int count = 0; 
	for (int q = 2; q <= m; q++){
		count = count + 1;
		while (k>0 and pattern[k+1] != pattern[q]){
			k = pi[k];
			count++;
		}
		if (pattern[k+1] == pattern[q]) k++;
		pi[q] = k; 
	}
	cout<< "Preprocessing count: "<<count<<endl;  
}

int kmp_matcher(string text, string pattern){
	int n = text.length();
	int m = pattern.length();
	int pi[m+1];
	compute_prefix(pattern,pi);
	int count = 0;
	int q = 0; 
	for (int i = 1; i <= n; i++){
		count++;
		while(q > 0 and pattern[q+1] != text[i]){
			q = pi[q];
			count++;
		}
		if (pattern[q+1] == text[i]){
			q = q+1;
			if (q == m){
				cout<< "Pattern occurs with valid shift: "<<i-m<<endl;
				q = pi[q];
			}
		}
	}
	return count;
}

main(){
	string text1, text2, text3;
	string pattern;
	cout<<"For Set 1: "<<endl;
	pattern = "ABABCABAB";
	text1 = "ABABCABABACABABCCABABCCABAB";
	text2 = "ABABABCABABCABABCCABABABCABABABB";
	text3 = "AABABCABCABABCABACABABCABABCABAC";

	cout<< "Comparisons taken for Naive for text1 is: "<< naive(text1, pattern)<< endl;
	cout<< "Comparisons taken for Rabin Karp Algo for text1 is: "<< rk_matcher(text1, pattern, 10, 11)<< endl;
	cout<<"Comparisons taken for KMP algo for text1 is: "<< kmp_matcher(text1, pattern)<< endl;
	
	cout<< "Comparisons taken for Naive for text2 is: "<< naive(text2, pattern)<< endl;
	cout<< "Comparisons taken for Rabin Karp Algo for text2 is: "<< rk_matcher(text2, pattern, 10, 11)<< endl;
	cout<<"Comparisons taken for KMP algo for text2 is: "<< kmp_matcher(text2, pattern)<< endl;
	
	cout<< "Comparisons taken for Naive for text3 is: "<< naive(text3, pattern)<< endl;
	cout<< "Comparisons taken for Rabin Karp Algo for text3 is: "<< rk_matcher(text3, pattern, 10, 11)<< endl;
	cout<<"Comparisons taken for KMP algo for text3 is: "<< kmp_matcher(text3, pattern)<< endl;

	cout<<"\nFor Set 2: "<<endl;
	pattern = "GTXCGGGTXCGTXC";
	text1 = "GTGTXCGGGTXCGTXCGGGTXCGTXCGTCG";
	text2 = "GTXCGGGTXCGTXCGGGGTXCGGGTXCGTXC";
	text3 = "GGGTXCGGGTXCGTXCGGGTXCGGTXCGGGTXCGTXC";

	cout<< "Comparisons taken for Naive for text1 is: "<< naive(text1, pattern)<< endl;
	cout<< "Comparisons taken for Rabin Karp Algo for text1 is: "<< rk_matcher(text1, pattern, 10, 11)<< endl;
	cout<<"Comparisons taken for KMP algo for text1 is: "<< kmp_matcher(text1, pattern)<< endl;
	
	cout<< "Comparisons taken for Naive for text2 is: "<< naive(text2, pattern)<< endl;
	cout<< "Comparisons taken for Rabin Karp Algo for text2 is: "<< rk_matcher(text2, pattern, 10, 11)<< endl;
	cout<<"Comparisons taken for KMP algo for text2 is: "<< kmp_matcher(text2, pattern)<< endl;
	
	cout<< "Comparisons taken for Naive for text3 is: "<< naive(text3, pattern)<< endl;
	cout<< "Comparisons taken for Rabin Karp Algo for text3 is: "<< rk_matcher(text3, pattern, 10, 11)<< endl;
	cout<<"Comparisons taken for KMP algo for text3 is: "<< kmp_matcher(text3, pattern)<< endl;
}
