#pragma once

#include <string>
#include <unordered_map>

class Node
{
public:
    Node(const char* nodeName);

    Node(const Node& other) = delete;

    std::string GetName() const;

    void AddNode(Node* node);

    void SetParent(Node* parent);

    void RemoveNode(const char* nodeName);

    Node* GetNode(const char* nodeName);

    std::vector<Node*> GetNodes() const;

    virtual void EnterTree() {}

    virtual void Ready() {}

    virtual void Process() {}

    virtual void ExitTree() {}

    virtual ~Node();

protected:
    std::string _nodeName;
    Node* _parent = nullptr;
    std::unordered_map<std::string, Node*> _nodes;
};
