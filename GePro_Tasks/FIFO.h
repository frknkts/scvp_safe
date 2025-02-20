#ifndef SIMPLE_FIFO_H
#define SIMPLE_FIFO_H

#include <systemc>
#include <queue>

class SimpleFifo : public sc_core::sc_interface
{
public:
    SimpleFifo(unsigned int maxDepth) : m_maxDepth(maxDepth) {}

    virtual unsigned int read()
    {
        while (m_queue.empty())
        {
            wait(m_dataAvailableEvent);
        }

        unsigned int value = m_queue.front();
        m_queue.pop();

        m_spaceAvailableEvent.notify();
        return value;
    }

    virtual void write(unsigned int val)
    {
        while (m_queue.size() >= m_maxDepth)
        {
            wait(m_spaceAvailableEvent);
        }

        m_queue.push(val);
        m_dataAvailableEvent.notify();
    }

    virtual const sc_core::sc_event& default_event() const
    {
        return m_dataAvailableEvent;
    }

private:
    std::queue<unsigned int> m_queue;
    unsigned int m_maxDepth;
    sc_core::sc_event m_dataAvailableEvent;
    sc_core::sc_event m_spaceAvailableEvent;
};

#endif // SIMPLE_FIFO_H