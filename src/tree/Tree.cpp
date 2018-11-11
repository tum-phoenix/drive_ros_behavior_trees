#include <ros/ros.h>

#include <behavior_tree.h>
#include <iostream>
#include <vector>

#include "drive_ros_behavior_trees/BehaviorTreeMessage.h"

#include <nodes/initial_drive.h>
#include <nodes/parking_spot_search.h>
#include <nodes/parking_getready.h>
#include <nodes/parking_in_progress.h>
#include <nodes/parking_reverse.h>
#include <nodes/drive.h>
#include <nodes/cross_intersection.h>

#include <nodes/track_property.h>
#include <nodes/switch_to_left_lane.h>
#include <nodes/switch_to_right_lane.h>
#include <nodes/pass_object.h>
#include <nodes/pass_barred_area.h>
#include <nodes/following_object.h>
#include <nodes/crosswalk_break.h>
#include <nodes/crosswalk_wait.h>
#include <nodes/intersection_break.h>
#include <nodes/intersection_wait.h>
#include <nodes/intersection_crossing.h>

drive_ros_behavior_trees::BehaviorTreeMessage latestMessage;
bool messageProcessed;
bool RCenabled;
bool TPnodesActive[5];

void subscriberCallback(const drive_ros_behavior_trees::BehaviorTreeMessage& msg) {
  latestMessage = msg;
  messageProcessed = false;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "BehaviorTree");
    ros::NodeHandle n;
    std::string mode;
    n.getParam("behavior_tree/mode", mode);

    ros::Subscriber sub = n.subscribe("behavior_tree_topic", 32, subscriberCallback);
    messageProcessed = true;

    RCenabled = false;

    try {
        int tick_freq_ms = 50;

        if(mode == "PARKING") {
          //Declare and initialize all BT nodes for PARKING mode
          BT::SequenceNodeWithMemory* headNode_P = new BT::SequenceNodeWithMemory("headOfTree");
          NODES::InitialDrive* initialDriveNode = new NODES::InitialDrive("Initial driving");
          BT::SequenceNodeWithMemory* doCourseNode = new BT::SequenceNodeWithMemory("Doing course...");

          BT::SequenceNodeWithMemory* parkingPendingNode = new BT::SequenceNodeWithMemory("Parking...");
          NODES::ParkingSpotSearch* parkingSpotSearchNode = new NODES::ParkingSpotSearch("Parking spot search");
          NODES::ParkingGetready* parkingGetReadyNode = new NODES::ParkingGetready("Parking-getready");
          NODES::ParkingInProgress* parkingInProgressNode = new NODES::ParkingInProgress("Parking in progress");
          NODES::ParkingReverse* parkingReverseNode = new NODES::ParkingReverse("Reversing parking");

          BT::SequenceNodeWithMemory* drivingNode = new BT::SequenceNodeWithMemory("Driving...");
          NODES::Drive* standardDrivingNode = new NODES::Drive("On normal track");
          NODES::CrossIntersection* intersectionNode = new NODES::CrossIntersection("Crossing intersection");

          headNode_P->AddChild(initialDriveNode);
          headNode_P->AddChild(doCourseNode);

          doCourseNode->AddChild(parkingPendingNode);
          doCourseNode->AddChild(drivingNode);

          parkingPendingNode->AddChild(parkingSpotSearchNode);
          parkingPendingNode->AddChild(parkingGetReadyNode);
          parkingPendingNode->AddChild(parkingInProgressNode);
          parkingPendingNode->AddChild(parkingReverseNode);
          drivingNode->AddChild(standardDrivingNode);
          drivingNode->AddChild(intersectionNode);

          //Fire up
          Execute(headNode_P, tick_freq_ms);
        }

        else if(mode == "OBSTACLES") {
          //Declare and initialize all BT nodes for OBSTACLES mode
          BT::SequenceNodeWithMemory* headNode_O = new BT::SequenceNodeWithMemory("headOfTree");
          NODES::InitialDrive* initialDriveNode = new NODES::InitialDrive("Initial driving");
          NODES::TrackPropertyNode* trackPropertyNode = new NODES::TrackPropertyNode("Driving", 5);

          BT::SequenceNodeWithMemory* staticLaneBlockingNode = new BT::SequenceNodeWithMemory("Handling static lane-blocking obstacle");
          NODES::SwitchToLeftLane* staticLaneBlockingLeftswitchNode = new NODES::SwitchToLeftLane("Switching to left lane");
          NODES::PassObject* staticLaneBlockingPassingNode = new NODES::PassObject("Passing...");
          NODES::SwitchToRightLane* staticLaneBlockingRightswitchNode = new NODES::SwitchToRightLane("Switching to right lane");

          BT::SequenceNodeWithMemory* barredAreaNode = new BT::SequenceNodeWithMemory("Barred Area");
          NODES::SwitchToLeftLane* barredAreaLeftswitchNode = new NODES::SwitchToLeftLane("Switching to left lane");
          NODES::PassBarredArea* barredAreaPassingNode = new NODES::PassBarredArea("Passing...");
          NODES::SwitchToRightLane* barredAreaRightswitchNode = new NODES::SwitchToRightLane("Switching to right lane");

          BT::SequenceNodeWithMemory* dynamicObjectHandlingNode = new BT::SequenceNodeWithMemory("Handling dynamic obstacle");
          NODES::FollowingObject* followingObjectNode = new NODES::FollowingObject("Following...");
          BT::SequenceNodeWithMemory* dynamicObjectAvoidingNode = new BT::SequenceNodeWithMemory("Avoiding dynamic obstacle");
          NODES::SwitchToLeftLane* dynamicObjectLeftswitchNode = new NODES::SwitchToLeftLane("Switching to left lane");
          NODES::PassObject* dynamicObjectPassingNode = new NODES::PassObject("Passing...");
          NODES::SwitchToRightLane* dynamicObjectRightswitchNode = new NODES::SwitchToRightLane("Switching to right lane");

          BT::SequenceNodeWithMemory* crosswalkNode = new BT::SequenceNodeWithMemory("Handling Crosswalk");
          NODES::CrosswalkBreak* crosswalkBreakNode = new NODES::CrosswalkBreak("Breaking...");
          NODES::CrosswalkWait* crosswalkWaitNode = new NODES::CrosswalkWait("Waiting...");

          BT::FallbackNodeWithMemory* intersectionHandlingNode = new BT::FallbackNodeWithMemory("Handling intersection");
          BT::SequenceNodeWithMemory* intersectionGiveWayNode = new BT::SequenceNodeWithMemory("Giving way");
          NODES::IntersectionBreak* intersectionBreakNode = new NODES::IntersectionBreak("Breaking...");
          NODES::IntersectionWait* intersectionWaitNode = new NODES::IntersectionWait("Waiting...");
          NODES::IntersectionCrossing* intersecionCrossingNode = new NODES::IntersectionCrossing("Crossing intersection");
          NODES::IntersectionCrossing* intersectionDirectCrossingNode = new NODES::IntersectionCrossing("Crossing intersection without waiting");

          headNode_O->AddChild(initialDriveNode);
          headNode_O->AddChild(trackPropertyNode);

          trackPropertyNode->AddChild(staticLaneBlockingNode);
          trackPropertyNode->AddChild(barredAreaNode);
          trackPropertyNode->AddChild(dynamicObjectHandlingNode);
          trackPropertyNode->AddChild(crosswalkNode);
          trackPropertyNode->AddChild(intersectionHandlingNode);

          staticLaneBlockingNode->AddChild(staticLaneBlockingLeftswitchNode);
          staticLaneBlockingNode->AddChild(staticLaneBlockingPassingNode);
          staticLaneBlockingNode->AddChild(staticLaneBlockingRightswitchNode);
          barredAreaNode->AddChild(barredAreaLeftswitchNode);
          barredAreaNode->AddChild(barredAreaPassingNode);
          barredAreaNode->AddChild(barredAreaRightswitchNode);
          dynamicObjectHandlingNode->AddChild(followingObjectNode);
          dynamicObjectHandlingNode->AddChild(dynamicObjectAvoidingNode);
          dynamicObjectAvoidingNode->AddChild(dynamicObjectLeftswitchNode);
          dynamicObjectAvoidingNode->AddChild(dynamicObjectPassingNode);
          dynamicObjectAvoidingNode->AddChild(dynamicObjectRightswitchNode);
          crosswalkNode->AddChild(crosswalkBreakNode);
          crosswalkNode->AddChild(crosswalkWaitNode);
          intersectionHandlingNode->AddChild(intersectionGiveWayNode);
          intersectionHandlingNode->AddChild(intersectionDirectCrossingNode);
          intersectionGiveWayNode->AddChild(intersectionBreakNode);
          intersectionGiveWayNode->AddChild(intersectionWaitNode);

          Execute(headNode_O, tick_freq_ms);
        }

        else ROS_INFO("Wrong driving mode declared. Check behaviorTree.launch");
    } catch(BT::BehaviorTreeException& exception) {
        std::cout << exception.what() << std::endl;
    }

    return 0;
}
