/*
    --- Node description ---
    Used in: Parking
    Activation: Start line crossed, successful parking count below 2
    Termination: Car is on track again, after parking has been performed
    Contains: The whole parking process. Search of parking spot, (positioning and )stopping, applying defined parking technique, driving out of parking spot
    Child nodes: parking_spot_search, parking_getready, parking_in_progress, parking_reverse
*/

#include <parking_pending.h>
#include <string>

NODE_PARKING_PENDING::ParkingPending(std::string name) : ActionNode::ActionNode(name)
{
    thread_ = std::thread(&ActionTestNode::WaitForTick, this)
}

NODE_PARKING_PENDING::ParkingPending::~CONSTRUCTOR() {}


void NODE_PARKING_PENDING::ParkingPending::WaitForTick()
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

void NODE_PARKING_PENDING::ParkingPending::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}

BT::ReturnStatus NODE_PARKING_PENDING::ParkingPending::Tick() {
  return BT::EXIT;
}

int NODE_PARKING_PENDING::ParkingPending::DrawType() {
  return BT::ACTION;
}

void NODE_PARKING_PENDING::ParkingPending::execute_callback(const behavior_tree_core::BTGoalConstPtr& ptr) {

}
