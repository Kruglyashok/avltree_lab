#pragma once
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <fstream>

static constexpr auto auth_len = 12U;
static constexpr auto name_len = 32U;
static constexpr auto title_len = 16U;

typedef struct Record
{
    char *auth = new char[auth_len];
    char *name = new char[name_len];
    char *title = new char[title_len];
    uint16_t year = 0U;
    uint16_t pages = 0U;

} Record;

inline bool operator<(const Record& lhs, const Record& rhs)
{
    return lhs.year < rhs.year;
}
inline bool operator> (const Record& lhs, const Record& rhs) { return rhs < lhs; }
inline bool operator<=(const Record& lhs, const Record& rhs) { return !(lhs > rhs); }
inline bool operator>=(const Record& lhs, const Record& rhs) { return !(lhs < rhs); }

typedef struct Node
{
    //key
    int data;
    Node *left, *right;
    int height;
    Record rec{};
} Node;


class AVLTree
{

    Node* root = nullptr;

    void makeEmpty(Node*);
    Node* insert(Record, Node*);
    Node* singleRightRotate(Node*&);
    Node* singleLeftRotate(Node*&);
    Node* doubleLeftRotate(Node*&);
    Node* doubleRightRotate(Node*&);
    Node* findMin(Node*);
    Node* findMax(Node*);
    Node* remove(int, Node*);
    int height(Node*);
    int getBalance(Node*);
    void inorder(Node*);

public:
    AVLTree();
    void insert(Record);
    void remove(int);
    void display();
};
#endif//AVL_TREE_H