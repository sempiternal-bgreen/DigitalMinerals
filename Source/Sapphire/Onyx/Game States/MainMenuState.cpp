#include "MainMenuState.h"


MainMenuState* MainMenuState::m_pInstance = nullptr;

MainMenuState* MainMenuState::GetInstance( void )
{
	if (m_pInstance == nullptr )
		m_pInstance = new MainMenuState();

	return m_pInstance;
}

void MainMenuState::DeleteInstance()
{
	if(m_pInstance)
		delete m_pInstance;
	m_pInstance = nullptr;
}

void MainMenuState::HandleEvent( Event* pEvent )
{

}

void MainMenuState::Enter()
{

}
void MainMenuState::Input(float _fElapsedTime)
{

}

void MainMenuState::Update(float _fElapsedTime)
{

}
void MainMenuState::Render(float _fElapsedTime)
{

}
void MainMenuState::Exit(void)
{

}