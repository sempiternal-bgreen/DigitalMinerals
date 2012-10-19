#ifndef MESSAGE_H_
#define MESSAGE_H_

typedef int MSGID;

//enum eActions { ACT_RUN, ACT_FIRE, JUMP, DUCK };
//enum eElements { ELM_EARTH, WIND, ELM_FIRE, WATER, HEART};

enum eMsgTypes { MSG_NULL = 0, MSG_MAX };

class BaseMessage
{
private:
	MSGID	m_msgID;

public:
	BaseMessage(MSGID msgID)
	{
		m_msgID = msgID;
	}

	virtual ~BaseMessage(void) {}

	MSGID GetMsgID(void)	{ return m_msgID; }
};

#endif // !MESSAGE_H_