/*
    --- Node description ---
    Used in: Obstacles
    Activation: Barred area detected and car is on left lane
    Termination: barred area isn't detected any more
    Contains: Driving on the left lane.
*/

#include <ros/ros.h>
#include <nodes/pass_barred_area.h>
#include <string>

NODES::PassBarredArea::PassBarredArea(std::string name):
  BT::ActionNode(name)
{
  thread_ = std::thread(&NODES::PassBarredArea::WaitForTick, this);
}

void NODES::PassBarredArea::WaitForTick()
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
            /* General actions */
            if(!messageProcessed) {
              /* Action when message is received */
              messageProcessed = true;
            }
          }
          else {
            //Handle RC mode
          }
        }
    }
}

void NODES::PassBarredArea::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
