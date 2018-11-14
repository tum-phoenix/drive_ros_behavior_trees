/*
    --- Node description ---
    Used in: Obstacles
    Activation: Intersection detected
    Termination: Car velocity is 0
    Contains: Breaking and following the track.
*/

#include <drive_ros_behavior_trees/VelocityService.h>

#include <ros/ros.h>
#include <RCMode.h>
#include <nodes/intersection_break.h>
#include <string>

extern ros::ServiceClient velocityClient;

NODES::IntersectionBreak::IntersectionBreak(std::string name):
  BT::ActionNode(name)
{
  thread_ = std::thread(&NODES::IntersectionBreak::WaitForTick, this);
}

void NODES::IntersectionBreak::WaitForTick()
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
              //TODO: Send command to stop the car!!!
              //This assumes the car is always in an appropriate position on the lane while looking for a parking spot.
              drive_ros_behavior_trees::VelocityService vs;
              do {
                if(!velocityClient.call(vs)) ROS_ERROR("Velocity Service call failed.");
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
              }
              while(vs.response.velocity != 0); //Maybe use some tolerance value?
              set_status(BT::SUCCESS);
            }
          }
          else {
            handleRCMode();
          }
        }
    }
}

void NODES::IntersectionBreak::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
