#include "BTree.h"
#include <iostream>
using  namespace std;

void BTree::insert(int key, int num_keys){
    if(root == NULL){
        root = new BTreeNode(key); 
        return;
    }
    
    //if its not the root, 
    
    //get the leaf node
    path.clear();
    IBTreeNode* ileaf = findLeafNode(key, root); 
    BTreeNode* leaf = static_cast<BTreeNode*> (ileaf);
    BTreeNode* split_b = NULL;
    BTreeNode* prev_leaf = NULL;
    while(true){
        int leaf_key_size = leaf->keys.size();
        if( leaf_key_size <5){
            //add into the leaf
            leaf->keys.push_back(key);
            sort(leaf->keys);
            if(split_b != NULL){
                for(int i =0;i<leaf->branches.size(); i++){
                    if (leaf->branches.at(i) == prev_leaf){
                        leaf->branches.insert(leaf->branches.begin()+i+1, split_b);
                        break;
                        }
                    }
            }
            return;
        }
        else{
            leaf->keys.push_back(key);
            sort(leaf->keys);
            int median = 2;
            int median_element = leaf->keys[2];
            if(split_b != NULL){
                for(int i =0;i<leaf->branches.size(); i++){
                    if (leaf->branches.at(i) == prev_leaf){
                        leaf->branches.insert(leaf->branches.begin()+i+1, split_b);
                        break;
                        }
                    }
            }
            split_b = new BTreeNode();
            //copy all the keys and pointer >2
            for(int i=median+1; i < leaf->keys.size(); i++){
               split_b->keys.push_back(leaf->keys[i]);  
            }
            for(int i=median+1; i < leaf->branches.size(); i++){
               split_b->branches.push_back(leaf->branches[i]);
            }
            // now reset the leaf;
            int i = (int(leaf->keys.size()) -median);
            while(i>0){
                leaf->keys.pop_back();
                i--;
            }
            int k = (int(leaf->branches.size()) - (median+1));
            while(k>0){
                leaf->branches.pop_back();
                k--;
            }
            if(leaf == root){
                //split at 2
                BTreeNode *temp_root = new BTreeNode();
                temp_root->keys.push_back(median_element);
                temp_root->branches.push_back(leaf);
                temp_root->branches.push_back(split_b);
                root = temp_root;
                return;
                }
            //go to the parent and add the new split node with the other
            else{
                path.pop_back();
                BTreeNode* parent = static_cast<BTreeNode*> (path.at(path.size()-1));
                key = median_element;
                prev_leaf = leaf;
                leaf = parent;
            }
    }
    } 
}

 void BTree::swap(std::vector<int> &a, int index1, int index2){
    int lhs = a[index1];
    int rhs = a[index2];
   a[index1] = rhs;
   a[index2] = lhs;
 }
 
 void BTree::sort(std::vector<int> &a){
   int n = a.size();
   int newn;
   while(n > 0){
     newn = 0;
     for(int i = 1; i < n; ++i){
       if(a[i - 1] > a[i]){
         swap(a, i-1, i);
         newn = i;
       }
     }
     n = newn;
   }
 }

IBTreeNode* BTree::findLeafNode(int key, IBTreeNode* curr){
   int i=0;
    for(i=0; (i< curr->getKeySize()) and (curr->getKey(i)<key); i++);
    path.push_back(curr);
    index.push_back(i);
    if (i >= curr->getKeySize() || curr->getKey(i) > key){
        if(i <= curr->getChildSize()){
            if(curr->getChildSize() >0)
                return findLeafNode(key, curr->getChild(i));
            else
                return curr;
            }
        else
            return curr;
    }
}

IBTreeNode* BTree::findLeafNodeForRemove(int key, IBTreeNode* curr){
   if(curr!=NULL){
       int i;
        for(i=0; (i< curr->getKeySize()) and (curr->getKey(i)<key); i++);
        path.push_back(curr);
        index.push_back(i);
        if (i >= curr->getKeySize() || curr->getKey(i) > key){
                if(curr->getChildSize() >0)
                    return findLeafNodeForRemove(key, curr->getChild(i));
            }
        else
            return curr;
    }
    else
        return NULL;
}

void BTree::remove(int key, int num_keys){
    path.clear();
    index.clear();
    IBTreeNode* inode = findLeafNodeForRemove(key, root); 
    if(inode == root){
        if(root->getKeySize() == 1){
            root = NULL;
            return;
        }
    }
    
    if(inode ==NULL)
        return;
    BTreeNode* node = static_cast<BTreeNode*> (inode);
    BTreeNode* predOfLeaf =NULL;
    BTreeNode* parent_node = NULL;
    if(not node->isLeaf()){
        //find a leaf with closest predecessor S of key
        predOfLeaf= static_cast<BTreeNode*> (node->branches.at(index.at(index.size()-1)));
        if(predOfLeaf->isLeaf()){
            node->keys.at(index.at(index.size()-1)) = predOfLeaf->keys.at(predOfLeaf->keys.size()-1);
            predOfLeaf->keys.pop_back();
            path.push_back(predOfLeaf);
            index.push_back(predOfLeaf->keys.size()-1);
            node = predOfLeaf;
            }
        else{
            int ind = index.at(index.size()-1);
            while(not predOfLeaf->isLeaf()){
                path.push_back(predOfLeaf);
                index.push_back(predOfLeaf->keys.size()-1);
                predOfLeaf = static_cast<BTreeNode*> (predOfLeaf->branches.at(predOfLeaf->branches.size()-1));
            }
            path.push_back(predOfLeaf);
            index.push_back(predOfLeaf->keys.size()-1);
            node->keys.at(ind) = predOfLeaf->keys.at(predOfLeaf->keys.size()-1);
            predOfLeaf->keys.pop_back();
            node = predOfLeaf;
        }
            return;
    }
    else{
        //remove from the leaf
        int ind = index.at(index.size()-1);
        for(int k=ind; k<(node->keys.size()-1); k++){
            node->keys.at(k) = node->keys.at(k+1);
        }
        node->keys.pop_back();
    }
    while(true){
        if(path.size() > 1){
            parent_node = static_cast<BTreeNode*> (path.at(path.size()-2));
            }
        else{   
            parent_node = root;
        }
        if(node->getKeySize()>=2){
            return;
        } 
        else if ((parent_node and  (parent_node->branches.size() > (index.at((index.size()-2)) + 1)) and (parent_node->branches.at((index.at(index.size()-2) +1))->getKeySize() > 2)))  {
           //find sibling with enough keys
           //redistribute keys between node and its sibling
            BTreeNode* sibling = static_cast<BTreeNode*> (parent_node->branches.at((index.at(index.size()-2) +1)));
            int sibling_key = sibling->keys.at(0);
            node->keys.push_back(parent_node->keys.at(index.at(index.size()-2)));
            sort(node->keys);
            parent_node->keys.at(index.at(index.size()-2)) = sibling_key;
            for(int k=0; k<(sibling->keys.size()-1); k++){
                sibling->keys.at(k) = sibling->keys.at(k+1);
            }
            sibling->keys.pop_back();
            return;
        }
        else if( parent_node == root){
           BTreeNode* sibling = static_cast<BTreeNode*> (parent_node->branches.at((index.at(index.size()-2) +1)));
           if(parent_node->keys.size() == 1){
               //merge node and its sibling along with the parent
               node->keys.push_back(parent_node->keys.at(0));
               for(int k=0;k< sibling->keys.size(); k++){
                    node->keys.push_back(sibling->keys.at(k));
                }
               for(int k=0;k< sibling->branches.size(); k++){
                    node->branches.push_back(sibling->branches.at(k));
                }
                root = node;
                delete parent_node;
                delete sibling;
            } 
            else{
               for(int k=0;k< sibling->keys.size(); k++){
                    node->keys.push_back(sibling->keys.at(k));
                }
               for(int k=0;k< sibling->branches.size(); k++){
                    node->branches.push_back(sibling->branches.at(k));
                }
            }
            return ;
        }
        else{
               BTreeNode* sibling = static_cast<BTreeNode*> (parent_node->branches.at((index.at(index.size()-2) +1)));
               for(int k=0;k< sibling->keys.size(); k++){
                    node->keys.push_back(sibling->keys.at(k));
                }
               for(int k=0;k< sibling->branches.size(); k++){
                    node->branches.push_back(sibling->branches.at(k));
                }
              path.pop_back();
              index.pop_back();
              node = parent_node;            

        }
    }

}                                                       
int BTree::kthMin(int k){
    return find_kth_min(k, root);
}

int BTree::find_kth_min(int k, IBTreeNode* curr){
        for(int i= 0; i <curr->getChildSize(); i++){
            int cl = countNodes(curr->getChild(i)) ;
            if(cl == k){
                return curr->getKey(i);
            }
            else if (k <cl){
                return find_kth_min(k, curr->getChild(i));
                
            }
            else if(k > cl){
                k = k-cl-1;
             }
        }
    if( k < curr->getKeySize())
           return curr->getKey(k);
}
int BTree::countNodes(IBTreeNode* curr){
    if(curr->isLeaf())
        return curr->getKeySize();
   int sum = 0;
   for(int i=0; i<curr->getChildSize(); i++){
        sum = sum + countNodes(curr->getChild(i));
    }
    return curr->getKeySize() + sum;

}
IBTreeNode * BTree::getRoot(){
    return root;
}
