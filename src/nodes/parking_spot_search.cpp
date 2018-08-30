/*
    --- Node description ---
    Used in: Parking
    Activation: Start of parking process
    Termination: Parking spot found
    Contains: Following the track, lookout for parking spot
    Child nodes: -/-
*/

#include <parking_spot_search.h>
#include <string>

NODE_PARKING_SPOT_SEARCH::ParkingSpotSearch(std::string name) : ActionNode::ActionNode(name)
{
    thread_ = std::thread(&ActionTestNode::WaitForTick, this)
}

NODE_PARKING_SPOT_SEARCH::ParkingSpotSearch::~CONSTRUCTOR() {}


void NODE_PARKING_SPOT_SEARCH::ParkingSpotSearch::WaitForTick()
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

void NODE_PARKING_SPOT_SEARCH::ParkingSpotSearch::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}

BT::ReturnStatus NODE_PARKING_SPOT_SEARCH::ParkingSpotSearch::Tick() {
  return BT::EXIT;
}

int NODE_PARKING_SPOT_SEARCH::ParkingSpotSearch::DrawType() {
  return BT::ACTION;
}

void NODE_PARKING_SPOT_SEARCH::ParkingSpotSearch::execute_callback(const behavior_tree_core::BTGoalConstPtr& ptr) {

}
