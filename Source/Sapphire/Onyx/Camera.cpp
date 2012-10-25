#include "Camera.h"
#include "Math\matrix3.h"
#include "Math\matrix4.h"
#include "Math\vec3.h"

using namespace std;

D3DXVECTOR3 GetXAXIS( D3DXMATRIX &matrix )
{
	D3DXVECTOR3 vector;

	vector.x = matrix._11;
	vector.y = matrix._12;
	vector.z = matrix._13;

	return vector;
}

D3DXVECTOR3 GetYAXIS( D3DXMATRIX &matrix )
{
	D3DXVECTOR3 vector;

	vector.x = matrix._21;
	vector.y = matrix._22;
	vector.z = matrix._23;

	return vector;
}

D3DXVECTOR3 GetZAXIS( D3DXMATRIX &matrix )
{
	D3DXVECTOR3 vector;

	vector.x = matrix._31;
	vector.y = matrix._32;
	vector.z = matrix._33;

	return vector;
}

void Camera::Initialize( float screenWidth, float screenHeight )
{
	Eye.x = 0.0f;
	Eye.y = 0.0f;
	Eye.z = 0.0f;

	At.x = 0.0f;
	At.y = 0.0f;
	At.z = -5.0f;

	Up.x = 0.0f;
	Up.y = 1.0f;
	Up.z = 0.0f;

	D3DXMatrixIdentity( &CameraViewMatrix );

	//D3DXMatrixLookAtLH( &CameraViewMatrix, &Eye, &At, &Up );

	m_fFieldOfView = D3DXToRadian( 75.0f );
	m_fAspectRatio = screenWidth / screenHeight;
	m_fZNear = 1.0f;
	m_fZFar = 100.0f;

	D3DXMatrixPerspectiveFovLH( &ProjectionMatrix, m_fFieldOfView, m_fAspectRatio, m_fZNear, m_fZFar );

	//bCameraIsLocked = false;
}

void Camera::Update( float time, float screenWidth, float screenHeight )
{
	if( GetAsyncKeyState( 'W' ) )	
	{ 
		//CameraViewMatrix._43 -= 10.0f * time; 
		D3DXVECTOR3 temp = GetZAXIS( CameraViewMatrix );
		temp = temp * 10.0f * time;
		CameraViewMatrix._41 += temp.x;
		CameraViewMatrix._42 += temp.y;
		CameraViewMatrix._43 += temp.z;
	}
	if( GetAsyncKeyState( 'S' ) )	
	{ 
		D3DXVECTOR3 temp = GetZAXIS( CameraViewMatrix );
		temp = temp * 10.0f * time;
		CameraViewMatrix._41 -= temp.x;
		CameraViewMatrix._42 -= temp.y;
		CameraViewMatrix._43 -= temp.z; 
	}
	if( GetAsyncKeyState( 'A' ) )	
	{ 
		//CameraViewMatrix._41 += 10.0f * time; 
		D3DXVECTOR3 temp = GetXAXIS( CameraViewMatrix );
		temp = temp * 10.0f * time;
		CameraViewMatrix._41 -= temp.x;
		CameraViewMatrix._42 -= temp.y;
		CameraViewMatrix._43 -= temp.z; 
	}
	if( GetAsyncKeyState( 'D' ) )	
	{ 
		//CameraViewMatrix._41 -= 10.0f * time; 
		D3DXVECTOR3 temp = GetXAXIS( CameraViewMatrix );
		temp = temp * 10.0f * time;
		CameraViewMatrix._41 += temp.x;
		CameraViewMatrix._42 += temp.y;
		CameraViewMatrix._43 += temp.z; 
	}

	GetCursorPos( &mousePos );
	if( GetAsyncKeyState( VK_RBUTTON ) )
	{
		//bCameraIsLocked = !bCameraIsLocked;
		if ( bCameraIsLocked ) 
		{ 
			GetCursorPos( &holdMousePos ); 
		}
	}
	if ( bCameraIsLocked && MouseHasMoved()  ) 
	{ 
		MouseLook( CameraViewMatrix, time, screenWidth, screenHeight ); 
		//ShowCursor( false );
	}
}

void Camera::MouseLook( D3DXMATRIX &matrix, float time, float screenWidth, float screenHeight )
{
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

	matrix = xRot * matrix;
	matrix = yRot * matrix;

	NormalizeCameraMatrix();
}

void Camera::NormalizeCameraMatrix()
{
	D3DXVECTOR3 VectorZ( CameraViewMatrix._31, CameraViewMatrix._32, CameraViewMatrix._33 );
	D3DXVec3Normalize( &VectorZ, &VectorZ );

	D3DXVECTOR3 VectorX;
	D3DXVec3Cross( &VectorX, &Up, &VectorZ );

	D3DXVec3Normalize( &VectorX, &VectorX );

	D3DXVECTOR3 VectorY;
	D3DXVec3Cross( &VectorY, &VectorZ, &VectorX );

	D3DXVec3Normalize( &VectorY, &VectorY );

	CameraViewMatrix._11 = VectorX.x;
	CameraViewMatrix._12 = VectorX.y;
	CameraViewMatrix._13 = VectorX.z;

	CameraViewMatrix._21 = VectorY.x;
	CameraViewMatrix._22 = VectorY.y;
	CameraViewMatrix._23 = VectorY.z;

	CameraViewMatrix._31 = VectorZ.x;
	CameraViewMatrix._32 = VectorZ.y;
	CameraViewMatrix._33 = VectorZ.z;
}

bool Camera::MouseHasMoved()
{
	return (mousePos.x == holdMousePos.x && mousePos.y == holdMousePos.y) ? false : true;
}

