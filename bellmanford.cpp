#include <iostream>
#include <iomanip>
using namespace std;
struct node{
	int from; 
	int to; 
	int weight;
	node* next;
};
struct vnode{
	string name; 
	int d;
	int pi;
};
class graph{
	int n, m;
	vnode vertex[10];
	node* elist;
	public:
		void creategraph(){
			cout<<"Enter the number of vertices in the graph: ";
			cin>>n;
			for (int i = 1; i<=n; i++){
				cout<<"Enter the edge name: ";
				cin>>vertex[i].name;
			}
			cout<<"Enter the number of edges: ";
			cin>>m;
			elist = NULL;
			node* last = NULL;
			for (int j = 1; j<=m; j++){
				node* t = new node;
				cout<<"From: ";
				cin>>t->from;
				cout<<"To: ";
				cin>>t->to;
				cout<<"Edge Weight: ";
				cin>>t->weight;
				t->next = NULL;
				if (last == NULL){
					elist = t;
					last = t;
				}
				else 
					last->next = t;
				last = t;
			}
		}

		void initialize_single_source(int s){
			for (int i = 1; i<=n; i++){
				vertex[i].d = 100000;
				vertex[i].pi = 0;
			}
			vertex[s].d = 0;
		}
		
		void relax(int u, int v, int weight){
			if (vertex[v].d > (vertex[u].d + weight)){
				vertex[v].d = vertex[u].d + weight;
				vertex[v].pi = u;
			}
		}
		
		bool bellman_ford(int s){
			initialize_single_source(s);
			for (int i = 1; i<=n-1; i++){
				node* t = elist;
				while (t != NULL){
					relax(t->from, t->to, t->weight);
					t = t->next;
				}
			}
			node* t = elist;
			while (t != NULL){
				if (vertex[t->to].d > vertex[t->from].d + t->weight) return false;
				t = t->next;
			}
			return true;
		}
		
		void print_shortest_path(int i, int j){
			if (i == j)
				cout<<i;
			else if (vertex[j].pi < 0)
				cout<< "No path exists from "<<vertex[i].name<< " to " <<vertex[j].name;
			else{
				print_shortest_path(i, vertex[j].pi);
				cout<<"-->"<<j;
			}
		}
		
		void display(){
			cout<<setiosflags(ios::right);
			cout<<setw(8)<<"Vertex Index"<<setw(8)<<"Vertex"<<setw(9)<<"Distance"<<setw(8)<<"Parent"<<endl;
			for (int i = 1; i<=n; i++)
				cout<<setw(8)<<i<<setw(8)<<vertex[i].name<<setw(8)<<vertex[i].d<<setw(8)<<vertex[i].pi<<endl;
			for (int i = 2; i<=n; i++){
				cout<<"Shortest Path from 1 to "<<i<<" is: ";
				print_shortest_path(1,i);
				cout<<endl;			
			}
		}

};

int main(){
	graph g; 
	g.creategraph();
	bool flag = g.bellman_ford(1);
	if (flag == true) g.display();
	else cout<<"Graph contains negative valued cycle"<<endl;
}
 
			
