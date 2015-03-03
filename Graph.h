#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <set>
#define Vertex int
#define INF 999999999
using namespace std;


class Edge{
private:
    Vertex A;
    Vertex B;
    int capacity;
    int flow;

public:
    Edge(){
        A = -1;
        B = -1;
        capacity = -1;
        flow = 0;
    }

    Edge(Vertex A, Vertex B, int capacity, int flow){
        this->A = A;
        this->B = B;
        this->capacity = capacity;
        this->flow = flow;
    }

    void init(Vertex A, Vertex B, int capacity, int flow){
        this->A = A;
        this->B = B;
        this->capacity = capacity;
        this->flow = flow;
    }

    Vertex getA(){  return A;   }
    Vertex getB(){  return B;   }
    
    
    void setCapacity(int c){
        capacity = c;
    }

    int getCapacity(){
        return capacity;
    }

    void setFlow(int f){
        flow = f;
    }

    int getFlow(){
        return flow;
    }
};

class Path: public vector<Edge>{
private:
    bool valid;
public:

    Path(){
        valid = false;
    }

    long getFlow(){
        long flow = INF;
        for(int i=0; i<this->size(); i++){
            if( flow > this->at(i).getCapacity() - this->at(i).getFlow() ){
                flow = this->at(i).getCapacity() - this->at(i).getFlow();
            }
        }
        return flow;
    }

    void setValidation(bool v){
        valid = v;
    }

    bool isValid(){
        return valid;
    }

};

class Graph{
private:
    int vertexNum;
    vector<Edge> argPath;
    Edge **graph;


public:
    Graph(int vertexNum){
        this->vertexNum = vertexNum;

        graph = new Edge* [vertexNum];
        for(int i=0; i<vertexNum; i++){
            graph[i] = new Edge [vertexNum];
        }

        argPath.clear();
    }

    ~Graph(){
        for(int i=0; i<vertexNum; i++){
            delete [] graph[i];
        }
        delete [] graph;
    }


    void init(){
        int capacity;
        for(int i=0; i<vertexNum; i++){
            for(int j=0; j<vertexNum; j++){
                cin >> capacity;
                graph[i][j].init( i, j, capacity, 0 );
            }
        }
    }


    void setFlow(Vertex a, Vertex b, int flow){
        graph[a][b].setFlow(flow);
    }

    int getFlow(Vertex a, Vertex b){
        return graph[a][b].getFlow();
    }


    //NOT finish yet
    Path findArgumentPath(Vertex s, Vertex t){

        set<Vertex> visit;
        vector<Vertex> vec;
        visit.insert(s);
        vec.push_back(s);


        int startNum = 0;
        while(!vec.empty()){
            Vertex v = vec.back();

            //  arrive the end
            if(v == t){
                break;
            }

            bool canFind = false;
            for(int i=startNum; i<vertexNum; i++){
                if(visit.find(i)==visit.end() && graph[v][i].getCapacity() - graph[v][i].getFlow() > 0){
                     visit.insert(i);
                     vec.push_back(i);
                     canFind = true;
                     break;
                }
            }

            if(!canFind){
                vec.pop_back();      //  remove the "v" from vec
                visit.erase(v); //  remove the "v" from visit
                startNum = v+1; //  
            }
            else{
                startNum = 0;
            }
        }



        //  find the argument path
        Path path;

        if(!vec.empty()){
            
            for(int i=0; i<vec.size()-1; i++){
                Vertex a = vec[i];
                Vertex b = vec[i+1];
                Edge edge(a, b, graph[a][b].getCapacity(), graph[a][b].getFlow());
                path.push_back(edge);
            }

            path.setValidation(true);
        }
        //  CANNOT find the argument path
        else{
            path.setValidation(false);
        }

        return path;
    }

    int getNum(){
        return vertexNum;
    }

};


#endif
