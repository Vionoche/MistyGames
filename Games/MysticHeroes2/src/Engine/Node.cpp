#include "Node.h"

#include <ranges>
#include <string>
#include <unordered_map>

const char* Node::GetName() const
{
    return _nodeName.c_str();
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

Node* Node::GetParent() const
{
    return _parent;
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

bool Node::HasNodes() const
{
    return !_nodes.empty();
}

std::vector<Node*> Node::GetNodes() const
{
    std::vector<Node*> childNodes;

    for (auto node : _nodes | std::views::values)
    {
        childNodes.push_back(node);
    }

    return childNodes;
}

void Node::QueueToDelete()
{
    NodeDeletingQueue::GetInstance().QueueToDelete(this);
}

Node::~Node()
{
    for (const auto& nodeName : _nodes | std::views::keys)
    {
        const Node* node = _nodes[nodeName];
        delete node;
    }
    _nodes.clear();
}
