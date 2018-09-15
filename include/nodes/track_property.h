#ifndef NODE_TRACK_PROPERTY
#define NODE_TRACK_PROPERTY

#include <control_node.h>
#include <string>
#include "drive_ros_behavior_trees/BehaviorTreeMessage.h"

extern drive_ros_behavior_trees::BehaviorTreeMessage latestMessage;
extern bool messageProcessed;
extern bool TPnodesActive[];

class TrackPropertyNode : public BT::ControlNode
{
public:
    // Constructor
    explicit TrackPropertyNode(std::string name, int threshold_M);
    ~TrackPropertyNode();
    int DrawType();
    BT::ReturnStatus Tick();
    void Halt();

    unsigned int get_threshold_M();
    void set_threshold_M(unsigned int threshold_M);

private:
    unsigned int threshold_M_;
    unsigned int success_childred_num_;
    unsigned int failure_childred_num_;
};

#endif  // PARALLEL_NODE_H
