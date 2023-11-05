#pragma once

#include <ranges>
#include <string>
#include <unordered_map>

class Node
{
public:
    Node(const char* nodeName) : _nodeName(nodeName) {}

    Node(const Node& other) = delete;

    std::string GetName() const;

    void AddNode(Node* node);

    void SetParent(Node* parent);

    void RemoveNode(const char* nodeName);

    Node* GetNode(const char* nodeName);

    bool HasNodes() const;

    std::vector<Node*> GetNodes() const;

    virtual void Process() {}

    virtual void Draw() {}

    virtual ~Node();

protected:
    std::string _nodeName;
    Node* _parent = nullptr;
    std::unordered_map<std::string, Node*> _nodes;
};


template<class TNode>
TNode* FindNode(const std::vector<Node*>& nodes)
{
    for (int index = 0; index < static_cast<int>(nodes.size()); index++)
    {
        Node* current = nodes[index];
        if (TNode* node = dynamic_cast<TNode*>(current))
        {
            return node;
        }
    }

    return nullptr;
}

template<class TNode>
TNode* FindNode(const std::unordered_map<std::string, Node*>& nodes)
{
    for (auto current : nodes | std::views::values)
    {
        if (TNode* node = dynamic_cast<TNode*>(current))
        {
            return node;
        }
    }

    return nullptr;
}

template<class TNode>
std::vector<TNode*> FindNodes(const std::vector<Node*>& nodes)
{
    std::vector<TNode*> results;

    for (auto& current : nodes)
    {
        if (TNode* node = dynamic_cast<TNode*>(current))
        {
            results.push_back(node);
        }
    }

    return results;
}

template<class TNode>
std::vector<TNode*> FindNodes(const std::unordered_map<std::string, Node*>& nodes)
{
    std::vector<TNode*> results;

    for (auto current : nodes | std::views::values)
    {
        if (TNode* node = dynamic_cast<TNode*>(current))
        {
            results.push_back(node);
        }
    }

    return results;
}