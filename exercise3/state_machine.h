#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <systemc.h>

SC_MODULE(stateMachine){
    sc_in<char> input;
    sc_in<bool> clk;

    enum base {Start, G, GA, GAA, GAAG};
    base current_state, next_state;

    int inputcounter = 0 , sequencecounter = 0;

    SC_CTOR(stateMachine){
        SC_METHOD(process);
        sensitive << clk.pos();
        dont_initialize();
    }

    void process(){

        current_state = next_state;
        inputcounter++;
        // std::cout << inputcounter << " " << input.read() <<" @ " << sc_time_stamp() << std::endl;

        switch(current_state){

            case Start:
                if (input.read()=='G'){
                    next_state = G;
                }
                else{
                    next_state = Start;
                }
                break;

            case G:
                if (input.read()=='G'){
                    next_state = current_state;
                }
                else if (input.read()=='A'){
                    next_state = GA;
                }
                else {
                    next_state = Start;
                }
                break;

            case GA:
                if (input.read()=='G'){
                    next_state = G;
                
                }
                else if (input.read()=='A'){
                    next_state = GAA;
                }
                else {
                    next_state = Start;
                }
                break;

            case GAA:
                if (input.read()=='G'){
                    next_state = GAAG;
                    sequencecounter++;
                    std::cout << "State GAA{2,}+G No."<< sequencecounter << " reached at position " << inputcounter << std::endl;
                }
                else if (input.read()=='A'){
                    next_state = GAA;
                }
                else {
                    next_state = Start;
                }
                break;

            case GAAG:
                if (input.read()=='G'){
                    next_state = G;
                }
                else {
                    next_state = Start;
                }
                break;

            default:
                next_state = Start;
                break;
        }
    };
};

#endif // STATE_MACHINE_H


