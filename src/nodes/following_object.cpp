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

NODE_FOLLOWING_OBJECT::FollowingObject::FollowingObject(std::string name):
  BT::ActionNode(name)
{
  thread_ = std::thread(&FollowingObject::WaitForTick, this);
}

void FollowingObject::WaitForTick()
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

void FollowingObject::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
