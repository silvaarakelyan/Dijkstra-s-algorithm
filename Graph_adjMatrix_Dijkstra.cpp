#include<iostream>
using namespace std;
#define INFINITY 9000;

//this is the implemenataion of Dijkstras algorithm by using adj. matirx
// here my goal is to show how Dijkstras algorithm works, so the main part is concentraited on it
class Dijkstra{
    
    private:
    int numOfVertices;
    int adjMatrix[10][10];
    int *predecessor;
    int *distance;
    bool *visited; //keep track of visited node
    int source;
    
    public:
	//this function is for constructing adj. matrix and getting the vertex (source) from which it must calculate shortest paths
	void read(); 

	//this is like a preparation for calculating shortest distances
    void initialize();

    //if node isnt visited returns the node which is nearest from the Predecessor marked node
    int getClosestUnmarkedNode();

    //caluculate min distance from source node to all the other nodes
    void calculateDistance();

    //print results of dijkstras algorithm
    void output();

    //print the shortest path from vertex to all the nodes
    void printPath(int);
};    

void Dijkstra::read(){
    cout<<"Enter the number of vertices of the graph(should be positive)\n";
    cin>>numOfVertices;

    while(numOfVertices <= 0) {
        cout<<"Enter the number of vertices of the graph(should be positive )\n";
        cin>>numOfVertices;
    }


    cout<<"Enter the adjacency matrix for the graph"<<endl;
    cout<<"To enter infinity enter INFINITY (9000) "<<endl;
    for(int i=0;i<numOfVertices;i++) {
        cout<<"Enter the positive weights for the row "<<i<<endl;
        for(int j=0;j<numOfVertices;j++) {
            cin>>adjMatrix[i][j];
            while(adjMatrix[i][j]<0) {
                cout<<"Weights should be +ve. Enter the weight again\n";
                cin>>adjMatrix[i][j];
            }
        }
    }
    cout<<"Enter the source vertex\n";
    cin>>source;
    while((source<0) && (source>numOfVertices-1)) {
        cout<<"Source vertex should be between 0 and"<<numOfVertices-1<<endl;
        cout<<"Enter the source vertex again\n";
        cin>>source;
    }
}
 



//here we initialize a distance of all the vertexes as infinity-s and for source vertex 0
void Dijkstra::initialize(){
    predecessor=new int[numOfVertices];
    distance=new int[numOfVertices];
    visited=new bool[numOfVertices];

    for(int i=0;i<numOfVertices;i++) {
        visited[i] = false;
        predecessor[i] = -1;
        distance[i] = INFINITY;
    }
    distance[source]= 0;
}

//by this function we get the min distace which we have
//So in the first step this returns source node 
int Dijkstra::getClosestUnmarkedNode(){
    int minDistance = INFINITY;
    int closestUnmarkedNode;
    
    for(int i=0;i<numOfVertices;i++) 
    {
        if((!visited[i]) && ( minDistance >= distance[i])) {
            minDistance = distance[i];
            closestUnmarkedNode = i;
        }
    }
    return closestUnmarkedNode;
}
 
void Dijkstra::calculateDistance(){
    initialize();
    //int minDistance = INFINITY;
    int closestUnmarkedNode;
    int count = 0;
    while(count < numOfVertices) {
        closestUnmarkedNode = getClosestUnmarkedNode();
        visited[closestUnmarkedNode] = true;
        for(int i=0;i<numOfVertices;i++) {
            if((!visited[i]) && (adjMatrix[closestUnmarkedNode][i]>0) ) {
                if(distance[i] > distance[closestUnmarkedNode]+adjMatrix[closestUnmarkedNode][i]) {
                    distance[i] = distance[closestUnmarkedNode]+adjMatrix[closestUnmarkedNode][i];
                    predecessor[i] = closestUnmarkedNode;
                }
            }
        }
        count++;
    }
}
 
//recursive function which prints the path 
void Dijkstra::printPath(int node){
    if(node == source)
        cout<<(char)(node + 97)<<"..";
    else if(predecessor[node] == -1)
        cout<<"No path from “<<source<<”to "<<(char)(node + 97)<<endl;
    else {
        printPath(predecessor[node]);
        cout<<(char) (node + 97)<<"..";
    }
}
 
 
void Dijkstra::output(){
    for(int i=0;i<numOfVertices;i++) {
        if(i == source)
            cout<<(char)(source + 97)<<".."<<source;
        else
            printPath(i);
        cout<<"->"<<distance[i]<<endl;
    }
}

int main(){
	Dijkstra g;
	g.read();
	g.calculateDistance();
	g.output();
	system("pause");
	
}



