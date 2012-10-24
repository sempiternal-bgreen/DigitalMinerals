#include "Camera.h"
#include "Math\matrix3.h"
#include "Math\matrix4.h"
#include "Math\vec3.h"

using namespace std;

void Camera::Initialize( float screenWidth, float screenHeight )
{
	Eye.x = 0.0f;
	Eye.y = 0.0f;
	Eye.z = -5.0f;

	At.x = 0.0f;
	At.y = 0.0f;
	At.z = 0.0f;

	Up.x = 0.0f;
	Up.y = 1.0f;
	Up.z = 0.0f;

	D3DXMatrixLookAtLH( &CameraMatrix, &Eye, &At, &Up );

	m_fFieldOfView = D3DXToRadian( 75.0f );
	m_fAspectRatio = screenWidth / screenHeight;
	m_fZNear = 0.01f;
	m_fZFar = 100.0f;

	D3DXMatrixPerspectiveFovLH( &ProjectionMatrix, m_fFieldOfView, m_fAspectRatio, m_fZNear, m_fZFar );

	bCameraIsLocked = false;
}

void Camera::Update( float time, float screenWidth, float screenHeight )
{
	//GetCursorPos( &mousePos );

	//if( GetAsyncKeyState( VK_RBUTTON ) )
	//{
	//	//toggle moving the camera around this location
	//	bCameraIsLocked = !bCameraIsLocked;

	//	if ( bCameraIsLocked )
	//	{
	//		GetCursorPos( &holdMousePos );
	//	}		
	//}		

	//if ( bCameraIsLocked && MouseHasMoved()  )
	//		MouseLook( CameraMatrix, time, screenWidth, screenHeight );

	//	if( GetAsyncKeyState( 'W' ) )	{ CameraMatrix._43 -= 10.0f * time; }
	//	if( GetAsyncKeyState( 'S' ) )	{ CameraMatrix._43 += 10.0f * time; }
	//	if( GetAsyncKeyState( 'A' ) )	{ CameraMatrix._41 += 10.0f * time; }
	//	if( GetAsyncKeyState( 'D' ) )	{ CameraMatrix._41 -= 10.0f * time; }
}

void Camera::MouseLook( D3DXMATRIX &matrix, float time, float screenWidth, float screenHeight )
{
	/*POINT tempMousePos;
	GetCursorPos( &tempMousePos );*/
	SetCursorPos( holdMousePos.x, holdMousePos.y );

	// How much has the mouse moved?
	float mouseDiff[2] = { float( mousePos.x - holdMousePos.x ), float( mousePos.y - holdMousePos.y ) };

	mouseDiff[0] *= 0.1f; 
	mouseDiff[1] *= 0.1f;

	D3DXMATRIX yRot = matrix;
	D3DXMATRIX xRot = matrix;
	D3DXMatrixIdentity(&yRot);
	D3DXMatrixIdentity(&xRot);
	D3DXMatrixRotationY( &yRot, D3DXToRadian( mouseDiff[0] ) );
	D3DXMatrixRotationX( &xRot, D3DXToRadian( mouseDiff[1] ) );

	// Rotate the camera about the y and x axes
	matrix *= yRot;// * matrix;
	matrix *= xRot;// * matrix;
	//D3DXMatrixRotationY( &matrix, D3DXToRadian( mouseDiff[0] ) );
	//D3DXMatrixRotationX( &matrix, D3DXToRadian( mouseDiff[1] ) );

	NormalizeCameraMatrix();
}

void Camera::NormalizeCameraMatrix()
{
	D3DXVECTOR3 VectorZ( CameraMatrix._31, CameraMatrix._32, CameraMatrix._33 );
	D3DXVec3Normalize( &VectorZ, &VectorZ );

	D3DXVECTOR3 VectorX;
	D3DXVec3Cross( &VectorX, &Up, &VectorZ );

	D3DXVec3Normalize( &VectorX, &VectorX );

	D3DXVECTOR3 VectorY;
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

bool Camera::MouseHasMoved()
{
	return (mousePos.x == holdMousePos.x && mousePos.y == holdMousePos.y) ? false : true;
}