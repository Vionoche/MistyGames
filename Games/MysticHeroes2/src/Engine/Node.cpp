#include "Node.h"

#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>

Node::Node(const char* nodeName): _nodeName(nodeName)
{
    std::cout << "Node " << _nodeName << " was created" << std::endl;
}

std::string Node::GetName() const
{
    return _nodeName;
}

void Node::AddNode(Node* node)
{
    node->SetParent(this);
    _nodes[node->GetName()] = node;
}

void Node::SetParent(Node* parent)
{
    _parent = parent;
}

void Node::RemoveNode(const char* nodeName)
{
    const Node* node = _nodes[nodeName];
    _nodes.erase(nodeName);
    delete node;
}

Node* Node::GetNode(const char* nodeName)
{
    return _nodes[nodeName];
}

std::vector<Node*> Node::GetNodes() const
{
    std::vector<Node*> childNodes(_nodes.size());

    for (auto node : _nodes | std::views::values)
    {
        childNodes.push_back(node);
    }

    return childNodes;
}

Node::~Node()
{
    for (const auto& nodeName : _nodes | std::views::keys)
    {
        RemoveNode(nodeName.c_str());
    }

    std::cout << "Node " << _nodeName << " was destroyed" << std::endl;
}