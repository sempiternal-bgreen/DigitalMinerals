#ifndef MESSAGEMANAGER_H_
#define MESSAGEMANAGER_H_

#include "Message.h"
#include <queue>
using std::queue;

typedef void (*MESSAGEPROC)(BaseMessage*);

class MessageManager
{
private:
	queue<BaseMessage*>			m_MsgQueue;				//	Stores my messages.
	MESSAGEPROC						m_pfnMsgProc;			//	Points to user defined function.

	MessageManager() { m_pfnMsgProc = NULL;	}
	MessageManager(const MessageManager&);
	MessageManager& operator=(const MessageManager&);

	~MessageManager() {}
	static MessageManager* m_pInstance;
public:
	
	static MessageManager* GetInstance(void);
	static void DeleteInstance()
	{
		if(m_pInstance)
			delete m_pInstance;
		m_pInstance = NULL;
	}
	//	How many messages waiting to be processed.
	inline int GetNumMessages(void) { return (int)m_MsgQueue.size(); }

	//	Setup the function pointer for our messages.
	void InitMessageSystem(MESSAGEPROC pfnMsgProc);

	//	Sends the message into the queue and awaits processing later on through
	//	The ProcessMessages() function.
	void SendMsg(BaseMessage* pMsg);

	//	Processes all the messages that are waiting inside of the queue.
	//	Normally you only call this function once per frame.
	void ProcessMessages(void);

	//	Clears any messages that may be remaining
	void ClearMessages(void);

	//	Clears any messages that may be remaining and sets the function pointer to NULL.
	void ShutdownMessageSystem(void);
};

#endif // !MESSAGEMANAGER_H_