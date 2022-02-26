#pragma once
#include "avl_tree.h"
#include <locale>
#include <cassert>

int max(int a, int b)
{
    return (a > b ? a : b);
}

Node* AVLTree::insert(Record x, Node* node)
{
    if (node == nullptr)
    {
        node = new Node;
        node->rec = x;
        node->height = 0;
        node->left = node->right = nullptr;
    }
    else if (x < node->rec)
    {
        node->left = insert(x, node->left);
        if (height(node->left) - height(node->right) == 2)
        {
            if (x < node->left->rec)
                node = singleRightRotate(node);
            else
                node = doubleRightRotate(node);
        }
    }
    else if (x >= node->rec)
    {
        node->right = insert(x, node->right);
        if (height(node->right) - height(node->left) == 2)
        {
            if (x >= node->right->rec)
                node = singleLeftRotate(node);
            else
                node = doubleLeftRotate(node);
        }
    }

    node->height = max(height(node->left), height(node->right)) + 1;
    return node;
}

void AVLTree::makeEmpty(Node* node)
{
    if (node == nullptr) return;
    makeEmpty(node->left);
    makeEmpty(node->right);
    delete node;
}

Node* AVLTree::singleRightRotate(Node*& node)
{
    Node* u = node->left;
    node->left = u->right;
    u->right = node;
    node->height = max(height(node->left), height(node->right)) + 1;
    u->height = max(height(u->left), node->height) + 1;
    return u;
}

Node* AVLTree::singleLeftRotate(Node*& node)
{
    Node* u = node->right;
    node->right = u->left;
    u->left = node;
    node->height = max(height(node->left), height(node->right)) + 1;
    u->height = max(height(node->right), node->height) + 1;
    return u;
}

Node* AVLTree::doubleLeftRotate(Node*& node)
{
    node->right = singleRightRotate(node->right);
    return singleLeftRotate(node);
}

Node* AVLTree::doubleRightRotate(Node*& node)
{
    node->left = singleLeftRotate(node->left);
    return singleRightRotate(node);
}

Node* AVLTree::findMin(Node* node)
{
    if (node == nullptr)
        return nullptr;
    else if (node->left == nullptr)
        return node;
    else
        return findMin(node->left);
}

Node* AVLTree::findMax(Node* node)
{
    if (node == nullptr)
        return nullptr;
    else if (node->right == nullptr)
        return node;
    else
        return findMax(node->right);
}

int AVLTree::height(Node* node)
{
    return (node == nullptr ? -1 : node->height);
}

int AVLTree::getBalance(Node* node)
{
    if (node == nullptr)
        return 0;
    else
        return height(node->left) - height(node->right);
}

void AVLTree::inorder(Node* node)
{
    if (node == nullptr)
        return;
    std::cout << node->rec.auth << " " << node->rec.name << " "
        << node->rec.title << " " << node->rec.year << " " << node->rec.pages << std::endl;
    inorder(node->left);
    inorder(node->right);
}

AVLTree::AVLTree(std::string filename)
{ 
    root = nullptr;
    std::ifstream ifs(filename, std::ios::in | std::ios::binary);
    assert(ifs.is_open());
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
        this->insert(rec);
    }
    ifs.close();
}

void AVLTree::insert(Record x)
{
    root = insert(x, root);
}

void AVLTree::display()
{
    inorder(root);
    std::cout << std::endl;
}

void AVLTree::getRecByYear(Node* node, uint16_t from, uint16_t to, std::vector<Record>& results, std::string& publisher)
{
    if (node == nullptr)
        return;

    if (node->rec.year >= from && node->rec.year <= to && node->rec.title == publisher)
    {
        results.push_back(node->rec);
    }
    getRecByYear(node->left, from, to, results, publisher);
    getRecByYear(node->right, from, to, results, publisher);
}




std::vector<Record> AVLTree::getRecByYear(uint16_t from, uint16_t to, std::string& publisher)
{
    std::vector<Record> results{};
    if (from > to)
    {
        uint16_t tmp = to;
        to = from;
        from = tmp;
    }
    getRecByYear(root, from, to, results, publisher);
    std::sort(results.begin(), results.end());
    std::cout << "\nresults found : " << results.size() << std::endl;
    return results;
}

void AVLTree::getPublishers(Node* node, std::unordered_map<std::string, int> &map)
{
    if (node == nullptr) return;
    if (map.find(node->rec.title) == map.end())
    {
        map.insert(std::pair<std::string, int>(node->rec.title, 1));
    }
    else
    {
        map[node->rec.title]++;
    }
    getPublishers(node->left, map);
    getPublishers(node->right, map);
}

std::unordered_map<std::string, int> AVLTree::getPublishers()
{
    std::unordered_map<std::string, int> map{};
    getPublishers(root, map);
    return map;
}
