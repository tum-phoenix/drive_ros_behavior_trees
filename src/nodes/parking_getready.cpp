/*
    --- Node description ---
    Used in: Parking
    Activation: Parking spot found
    Termination: Car is ready to apply parking technique
    Contains: Stopping, maybe repositioning
*/

#include <nodes/parking_getready.h>
#include <string>

NODES::ParkingGetready::ParkingGetready(std::string name) : BT::ActionNode(name)
{
    thread_ = std::thread(&NODES::ParkingGetready::WaitForTick, this);
}



void NODES::ParkingGetready::WaitForTick()
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
              if(!latestMessage.command.compare("Ready for parking")) {
                set_status(BT::SUCCESS);
                messageProcessed = true;
              }
            }
          }
          else {
            //Handle RC mode
          }
        }
    }
}

void NODES::ParkingGetready::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
