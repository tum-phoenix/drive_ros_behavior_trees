#ifndef NODE_INTERSECTION_BREAK
#define NODE_INTERSECTION_BREAK

#include "action_node.h"

extern bool RCenabled;

class IntersectionBreak : public BT::ActionNode {
public:
    IntersectionBreak(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
