#include "EventManager.h"

EventManager* EventManager::m_pInstance = NULL;
//	Register Client.
void EventManager::RegisterClient( EVENTID eventID, IListener* pClient )
{
	//	Error check to make sure the client exists and hasn't been registered for this event already.
	if ( !pClient || AlreadyRegistered( eventID, pClient ) )	return;

	//	Register (Build) the database of clients.
	m_ClientDatabase.insert( make_pair( eventID, pClient ) );
}

//	Unregister Client
void EventManager::UnregisterClient( EVENTID eventID, IListener *pClient )
{
	//	Make an iterator that will iterate all of our clients that
	//	should be receiveing this event
	pair<multimap<EVENTID, IListener*>::iterator, 
		multimap<EVENTID, IListener*>::iterator> range;

	//	Find all of the clients that are able to receive this event.
	range = m_ClientDatabase.equal_range( eventID );

	//	Go through the list of clients that are able to receive this event.
	for( multimap<EVENTID, IListener*>::iterator mmIter = range.first;
		mmIter != range.second; mmIter++ )
	{
		//	check if the pointer is equal to the client
		if ( ( *mmIter ).second == pClient )
		{
			//	remove the client from the list
			mmIter = m_ClientDatabase.erase( mmIter );
			break;
		}
	}
}

//	Unregister Client All
void EventManager::UnregisterClientAll( IListener *pClient)
{
	multimap<string, IListener*>::iterator mmIter = m_ClientDatabase.begin();

	while(mmIter !=m_ClientDatabase.end())
	{
		if((*mmIter).second == pClient)
		{
			mmIter = m_ClientDatabase.erase(mmIter);
		}
		else
			mmIter++;
	}
}

//	Dispatch Event.
void EventManager::DispatchEvent(Event *pEvent)
{
	//	Make an iterator that will iterate all of our clients that
	//	should be receiveing this event
	pair<multimap<EVENTID, IListener*>::iterator,
		multimap<EVENTID, IListener*>::iterator> range;

	//	Find all of the clients that are able to receive this event.
	range = m_ClientDatabase.equal_range(pEvent->GetEventID());

	//	Go through the linked list of clients that are able to receive this event.
	for(multimap<EVENTID, IListener*>::iterator mmIter = range.first;
		mmIter != range.second; mmIter++)
	{
		//	Pass this event to the client
		(*mmIter).second->HandleEvent(pEvent);
	}
}

bool EventManager::AlreadyRegistered(EVENTID eventID, IListener* pClient)
{
	bool bIsAlreadyRegistered = false;

	//	Make an iterator that will iterate all of our clients that
	//	should be receiveing this event
	pair<multimap<EVENTID, IListener*>::iterator,
		multimap<EVENTID, IListener*>::iterator> range;

	//	Find all of the clients that are able to receive this event.
	range = m_ClientDatabase.equal_range(eventID);

	//	Go through the list of clients that are able to receive this event.
	for(multimap<EVENTID, IListener*>::iterator mmIter = range.first;
		mmIter != range.second; mmIter++)
	{
		//	check if the pointer is equal to the client
		if((*mmIter).second == pClient)
		{
			bIsAlreadyRegistered = true;
			break;
		}
	}

	return bIsAlreadyRegistered;
}


void EventManager::SendEvent(EVENTID eventID, void* pData)
{
	//	Push my event into the list.
	Event newEvent(eventID, pData);

	m_CurrentEvents.push_back(newEvent);
}

void EventManager::ProcessEvents(void)
{
	//	Go through my list of events that are waiting to be processed.
	while(m_CurrentEvents.size())
	{
		DispatchEvent(&m_CurrentEvents.front());
		m_CurrentEvents.pop_front();
	}
}

void EventManager::ClearEvents(void)
{
	m_CurrentEvents.clear();
}

void EventManager::ShutdownEventSystem(void)
{
	m_ClientDatabase.clear();
	m_CurrentEvents.clear();
	DeleteInstance();
}
