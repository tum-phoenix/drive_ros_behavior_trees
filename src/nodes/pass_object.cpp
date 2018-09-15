/*
    --- Node description ---
    Used in: Obstacles
    Activation: Object (dynamic or static) detected and car is on the left lane
    Termination: Object isn't detected any more
    Contains: Driving on the left lane.
*/

#include <ros/ros.h>
#include <nodes/pass_object.h>
#include <string>

NODE_PASS_OBJECT::PassObject::PassObject(std::string name):
  BT::ActionNode(name)
{
  thread_ = std::thread(&PassObject::WaitForTick, this);
}

void PassObject::WaitForTick()
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

void PassObject::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
