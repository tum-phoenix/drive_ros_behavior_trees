/*
    --- Node description ---
    Used in: Parking
    Activation: Car is ready to start parking
    Termination: Parking failed / Car is in parking spot according to selected technique
    Contains: Applying the predefined parking technique (parallel or perpendicular -> specific instructions)
    Child nodes: -/-
*/

#include <parking_in_progress.h>
#include <string>

NODE_PARKING_IN_PROGRESS::ParkingInProgress(std::string name) : ActionNode::ActionNode(name)
{
    thread_ = std::thread(&ActionTestNode::WaitForTick, this)
}

NODE_PARKING_IN_PROGRESS::ParkingInProgress::~CONSTRUCTOR() {}


void NODE_PARKING_IN_PROGRESS::ParkingInProgress::WaitForTick()
{
    while (true)
    {
        // Waiting for the first tick to come
        DEBUG_STDOUT(get_name() << " WAIT FOR TICK");

        tick_engine.Wait();
        DEBUG_STDOUT(get_name() << " TICK RECEIVED");

        // Running state
        set_status(BT::RUNNING);
        // Perform action...

        while (get_status() != BT::HALTED)
        {
	/*HERE THE CODE TO EXECUTE FOR THE ACTION.
	 wHEN THE ACTION HAS FINISHED CORRECLTY, CALL set_status(BT::SUCCESS)
	IF THE ACTION FAILS, CALL set_status(BT::FAILURE)*/
        }

        ROS_INFO("Parking successful");
        //Increment successful parking counter
    }
}

void NODE_PARKING_IN_PROGRESS::ParkingInProgress::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}

BT::ReturnStatus NODE_PARKING_IN_PROGRESS::ParkingInProgress::Tick() {
  return BT::EXIT;
}

int NODE_PARKING_IN_PROGRESS::ParkingInProgress::DrawType() {
  return BT::ACTION;
}

void NODE_PARKING_IN_PROGRESS::ParkingInProgress::execute_callback(const behavior_tree_core::BTGoalConstPtr& ptr) {

}
