/*
    --- Node description ---
    Used in: Parking
    Activation: Parking finished successfully
    Termination: Car is on track again, after parking has been performed
    Contains: Reversing the taken steps to get back on track
*/

#include <nodes/parking_reverse.h>
#include <RCMode.h>
#include <string>

extern int successfulParkingCount;

NODES::ParkingReverse::ParkingReverse(std::string name) : ActionNode::ActionNode(name)
{
    thread_ = std::thread(&NODES::ParkingReverse::WaitForTick, this);
}


void NODES::ParkingReverse::WaitForTick()
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

            successfulParkingCount++;
            set_status(BT::SUCCESS);
          }
          else {
            handleRCMode();
          }
        }
    }
}

void NODES::ParkingReverse::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
