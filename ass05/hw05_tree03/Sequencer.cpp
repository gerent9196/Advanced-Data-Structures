#include "Sequencer.h"
#include <iostream>
#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "string.h"
#include "Vertex.h"
#include "TSPNode.h"

using namespace std;

IGraph *  Sequencer::buildGraph(std::vector<std::string>& reads){
    IGraph * graph = new Graph();
    graph->insertVertex(reads.at(0));
    for(int i = int(reads.size() - 1);i>0 ; i-- ){
        for(int j = i-1; j>=0; j--){
            if( reads.at(i).compare(reads.at(j)) == 0){
                break;
            }
            if(j == 0){
                graph->insertVertex(reads.at(i));
            }
        }
    } 

    std::vector<IVertex *> graph_vertices = graph->getVertices();
    int size_graph_vertices = graph_vertices.size();
    int max_overlap = 0;
    for(int i=0; i< size_graph_vertices; i++){
       for(int j=0; j< size_graph_vertices; j++){
            //find overlap
            if(i != j){
                int overlap = 0;
                for(int k = 0; k< graph_vertices.at(i)->getName().size(); k++){
                    int l = 0;
                    int count = 0;
                    int m = k;
                    while( graph_vertices.at(i)->getName()[m] == graph_vertices.at(j)->getName()[l] ){
                       m++;
                       l++; 
                       count++;
                    }   
                   if(count > overlap){
                        overlap = count;
                    }
                }
            if(max_overlap < overlap){
               max_overlap = overlap; 
            }
            if(overlap>0){
            IEdge *edge = new Edge();
            edge->setTarget(graph_vertices.at(j));
            edge->setWeight(overlap);
            graph_vertices.at(i)->addEdge(edge);
            }
            }
        } 
    }

    for(int i=0; i< size_graph_vertices; i++){
       IVertex* vert = graph_vertices.at(i);
       for(int j =0; j < vert->getEdges().size(); j++){
            IEdge * edg = vert->getEdges()[j];
            int wt = max_overlap - edg->getWeight();
            edg->setWeight(max_overlap - edg->getWeight());
        }     
    }
    return graph;
}
std::vector<std::string>  Sequencer::tsp(std::string start_read, IGraph * graph){
    std::vector<TSPNode *> priority_queue;

    IVertex* vert = NULL;
    for(int i=0; i< graph->getVertices().size(); i++){
        if(graph->getVertices()[i]->getName().compare(start_read) == 0){
           vert = graph->getVertices()[i]; 
           break;
        }
    }
    TSPNode *initial_node = new TSPNode(vert);
    priority_queue.push_back(initial_node);
    int min_bound = 44435;
    std::vector<IVertex*> min_path;
    while(priority_queue.size() != 0){
/*
       cout<<"\n Priority Queue Entries:";

       for(int pr_count =0; pr_count < (priority_queue.size()); pr_count++){
           cout <<"\nweight: "<< priority_queue[pr_count]->weight;
           for(int k=0; k< priority_queue[pr_count]->path.size(); k++){
                cout << "\t"<< priority_queue[pr_count]->path[k]->getName();
            }
        }
*/

       //sort the priority queue by weight
       int pr_weight = priority_queue[0]->weight;
       int pr_index = 0;
       TSPNode *temp;
       for(int pr_count =1; pr_count < (priority_queue.size()); pr_count++){
            if(priority_queue[pr_count]->weight < pr_weight){
               pr_weight = priority_queue[pr_count]->weight;
               pr_index = pr_count; 
            } 
        }
       TSPNode *curr = priority_queue[pr_index];
       priority_queue[pr_index] = priority_queue[priority_queue.size() -1];
       priority_queue.pop_back();
        
       int curr_bound = curr->weight;
       //int other_bound = calculate_other_bound(curr->path, graph);
       //cout<< "\n curr bound:"<< curr_bound;
       //cout <<"\n other bound:"<< other_bound;
      // cout << "\n pr qu:"<< priority_queue.size();

       if(curr_bound < min_bound){
            IVertex *last_vertex = curr->path[curr->path.size() -1];
            std::vector<IEdge*> last_vertex_edges = last_vertex->getEdges();
            for(int edge_count =0; edge_count< last_vertex_edges.size(); edge_count++){
                bool in_path = false;
                for(int path_count =0; path_count<curr->path.size(); path_count++){
                    if(last_vertex_edges[edge_count]->getTarget()->getName().compare(curr->path[path_count]->getName()) == 0){
                    in_path= true;
                    }
                }
                //if not in path do the nex step
                if(not in_path){
                    TSPNode * new_node = new TSPNode();
                    new_node->start = last_vertex;
                    new_node->path = curr->path;
                    new_node->path.push_back(last_vertex_edges[edge_count]->getTarget());
                    new_node->weight = (curr->weight + (last_vertex_edges[edge_count]->getWeight()));
                    if(new_node->path.size() == graph->getVertices().size()){
                        if(new_node->weight < min_bound){
                            //cout<< "\n min bound:"<< new_node->weight;
                            min_bound = new_node->weight;
                            min_path = new_node->path;
                            std::vector<string> final;
                            for(int c = 0; c< min_path.size(); c++){
                                    final.push_back(min_path[c]->getName()); 
                                }
                            final.push_back(start_read);
                            return final;
                        }
                    }
                    else{
                        priority_queue.push_back(new_node);
                    }
                }
            }
        }
    } 
    std::vector<string> final;
    for(int c = 0; c< min_path.size(); c++){
            final.push_back(min_path[c]->getName()); 
        }
    final.push_back(start_read);

    return final;
}

int Sequencer::calculate_other_bound(std::vector<IVertex *>& path, IGraph * graph){
    std::vector<std::string> visited_node;
    std::vector<int> visited_node_weight;
    for(int i=0; i<path.size(); i++){
        //get start vertex of this path
        IVertex * vert = path[i];
        std::vector<IEdge *> edges = vert->getEdges();
        for(int k=0; k<edges.size(); k++){
            //edges should not be in path
            bool in_path = false;
            bool in_visited = false;
            string vertex = edges[k]->getTarget()->getName();
            for(int path_index = 0; path_index < path.size(); path_index++){
                if(vertex.compare(path[path_index]->getName()) == 0){
                    in_path = true;
                    break;
                }
            }
            //edges should not be in visited_node
            for(int visited_index =0; i< visited_node.size(); i++){
                if(vertex.compare(visited_node[visited_index]) == 0){
                    in_visited = true;
                    if(visited_node_weight[visited_index] > (edges[k]->getWeight()))
                        visited_node_weight[visited_index] = (edges[k]->getWeight());
                    break;
                }
            }
           if(in_path == true || in_visited == true)
                continue;
           else{
                visited_node.push_back(vertex);
                visited_node_weight.push_back(edges[k]->getWeight());
            }


        }
    }

    int sum =0;
    for(int m=0; m< visited_node_weight.size(); m++){
        sum = sum+ visited_node_weight[m]; 
        }
    return sum;
}

std::string  Sequencer::assemble(std::vector<std::string>& tsp_result){

    std::string final = tsp_result[0];
    for(int tsp_c=1; tsp_c < tsp_result.size(); tsp_c++){


        int count=0;
        int ind = 0;
        for(int str_in =final.size()-10; str_in < final.size(); str_in++){
            int lc=0;
            int m = 0;
            int l= str_in;
            while(tsp_result[tsp_c][m] == final[l]){
                   lc++; 
                   m++;
                   l++;
            }
        
            if( l==final.size() and lc >= count){
                count = lc;
                ind = str_in;
            }
        }
        final.replace(ind,tsp_result[tsp_c].size(),tsp_result[tsp_c]);
    }
    return final;
}
