#ifndef PINVOKE_H_
#define PINVOKE_H_

#include "D3DRenderer.h"

extern "C"
{
__declspec(dllexport) void CALLBACK _InitializeD3D( HWND handle, float screenWidth, float screenHeight );
__declspec(dllexport) void CALLBACK _RenderD3D();
__declspec(dllexport) void CALLBACK _UpdateD3D();
__declspec(dllexport) void CALLBACK _ShutDownD3D();
__declspec(dllexport) void CALLBACK _ResetD3D();

__declspec(dllexport) int CALLBACK  _GetFPS();
__declspec(dllexport) void CALLBACK _ToggleVSync( bool set );

__declspec(dllexport) void CALLBACK _TogglePostProcess( bool set );
__declspec(dllexport) void CALLBACK _SetPostProcessEffect( int set );
__declspec(dllexport) void CALLBACK _PostProcessMaximizeThresholdColors();

__declspec(dllexport) void CALLBACK _SetCameraToggle( bool set );
}

#endif
