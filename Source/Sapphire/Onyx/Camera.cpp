#include "Camera.h"
#include "Math\matrix3.h"
#include "Math\matrix4.h"
#include "Math\vec3.h"

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

	m_fFieldOfView = D3DXToRadian( 75.0f );
	m_fAspectRatio = width / height;
	m_fZNear = 0.01f;
	m_fZFar = 100.0f;

	D3DXMatrixPerspectiveFovLH( &ProjectionMatrix, m_fFieldOfView, m_fAspectRatio, m_fZNear, m_fZFar );
}

void Camera::Update( float time, float screenWidth, float screenHeight )
{
	if( GetAsyncKeyState( VK_RBUTTON ) )
	{
		MouseLook( CameraMatrix, time, screenWidth, screenHeight );

		if( GetAsyncKeyState( 'W' ) )	{ CameraMatrix._43 -= 1.0f * time; }
		if( GetAsyncKeyState( 'S' ) )	{ CameraMatrix._43 += 1.0f * time; }
		if( GetAsyncKeyState( 'A' ) )	{ CameraMatrix._41 += 1.0f * time; }
		if( GetAsyncKeyState( 'D' ) )	{ CameraMatrix._41 -= 1.0f * time; }
	}
}

void Camera::MouseLook( D3DXMATRIX matrix, float time, float screenWidth, float screenHeight )
{
	
	POINT mousePos;
	GetCursorPos( &mousePos );
	SetCursorPos( (int)screenWidth / 2, (int)screenHeight / 2 );

	float mouseDiff[2] = { float( screenWidth - mousePos.x ), float( mousePos.y - screenHeight ) };

	mouseDiff[0] *= time;
	mouseDiff[1] *= time;

	D3DXMatrixRotationY( &matrix, D3DXToRadian( mouseDiff[0] ) );
	D3DXMatrixRotationX( &matrix, D3DXToRadian( mouseDiff[1] ) );

	D3DXVECTOR3 VectorZ( matrix._31, matrix._32, matrix._33 );
	D3DXVec3Normalize( &VectorZ, &VectorZ );

	D3DXVECTOR3 VectorX( matrix._11, matrix._12, matrix._13 );
	D3DXVec3Cross( &VectorX, &VectorZ, &Up );

	D3DXVec3Normalize( &VectorX, &VectorX );

	D3DXVECTOR3 VectorY( matrix._21, matrix._22, matrix._23 );
	D3DXVec3Cross( &VectorY, &VectorZ, &VectorX );

	D3DXVec3Normalize( &VectorY, &VectorY );

	CameraMatrix._11 = VectorX.x;
	CameraMatrix._12 = VectorX.y;
	CameraMatrix._13 = VectorX.z;

	CameraMatrix._21 = VectorY.x;
	CameraMatrix._22 = VectorY.y;
	CameraMatrix._23 = VectorY.z;

	CameraMatrix._31 = VectorZ.x;
	CameraMatrix._32 = VectorZ.y;
	CameraMatrix._33 = VectorZ.z;
}