/*
    --- Node description ---
    Used in: Parking
    Activation: Start of parking process
    Termination: Parking spot found
    Contains: Following the track, lookout for parking spot
*/

#include <ros/ros.h>
#include <RCMode.h>
#include <nodes/parking_spot_search.h>
#include <string>

extern int successfulParkingCount;

NODES::ParkingSpotSearch::ParkingSpotSearch(std::string name) : ActionNode::ActionNode(name)
{
    thread_ = std::thread(&NODES::ParkingSpotSearch::WaitForTick, this);
}



void NODES::ParkingSpotSearch::WaitForTick()
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

        while (get_status() != BT::HALTED && get_status() != BT::SUCCESS)
        {
          if(!RCenabled) {
            if(successfulParkingCount >= 2) {
              set_status(BT::FAILURE);
            }
            else {
              /* General actions */
              if(!messageProcessed) {
                if(!latestMessage.command.compare("Parking spot found")) {
                  set_status(BT::SUCCESS);
                  messageProcessed = true;
                }
              }
            }
          }
          else {
            handleRCMode();
          }
        }
    }
}

void NODES::ParkingSpotSearch::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
