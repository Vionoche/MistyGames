#pragma once

#include "../Engine/Node.h"

class ConsolePrinter : public Node
{
public:
    ConsolePrinter(const char* nodeName)
        : Node(nodeName)
    {
    }

    virtual void Draw() {}

    void SendNotification(const NotificationType notificationType) override
    {
        if (notificationType == NotificationType::Draw)
        {
            Draw();
        }

        Node::SendNotification(notificationType);
    }
};