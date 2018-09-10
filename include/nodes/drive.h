#ifndef NODE_DRIVE
#define NODE_DRIVE

#include "action_node.h"

extern bool RCenabled;

class Drive : public BT::ActionNode {
private:
    bool started;
public:
    Drive(std::string name);
    void start();
    void WaitForTick();
    void Halt() override;
};

#endif
