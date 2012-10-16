// application exposed variables
float4x4 gWorld : WORLD;
float4x4 gViewProjection : VIEWPROJECTION;

// global direction of light
float3 gLightDir : DIRECTION
< string Object = "DirectionalLight"; >
= { -1, -1, 1 };

// texture to be used
texture gDiffuseTexture : DIFFUSE;
// the matching sampler
sampler2D gDiffuseSampler = 
sampler_state 
{
    Texture = <gDiffuseTexture>;
    FILTER = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

// vertex shader inputs (must match the vertex declaration in C++)
struct VS_INPUT
{
    float3 untransformed_pos	: POSITION0;
	float3 untransformed_norm	: NORMAL0;
	float2 uv					: TEXCOORD0;
};
// vertex shader outputs
struct VS_OUTPUT
{
    float4 transformed_pos	: POSITION0;
	float4 transformed_norm	: TEXCOORD0;
	float2 uv				: TEXCOORD1;
};
// the vertex shader, run once for each vertex
VS_OUTPUT myVertexShader(VS_INPUT input)
{
	VS_OUTPUT output; // what we will output
   	// compute world vertex position
	float4 worldloc = float4(input.untransformed_pos,1.0f);
   	worldloc = mul(worldloc, gWorld); // not needed to be seperate just copy paste
    // transforming the incoming world vertex into camera, then clip space.
	output.transformed_pos = mul(worldloc, gViewProjection);
	// store world space normal for later
	output.transformed_norm = mul(input.untransformed_norm, gWorld);
	// transfer UVs
	output.uv = input.uv;
	// send data along to the pixel shader (will be interpolated)
	return output; 
}
// the pixel shader, each rasterized triangle's pixels will run through this 
float4 myPixelShader(VS_OUTPUT input) : COLOR
{
	// normalize in coming light dir and normal.
	float3 ldir = -normalize(gLightDir);
	float3 wnrm = normalize(input.transformed_norm);
	// perform dot and add color.
	return float4(dot(ldir,wnrm) * tex2D(gDiffuseSampler,input.uv).rgb,1);
}
// Techniques are read in by the effect framework.
// They allow one to add variation to how a particular shader might be executed. 
technique myTechnique
{
	// Each pass in the technique corresponds to a single iteration over all 
	// verticies sent during a draw call and the subsequently created pixels. 
	// If we had a special effect that required us to draw our geometry and pixels more than once,
	// we could acheive this by adding more passes across our vertex and pixel data.
    pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 myVertexShader();
        pixelShader  = compile ps_2_0 myPixelShader();
		// Setting a few of the many D3D renderstates via the effect framework
		//ShadeMode = GOURAUD; // smooth color interpolation across triangles
        //FillMode = SOLID; // no wireframes, no point drawing.
        //CullMode = CCW; // cull any clockwise polygons.
    }
}