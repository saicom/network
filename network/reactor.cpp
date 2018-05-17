#include "network_pch.h"
#include "reactor.h"
#include "event_handler.h"
#include "buildconfig.h"

//list_node Reactor::HandlerTable[HANDLER_TABLE_SIZE];
std::map<uint32_t, Event_Handler*> Reactor::m_eventHandlerMap;

static inline uint32_t hashFn(uint32_t nKey)
{
    //return nKey % HANDLER_TABLE_SIZE;
	return 0;
}

//int Reactor::m_HandlerCount = 0;

Reactor::~Reactor()
{

}

void Reactor::initHandlerTable()
{
	//list_nodefor (int nIndex = 0; nIndex < HANDLER_TABLE_SIZE; nIndex++)
    //{
    //    INIT_LIST_NODE(&HandlerTable[nIndex]);
    //}
    //m_HandlerCount = 0;
}

Event_Handler* Reactor::getHandler(uint32_t id)
{
    //int npos = hashFn(id);
    //assert(npos < HANDLER_TABLE_SIZE && npos >= 0);
	
    Event_Handler* poEventHandler = nullptr;
	auto it = m_eventHandlerMap.find(id);
	if (it != m_eventHandlerMap.end()) {
		poEventHandler = it->second;
	}
	//list_node* head = &HandlerTable[npos];
	//list_node* pos;
    //list_for_each(pos, head)
    //{
    //    pEventHandler = list_entry(pos, Event_Handler, hashitem);
    //    if (pEventHandler->get_id() == id)
    //    {
    //        break;
    //    }
    //    pEventHandler = NULL;
    //}
    return poEventHandler;
}


void Reactor::putHandler(Event_Handler* poHandler, uint32_t id)
{
    assert(poHandler != nullptr);
    //int npos = hashFn(id);
    //assert(npos < HANDLER_TABLE_SIZE && npos >= 0);
	//list_node* head = &HandlerTable[npos];
    //list_add_tail(&pHandler->hashitem, head);
	m_eventHandlerMap.insert(std::make_pair(id, poHandler));
}

void Reactor::removeHandler(uint32_t id)
{
	m_eventHandlerMap.erase(id);
    //int npos = hashFn(id);
    //assert(npos < HANDLER_TABLE_SIZE && npos >= 0);
	//list_node* head = &HandlerTable[npos];
	//list_node* pos, *n;

    //Event_Handler* pEventHandler = NULL;
    //list_for_each_safe(pos, n, head)
    //{
    //    pEventHandler = list_entry(pos, Event_Handler, hashitem);
    //    if (pEventHandler->get_id() == id)
    //    {
    //        list_del(pos);
    //        m_HandlerCount--;
    //        break;
    //    }
    //}
}

void Reactor::removeHandler(Event_Handler* pHandler)
{
	removeHandler(pHandler->get_id());
    //list_del(&pHandler->hashitem);
    //m_HandlerCount--;
}

void Reactor::finitHandlerTable()
{
	//list_node *pos, *n;
	//list_node* head;
    //for (int nIndex = 0; nIndex < HANDLER_TABLE_SIZE; nIndex++)
    //{
    //    head = &HandlerTable[nIndex];
    //    list_for_each_safe(pos, n, head) 
    //    {
    //        Event_Handler* pEventHandler = list_entry(pos, Event_Handler, hashitem);
    //        list_del(pos);
    //        CnDelete pEventHandler;
    //    }
    //}
    //m_HandlerCount = 0;
	for (auto it = m_eventHandlerMap.begin(); it != m_eventHandlerMap.end(); ++it) {
		CnDelete it->second;
	}

	m_eventHandlerMap.clear();
}

int Reactor::end_reactor_event_loop()
{
	//list_node* pos;
	//list_node* head;
    //for (int nIndex = 0; nIndex < HANDLER_TABLE_SIZE; nIndex++)
    //{
    //    head = &HandlerTable[nIndex];
    //    list_for_each(pos, head)
    //    {
    //        Event_Handler *event_handler = list_entry(pos, Event_Handler, hashitem);
    //        event_handler->handle_close();
    //    }
    //}
	for (auto it = m_eventHandlerMap.begin(); it != m_eventHandlerMap.end(); ++it) {
		Event_Handler* event_handler = it->second;
		if (event_handler != nullptr) {
			event_handler->handle_close();
		}
	}
    return 0;
}


uint32_t Reactor::get_handler_count() {
	return m_eventHandlerMap.size();
}