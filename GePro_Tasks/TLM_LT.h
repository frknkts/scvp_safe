#pragma once
#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/multi_passthrough_target_socket.h>
#include <tlm_utils/multi_passthrough_initiator_socket.h>
#include <cassert>

using namespace sc_core;
using namespace std;

// Define the Interconnect module
class Interconnect : public sc_module {
public:
    // Target socket for incoming transactions
    tlm_utils::multi_passthrough_target_socket<Interconnect> tSocket;
    // Initiator socket for outgoing transactions
    tlm_utils::multi_passthrough_initiator_socket<Interconnect> iSocket;

    // Constructor with memory size and routing delay parameters
    SC_HAS_PROCESS(Interconnect);
    Interconnect(sc_module_name name, uint64_t memSize, sc_time routingDelay)
        : sc_module(name), _memSize(memSize), _routingDelay(routingDelay) {
        // Register callback for the b_transport interface
        tSocket.register_b_transport(this, &Interconnect::b_transport);
    }

protected:
    uint64_t _memSize; // Size of each memory
    sc_time _routingDelay; // Routing delay

    // TLM-2 blocking transport method
    void b_transport(int id, tlm::tlm_generic_payload& trans, sc_time& delay) {
        tlm::tlm_command cmd = trans.get_command();
        sc_dt::uint64 addr = trans.get_address();
        
        // Adjust the address based on memory size
        uint64_t targetId = addr / _memSize;
        assert(targetId < iSocket.size()); // Ensure the target exists

        // Adjust the address for the target memory
        addr = addr % _memSize;
        trans.set_address(addr);

        // Add the routing delay
        delay += _routingDelay;

        // Forward the transaction to the target memory
        iSocket[targetId]->b_transport(trans, delay);
    }
};
