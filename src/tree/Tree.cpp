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
          NODE_INITIAL_DRIVE::InitialDrive* initialDriveNode = new NODE_INITIAL_DRIVE::InitialDrive("Initial driving");
          BT::SequenceNodeWithMemory* doCourseNode = new BT::SequenceNodeWithMemory("Doing course...");

          BT::SequenceNodeWithMemory* parkingPendingNode = new BT::SequenceNodeWithMemory("Parking...");
          NODE_PARKING_SPOT_SEARCH::ParkingSpotSearch* parkingSpotSearchNode = new NODE_PARKING_SPOT_SEARCH::ParkingSpotSearch("Parking spot search");
          NODE_PARKING_GETREADY::ParkingGetready* parkingGetReadyNode = new NODE_PARKING_GETREADY::ParkingGetready("Parking-getready");
          NODE_PARKING_IN_PROGRESS::ParkingInProgress* parkingInProgressNode = new NODE_PARKING_IN_PROGRESS::ParkingInProgress("Parking in progress");
          NODE_PARKING_REVERSE::ParkingReverse* parkingReverseNode = new NODE_PARKING_REVERSE::ParkingReverse("Reversing parking");

          BT::SequenceNodeWithMemory* drivingNode = new BT::SequenceNodeWithMemory("Driving...");
          NODE_DRIVE::Drive* standardDrivingNode = new NODE_DRIVE::Drive("On normal track");
          NODE_CROSS_INTERSECTION::CrossIntersection* intersectionNode = new NODE_CROSS_INTERSECTION::CrossIntersection("Crossing intersection");

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
          NODE_INITIAL_DRIVE::InitialDrive* initialDriveNode = new NODE_INITIAL_DRIVE::InitialDrive("Initial driving");
          NODE_TRACK_PROPERTY::TrackPropertyNode* trackPropertyNode = new NODE_TRACK_PROPERTY::TrackPropertyNode("Driving", 5);

          BT::SequenceNodeWithMemory* staticLaneBlockingNode = new BT::SequenceNodeWithMemory("Handling static lane-blocking obstacle");
          NODE_SWITCH_TO_LEFT_LANE::SwitchToLeftLane* staticLaneBlockingLeftswitchNode = new NODE_SWITCH_TO_LEFT_LANE::SwitchToLeftLane("Switching to left lane");
          NODE_PASS_OBJECT::PassObject* staticLaneBlockingPassingNode = new NODE_PASS_OBJECT::PassObject("Passing...");
          NODE_SWITCH_TO_RIGHT_LANE::SwitchToRightLane* staticLaneBlockingRightswitchNode = new NODE_SWITCH_TO_RIGHT_LANE::SwitchToRightLane("Switching to right lane");

          BT::SequenceNodeWithMemory* barredAreaNode = new BT::SequenceNodeWithMemory("Barred Area");
          NODE_SWITCH_TO_LEFT_LANE::SwitchToLeftLane* barredAreaLeftswitchNode = new NODE_SWITCH_TO_LEFT_LANE::SwitchToLeftLane("Switching to left lane");
          NODE_PASS_BARRED_AREA::PassBarredArea* barredAreaPassingNode = new NODE_PASS_BARRED_AREA::PassBarredArea("Passing...");
          NODE_SWITCH_TO_RIGHT_LANE::SwitchToRightLane* barredAreaRightswitchNode = new NODE_SWITCH_TO_RIGHT_LANE::SwitchToRightLane("Switching to right lane");

          BT::SequenceNodeWithMemory* dynamicObjectHandlingNode = new BT::SequenceNodeWithMemory("Handling dynamic obstacle");
          NODE_FOLLOWING_OBJECT::FollowingObject* followingObjectNode = new NODE_FOLLOWING_OBJECT::FollowingObject("Following...");
          BT::SequenceNodeWithMemory* dynamicObjectAvoidingNode = new BT::SequenceNodeWithMemory("Avoiding dynamic obstacle");
          NODE_SWITCH_TO_LEFT_LANE::SwitchToLeftLane* dynamicObjectLeftswitchNode = new NODE_SWITCH_TO_LEFT_LANE::SwitchToLeftLane("Switching to left lane");
          NODE_PASS_OBJECT::PassObject* dynamicObjectPassingNode = new NODE_PASS_OBJECT::PassObject("Passing...");
          NODE_SWITCH_TO_RIGHT_LANE::SwitchToRightLane* dynamicObjectRightswitchNode = new NODE_SWITCH_TO_RIGHT_LANE::SwitchToRightLane("Switching to right lane");

          BT::SequenceNodeWithMemory* crosswalkNode = new BT::SequenceNodeWithMemory("Handling Crosswalk");
          NODE_CROSSWALK_BREAK::CrosswalkBreak* crosswalkBreakNode = new NODE_CROSSWALK_BREAK::CrosswalkBreak("Breaking...");
          NODE_CROSSWALK_WAIT::CrosswalkWait* crosswalkWaitNode = new NODE_CROSSWALK_WAIT::CrosswalkWait("Waiting...");

          BT::FallbackNodeWithMemory* intersectionHandlingNode = new BT::FallbackNodeWithMemory("Handling intersection");
          BT::SequenceNodeWithMemory* intersectionGiveWayNode = new BT::SequenceNodeWithMemory("Giving way");
          NODE_INTERSECTION_BREAK::IntersectionBreak* intersectionBreakNode = new NODE_INTERSECTION_BREAK::IntersectionBreak("Breaking...");
          NODE_INTERSECTION_WAIT::IntersectionWait* intersectionWaitNode = new NODE_INTERSECTION_WAIT::IntersectionWait("Waiting...");
          NODE_INTERSECTION_CROSSING::IntersectionCrossing* intersecionCrossingNode = new NODE_INTERSECTION_CROSSING::IntersectionCrossing("Crossing intersection");
          NODE_INTERSECTION_CROSSING::IntersectionCrossing* intersectionDirectCrossingNode = new NODE_INTERSECTION_CROSSING::IntersectionCrossing("Crossing intersection without waiting");

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
