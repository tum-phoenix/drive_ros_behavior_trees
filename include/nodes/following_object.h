#ifndef NODE_FOLLOWING_OBJECT
#define NODE_FOLLOWING_OBJECT

#include "action_node.h"

extern bool RCenabled;

class FollowingObject : public BT::ActionNode {
public:
    FollowingObject(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
