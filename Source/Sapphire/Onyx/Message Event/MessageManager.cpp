#include "MessageManager.h"

MessageManager* MessageManager::m_pInstance = nullptr;

MessageManager* MessageManager::GetInstance(void)
{	
	if (m_pInstance == NULL )
		m_pInstance = new MessageManager();

return m_pInstance;
}

void MessageManager::InitMessageSystem(MESSAGEPROC pfnMsgProc)
{
	//	Error check to make sure the message proc is valid.
	if (!pfnMsgProc)	return;

	//	Get the Msg Proc
	m_pfnMsgProc = pfnMsgProc;
}

void MessageManager::SendMsg(BaseMessage* pMsg)
{
	//	Make sure the message exists.
	if (!pMsg)	return;

	//	Send the message to the queue for processing later on.
	m_MsgQueue.push(pMsg);
}

void MessageManager::ProcessMessages(void)
{
	//	Error check to make sure we get a message proc.
	if(!m_pfnMsgProc)	return;

	//	go through the entire queue and process the messsages that are waiting.
	while(!m_MsgQueue.empty())
	{
		m_pfnMsgProc(m_MsgQueue.front());		//	Process the first message.
		delete m_MsgQueue.front();				//	Delete the message memory.
		m_MsgQueue.pop();						//	Go to the next message.
	}
}

void MessageManager::ClearMessages(void)
{
	//	Clear out any messages waititng.
	while(!m_MsgQueue.empty())
	{
		delete m_MsgQueue.front();
		m_MsgQueue.pop();
	}
}

void MessageManager::ShutdownMessageSystem(void)
{
	//	Clear out any messages waiting.
	ClearMessages();
	
	//	Clear the function pointer
	m_pfnMsgProc = NULL;

	DeleteInstance();
}