#ifndef PLACE_H
#define PLACE_H

#include <systemc.h>

// Place Interface:
// TODO
class placeInterface: public sc_interface{

public:
    // Virtual functions which need to be implemented by the class inheriting them
    virtual void addTokens() = 0;
    virtual void removeTokens() = 0;
    virtual bool testTokens() = 0;

    virtual ~placeInterface() {}
};

// Place Channel:
// TODO
template<unsigned int Win = 1, unsigned int Wout = 1>
class place : public placeInterface {
    private:

    unsigned int tokens; // Number of tokens in this place

    public:

    // Constructor to initialize the tokens
    place(unsigned int initial_tokens = 0) : tokens(initial_tokens) {}

    void addTokens() override {
        tokens += Win;
    }

    void removeTokens() override {
        if (testTokens())
        {
            tokens -= Wout;
        }
    }

    bool testTokens() override 
    {
        return (tokens >= Wout) ;
    }
};

#endif // PLACE_H
