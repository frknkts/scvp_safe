#include <systemc.h>

#include "place.h"
#include "transition.h"
#include "subnet.h"

// Toplevel:
// TODO

SC_MODULE(toplevel) {
    // Declare places and transitions
    place p1;         // First place
    place p2;         // Second place
    transition t1;    // Transition from p1 to p2
    transition t2;    // Transition from p2 to p1

    SC_CTOR(toplevel) : p1(1), p2(0), t1("t1"), t2("t2") { // Initialize places and transitions
        // Connect ports for t1
        t1.in(p1);   // t1 takes input from p1
        t1.out(p2);  // t1 outputs to p2

        // Connect ports for t2
        t2.in(p2);   // t2 takes input from p2
        t2.out(p1);  // t2 outputs to p1

        // Define the test process
        SC_THREAD(process);
    }

    void process() {
        while (true) {
            // std::cout << p1.testTokens() << " :Tokens in p1 " <<" @ " << sc_time_stamp() << " " << sc_delta_count_at_current_time() << std::endl;
            
            wait(10, SC_NS);
            t1.fire(); // Attempt to fire t1

            // std::cout << p1.testTokens() << " :Tokens in p1 " <<" @ " << sc_time_stamp() << " " << sc_delta_count_at_current_time() << std::endl;

            wait(10, SC_NS);
            t1.fire(); // Attempt to fire t1 again

            // std::cout << p1.testTokens() << " :Tokens in p1 " <<" @ " << sc_time_stamp() << " " << sc_delta_count_at_current_time() << std::endl;

            wait(10, SC_NS);
            t2.fire(); // Attempt to fire t2

            sc_stop(); // End the simulation
        }
    }
};

int sc_main(int, char**)
{
    // TODO
    toplevel t("t");

    sc_start();
    return 0;
}
