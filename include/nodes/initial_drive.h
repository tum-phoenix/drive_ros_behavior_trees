#ifndef NODE_INITIAL_DRIVE
#define NODE_INITIAL_DRIVE

#include "action_node.h"

extern bool RCenabled;

class InitialDrive : public BT::ActionNode {
public:
    InitialDrive(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
