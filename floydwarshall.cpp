#include<iostream>
#include<iomanip>
using namespace std;
int INT_MAX = 100000;
int INT_MIN = -100000;
class Floyd_Warshall{
	int w[10][10],d[10][10],pi[10][10];
	int noV,noE;
	
	public:
		void initialize(int Mat[][5]){
			for(int i=0;i<5;i++){
		 		for(int j=0;j<5;j++)
		 			w[i][j]=Mat[i][j];
	     		}
		}
		void get(){
			cout<<"Enter the number of Vertices: ";
			cin>>noV;		 
			for(int i=0;i<noV;i++){
				for(int j=0;j<noV;j++)
					d[i][j]=w[i][j];
			}
			for(int i=0;i<noV;i++){
				for(int j=0;j<noV;j++){
					if(i==j || w[i][j]==INT_MAX)
				 		pi[i][j]=INT_MIN;
					else
				 		pi[i][j]=i;
			    	}
			}  
		}
		void display(){
			cout<<"\nWeight matrix: \n";
			setiosflags(ios::right);
			for(int i=0;i<noV;i++){
			 	for(int j=0;j<noV;j++)
			 		cout<<setw(12)<<w[i][j];
			 	cout<<endl;
		    	}
		    	cout<<"\nDistance matrix: \n";
			for(int i=0;i<noV;i++){
			 	for(int j=0;j<noV;j++)
			 		cout<<setw(12)<<d[i][j];
			 	cout<<endl;
		    	}
		    	cout<<"\nP matrix: \n";
			for(int i=0;i<noV;i++){
			 	for(int j=0;j<noV;j++)
			 		cout<<setw(12)<<pi[i][j];
			 	cout<<endl;
		    	}
   		}

	   	void floydWarshall(){
	   		for(int k=0;k<noV;k++){
		   		for(int i=0;i<noV;i++){
		   			for(int j=0;j<noV;j++){
		   				if(pi[i][k]!=INT_MIN && pi[k][j]!=INT_MIN && d[i][j]>(d[i][k]+d[k][j])){
		   					d[i][j]=d[i][k]+d[k][j];
		   					pi[i][j]=pi[k][j];
						}
					}
		   		}
	    		} 
	   	}

   		void Print_All_Pairs_ShortestPath(){
      			for(int i=0;i<noV;i++){
				for(int j=0;j<noV;j++){ 
					Print_ShortestPath(i,j);
		  			cout<<endl;
	      			}
	      			cout<<endl;
			}
   		}

   		void Print_ShortestPath(int i,int j){
   			if (i==j)
   				cout<<i;
   			else if (pi[i][j]==INT_MIN)
				cout<<"No path from "<<i <<" to "<<j<<" exists\n";
   			else{
	 			Print_ShortestPath(i,pi[i][j]);
	 			cout<<"->"<<j;
	 		}  	
	   
   		}
};
int main(){
	Floyd_Warshall obj;
	int w[][5]={
			{0,3,8,INT_MAX,-4},
			{INT_MAX,0,INT_MAX,1,7},
			{INT_MAX,4,0,INT_MAX,INT_MAX},
			{2,INT_MAX,-5,0,INT_MAX},
			{INT_MAX,INT_MAX,INT_MAX,6,0},
		   };	
	obj.initialize(w);	        	  
	obj.get();
	obj.display();	
	obj.floydWarshall();
	obj.display();
	obj.Print_All_Pairs_ShortestPath();
}
