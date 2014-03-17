#include "AVLTree.h"
#include <iostream>
#include <vector>
using namespace std;

void AVLTree::insert(int key){
    IAVLTreeNode* new_node = new AVLTreeNode(key);
    if (root == NULL){
       root = new_node; 
       return;
    }
    IAVLTreeNode* temp_root = root;
    std::vector <IAVLTreeNode*> path;
    std::vector <int> path_Bf;
    
    //insert iteratively
    while(temp_root!=NULL){
        path.push_back(temp_root);
        path_Bf.push_back(0);
        if( key > temp_root->getKey()){
            //should be on the right side
            temp_root = temp_root->getRight();
        }
        else{ 
            //should be on the left side
            temp_root = temp_root->getLeft();
        }
    }
    if (path.at(path.size()-1)->getKey() > key){  
        //add to the left
        path.at(path.size()-1)->setLeft(new_node);
    }
    else{
        //add to the right
        path.at(path.size()-1)->setRight(new_node);
    }
   for(int i=int(path.size())-1; i>=0; i--){
        int h = diffHeight(path.at(i));
        path_Bf[i] = h;
        if(h ==2) {
            if(path_Bf.at(i+1) == 1){   
            // 2,1 combination;
                if(i==0){   
                    rightLeftRotate(NULL, path.at(i));
                } else{
                    rightLeftRotate(path.at(i-1), path.at(i));
                }
                //print(root);
            }
            else{
            // 2,-1 combination
                rightRightRotate(path.at(i));
                if(i==0){   
                    rightLeftRotate(NULL, path.at(i));
                } else{
                    rightLeftRotate(path.at(i-1), path.at(i));
                }
            }
        }
        if(h == -2) {
            if(path_Bf.at(i+1) == 1){   
            // -2,1 combination;
                leftLeftRotate(path.at(i));
                if(i==0){   
                    leftRightRotate(NULL, path.at(i));
                } else{
                    leftRightRotate(path.at(i-1), path.at(i));
                }
                //print(root);
            }
            else{
                if(i==0){   
                    leftRightRotate(NULL, path.at(i));
                } else{
                    leftRightRotate(path.at(i-1), path.at(i));
                }
            }
        }
    } 
}


void AVLTree::print(IAVLTreeNode* temp){
    if(temp == NULL)
        return;
    print(temp->getLeft());
    print(temp->getRight());
}
void AVLTree::remove(int key){
    IAVLTreeNode* temp_root = root;
    std::vector <IAVLTreeNode*> path;
    std::vector <int> path_Bf;
    
    //check iteratively
    while(temp_root!=NULL){
        path.push_back(temp_root);
        path_Bf.push_back(0);
        if( key == temp_root->getKey() ){
            break;
        }
        else if( key > temp_root->getKey()){
            //should be on the right side
            temp_root = temp_root->getRight();
        }
        else{ 
            //should be on the left side
            temp_root = temp_root->getLeft();
        }
    }
    //if its the leaf node
    path.pop_back();
    IAVLTreeNode* prev = path.at(int(path.size()-1));
    if (temp_root->getLeft()==NULL && temp_root->getRight() == NULL) {
        if( prev->getLeft() == temp_root){
            prev->setLeft(NULL);
        }
        else {
            prev->setRight(NULL);
        }
        delete temp_root;
    }
            // has only one child
    else if( temp_root->getLeft() == NULL){
        if( prev->getLeft() == temp_root){
            prev->setLeft(temp_root->getRight());
        }
        else {
            prev->setRight(temp_root->getRight());
        }
    }
    else if ( temp_root->getRight() == NULL) {
        if( prev->getLeft() == temp_root){
            prev->setLeft(temp_root->getLeft());
        }
        else {
            prev->setRight(temp_root->getLeft());
        }
        delete temp_root;  
    }
    //its not the leaf node, find left most node's right most
    else {
    IAVLTreeNode* left_of_to_del = temp_root->getLeft();
    if (left_of_to_del->getRight() == NULL){
        left_of_to_del->setRight(temp_root->getRight());
        if( prev->getLeft() == temp_root){
            prev->setLeft(left_of_to_del);
        }
        else {
            prev->setRight(left_of_to_del);
        }
        delete temp_root;
    }
    else{
        path.push_back(temp_root);
        path_Bf.push_back(0);
        while(left_of_to_del->getRight()!= NULL){
            path.push_back(left_of_to_del);
            path_Bf.push_back(0);
            left_of_to_del = left_of_to_del->getRight();
        }
        temp_root->setKey(left_of_to_del->getKey());
        delete left_of_to_del;
    }
    }

   for(int i=int(path.size())-1; i>=0; i--){
        int h = diffHeight(path.at(i));
        path_Bf[i] = h;
        if(h ==2) {
            if(path_Bf.at(i+1) == 1){   
            // 2,1 combination;
                if(i==0){   
                    rightLeftRotate(NULL, path.at(i));
                } else{
                    rightLeftRotate(path.at(i-1), path.at(i));
                }
           //     //print(root);
            }
            else{
            // 2,-1 combination
                rightRightRotate(path.at(i));
                if(i==0){   
                    rightLeftRotate(NULL, path.at(i));
                } else{
                    rightLeftRotate(path.at(i-1), path.at(i));
                }
            }
        }
        if(h == -2) {
            if(path_Bf.at(i+1) == 1){   
            // -2,1 combination;
                leftLeftRotate(path.at(i));
                if(i==0){   
                    leftRightRotate(NULL, path.at(i));
                } else{
                    leftRightRotate(path.at(i-1), path.at(i));
                }
                //print(root);
            }
            else{
                if(i==0){   
                    leftRightRotate(NULL, path.at(i));
                } else{
                    leftRightRotate(path.at(i-1), path.at(i));
                }
            }
        }
    } 
}

int AVLTree::kthMin(int k){
    return find_kth_min(k, root);
}

int AVLTree::find_kth_min(int k, IAVLTreeNode* curr){
    int cl = countNodes(curr->getLeft());    
    if(cl==k)
        return curr->getKey();
    if (k < cl){
        find_kth_min(k, curr->getLeft());
    }
    else if(k > cl){
        find_kth_min(int(k-cl-1), curr->getRight());
     }
}

IAVLTreeNode * AVLTree::getRoot(){
    return root;
}


int AVLTree::countNodes(IAVLTreeNode* curr){
    if(curr == NULL)
        return 0;
    return (countNodes(curr->getLeft()) + countNodes(curr->getRight()) + 1);
}
int AVLTree::calcHeight(IAVLTreeNode* curr){
    if(curr == NULL) {
        return 0;
    }
    int lh = calcHeight(curr->getLeft());
    int rh = calcHeight(curr->getRight());
    if (lh > rh){
        return lh+1;
    }
    else {
        return rh+1;
    }
}

int AVLTree::diffHeight(IAVLTreeNode* curr){
    int lh = calcHeight(curr->getLeft());
    int rh = calcHeight(curr->getRight());
    return rh-lh;
}

void AVLTree::rightLeftRotate(IAVLTreeNode* curr, IAVLTreeNode* toBeRotated){
    /*  2 and 1
                x                 y
               / \               / \
              A   y      =      x   C
                /   \          /\
                B   C         A  B 
    */
    IAVLTreeNode* temp;
    temp = toBeRotated->getRight();
    toBeRotated->setRight(temp->getLeft());
    temp->setLeft(toBeRotated);
    if(toBeRotated == root){
        //
        root = temp;
    }
    else{
       //we are getting ptr before x . i.e parent of node with diff 2
        if(curr->getRight() == toBeRotated){
            //toBeRorated is a right child, set it to temp
            curr->setRight(temp);
        }
        else{
            curr->setLeft(temp);
        }
    }
}


void AVLTree::leftRightRotate(IAVLTreeNode* rootOftoBeRotated, IAVLTreeNode* toBeRotated){
    /* -2 and -1
        Mirror Image of the previous rightLeftRotate
    */
    IAVLTreeNode* temp;
    temp = toBeRotated->getLeft();
    toBeRotated->setLeft(temp->getRight());
    temp->setRight(toBeRotated);
    if(toBeRotated == root){
        //
        root = temp;
    }
    else{
       //we are getting ptr before x . i.e parent of node with diff 2
        if(rootOftoBeRotated->getRight() == toBeRotated){
            //toBeRorated is a right child, set it to temp
            rootOftoBeRotated->setRight(temp);
        }
        else{
            rootOftoBeRotated->setLeft(temp);
        }
    }
}

//Rotation 2
void AVLTree::rightRightRotate(IAVLTreeNode* toBeRotated){
    // toBeRotated is with height df 2
    /*
               x                         x                      y 
              / \              =>       / \           =>       /  \
             A   Z                     A   y                  x     z
                / \                       / \                / \  /  \
                Y  D                    B    z              A   B C   D
               / \                          /  \
              B   C                        C    D
    */ 
    //we are getting root of x, x
   IAVLTreeNode* temp = toBeRotated->getRight()->getLeft();  // y
   toBeRotated->getRight()->setLeft(temp->getRight());
   temp->setRight(toBeRotated->getRight());
   toBeRotated->setRight(temp);
}

void AVLTree::leftLeftRotate(IAVLTreeNode* toBeRotated){
    //mirror image of leftLeftRotate
    /*
               x                         x                      y 
              / \              =>       / \           =>       /  \
             A   Z                     A   y                  x     z
                / \                       / \                / \  /  \
                Y  D                    B    z              A   B C   D
               / \                          /  \
              B   C                        C    D
    */ 
    //we are getting root of x, x
   IAVLTreeNode* temp = toBeRotated->getLeft()->getRight();  // y
   toBeRotated->getLeft()->setRight(temp->getLeft());
   temp->setLeft(toBeRotated->getLeft());
   toBeRotated->setLeft(temp);
}
