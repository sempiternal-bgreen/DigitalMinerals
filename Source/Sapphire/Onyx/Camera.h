#ifndef CAMERA_H_
#define CAMERA_H_

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )


class Camera
{
public:
	D3DXMATRIX	CameraViewMatrix;
	D3DXMATRIX	ProjectionMatrix;
	D3DXMATRIX  CameraInverseMatrix;

	D3DXVECTOR3 Eye;
	D3DXVECTOR3 At;
	D3DXVECTOR3 Up;
	
	float m_fFieldOfView;
	float m_fAspectRatio;
	float m_fZNear;
	float m_fZFar;
	
	POINT mousePos;
	POINT holdMousePos;			// the mouse's position when you lock the camera
	bool bCameraIsLocked;

	void Initialize( float screenWidth, float screenHeight );
	void Update( float time, float screenWidth, float screenHeight );
	void MouseLook( D3DXMATRIX &matrix, float time, float screenWidth, float screenHeight );
	void NormalizeCameraMatrix();
	bool MouseHasMoved();
};


#endif
