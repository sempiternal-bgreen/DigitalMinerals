#ifndef IBASESTATE_H_
#define IBASESTATE_H_

class IBaseState
{
public:
	virtual ~IBaseState(void) = 0{};
	virtual void Enter(void) = 0;
	virtual void Input(float fElapsedTime) = 0;
	virtual void Update(float fElapsedTime) = 0;
	virtual void Render(float fElapsedTime) = 0;
	virtual void Exit(void) = 0;
};

#endif // !IBASESTATE_H_