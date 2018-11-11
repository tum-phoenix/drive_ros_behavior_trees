/*
    --- Node description ---
    Used in: Obstacles
    Activation: Dynamic object detected in front of the car
    Termination: (The object is not in front of the car any more) or (passing maneuver started)
    Contains: Following the track maintaining a minimum distance to the object
*/

#include <ros/ros.h>
#include <nodes/following_object.h>
#include <string>

NODES::FollowingObject::FollowingObject(std::string name):
  BT::ActionNode(name)
{
  thread_ = std::thread(&NODES::FollowingObject::WaitForTick, this);
}

void NODES::FollowingObject::WaitForTick()
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

void NODES::FollowingObject::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
