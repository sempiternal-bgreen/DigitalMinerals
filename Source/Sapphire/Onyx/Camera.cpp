#include "Camera.h"

void Camera::Initialize( float width, float height )
{
	Eye.x = 0.0f;
	Eye.y = 2.0f;
	Eye.z = -5.0f;

	At.x = 0.0f;
	At.y = 0.0f;
	At.z = 0.0f;

	Up.x = 0.0f;
	Up.y = 1.0f;
	Up.z = 0.0f;

	D3DXMatrixLookAtLH( &CameraMatrix, &Eye, &At, &Up );

	m_fFieldOfView = D3DXToRadian( 75 );
	m_fAspectRatio = width / height;
	m_fZNear = 0.01f;
	m_fZFar = 100.0f;

	D3DXMatrixPerspectiveFovLH( &ProjectionMatrix, m_fFieldOfView, m_fAspectRatio, m_fZNear, m_fZFar );
}

void Camera::Update( float time )
{
	if( GetAsyncKeyState( VK_RBUTTON ) )
	{
		if( GetAsyncKeyState( 'W' ) )
		{
			CameraMatrix._43 -= 1.0f * time;
		}
		if( GetAsyncKeyState( 'S' ) )
		{
			CameraMatrix._43 += 1.0f * time;
		}
		if( GetAsyncKeyState( 'A' ) )
		{
			CameraMatrix._41 += 1.0f * time;
		}
		if( GetAsyncKeyState( 'D' ) )
		{
			CameraMatrix._41 -= 1.0f * time;
		}


	}
}

void Camera::MouseLook( D3DXMATRIX matrix, float time )
{
	POINT mousePos;
	GetCursorPos( &mousePos );
	SetCursorPos( 320, 240 );

	float mouseDiff[2] = { float( 320 - mousePos.x ), float( mousePos.y - 240 ) };


 
}