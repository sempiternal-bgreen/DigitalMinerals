#ifndef ILISTENER_H_
#define ILISTENER_H_

#include "Event.h"

class IListener
{
public:
	IListener(void) {}
	virtual ~IListener(void) {}

	virtual void HandleEvent(Event* pEvent) = 0;
};

#endif // !ILISTENER_H_

