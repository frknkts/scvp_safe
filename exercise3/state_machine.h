#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <systemc.h>

SC_MODULE(stateMachine){
    sc_in<char> input;
    sc_in<bool> clk;

    enum base {START, G, GA, GAA, GAAG};

    sc_signal<base> state;

    int inputcounter = 0 , sequencecounter = 0;

    SC_CTOR(stateMachine){
        SC_METHOD(process);
        sensitive << clk.pos();
        dont_initialize();
    }

    void process() {

        inputcounter++;
        // std::cout << inputcounter << " " << input.read() <<" @ " << sc_time_stamp() << std::endl;

        switch(state){
            case START: 
                if (input.read() == 'G'){
                    state = G;
                } else {
                    state = START;
                }
            break;
            case G:
                if (input.read() == 'A'){
                    state = GA;
                } else if (input.read() == 'G'){
                    state = G;
                } else {
                    state = START;
                }
            break;
            case GA:
                if (input.read() == 'A'){
                    state = GAA;
                } else if (input.read() == 'G'){
                    state = G;
                } else {
                    state = START;
                }
            break;
            case GAA:
                if (input.read() == 'G'){
                    state = GAAG;
                    sequencecounter++;
                    std::cout << "State GAA{2,}+G No."<< sequencecounter << " reached at position " << inputcounter << std::endl;
                } else if (input.read() == 'A'){
                    state = GAA;
                } else {
                    state = START;
                }
            break;
            case GAAG:
                if (input.read() == 'G'){
                    state = G;
                } else {
                    state = START;
                }
            break;
        }
    }
};

#endif // STATE_MACHINE_H


