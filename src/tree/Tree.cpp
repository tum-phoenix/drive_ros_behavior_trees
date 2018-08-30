#include <ros/ros.h>

#include <behavior_tree.h>
#include <iostream>

#include <nodes/initial_drive.h>
//#include <nodes/parking_pending.h>
//#include <nodes/parking_spot_search.h>
//#include <nodes/parking_getready.h>
//#include <nodes/parking_in_progress.h>
//#include <nodes/parking_reverse.h>

int main(int argc, char** argv) {
    ros::init(argc, argv, "BehaviorTree");
    ros::NodeHandle n;


//    try {
//        int tick_freq_ms = 100;

//        //Declare and initialize all BT nodes for PARKING mode
//        BT::SequenceNodeWithMemory* headNode_P = new BT::SequenceNodeWithMemory("headOfTree");
//        NODE_INITIAL_DRIVE::InitialDrive* initialDriveNode = new NODE_INITIAL_DRIVE::InitialDrive("1");
//        BT::SequenceNodeWithMemory* parkingPendingNode = new BT::SequenceNodeWithMemory("2");
//        NODE_PARKING_SPOT_SEARCH::ParkingSpotSearch* parkingSpotSearchNode = new NODE_PARKING_SPOT_SEARCH::ParkingSpotSearch("3");
//        NODE_PARKING_GETREADY::ParkingGetready* parkingGetReadyNode = new NODE_PARKING_GETREADY::ParkingGetready("4");
//        NODE_PARKING_IN_PROGRESS::ParkingInProgress* parkingInProgressNode = new NODE_PARKING_IN_PROGRESS::ParkingInProgress("5");
//        NODE_PARKING_REVERSE::ParkingReverse* parkingReverseNode = new NODE_PARKING_REVERSE::ParkingReverse("6");


//        headNode_P->AddChild(initialDriveNode);
//        headNode_P->AddChild(parkingPendingNode);
//        parkingPendingNode->AddChild(parkingSpotSearchNode);
//        parkingPendingNode->AddChild(parkingGetReadyNode);
//        parkingPendingNode->AddChild(parkingInProgressNode);
//        parkingPendingNode->AddChild(parkingReverseNode);

//        //Declare and initialize all BT nodes for OBSTACLES mode
//        BT::SequenceNodeWithMemory* headNode_O = new BT::SequenceNodeWithMemory("headOfTree");

//        //Fire up
//        Execute(headNode_P, tick_freq_ms);
//    } catch(BT::BehaviorTreeException& exception) {
//        std::cout << exception.what() << std::endl;
//    }

    return 0;
}
