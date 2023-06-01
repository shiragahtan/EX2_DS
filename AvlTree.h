//
// Created by shira on 25/04/2023.
//
#include <iostream>

#ifndef EX1_DS_AVLTREE_H
#define EX1_DS_AVLTREE_H
using namespace std;


#define FAILED 0
#define SUCCEED 1
#include "wet1util.h"
#include <exception>

class MovieByRate{

public:
    MovieByRate();
    MovieByRate(int id, bool isVip, int views, Genre genre);
    int movieId;
    bool vipOnly;
    int numberOfWatches;
    int numRates;
    Genre m_genre;
    double totalRate;
    friend bool operator<(const MovieByRate& movie1, const MovieByRate& movie2);
};

class MovieByRate;

template <class Key, class Value>
class Node {
public:
    Key m_key;
    Node<Key, Value>* m_left ;
    Node<Key, Value>* m_right;
    Node<Key, Value>* m_father;
    Value m_info;

    explicit Node(Key id,Value m_info): m_key(id),m_left(nullptr), m_right(nullptr), m_father(nullptr),m_info(m_info){};//m_height
};

template <class Key, class Value>
class AvlTree{
private:
    int getBalanceFactor(Node<Key, Value>* nodeToCheck) const;
    Node<Key, Value>* rightRotate(Node<Key, Value>* parent);
    Node<Key, Value>* leftRotate(Node<Key, Value>* parent);
    Node<Key, Value>* leftRightRotate(Node<Key, Value>* node);
    Node<Key, Value>* rightLeftRotate(Node<Key, Value>* node);
    void insertAux(Node<Key, Value>* parent, Node<Key, Value>* node);
    int inorderAux(Node<Key, Value>* node, int* arr, int count=0) const;
    int inorderOppositeAux(Node<Key, Value>* node, int* arr, int count=0) const;
    Node<Key, Value>* findAux(Node<Key, Value>* parent, Key key) const;
    Node<Key, Value>* findAux(Node<Key, Value>* parent, MovieByRate value) const;
    void removeAux(Node<Key, Value>* node, Node<Key, Value>* nodeToReplace);
    void nodeNotParentRemove(Node<Key, Value>* node, Node<Key, Value>* nextNode);
    Node<Key, Value>* findNextNode (Node<Key, Value>* node);
    Node<Key, Value>* balanceCorrector(Node<Key, Value>* node);
    void checkBalanceMistakes(Node<Key, Value>* node);
    void updateFamilyRightRotate(Node<Key, Value>* parent, Node<Key, Value>* futureFather);
    void updateFamilyLeftRotate(Node<Key, Value>* parent, Node<Key, Value>* futureFather);
    Node<Key, Value>* correctPositiveBF(Node<Key, Value>* node);
    Node<Key, Value>* correctNegativeBF(Node<Key, Value>* node);
    int checkWhichChild(Node<Key, Value>* parent, int key) const;
    int checkWhichChild(Node<Key, Value>* parent, MovieByRate value) const;
    int checkWhichDirection(Node<Key, Value>* parent, Node<Key, Value>* node);

public:
    void deleteTreeAux(Node<Key, Value>* node);
    static int height(Node<Key, Value>* nodeToCheck);
    Node<Key, Value>* callLeftRightRotate();
    Node<Key, Value>* callLeftRotate();
    Node<Key, Value>* callRightRotate();
    int m_size;
    Node<Key, Value>* root;
    explicit AvlTree(): m_size(0), root(nullptr){};
    Node<Key, Value>* find(Key key) const;
    void remove(Key key);
    int insert(Key key, Value info);
    int insert(MovieByRate info);
    void inorder(int* arr) const;
    void deleteTree(Node<Key, Value>* node);
    Node<Key, Value>* getMax();
    ~AvlTree();
    void deleteTree();
    Node<Key, Value>* find(MovieByRate value) const;
    void remove(MovieByRate value);
    void inorderOpposite(int* arr) const;

};


static int LEFT_CHILD =1;
static int RIGHT_CHILD =2;
static int NOT_A_CHILD = 0;
static int NO_DECISION = 0;
static int ALLOCATION_ERROR = 3;

#include "StreamingDBa1.h"

template <class Key, class Value>
AvlTree<Key, Value>:: ~AvlTree(){
    if (!root){
        return;
    }
    deleteTreeAux(root);
}


template <class Key, class Value>
void AvlTree<Key, Value>:: inorder(int* arr) const{
    inorderAux(root,arr);
}
template <class Key, class Value>
int AvlTree<Key, Value>:: inorderAux(Node<Key, Value>* node, int* arr, int count) const{
    if(!node) {
        return count;
    }
    count= inorderAux(node->m_left,arr,count);
    arr[count++]=node->m_key;
    return inorderAux(node->m_right,arr,count);

}

template <class Key, class Value>
void AvlTree<Key, Value>::inorderOpposite(int* arr) const{
    inorderOppositeAux(root, arr);
}

template <class Key, class Value>
int AvlTree<Key, Value>::inorderOppositeAux(Node<Key, Value>* node, int* arr, int count) const{
    if (!node){
        return count;
    }
    count = inorderOppositeAux(node->m_right, arr, count);
    arr[count++]=node->m_key;
    return inorderOppositeAux(node->m_left, arr, count);
}


template <class Key, class Value>
int AvlTree<Key, Value>::height(Node<Key, Value>* nodeToCheck){
    int h =-1;
    if (nodeToCheck != NULL){
        int leftHeight = height(nodeToCheck->m_left);
        int rightHeight = height(nodeToCheck->m_right);
        int maxHeight = max(leftHeight, rightHeight);
        h = maxHeight + 1;
    }
    return h;
}

template <class Key, class Value>
int AvlTree<Key, Value>::getBalanceFactor(Node<Key, Value>* nodeToCheck) const{
    int leftHeight = height(nodeToCheck->m_left);
    int rightHeight = height(nodeToCheck->m_right);
    return leftHeight - rightHeight;
}


template <class Key, class Value>
int AvlTree<Key, Value>::checkWhichDirection(Node<Key, Value>* parent, Node<Key, Value>* node){
    if (node->m_info < parent->m_info){
        if (!parent->m_left){
            node->m_father = parent;
            parent->m_left = node;
            return LEFT_CHILD;
        }
    }
    else if(node->m_info > parent->m_info){
        if (!parent->m_right){
            node->m_father = parent;
            parent->m_right = node;
            return RIGHT_CHILD;
        }
    }
    return NO_DECISION;
}

template <class Key, class Value>
void AvlTree<Key, Value>::insertAux(Node<Key, Value>* parent, Node<Key, Value>* node){
    int direction = checkWhichDirection(parent, node);
    if (direction == LEFT_CHILD || direction == RIGHT_CHILD) return;
    else if (direction == NO_DECISION && node->m_info < parent->m_info) insertAux(parent->m_left, node); // GOING LEFT
    else if (direction == NO_DECISION && node->m_info > parent->m_info) insertAux(parent->m_right, node); // GOING RIGHT
    checkBalanceMistakes(node);
}

template <class Key, class Value>
int AvlTree<Key, Value>::insert(Key key, Value info){
    if (!this->root){
        try {
            auto node1 = new Node<Key, Value>(key, info);
            root = node1;
            m_size++;
            return SUCCEED;
        }
        catch (std::exception &exe){
            return ALLOCATION_ERROR;
        }
    }
    if ((this->find(key) != nullptr)){
        return FAILED;
    }
    m_size++;
    auto newNode = new Node<Key, Value>(key, info);
    insertAux(this->root,newNode);
    return SUCCEED;
}

template <class Key, class Value>
int AvlTree<Key, Value>::insert(MovieByRate info){
    if (!this->root){
        try {
            auto node1 = new Node<Key, Value>(info.movieId, info);
            root = node1;
            m_size++;
            return SUCCEED;
        }
        catch (std::exception &exe){
            return ALLOCATION_ERROR;
        }
    }
    if ((this->find(info) != nullptr)){
        return FAILED;
    }
    m_size++;
    auto newNode = new Node<Key, Value>(info.movieId, info);
    insertAux(this->root,newNode);
    return SUCCEED;
}

template <class Key, class Value>
int AvlTree<Key, Value>::checkWhichChild(Node<Key, Value>* parent, int key) const{
    if (parent->m_key > key ){
        if (parent->m_left){
            return LEFT_CHILD;
        }
    }
    else if (parent->m_key < key){
        if (parent->m_right){
            return RIGHT_CHILD;
        }
    }
    return NOT_A_CHILD;
}

template <class Key, class Value>
int AvlTree<Key, Value>::checkWhichChild(Node<Key, Value>* parent, MovieByRate value) const{
    if (parent->m_info > value ){
        if (parent->m_left){
            return LEFT_CHILD;
        }
    }
    else if (parent->m_info < value){
        if (parent->m_right){
            return RIGHT_CHILD;
        }
    }
    return NOT_A_CHILD;
}

template <class Key, class Value>
Node<Key, Value>* AvlTree<Key, Value>::findAux(Node<Key, Value>* parent, Key key) const{
    if (parent->m_key == key ){
        return parent;
    }
    int childType = checkWhichChild(parent, key);
    if (childType == LEFT_CHILD){
        return findAux(parent->m_left, key);
    }
    else if (childType == RIGHT_CHILD){
        return findAux(parent->m_right, key);
    }
    return 0;
}

template <class Key, class Value>
Node<Key, Value>* AvlTree<Key, Value>::findAux(Node<Key, Value>* parent, MovieByRate value) const{
    if (parent->m_key == value.movieId ){
        return parent;
    }
    int childType = checkWhichChild(parent, value);
    if (childType == LEFT_CHILD){
        return findAux(parent->m_left, value);
    }
    else if (childType == RIGHT_CHILD){
        return findAux(parent->m_right, value);
    }
    return 0;
}

template <class Key, class Value>
Node<Key, Value>* AvlTree<Key, Value>::find(Key key) const{
    if (!root){
        return 0;
    }
    if (root->m_key == key){
        return this->root;
    }
    return findAux(this->root, key);
}

template <class Key, class Value>
Node<Key, Value>* AvlTree<Key, Value>::find(MovieByRate value) const{
    if (!root){
        return 0;
    }
    if (root->m_key == value.movieId){
        return this->root;
    }
    return findAux(this->root, value);
}

template <class Key, class Value>
void AvlTree<Key, Value>::remove(MovieByRate value) {
    Node<Key, Value>* node = find(value);
    if (!node){
        return;
    }
    m_size--;
    if(!node->m_right || !node->m_left){
        if(!node->m_right) {
            removeAux(node, node->m_left);
        }
        else {
            removeAux(node, node->m_right);
        }
        checkBalanceMistakes(node);
    }
    else {
        Node<Key, Value>* temp = findNextNode(node);
        if (node->m_key != temp->m_father->m_key) {
            nodeNotParentRemove(node,temp);
        }
        removeAux(node, temp);
        temp->m_left = node->m_left;
        if (temp->m_left) {
            temp->m_left->m_father = temp;
        }
        checkBalanceMistakes(temp);
    }
    delete(node);
}


template <class Key, class Value>
void AvlTree<Key, Value>::remove(Key key) {
    Node<Key, Value>* node = find(key);
    if (!node){
        return;
    }
    m_size--;
    if(!node->m_right || !node->m_left){
        if(!node->m_right) {
            removeAux(node, node->m_left);
        }
        else {
            removeAux(node, node->m_right);
        }
        checkBalanceMistakes(node);
    }
    else {
        Node<Key, Value>* temp = findNextNode(node);
        if (node->m_key != temp->m_father->m_key) {
            nodeNotParentRemove(node,temp);
        }
        removeAux(node, temp);
        temp->m_left = node->m_left;
        if (temp->m_left) {
            temp->m_left->m_father = temp;
        }
        checkBalanceMistakes(temp);
    }
        delete(node);
}


template <class Key, class Value>
void AvlTree<Key, Value>::removeAux(Node<Key, Value>* node, Node<Key, Value>* nodeToReplace){
    if (node->m_father){
        if(node->m_father->m_left == node) {
            node->m_father->m_left = nodeToReplace;
        }
        else{
            node->m_father->m_right = nodeToReplace;
        }
        if(nodeToReplace) {
            nodeToReplace->m_father = node->m_father;
        }
    }
    else {
        this->root = nodeToReplace;
        if(nodeToReplace){
            nodeToReplace->m_father=nullptr;
        }
    }
}

template <class Key, class Value>
Node<Key, Value>* AvlTree<Key, Value>::findNextNode (Node<Key, Value>* node){
    Node<Key, Value>* temp = node->m_right;
    while(temp->m_left) {
        temp = temp->m_left;
    }
    return temp;

}

template <class Key, class Value>
void AvlTree<Key, Value>::nodeNotParentRemove(Node<Key, Value>* node, Node<Key, Value>* nextNode){
    removeAux(nextNode, nextNode->m_right);
    checkBalanceMistakes(nextNode->m_father);
    nextNode->m_right = node->m_right;
    if(nextNode->m_right)
    {
        nextNode->m_right->m_father = nextNode;
    }

}


template <class Key, class Value>
void AvlTree<Key, Value>::updateFamilyRightRotate(Node<Key, Value>* parent, Node<Key, Value>* futureFather){
    if (parent->m_left){
        parent->m_left->m_father = parent;
    }
    if (parent->m_father) {
        if (parent->m_father->m_left == parent){
            //node is the left child of his father
            parent->m_father->m_left = futureFather;
        }
        else{
            //node is the right child of his father
            parent->m_father->m_right = futureFather;
        }
    }
}


template <class Key, class Value>
Node<Key, Value>* AvlTree<Key, Value>::rightRotate(Node<Key, Value>* parent){
    auto futureFather = parent->m_left;
    futureFather->m_father = parent->m_father;
    parent->m_left = futureFather->m_right;
    updateFamilyRightRotate(parent, futureFather);
    futureFather->m_right = parent;
    parent->m_father = futureFather;
    if (parent == this->root){
        this->root = futureFather;
    }
    return futureFather;
}

template <class Key, class Value>
void AvlTree<Key, Value>::updateFamilyLeftRotate(Node<Key, Value>* parent, Node<Key, Value>* futureFather){
    if(parent->m_right){
        parent->m_right->m_father = parent;
    }
    if (parent->m_father) {
        if (parent->m_father->m_left == parent){
            parent->m_father->m_left = futureFather;
        }
        else{
            parent->m_father->m_right = futureFather;
        }
    }
}

template <class Key, class Value>
Node<Key, Value>* AvlTree<Key, Value>::leftRotate(Node<Key, Value>* parent){
    auto futureFather = parent->m_right;
    futureFather->m_father = parent->m_father;
    parent->m_right = futureFather->m_left;
    updateFamilyLeftRotate(parent, futureFather);
    futureFather->m_left = parent;
    parent->m_father = futureFather;
    if (parent == this->root){
        this->root = futureFather;
    }
    return futureFather;
}


template <class Key, class Value>
Node<Key, Value>* AvlTree<Key, Value>::callRightRotate(){
    rightRotate(this->root);
}


template <class Key, class Value>
Node<Key, Value>* AvlTree<Key, Value>::callLeftRotate(){
    leftRotate(this->root);
}

template <class Key, class Value>
Node<Key, Value>* AvlTree<Key, Value>::leftRightRotate(Node<Key, Value>* node){
    node->m_left = leftRotate(node->m_left);
    auto nodeAfterRightRotate = rightRotate(node);
    return nodeAfterRightRotate;
}

template <class Key, class Value>
Node<Key, Value>* AvlTree<Key, Value>::callLeftRightRotate(){
    return leftRightRotate(this->root);
}

template <class Key, class Value>
Node<Key, Value>* AvlTree<Key, Value>::rightLeftRotate(Node<Key, Value>* node){
    node->m_right = rightRotate(node->m_right);
    auto nodeAfterLeftRotate = leftRotate(node);
    return nodeAfterLeftRotate;
}

template <class Key, class Value>
Node<Key, Value>* AvlTree<Key, Value>::correctPositiveBF(Node<Key, Value>* node){
    int leftBF = getBalanceFactor(node->m_left);
    if (leftBF >= 0){
        return rightRotate(node);
    }
    else{
        return leftRightRotate(node);
    }
}

template <class Key, class Value>
Node<Key, Value>* AvlTree<Key, Value>::correctNegativeBF(Node<Key, Value>* node){
    int rightBF = getBalanceFactor(node->m_right);
    if (rightBF == 1){
        return rightLeftRotate(node);
    }
    else {
        return leftRotate(node);
    }
}

template <class Key, class Value>
Node<Key, Value>* AvlTree<Key, Value>::balanceCorrector(Node<Key, Value>* node){
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1){
        node = correctPositiveBF(node);
    }
    else if (balanceFactor < -1){
        node = correctNegativeBF(node);
    }
    if (!node->m_father) {
        this->root = node;
    }
    return node;
}

template <class Key, class Value>
void AvlTree<Key, Value>::checkBalanceMistakes(Node<Key, Value>* currentNode){
    int balanceFactor = getBalanceFactor(currentNode);
    if (balanceFactor > 1 || balanceFactor < -1){
        currentNode = balanceCorrector(currentNode);
    }
    if (!currentNode->m_father){
        return;
    }
    checkBalanceMistakes(currentNode->m_father);
}

template <class Key, class Value>
void AvlTree<Key, Value>::deleteTreeAux(Node<Key, Value>* node){
    if (node->m_left){
        deleteTreeAux(node->m_left);
    }
    if (node->m_right){
        deleteTreeAux(node->m_right);
    }
    delete(node);
}

template <class Key, class Value>
void AvlTree<Key, Value>::deleteTree(Node<Key, Value>* node){
    if (!root){
        return;
    }
    deleteTreeAux(root);
}

template <class Key, class Value>
void AvlTree<Key, Value>::deleteTree(){
    if (!root){
        return;
    }
    deleteTreeAux(root);
}

template <class Key, class Value>
Node<Key, Value>* AvlTree<Key, Value>:: getMax(){
    if (!root){
        return nullptr;
    }
    if (!root->m_right){
        return root;
    }
    Node<Key, Value>* node = root->m_right;
    while(node->m_right){
        node=node->m_right;
    }
    return node;
}



#endif //EX1_DS_AVLTREE_H