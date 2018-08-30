/*
    --- Node description ---
    Used in: Parking
    Activation: Parking spot found
    Termination: Car is ready to apply parking technique
    Contains: Stopping, maybe repositioning
    Child nodes: -/-
*/

#include <parking_getready.h>
#include <string>

NODE_PARKING_GETREADY::ParkingGetready(std::string name) : ActionNode::ActionNode(name)
{
    thread_ = std::thread(&ActionTestNode::WaitForTick, this)
}

NODE_PARKING_GETREADY::ParkingGetready::~CONSTRUCTOR() {}


void NODE_PARKING_GETREADY::ParkingGetready::WaitForTick()
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
    }
}

void NODE_PARKING_Getready::ParkingGetready::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}

BT::ReturnStatus NODE_PARKING_GETREADY::ParkingGetready::Tick() {
  return BT::EXIT;
}

int NODE_PARKING_GETREADY::ParkingGetready::DrawType() {
  return BT::ACTION;
}

void NODE_PARKING_GETREADY::ParkingGetready::execute_callback(const behavior_tree_core::BTGoalConstPtr& ptr) {

}
