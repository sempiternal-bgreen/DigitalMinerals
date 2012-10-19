#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include <list>
#include <map>
using std::multimap;
using std::pair;
using std::list;

#include "Event.h"
#include "IListener.h"

class EventManager
{
private:
	//	Our Database, this will contain clients that can "listen" for events.
	multimap<EVENTID, IListener*>	m_ClientDatabase;

	//	Events waiting to be processed.
	list<Event>		m_CurrentEvents;

	//	Utility functions - private because they will only ever be used by this class.
	//
	//	Finds the event in the database and then calls each of the registered client's 
	//	EventHandler functions.
	void DispatchEvent(Event* pEvent);
	bool AlreadyRegistered(EVENTID eventID, IListener* pClient);

	EventManager() {}
	EventManager(const EventManager&);
	EventManager& operator=(const EventManager&);

	~EventManager() {}
	static EventManager* m_pInstance;

public:

	static EventManager* GetInstance(void)
	{
		if (m_pInstance == NULL )
			m_pInstance = new EventManager();

		return m_pInstance;
	}


	static void DeleteInstance()
	{
		if(m_pInstance)
			delete m_pInstance;
		m_pInstance = NULL;
	}

	//	This adds a client to the database.  This will make new "buckets" if necessary and then
	//	add the client to that given bucket.
	void RegisterClient(EVENTID eventID, IListener* pClient);

	//	Unregisters the client for the specified event only
	void UnregisterClient(EVENTID eventID, IListener* pClient);

	//	Removes the client from the database entirely
	void UnregisterClientAll(IListener* pClient);

	//	Sends an event to be processed later on.
	void SendEvent(EVENTID eventID, void* pData = NULL);

	//	Processes all events in our event list.
	void ProcessEvents(void);

	//	Clears all pending events
	void ClearEvents(void);

	//	Unregisters all objects
	void ShutdownEventSystem(void);
};

#endif // !EVENTMANAGER_H_