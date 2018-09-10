/*
    --- Node description ---
    Used in: Parking
    Activation: Parking spot found
    Termination: Car is ready to apply parking technique
    Contains: Stopping, maybe repositioning
*/

#include <nodes/parking_getready.h>
#include <string>

NODE_PARKING_GETREADY::ParkingGetready::ParkingGetready(std::string name) : BT::ActionNode(name)
{
    thread_ = std::thread(&ParkingGetready::WaitForTick, this);
}



void ParkingGetready::WaitForTick()
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

void ParkingGetready::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
