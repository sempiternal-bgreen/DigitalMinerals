#ifndef MAINMENUSTATE_H_
#define MAINMENUSTATE_H_

#include "IBaseState.h"

class Event;

class MainMenuState : public IBaseState
{
public:
	//	Inherited State Functions
	void Enter(void);
	void Input(float _fElapsedTime);
	void Update(float _fElapsedTime);
	void Render(float _fElapsedTime);
	void Exit(void);
	
	void HandleEvent( Event* pEvent );


	//	State Pointer
	static MainMenuState* GetInstance(void);
	static void DeleteInstance();

private:
	//	Constructor
	MainMenuState(void){};

	//	Copy Constructor
	MainMenuState(const MainMenuState&);

	//	Assignment Operator
	MainMenuState& operator=(const MainMenuState&);

	//	Destructor
	~MainMenuState(void){};
	
	static MainMenuState* m_pInstance;
};


#endif // !MAINMENUSTATE_H_
