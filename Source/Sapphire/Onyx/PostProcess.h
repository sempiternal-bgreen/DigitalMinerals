#ifndef POSTPROCESS_H_
#define POSTPROCESS_H_

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

class PostProcess
{
private:
	PostProcess(void);
	PostProcess( const PostProcess& ){}
	PostProcess& operator=( const PostProcess& ){}
	~PostProcess(void);

public:
	static PostProcess* GetInstance(void);

	IDirect3DVertexBuffer9		*quadbuff;
	IDirect3DIndexBuffer9		*quadindex;
	IDirect3DVertexDeclaration9	*cubedecl;
	ID3DXEffect					*postEffect;
	IDirect3DTexture9			*renderTarget;
	IDirect3DSurface9			*current;
	IDirect3DSurface9			*output;

	D3DSURFACE_DESC				backbuffer;

	float						fRed;
	float						fGreen;
	float						fBlue;
	int							colChange;

	const char*					techs[11];
	int							index;

	bool						m_bPostProcess;

	void Initialize( IDirect3DDevice9 *device );
	void Update();
	void BeginPostProcess( IDirect3DDevice9 *device );
	void EndPostProcess( IDirect3DDevice9 *device );
	void ShutDown( void );
	void ReleaseTexture(void);
	void ReCreateTexture( IDirect3DDevice9 *device );
	void UpdateColor();
	void MaximizeThresholdColors()							{ fRed = fGreen = fBlue = 1.0f;}
};

#endif
