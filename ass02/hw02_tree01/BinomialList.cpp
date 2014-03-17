#include "BinomialList.h"
#include <iostream>
using namespace std;

void BinomialList::merge(BinomialList *list1){
        //cout << "\nthis binomial merge:";
        //this->print();
        //cout <<"\n given list";
        //list1->print();


        for(int i = (int(list1->getHeader()->size()) -1); i>0;i--){
            //cout << "\nmerge list1node :";
            //list1_node->print();
            for(int j=0; j< (int(this->header->size())); j++){
                Bnode *list1_node = list1->getHeader()->get(i);
                if( list1_node->getDegree() == this->header->get(j)->getDegree()) {

                    Bnode* temp = merge_binomial(list1_node, this->header->get(j));
                    //cout << "\n temp node";
                    //temp->print();
                    this->header->set(j, temp);
                    
                    //cout<< "\npositions:" << i << " " <<j << "size: "<< this->header->size();
                    list1->getHeader()->set( i, list1->getHeader()->get((int (list1->getHeader()->size()))-1));
                    //list1->getHeader()->set((int (list1->getHeader()->size()))-1, list1_node);
                    list1->getHeader()->pop_back();
                    i = (int(list1->getHeader()->size()) -1);
                    //cout <<"\nAfter merging temp";
                    //this->print();
                    //cout << "\nList1:";

                }
            }
        }
        for(int i =0; i<(int(list1->getHeader()->size())); i++){
            this->header->push_back(list1->getHeader()->get(i));
        }
    //cout << "final list1 header";
    //list1->print();
    //cout << "\n Before check Header:";
    //this->print();
    this->check_header();
    //cout << "\n After Merging:";
    //this->print();

}
void BinomialList::check_header(){

    while(true){
        int temp_size = this->header->size();
            
            for(int i = int((this->header->size()))-1; i>0 ; i--){
                for(int j = i-1; j>=0; j--){
                    Bnode *node1 = this->header->get(i);
                    Bnode *node2 = this->header->get(j);
                        if(node1->getDegree() == node2->getDegree()){
                            Bnode *temp = merge_binomial(node1, node2);
     //                           cout << "\ncheck_header:temp:";
                                //temp->print();
                                header->set(j, temp);
                                Bnode* temp1 = header->get(int((this->header->size()))-1);
                                header->set(i, temp1);
                                header->set(int((this->header->size()))-1, node2);
                                header->pop_back();
                                i = int((this->header->size()))-1;
                        }
                }
            }

        if(temp_size == this->header->size())
            break;
    }
    //cout << "\n Return Succesful return:";
}

Bnode* BinomialList::merge_binomial(Bnode* kv1, Bnode* kv2){
        Bnode *max_kv = ( (kv1->getKeyValue()->getKey() > kv2->getKeyValue()->getKey()) ? kv1 : kv2);
        Bnode *min_kv = (( kv1->getKeyValue()->getKey() > kv2->getKeyValue()->getKey()) ? kv2 : kv1);
        Bnode *temp = min_kv->getLeft();
        if(temp)
            temp->setParent(max_kv);
        min_kv->setLeft(max_kv);
        max_kv->setParent(min_kv);
        //min_kv->setDegree(kv1->getDegree() + kv2->getDegree());
        max_kv->setRight(temp);
        if(max_kv->getRight()){
     //       cout << "\n max merge:";
            //min_kv->print();
            //max_kv->print(); max_kv->getLeft()->print() ; max_kv->getRight()->print();
            max_kv->setDegree(max_kv->getLeft()->getDegree() + max_kv->getRight()->getDegree() +1);
            
            }
        min_kv->setDegree(max_kv->getDegree() +1);
        return min_kv;
}

VectorBnode* BinomialList::getHeader(){
   // cout << "\n return printing the vector pushed" << this->header.get(0);
    return this->header;
}

void BinomialList::delete_node(){
    //cout<< "Before delete:";
    //this->print();
    Bnode* to_delete = this->getHeader()->get(0) ;
    int index =0;
    int key = this->getHeader()->get(0)->getKeyValue()->getKey();
    for(int i = 0; i< this->getHeader()->size(); i++){
        if(key >= this->getHeader()->get(i)->getKeyValue()->getKey()){
            key = this->getHeader()->get(i)->getKeyValue()->getKey();
            index = i;
            to_delete = this->getHeader()->get(i);
        }
    }
    //cout<< "\n Deleting key:" << to_delete->getKeyValue()->getKey(); 
    if(to_delete->getLeft()!=NULL){
        Bnode * left_to_del = to_delete->getLeft();
        Bnode * right_to_left_to_del = NULL;
        if(left_to_del->getRight()!=NULL){
            right_to_left_to_del= left_to_del->getRight();
        }
        left_to_del->setRight(NULL);
        left_to_del->setParent(NULL);
        if (right_to_left_to_del){
            left_to_del->setDegree(left_to_del->getLeft()->getDegree() +1);
        }
        this->getHeader()->push_back(left_to_del);
        recursive_delete(right_to_left_to_del);
    }
    this->getHeader()->set(index, this->getHeader()->get(this->getHeader()->size()-1));
    this->getHeader()->pop_back();
    //cout<<"\n before check header";
    //cout << this->getHeader()->size();
    //this->print();
    this->check_header();
    //cout<< "Printing after delete:";
    //this->print();
    
}

void BinomialList::recursive_delete(Bnode* right_to_left_to_del){
            if(right_to_left_to_del!=NULL){
            recursive_delete(right_to_left_to_del->getRight());
                    if(right_to_left_to_del->getRight() == NULL and right_to_left_to_del->getLeft() == NULL)
                        right_to_left_to_del->setDegree(1);
                    else
                        right_to_left_to_del->setDegree(right_to_left_to_del->getLeft()->getDegree() + 1);
            right_to_left_to_del->getParent()->setRight(NULL);
            right_to_left_to_del->setParent(NULL);
            this->getHeader()->push_back(right_to_left_to_del);
            }
}
void BinomialList::add_to_binomial(IKeyValue *kv){
    Bnode *bnode = new Bnode(kv);
    this->header->push_back(bnode);
    //cout << "\nprinting the vector pushed" << this->header.get(0);
}

void BinomialList::print(){
    //cout << "\nheader print";
    for(int i=0; i< int(this->header->size()); i++){
        Bnode* temp = this->header->get(i);
        temp->print();
    }
}
