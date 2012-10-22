#ifndef CAMERA_H_
#define CAMERA_H_

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

class Camera
{
public:
	D3DXMATRIX	CameraMatrix;
	D3DXMATRIX	ProjectionMatrix;

	D3DXVECTOR3 Eye;
	D3DXVECTOR3 At;
	D3DXVECTOR3 Up;
	
	float m_fFieldOfView;
	float m_fAspectRatio;
	float m_fZNear;
	float m_fZFar;
	
	void Initialize( float width, float height );
	void Update( float time );
	void MouseLook( D3DXMATRIX matrix, float time );
};


#endif
