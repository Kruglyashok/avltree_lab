#pragma once
#include "avl_tree.h"
#include <locale>

int max(int a, int b)
{
    return (a > b ? a : b);
}

Node* AVLTree::insert(Record x, Node* t)
{
    if (t == nullptr)
    {
        t = new Node;
        t->rec = x;
        t->height = 0;
        t->left = t->right = nullptr;
    }
    else if (x < t->rec)
    {
        t->left = insert(x, t->left);
        if (height(t->left) - height(t->right) == 2)
        {
            if (x < t->left->rec)
                t = singleRightRotate(t);
            else
                t = doubleRightRotate(t);
        }
    }
    else if (x >= t->rec)
    {
        t->right = insert(x, t->right);
        if (height(t->right) - height(t->left) == 2)
        {
            if (x >= t->right->rec)
                t = singleLeftRotate(t);
            else
                t = doubleLeftRotate(t);
        }
    }

    t->height = max(height(t->left), height(t->right)) + 1;
    return t;
}

void AVLTree::makeEmpty(Node* t)
{
    if (t == nullptr) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

Node* AVLTree::singleRightRotate(Node*& t)
{
    Node* u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    u->height = max(height(u->left), t->height) + 1;
    return u;
}

Node* AVLTree::singleLeftRotate(Node*& t)
{
    Node* u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    u->height = max(height(t->right), t->height) + 1;
    return u;
}

Node* AVLTree::doubleLeftRotate(Node*& t)
{
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
}

Node* AVLTree::doubleRightRotate(Node*& t)
{
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
}

Node* AVLTree::findMin(Node* t)
{
    if (t == nullptr)
        return nullptr;
    else if (t->left == nullptr)
        return t;
    else
        return findMin(t->left);
}

Node* AVLTree::findMax(Node* t)
{
    if (t == nullptr)
        return nullptr;
    else if (t->right == nullptr)
        return t;
    else
        return findMax(t->right);
}

Node* AVLTree::remove(int x, Node* t)
{
    Node* temp;

    // Element not found
    if (t == nullptr)
        return nullptr;

    // Searching for element
    else if (x < t->data)
        t->left = remove(x, t->left);
    else if (x > t->data)
        t->right = remove(x, t->right);

    // Element found
    // With 2 children
    else if (t->left && t->right)
    {
        temp = findMin(t->right);
        t->data = temp->data;
        t->right = remove(t->data, t->right);
    }
    // With one or zero child
    else
    {
        temp = t;
        if (t->left == nullptr)
            t = t->right;
        else if (t->right == nullptr)
            t = t->left;
        delete temp;
    }
    if (t == nullptr)
        return t;

    t->height = max(height(t->left), height(t->right)) + 1;

    // If Node is unbalanced
    // If left Node is deleted, right case
    if (height(t->left) - height(t->right) == 2)
    {
        // right right case
        if (height(t->left->left) - height(t->left->right) == 1)
            return singleLeftRotate(t);
        // right left case
        else
            return doubleLeftRotate(t);
    }
    // If right Node is deleted, left case
    else if (height(t->right) - height(t->left) == 2)
    {
        // left left case
        if (height(t->right->right) - height(t->right->left) == 1)
            return singleRightRotate(t);
        // left right case
        else
            return doubleRightRotate(t);
    }
    return t;
}

int AVLTree::height(Node* t)
{
    return (t == nullptr ? -1 : t->height);
}

int AVLTree::getBalance(Node* t)
{
    if (t == nullptr)
        return 0;
    else
        return height(t->left) - height(t->right);
}

void AVLTree::inorder(Node* t)
{
    if (t == nullptr)
        return;
    inorder(t->left);
    std::cout << t->rec.year << " ";
    inorder(t->right);
}

AVLTree::AVLTree()
{ 
    root = nullptr;
    std::ifstream ifs("BASE1.dat", std::ios::in | std::ios::binary);
    Record rec{};
    ifs.seekg(0, ifs.end);
    auto endfile = ifs.tellg();
    ifs.seekg(0, ifs.beg);
    while(ifs.tellg() != endfile)
    {
        ifs.read(rec.auth, sizeof(char) * auth_len);
        ifs.read(rec.name, sizeof(char) * name_len);
        ifs.read(rec.title, sizeof(char) * title_len);
        ifs.read((char*)(&rec.year), sizeof(uint16_t));
        ifs.read((char*)(&rec.pages), sizeof(uint16_t));

        std::cout << std::endl;
        printf("auth === %s_\n", rec.auth);
        printf("name === %s_\n", rec.name);
        printf("title === %s_\n", rec.title);
        std::cout << "\nyear = " << rec.year << std::endl;
        std::cout << "\npages = " << rec.pages << std::endl;
        std::cout << std::endl;
        this->insert(rec);
    }
    ifs.close();
}

void AVLTree::insert(Record x)
{
    root = insert(x, root);
}

void AVLTree::remove(int x)
{
    root = remove(x, root);
}

void AVLTree::display()
{
    inorder(root);
    std::cout << std::endl;
}