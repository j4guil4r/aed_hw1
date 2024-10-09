#ifndef AVL_IMPL_H
#define AVL_IMPL_H

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "avl.h"

// AVLNode

template <typename T>
AVLNode<T>::AVLNode(T value)
    : data(value), left(nullptr), right(nullptr), height(0) {}

// AVLTree

template <typename T>
AVLTree<T>::AVLTree() : root(nullptr) {}

template <typename T>
int AVLTree<T>::height(AVLNode<T>* node) {
  // COMPLETE HERE
  if(node == nullptr){return -1;}
  return node->height;
}

template <typename T>
int AVLTree<T>::getBalance(AVLNode<T>* node) {
  // COMPLETE HERE
  if(node == nullptr){return 0;}
  return height(node->left) - height(node->right);
}

template <typename T>
AVLNode<T>* AVLTree<T>::rightRotate(AVLNode<T>* y) {
  // COMPLETE HERE
  AVLNode<T>* z = y->left; 
  y->left = z->right;
  z->right = y;

  //Actu de la altura.
  y->height = std::max(height(y->left), height(y->right)) + 1;
  z->height = std::max(height(z->left), height(z->right)) + 1;

  return z;
}

// Rotación izquierda
template <typename T>
AVLNode<T>* AVLTree<T>::leftRotate(AVLNode<T>* x) {
  // COMPLETE HERE
  AVLNode<T>* z = x->right;
  x->right = z->left;
  z->left = x;
  
  x->height = std::max(height(x->left), height(x->right)) + 1;
  z->height = std::max(height(z->left), height(z->right)) + 1;

  return z;
}

template <typename T>
AVLNode<T>* AVLTree<T>::minValueNode(AVLNode<T>* node) {
  // COMPLETE HERE
  AVLNode<T>* nodo_aux = node;
  while(nodo_aux && nodo_aux->left != nullptr){
    nodo_aux = nodo_aux->left;
  }
  return nodo_aux;
}

//Agregado: rebalanceador
template <typename T>
AVLNode<T>* AVLTree<T>::rebalance(AVLNode<T>* node) {
  if(node == nullptr){return node;}
  
  node->height = 1 + std::max(height(node->left), height(node->right));
  
  int balance = getBalance(node);

  // Rotación derecha simple
  if(balance > 1 && getBalance(node->left) >= 0){return rightRotate(node);}

  // Rotación izquierda-derecha
  if(balance > 1 && getBalance(node->left) < 0){
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // Rotación izquierda simple
  if(balance < -1 && getBalance(node->right) <= 0){return leftRotate(node);}

  // Rotación derecha-izquierda
  if(balance < -1 && getBalance(node->right) > 0){
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }
  
  return node;
}


// Inserción
template <typename T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T>* node, T key) {
  // COMPLETE HERE
  if(node == nullptr){return new AVLNode<T>(key);}

  if(key < node->data){node->left = insert(node->left, key);}
  else if(key > node->data){node->right = insert(node->right, key);}
  else{return node;}

  return rebalance(node);
}

// Eliminar un nodo
template <typename T>
AVLNode<T>* AVLTree<T>::remove(AVLNode<T>* root, T key) {
  // COMPLETE HERE
  if(root == nullptr){return root;}

  if(key < root->data){root->left = remove(root->left, key);}
  else if(key > root->data){root->right = remove(root->right, key);}
  else{
    // Caso con un hijo o sin hijos
    if(root->left == nullptr || root->right == nullptr){
      AVLNode<T>* temp = root->left ? root->left : root->right;
      if(temp == nullptr){
        delete root;
        root = nullptr;
      } 
      else{
        AVLNode<T>* toDelete = root;
        root = temp;
        delete toDelete;
      }
    } 
    else{
      // Caso con dos hijos
      AVLNode<T>* temp = minValueNode(root->right);
      root->data = temp->data;
      root->right = remove(root->right, temp->data);
    }
  }
  if(root == nullptr){return root;}
  return rebalance(root);
}

// Búsqueda
template <typename T>
bool AVLTree<T>::search(AVLNode<T>* node, T key) {
  // COMPLETE HERE
  if(node == nullptr){return false;}
  if(key < node->data){
    return search(node->left, key);
  }
  else if(key > node->data){
    return search(node->right, key);
  }
  else{return true;}
}

// Recorrido preorder
template <typename T>
void AVLTree<T>::preorder(AVLNode<T>* root, std::vector<T>& ret) {
  // COMPLETE HERE
  if(root != nullptr){
    ret.emplace_back(root->data);
    preorder(root->left, ret);
    preorder(root->right, ret);
  }
}

// Recorrido inorder
template <typename T>
void AVLTree<T>::inorder(AVLNode<T>* root, std::vector<T>& ret) {
  // COMPLETE HERE
  if(root != nullptr){
    inorder(root->left, ret);
    ret.emplace_back(root->data);
    inorder(root->right, ret);
  }
}

// Recorrido postorder
template <typename T>
void AVLTree<T>::postorder(AVLNode<T>* root, std::vector<T>& ret) {
  // COMPLETE HERE
  if(root != nullptr){
    postorder(root->left, ret);
    postorder(root->right, ret);
    ret.emplace_back(root->data);
  }
}

/// Public functions

template <typename T>
void AVLTree<T>::insert(T key) {
  // COMPLETE HERE
  root = insert(root, key);
}

template <typename T>
void AVLTree<T>::remove(T key) {
  // COMPLETE HERE
  root = remove(root, key);
}

template <typename T>
bool AVLTree<T>::search(T key) {
  // COMPLETE HERE
  return search(root, key);
}

template <typename T>
std::vector<T> AVLTree<T>::preorderTraversal() {
  // COMPLETE HERE
  std::vector<T> r;
  preorder(root, r);
  return r;

}

template <typename T>
std::vector<T> AVLTree<T>::inorderTraversal() {
  // COMPLETE HERE
  std::vector<T> r;
  inorder(root, r);
  return r;
}

template <typename T>
std::vector<T> AVLTree<T>::postorderTraversal() {
  // COMPLETE HERE
  std::vector<T> r;
  postorder(root, r);
  return r;
}

template <typename T>
int AVLTree<T>::height() {
  // COMPLETE HERE
  return height(root);
}


// Implementacion necesaria (?):

template <typename T>
bool AVLTree<T>::isBalanced(AVLNode<T>* node){
  if(node == nullptr){return true;}
  if(std::abs(getBalance(node)) > 1){
    return false;
  }
  else{
    return isBalanced(node->left) && isBalanced(node->right);
  }

}


template <typename T>
bool AVLTree<T>::isBalanced() {
  // COMPLETE HERE
  return isBalanced(root);
}

#endif
