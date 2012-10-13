#ifndef PINVOKE_H_
#define PINVOKE_H_

#include "D3DRenderer.h"

extern "C"
{
__declspec(dllexport) void CALLBACK _InitializeD3D( HWND handle );
__declspec(dllexport) void CALLBACK _RenderD3D();
__declspec(dllexport) void CALLBACK _UpdateD3D();
__declspec(dllexport) void CALLBACK _ShutDownD3D();
__declspec(dllexport) void CALLBACK _ResetD3D();

__declspec(dllexport) int CALLBACK  _GetFPS();
__declspec(dllexport) void CALLBACK _ToggleVSync( bool set );
}

#endif
