#include "PriorityQueue2.h"
#include "VectorKeyValue.h"
#include "VectorString.h"
#include <iostream>
#include <string>
using namespace std;


void PriorityQueue2::enqueue(IKeyValue * key_value){
    int key = key_value->getKey();
   // std:://cout <<"\ninsert key :"<< key << " ";

    node* node_new= new node();
    node_new->key = key;
    node_new->words->push_back(key_value->getValue());
    if (nodes->size() == 1 ) {
  //      std:://cout << "2pushing key "<< key << "@ position"<< nodes.size();
        nodes->push_back(node_new);
        return;
    }
    if(recursive_insert(key_value, 1))
        return;
    //std:://cout << "pushing key "<< key << "@ position"<< nodes->size() << " head now ";
    //cout << nodes->get(1).key;
    nodes->push_back(node_new);
    //cout << "\n vector print \t";
    for(int i = 1; i < nodes->size(); i++){
        //cout<< i<<"\t"<< nodes->get(i).key <<"\t\t ";
        }
    
    int k= ((int) nodes->size())-1;
    if(parent(k)){
        while(parent(k)>=1 and nodes->get(parent(k))->key > key){
            node *temp = nodes->get(parent(k));
            /*
            temp.key = nodes->get(parent(k)).key;
            temp.words = nodes->get(parent(k)).words;
            */
            //cout << "words inside" << temp.key << " " << k;
            nodes->set(parent(k),node_new );
            nodes->set(k, temp);
        //cout << "\n enqueue print \t";
        for(int i = 1; i < nodes->size(); i++){
            //cout<< i<<"\t"<< nodes->get(i).key <<"\t\t ";
            }
            if(parent(parent(k))){
                k = parent(k);
            }
            else{
                return;
            }
        }
    }
    //not added to the list
}

bool PriorityQueue2::recursive_insert(IKeyValue * key_value, int i){
    int key = key_value->getKey();
        ////cout << "\nrecur node key" << nodes->get(i).key<< " i " << i<< "key :"<< key;
        if(nodes->get(i)->key == key){
         //   //cout << "3recurpushing key "<< key << "@ position "<< i;
            nodes->get(i)->words->push_back(key_value->getValue());
            return true;
        }
        if (left(i) and key >= nodes->get(left(i))->key){
           // //cout << "left" << left(i) << nodes->get(left(i)).key << " ";
            if(recursive_insert(key_value, left(i)))
                return true;
        }
        if (right(i) and key >= nodes->get(right(i))->key){
            ////cout << "right" << right(i) << nodes->get(right(i)).key << " ";
            if (recursive_insert(key_value, right(i)))
                return true;
        }
        return false;
}
int PriorityQueue2::left(int i){
    return (2*i <= (int) (nodes->size()-1) ? 2*i : 0);
}
int PriorityQueue2::right(int i){
    return (2*i+1 <= (int) (nodes->size()-1) ? 2*i+1 : 0);

}
    
int PriorityQueue2::parent(int i){
    return (i/2 >= 1 ? i/2 : 0);

}
void PriorityQueue2::merge(IPriorityQueue * input_queue){
}

IVectorKeyValue* PriorityQueue2::returnSorted(){
}

int PriorityQueue2::lowestKey(){
    ////cout<< "lowest key" << nodes->get(1).key;
    return nodes->get(1)->key;
}

IVectorString* PriorityQueue2::lowestValues(){
    IVectorString *x = new VectorString();
    for(int i = 0; i < int(nodes->get(1)->words->size()); i++){
        x->push_back(nodes->get(1)->words->get(i));
    }
    return x;
}

void PriorityQueue2::dequeue(){
   // //cout << "\n vector print \t";
   // for(int i = 1; i < nodes->size(); i++){
   //     //cout<< i<<"\t"<< nodes->get(i).key <<"\t\t ";
   // }
    nodes->set(1, nodes->get(nodes->size()-1));
    nodes->pop_back();
    heapify(1);
    ////cout << "\n vector print \t";
   // for(int i = 1; i < nodes->size(); i++){
    //    //cout<< i<<"\t"<< nodes->get(i).key <<"\t\t ";
   // }
}

void PriorityQueue2::heapify(int i){
    if(nodes->size() == 1)
        return;
    for(int i=1; i < (int) nodes->size(); ){
        int key = nodes->get(i)->key;
        if(i==0)
            break;
        int min=0;
     //   //cout << "\nleft(i)"<< left(i)<< " "<<key ;
        if(left(i)){
            min = left(i);
            if(right(i)){
      //          //cout << "\nright(i)"<< right(i);
                min = (nodes->get(left(i))->key < nodes->get(right(i))->key) ? left(i) : right(i);
                }
            if( key > nodes->get(min)->key){
       //         //cout << "\n swapping"<< min << " " << i;
                node *temp = nodes->get(i);
                //temp.key = nodes->get(i)->key;
                //temp.words = nodes->get(i)->words;
                nodes->set(i,nodes->get(min));
                nodes->set(min,temp);
            }
        }
                    i = min;
    }
    }
    /*
    if (left(i) and right(i)){
       int min = (nodes->get(left(i)).key < nodes->get(right(i)).key) ? left(i) : right(i); 
       if( nodes->get(i).key > min){
            //exchange min and i
            node temp;
            temp.key = nodes->get(i).key;
            temp.words = nodes->get(i).words;
            nodes->set(i,nodes->get(min));
            nodes->set(min,temp);
            heapify(min);
       }
    }
    if(not right(i)){
            if(nodes->get(left(i)).key > min){
            //exchange min and i
            node temp;
            temp.key = nodes->get(i).key;
            temp.words = nodes->get(i).words;
            nodes->set(i,nodes->get(min));
            nodes->set(min,temp);
            heapify(min);
            }
    }
}
*/

size_t PriorityQueue2::size(){
    return nodes->size()-1;
}


