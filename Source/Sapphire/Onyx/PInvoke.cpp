#include "PInvoke.h"
#include "Timer.h"
#include "PostProcess.h"

__declspec(dllexport) void CALLBACK _InitializeD3D( HWND handle, float screenWidth, float screenHeight )
{
	Timer::GetInstance()->Reset();
	InitializeD3DRender( handle, screenWidth, screenHeight );
}
__declspec(dllexport) void CALLBACK _RenderD3D( )
{
	RenderD3DRender();
}
__declspec(dllexport) void CALLBACK _UpdateD3D()
{
	UpdateD3DRender();
}
__declspec(dllexport) void CALLBACK _ShutDownD3D()
{
	ShutDownD3DRender();
}
__declspec(dllexport) void CALLBACK _ResetD3D()
{
	ResetD3DRender();
}
__declspec(dllexport) int CALLBACK _GetFPS()
{
	return Timer::GetInstance()->GetFPS();
}
__declspec(dllexport) void CALLBACK _ToggleVSync( bool set )
{
	ToggleVSync( set );
}

__declspec(dllexport) void CALLBACK _TogglePostProcess( bool set )
{
	PostProcess::GetInstance()->m_bPostProcess = set;
}
__declspec(dllexport) void CALLBACK _SetPostProcessEffect( int set )
{
	PostProcess::GetInstance()->index = set;
}
__declspec(dllexport) void CALLBACK _PostProcessMaximizeThresholdColors()
{
	PostProcess::GetInstance()->MaximizeThresholdColors();
}

__declspec(dllexport) void CALLBACK _SetCameraToggle( bool set )
{
	SetCameraToggle( set );
}
