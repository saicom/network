#include "network_pch.h"
#include "event_handler.h"


// class Event_Handler
Event_Handler::Event_Handler()
{
    read = false;
    write = false;
    m_reactor = NULL;
}

Event_Handler::~Event_Handler()
{
}

Reactor* Event_Handler::reactor() 
{
    return m_reactor;
}

void Event_Handler::reactor(Reactor* reactor)
{
    m_reactor = reactor;
}


