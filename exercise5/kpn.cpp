#include <unistd.h>
#include <systemc.h>

#include "kpn.h"

// ADD THINGS HERE

// Add Process
void kpn::add() 
{
    while (true) 
    {
        b.write(a.read() + c.read());
    }
}

// Split Process
void kpn::split() 
{
    for (int i = 0; i < 10; ++i) 
    {   
        // Needs temp_val since multiple blocking reads will empty the fifo  
        int temp_val = b.read();

        a.write(temp_val);
        d.write(temp_val);
        e.write(temp_val);

        // Uses temp_val to not remove item from signal e 
        // Also not specified if value written to e or current value of e needs to be printed
        std::cout << "Output e: " << temp_val << " @ " << sc_time_stamp() << " Δ: " << sc_delta_count() << std::endl;
    }
    
    sc_stop(); // Terminate simulation after 10 prints
}

// Delay Process
void kpn::delay() 
{
    while (true) 
    {
        c.write(d.read());
    }
}