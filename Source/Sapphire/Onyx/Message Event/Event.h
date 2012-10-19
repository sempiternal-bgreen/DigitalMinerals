#ifndef EVENT_H_
#define EVENT_H_

#include <string>
using std::string;

typedef string EVENTID;

class Event
{
private:
	EVENTID		m_EventID;
	void*		m_pParam;

public:
	Event(EVENTID _eventID, void* _pParam = nullptr)
	{
		m_EventID = _eventID;
		m_pParam  = _pParam;
	}

	~Event(){}

	inline EVENTID	GetEventID(void)	{ return m_EventID; }
	inline void*	GetParam(void)		{ return m_pParam; }
};

#endif