#pragma once
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>

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
    Record& operator=(const Record& other)
    {
        if (this == &other)
            return *this;
        this->pages = other.pages;
        this->year = other.year;
        for (auto i{ 0U }; i < auth_len; ++i) this->auth[i] = other.auth[i];
        for (auto i{ 0U }; i < name_len; ++i) this->name[i] = other.name[i];
        for (auto i{ 0U }; i < title_len; ++i) this->title[i] = other.title[i];
        return *this;
    }
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
    Node* left = nullptr , * right = nullptr;
    int height{0};
    Record rec{};
} Node;

class AVLTree
{
private:
    Node* root = nullptr;

    void makeEmpty(Node*);
    Node* insert(Record, Node*);
    Node* singleRightRotate(Node*&);
    Node* singleLeftRotate(Node*&);
    Node* doubleLeftRotate(Node*&);
    Node* doubleRightRotate(Node*&);
    Node* findMin(Node*);
    Node* findMax(Node*);
    int height(Node*);
    int getBalance(Node*);
    void inorder(Node*);
    void getRecByYear(Node*, uint16_t, uint16_t, std::vector<Record>&, std::string&);
    void getPublishers(Node*, std::unordered_map<std::string, int>&);

public:
    AVLTree() = delete;
    AVLTree(std::string);
    void insert(Record);
    void display();
    std::vector<Record> getRecByYear(uint16_t, uint16_t, std::string&);
    std::unordered_map<std::string, int> getPublishers();
};
#endif//AVL_TREE_H