#include<iostream>
using namespace std;
class node{
    public:
        node *next;
        int x;

        void setValue(int value){
            this->x = value;
        }

        int getValue(){
            return x;
        }

        node* getNext(){
            return this->next;
        }

        void setNext(node* next){
            this->next = next;
        }
        };

class llist{
    public:
        node* head;
        llist(){
        head = NULL;
        }

        node* getHead(){
            return head;
        }

        void setHead(node* head){
            this->head = head;
        }

        void addHead(int value){
            node *n = new node();
            n->setValue(value); 
            //first time head assigning
            if(this->head == NULL)
                n->setNext(NULL);
            else
                n->setNext(this->head); 
            head = n;
            cout<< "head is " << head << "\n";
        }

};

int main(){
    llist l;
    l.addHead(1);
    l.addHead(2);

    node* head = l.getHead();

    while(head !=NULL){
        cout << head->getValue();
        head = head->getNext();
    }

    
    return 1;
}

