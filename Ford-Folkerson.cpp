#include <iostream>
#include "Graph.h"
using namespace std;

int FF(Graph *G, Vertex s, Vertex t);

int main(){

    int vertexNum;
    cin >> vertexNum;
    Graph *G = new Graph(vertexNum);
    G->init();

    Vertex s = 0;
    Vertex t = vertexNum-1;

    int maxflow = FF(G, s, t);

    cout << "Maxflow: " << maxflow <<endl;

    delete G;
    return 0;
}

int FF(Graph *G, Vertex s, Vertex t){

    Path argPath = G->findArgumentPath(s,t);

    while(argPath.isValid()){
        int cf_p = argPath.getFlow();
        for(int i=0; i<argPath.size(); i++){
            Edge edge = argPath.at(i);
            G->setFlow(edge.getA(), edge.getB(), G->getFlow(edge.getA(), edge.getB()) + cf_p );
            G->setFlow(edge.getB(), edge.getA(), -1 * G->getFlow(edge.getA(), edge.getB()) );
        }

        argPath = G->findArgumentPath(s,t);
    }

    int sum = 0;
    for(int i=0; i<G->getNum(); i++){
        sum += G->getFlow(i, t);
    }


    //----------------------------
    for(int i=0; i<G->getNum(); i++){
        for(int j=0; j<G->getNum(); j++){
            cout << G->getFlow(i,j)<<"\t";
        }
        cout<<endl;
    }
    
    //----------------------------

    return sum;
}
