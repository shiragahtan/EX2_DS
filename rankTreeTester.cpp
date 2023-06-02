/*
 * A Rank/AVL Tree Tester to test your tree implementation
 *
 * Please Read the instructions in the README file before you start

 * You may add any additional functions you need.
 *
 * I would suggest first beginning with a simple tree and then moving on to a more complex one.
 *
 * G O O D  L U C K !
 */

#include <iostream>
#include <vector>
#include <ostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <assert.h>



#include "AvlTree.h"

/*
 * is_tree_valid - checks if the tree is valid, meaning that the tree is balanced and the rank is correct
 * @param root - the root of the tree
 * @return true if the tree is valid, false otherwise
 * Should use to make sure your tree is valid after every insertion and deletion
 * If your Node class doesn't use a m_father pointer, remove lines 66-84
 * If your tree isn't a Rank Tree, remove lines 56-60
 * if assert happens, put breaking points in "return false" to see where the error is
 */

template<class Key, class Value>
bool is_tree_valid(Node<Key, Value> *root) {
    if (!root) {
        return true;
    }
    // Checks the height of every node is valid
    /*if (root->height != 1 + std::max(getHeight(root->m_left), getHeight(root->m_right))) {
        std::cout << "Height is not valid" << std::endl;
        return false;
    }
    if (!root->m_left && !root->m_right && root->height != 0) {
        std::cout << "Leaf Height is not valid" << std::endl;
        return false;
    }*/
    //checks the Tree is a Binary Search Tree
    if (root->m_left && root->m_left->m_key >= root->m_key) {
        std::cout << "Left son is not smaller than root" << std::endl;
        return false;
    }
    if (root->m_right && root->m_right->m_key <= root->m_key) {
        std::cout << "Right son is not bigger than root" << std::endl;
        return false;
    }
    /*//checks that the rank of every node is valid
    if (root->weight != 1 + getWeight(root->m_left) + getWeight(root->m_right)) {
        std::cout << "Rank is not valid" << std::endl;
        return false;
    }*/
    //checks that the Balance Factor of every node is valid
    if (std::abs(BalanceFactor(root)) > 1) {
        std::cout << "Balance Factor is not valid" << std::endl;
        return false;
    }
    //checks that the m_father pointer is valid
    if (root->m_father) {
        if (root->m_father->m_left != root && root->m_father->m_right != root) {
            std::cout << "m_father pointer is not valid" << std::endl;
            return false;
        }
    }
    if (root->m_left) {
        if (root->m_left->m_father != root) {
            std::cout << "m_father's Left Son pointer is not valid" << std::endl;
            return false;
        }
    }
    if (root->m_right) {
        if (root->m_right->m_father != root) {
            std::cout << "Parent's Right Son pointer is not valid" << std::endl;
            return false;
        }
    }
    return is_tree_valid(root->m_left) && is_tree_valid(root->m_right);
}

template<class Key, class Value>
int getHeight(Node<Key, Value> *root) {
    if (!root) {
        return -1;
    }
    return root->m_height;
}


template<class Key, class Value>
int BalanceFactor(Node<Key, Value> *node) {
    if (node == nullptr) {
        return 0;
    }
    int Rheight = -1;
    int Lheight = -1;
    if (node->m_right != nullptr) {
        Rheight = AvlTree<Key,Value>::height(node->m_right);//node->m_right->m_height; //node->m_left->m_height;
    }
    if (node->m_left != nullptr) {
        Lheight = AvlTree<Key,Value>::height(node->m_left);
    }
    return Lheight - Rheight;
}

template<class Key, class Value>
int getWeight(Node<Key, Value> *root) {
    if (!root) {
        return 0;
    }
    return root->weight;
}


// A function to print the tree
void print2DHelper(Node<int,int> *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process m_right child first
    print2DHelper(root->m_right, space);

    // Print current node after space
    std::cout<<std::endl;
    for (int i = 10; i < space; i++)
        std::cout<<" ";
    std::cout<<root->m_key<<"\n";//changed value to m_key

    // Process m_left child
    print2DHelper(root->m_left, space);
}

// Wrapper over print2DHelper()
void print2D(Node<int,int> *root)
{
    // Pass initial space count as 0
    print2DHelper(root, 0);
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

}
int main(){
    AvlTree<int,int> tree;
    std::vector<int> vector;
    int size = 0;
    int count = 0;
    //determines the size of the tree - change i to test different sizes
    for (int i = 1; i < 2000; i++) {
        vector.push_back(i);
        size = i;
    }

    //randomizes the vector, and k is the number of trees to randomize - change k to test different numbers of trees
    for (int k = 1; k < 1000; ++k) {
        count = k;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        //std::cout<<"\n     Creating The Tree \n"<<std::endl;
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); it++){
            tree.insert(*it, *it); //,*it
            assert(is_tree_valid(tree.root));
            if(is_tree_valid(tree.root)){}
            //print2D(tree.root);
        }
        if (tree.m_size == 200){
           cout << "200";
        }
        //std::cout<<"    Deleting The Tree \n"<<std::endl;
        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
            tree.remove(*it);
            assert(is_tree_valid(tree.root));
            //print2D(tree.root);

        }
        if(k != 1){
            std::cout<< " num node:" << tree.m_size << "\n" <<std::endl;
        }
        tree.deleteTree(tree.root);
        tree.root= nullptr;
    }
    std::cout<<" S U C C E S S"<<std::endl;
    std::cout << '\n';
    if(size < 100 && count < 6){
        std::cout << "Great! Now try a Larger Tree and more Trees " << std::endl;
        std::cout << '\n';
    }
    else if(size < 100){
        std::cout << "Great! Now try a Larger Tree " << std::endl;
        std::cout << '\n';
    }
    else if(count < 6){
        std::cout << "Great! Now try more Trees " << std::endl;
        std::cout << '\n';
    }
    else{
        std::cout << "    Great! " << std::endl;
        std::cout << '\n';
    }

    return 0;
}


