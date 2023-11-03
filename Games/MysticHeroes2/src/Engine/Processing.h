#pragma once

#include <stack>

#include "Node.h"

template<void(Node::* TFun)()>
void ProcessNodes(Node* root)
{
    if (root == nullptr)
    {
        return;
    }

    std::stack<Node*> stack;
    Node* current = root;

    while (current != nullptr || stack.empty() == false)
    {
        (current->*TFun)();

        if (current->HasNodes())
        {
            auto childNodes = current->GetNodes();
            std::reverse(childNodes.begin(), childNodes.end());

            for (auto childNode : childNodes)
            {
                stack.push(childNode);
            }
        }

        if (stack.empty() == false)
        {
            current = stack.top();
            stack.pop();
        }
        else
        {
            current = nullptr;
        }
    }
}
