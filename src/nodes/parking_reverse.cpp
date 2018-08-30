/*
    --- Node description ---
    Used in: Parking
    Activation: Parking finished successfully
    Termination: Car is on track again, after parking has been performed
    Contains: Reversing the taken steps to get back on track
    Child nodes: -/-
*/

#include <nodes/parking_reverse.h>
#include <string>

NODE_PARKING_REVERSE::ParkingReverse::ParkingReverse(std::string name) : ActionNode::ActionNode(name)
{
    thread_ = std::thread(&ParkingReverse::WaitForTick, this);
}


void ParkingReverse::WaitForTick()
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

void ParkingReverse::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}

BT::ReturnStatus ParkingReverse::Tick() {
  return BT::EXIT;
}

int ParkingReverse::DrawType() {
  return BT::ACTION;
}
/*
void NODE_PARKING_REVERSE::ParkingReverse::execute_callback(const behavior_tree_core::BTGoalConstPtr& ptr) {

}
*/
