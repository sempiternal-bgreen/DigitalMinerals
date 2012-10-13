// texture to be used
texture gDiffuseTexture : DIFFUSE;
texture gBackgroundTexture;
texture gDepthTexture;
float	gTime : TIME;
float   gRed;
float   gGreen;
float   gBlue;
// the matching sampler
sampler2D gDiffuseSampler = 
sampler_state 
{
    Texture = <gDiffuseTexture>;
    FILTER = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

sampler2D gBackgroundSampler = 
sampler_state 
{
    Texture = <gBackgroundTexture>;
    FILTER = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

sampler2D gDepthSampler = 
sampler_state 
{
    Texture = <gDepthTexture>;
    FILTER = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

// TODO: create vertex shader inputs (must match the vertex declaration in C++)
struct VS_INPUT
{
    float3 untransformed_pos	: POSITION0;
	float2 uv					: TEXCOORD0;
};
// TODO: create vertex shader outputs
struct VS_OUTPUT
{
    float4 transformed_pos	: POSITION0;
	//float4 transformed_norm	: TEXCOORD0;
	float2 uv				: TEXCOORD0;
};
// TODO: the vertex shader, run once for each vertex
VS_OUTPUT ScreenSpaceQuad(VS_INPUT input)
{
	VS_OUTPUT output;
	output.transformed_pos  = float4(input.untransformed_pos, 1.0f);
	output.uv = input.uv;
	return output;
}

// TODO: the vertex shader, run once for each vertex
VS_OUTPUT ScreenSpaceQuadInverse(VS_INPUT input)
{
	VS_OUTPUT output;
	output.transformed_pos  = float4(input.untransformed_pos, 1.0f);
	output.transformed_pos.x = -output.transformed_pos.x;
	output.transformed_pos.y = -output.transformed_pos.y;
	output.transformed_pos.z = -output.transformed_pos.z;
	output.uv = input.uv;
	return output;
}
// the pixel shader, each rasterized triangle's pixels will run through this 

// TODO: Render the image without any effect
float4 PassAlong(VS_OUTPUT input) : COLOR
{
	float4 texCol = tex2D(gDiffuseSampler, input.uv);
	// return texture color
	return texCol;
}

float4 InversionPS(VS_OUTPUT input) : COLOR
{
	input.uv.x = -input.uv.x;
	input.uv.y = -input.uv.y;
	float4 texCol = tex2D(gDiffuseSampler, input.uv);
	// return texture color
	return texCol;
}

// TODO: Create the Inversion effect
float4 Inversion(VS_OUTPUT input) : COLOR
{
	float4 texCol = tex2D(gDiffuseSampler, input.uv);
	// return texture color inverted
	texCol = 1 - tex2D(gDiffuseSampler, input.uv);
	return texCol;
}

// TODO: Create the Monochrome effect
float4 MonochromeShader(VS_OUTPUT input) : COLOR
{
	float4 texCol = tex2D(gDiffuseSampler, input.uv);
	// return texture color flattened
	float average = (texCol.r + texCol.g + texCol.b)/3.0f;
	texCol.r = average;
	texCol.g = average;
	texCol.b = average;

	/* GIVES PURE BLACK AND WHITE
	texCol = (texCol.r + texCol.g + texCol.b)/3.0f;
	// convert to greyscale
	if (texCol.r < 0.2 || texCol.r > 0.8)
		texCol.r = 0.0f;
	else
		texCol.r = 1.0f;

	if (texCol.g < 0.2 || texCol.g > 0.8)
		texCol.g = 0.0f;
	else
		texCol.g = 1.0f;

	if (texCol.b < 0.2 || texCol.b > 0.8)
		texCol.b = 0.0f;
	else
		texCol.b = 1.0f;
	*/
	// return monochrome
	return texCol;
}

// TODO: Create the Sepia effect
float4 SepiaScale(VS_OUTPUT input) : COLOR
{
	float4 texCol = tex2D(gDiffuseSampler, input.uv);
	// return texture color scaled
	float4 outputColor = texCol;
	outputColor.r = (texCol.r * 0.393) + (texCol.g * 0.769) + (texCol.b * 0.189);
    outputColor.g = (texCol.r * 0.349) + (texCol.g * 0.686) + (texCol.b * 0.168);    
    outputColor.b = (texCol.r * 0.272) + (texCol.g * 0.534) + (texCol.b * 0.131);
	// return sepia
	return outputColor;
}

float4 WarpEffect(VS_OUTPUT input) : COLOR
{
	input.uv.x = saturate(input.uv.x + 	sin(gTime * 2 + input.uv.y * 10) * 0.1f);
	float4 texCol = tex2D(gDiffuseSampler, input.uv);

	return texCol;
}

// TODO: Create the Black and White effect
float4 BlackAndWhiteShader(VS_OUTPUT input) : COLOR
{
	float4 texCol = tex2D(gDiffuseSampler, input.uv);
	
	// GIVES PURE BLACK AND WHITE
	texCol = (texCol.r + texCol.g + texCol.b)/3.0f;
	// convert to greyscale
	if (texCol.r < 0.2 || texCol.r > 0.8)
		texCol.r = 0.0f;
	else
		texCol.r = 1.0f;

	if (texCol.g < 0.2 || texCol.g > 0.8)
		texCol.g = 0.0f;
	else
		texCol.g = 1.0f;

	if (texCol.b < 0.2 || texCol.b > 0.8)
		texCol.b = 0.0f;
	else
		texCol.b = 1.0f;
	
	return texCol;
}

// TODO: Green value becomes the red value, blue becomes the green, 
//red becomes the blue
float4 ShiftColorRightShader(VS_OUTPUT input) : COLOR
{
	float4 texCol = tex2D(gDiffuseSampler, input.uv);
	//hold the original color so it doesn't get changed
	float4 holdCol = texCol;
	
	texCol.r = holdCol.b;
	texCol.g = holdCol.r;
	texCol.b = holdCol.g;
	return texCol;
}

// TODO: red value becomes the green value, green becomes the blue, 
//blue becomes the red
float4 ShiftColorLeftShader(VS_OUTPUT input) : COLOR
{
	float4 texCol = tex2D(gDiffuseSampler, input.uv);
	//hold the original color so it doesn't get changed
	float4 holdCol = texCol;
	
	texCol.r = holdCol.g;
	texCol.g = holdCol.b;
	texCol.b = holdCol.r;
	return texCol;
}

float4 EmbossedShader(VS_OUTPUT input) : COLOR
{
	float4 texCol = tex2D(gDiffuseSampler, input.uv);
	texCol.a = 1.0f;
	texCol.rgb = 0.5f;
	texCol -= tex2D( gDiffuseSampler, input.uv.xy-0.001)*2.0f;
	texCol += tex2D( gDiffuseSampler, input.uv.xy+0.001)*2.0f;
	texCol.rgb = (texCol.r + texCol.g + texCol.b)/3.0f;
	return texCol;
}

float4 ColorCycle(VS_OUTPUT input) : COLOR
{
	float4 texCol = tex2D(gDiffuseSampler, input.uv);

	
	//float red = (sin(gTime));
	//float green = (cos(gTime));
	//float blue = (sin(gTime));
	texCol.r *= gRed;
	texCol.g *= gGreen;
	texCol.b *= gBlue;
	// return texture color
	return texCol;
}

float4 TronLines(VS_OUTPUT input) : COLOR
{
	float4 texCol = tex2D(gDiffuseSampler, input.uv);
	//float4 magenta = float4(1.0f, 0, 1.0f, 1.0f);
	//if (texCol.r == 1.0f && texCol.g == 0.0f && texCol.b == 1.0f)
	//{
		//texCol.r *= gRed;
		//texCol.g *= gGreen;
		//texCol.b *= gBlue;
	//}
	// check for the magenta color of the texture (1,0,1)
	
	// using cos and the UV coordinates, create the line effect
	input.uv.y -= gTime * 0.5f;
	// tint the cos UV effect with the passed in color values
	if (texCol.r >= 0.6f && texCol.g <= 0.5f && texCol.b >= 0.6f)
	{
		texCol.r = cos(input.uv.y * 10) * gRed;
		texCol.g = cos(input.uv.y * 10) * gGreen;
		texCol.b = cos(input.uv.y * 10) * gBlue;
	}
	// apply the effect to the magenta parts of the texture
	
	// return the modified outcolor
	return texCol;
}

float4 BackgroundPS(VS_OUTPUT input) : COLOR
{
	return tex2D(gBackgroundSampler, input.uv);
}
float4 EatAway(VS_OUTPUT input) : COLOR
{
	float4 texCol = tex2D(gDiffuseSampler, input.uv);	
	
	if (texCol.r >= gRed)
		discard;
	if (texCol.g >= gGreen)
		discard;
	if(texCol.b >= gBlue)
		discard;
	//texCol.b = (tan(gTime));
	// return texture color
	return texCol;
}

// Techniques are read in by the effect framework.
// They allow one to add variation to how a particular shader might be executed. 
technique PassThrough
{
	// Each pass in the technique corresponds to a single iteration over all 
	// verticies sent during a draw call and the subsequently created pixels. 
	// If we had a special effect that required us to draw our geometry and pixels more than once,
	// we could acheive this by adding more passes across our vertex and pixel data.
    pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 PassAlong();
//		FillMode = WIREFRAME;
    }
}
technique Invert
{
	pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 Inversion();
    }
} 
technique Monochrome
{
	pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 MonochromeShader();
    }
}
technique Sepia
{
	pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 SepiaScale();
    }
}

technique Warped
{
	pass FirstPass
	{
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 WarpEffect();
	}
}

technique BlackAndWhite
{
	pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 BlackAndWhiteShader();
    }
}

technique ShiftColorRight
{
	pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 ShiftColorRightShader();
    }
}

technique ShiftColorLeft
{
	pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 ShiftColorLeftShader();
    }
}

technique InversePositions
{
	pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 InversionPS();
    }
} 

technique Embossed
{
	pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 EmbossedShader();
    }
}

technique ColorLoop
{
	pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 ColorCycle();
    }
}

technique TronEnergy
{
	pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 TronLines();
    }
}

technique Dissolve
{
	pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 BackgroundPS();
    }
	pass SecondPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 EatAway();
    }
}