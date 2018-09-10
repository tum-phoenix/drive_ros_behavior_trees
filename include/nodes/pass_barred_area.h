#ifndef NODE_PASS_BARRED_AREA
#define NODE_PASS_BARRED_AREA

#include "action_node.h"

extern bool RCenabled;

class PassBarredArea : public BT::ActionNode {
public:
    PassBarredArea(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
