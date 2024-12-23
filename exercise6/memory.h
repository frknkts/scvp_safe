#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <tlm.h>
#include <systemc.h>


// TODO: add your code here
template <unsigned int SIZE = 1024>
class memory : public sc_module,public tlm::tlm_fw_transport_if<> 
{
    private:

        // Mem size is in template, defaults to 1024
        unsigned char mem[SIZE];

    public:

        // Initiate the Member 
        tlm::tlm_target_socket<> tSocket;

        // Construct the Member 
        SC_CTOR(memory) : tSocket("tSocket")
        {   
            // Bind the socket to this class
            tSocket.bind(*this);
        }

        void b_transport(tlm::tlm_generic_payload &trans, sc_time &delay)
        {
            // Catch access out of bounds
            if (trans.get_address() >= SIZE)
            {
                trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
                return;
            }

            // 4 since processor 32-bit and already fixed in processor.h
            // see line 169: trans.set_data_length(4);
            if (trans.get_data_length() != 4)
            {
                trans.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
                return;
            }

            if (trans.get_command() == tlm::TLM_WRITE_COMMAND)
            {
                // Use get_data_ptr() to access data from trans!!
                memcpy( &mem[trans.get_address()], /*Destination with pointer access*/
                        trans.get_data_ptr(), /*Source via Interface Method*/
                        trans.get_data_length()); /*Data Size via Interface Method*/
            }
            else /* If no write -> READ */
            {
                // Memory safe handling of data
                memcpy(trans.get_data_ptr(), 
                        &mem[trans.get_address()], 
                        trans.get_data_length());
            }

            // Add delay of hardware to overall system delay
            delay = delay + sc_time(20, SC_NS);

            // Set response after action to OK
            trans.set_response_status(tlm::TLM_OK_RESPONSE);
        }

        // Dummy method
        virtual tlm::tlm_sync_enum nb_transport_fw(
            tlm::tlm_generic_payload& trans,
            tlm::tlm_phase& phase,
            sc_time& delay )
        {
            SC_REPORT_FATAL(this->name(),"nb_transport_fw is not implemented");
            return tlm::TLM_ACCEPTED;
        }

        // Dummy method
        bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans,
                                tlm::tlm_dmi& dmi_data)
        {
            SC_REPORT_FATAL(this->name(),"get_direct_mem_ptr is not implemented");
            return false;
        }

        // Dummy method
        unsigned int transport_dbg(tlm::tlm_generic_payload& trans)
        {
            SC_REPORT_FATAL(this->name(),"transport_dbg is not implemented");
            return 0;
        }
        
};

#endif // MEMORY_H
