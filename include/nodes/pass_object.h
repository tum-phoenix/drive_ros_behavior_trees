#ifndef NODE_PASS_OBJECT
#define NODE_PASS_OBJECT

#include "action_node.h"

extern bool RCenabled;

class PassObject : public BT::ActionNode {
public:
    PassObject(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
