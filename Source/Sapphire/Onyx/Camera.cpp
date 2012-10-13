#include "Camera.h"

void Camera::Initialize( void )
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
	m_fAspectRatio = 640.0f / 480.0f;
	m_fZNear = 0.01f;
	m_fZFar = 100.0f;

	D3DXMatrixPerspectiveFovLH( &ProjectionMatrix, m_fFieldOfView, m_fAspectRatio, m_fZNear, m_fZFar );
}

void Camera::Update( float time )
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
