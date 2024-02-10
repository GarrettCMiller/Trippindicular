//////////////////////////////////////////////////////////////////////////

#include "Globals.fx"

//////////////////////////////////////////////////////////////////////////

texture pTexture1 <>;
texture pTexture2 <>;

#define DEFAULT		LINEAR
#define FILTER1		DEFAULT
#define FILTER2		DEFAULT

#define ADD_MODE	WRAP	//CLAMP

sampler sR1 = sampler_state
{
	Texture = <pTexture1>;
	
	AddressU = ADD_MODE;
	AddressV = ADD_MODE;
	
	MinFilter = FILTER1;
	MagFilter = FILTER1;
	//MipFilter = LINEAR;
};

sampler sR2 = sampler_state
{
	Texture = <pTexture2>;
	
	AddressU = ADD_MODE;
	AddressV = ADD_MODE;
	
	MinFilter = FILTER1;
	MagFilter = FILTER1;
	//MipFilter = LINEAR;
};

int mode1 = 0, mode2 = -1;

float4 g_BGColor = float4(0.0f, 0.125f, 0.125f, 1.0f);
float4 g_ColorDecay = float4(0.005f, 0.005f, 0.005f, 0.0f);

//////////////////////////////////////////////////////////////////////////

PSOutput PS_Default(PSInput In)
{
	PSOutput Out = (PSOutput) 0;
	
	float2 tc = In.TexCoord;
	
	float4 color = tex2D(sR2, In.TexCoord);
	
	Out.Color = color;
	Out.Color2 = color;
	
	return Out;
}

PSOutput PS_FlowField(PSInput In)
{
	PSOutput Out = (PSOutput) 0;

	float2 tc = In.TexCoord;
	float2 otc =	tc * 162;//TWOPI;	
					//In.Pos / TWOPI;

	if (mode1 == 0 || mode2 == 0)
	{
		tc.x += Sine(0.1f, 0.0f, 0.5f, g_Time);
		tc.y += Cosine(0.1f, 0.0f, 0.5f, g_Time);
	}
	
	if (mode1 == 1 || mode2 == 1)
	{
		tc.x += Sine(0.0625f, 0.0f, 0.05f, otc.x);
		tc.y += Sine(0.0625f, 0.0f, 0.05f, otc.y);
	}
	
	if (mode1 == 2 || mode2 == 2)
	{
		tc.x += Sine(0.0625f, 0.0f, 0.05f, otc.y);
		tc.y += Sine(0.0625f, 0.0f, 0.05f, otc.x);
	}
	
	if (mode1 == 3 || mode2 == 3)
	{
		tc.x += Sine(0.0625f, 0.0f, 0.05f, otc.y);
		tc.y += 0.001f;
	}
	
	if (mode1 == 4 || mode2 == 4)
	{
		tc.x += 0.001f;
		tc.y += Sine(0.0625f, 0.0f, 0.05f, otc.y);
	}
	
	if (mode1 == 5 || mode2 == 5)
	{
		tc.x += Sine(0.0625f, 0.0f, 0.05f, otc.x);
		tc.y += 0.001f;
	}
	
	if (mode1 == 6 || mode2 == 6)
	{
		tc.x += 0.001f;
		tc.y += Sine(0.0625f, 0.0f, 0.05f, otc.x);
	}
	
	Out.Color.a = 1.0f;
	Out.Color.rgb = tex2D(sR1, tc);
	
	Out.Color2 = lerp(Out.Color, g_BGColor, g_ColorDecay);

	//Out.Color.rgb *= 0.75f;
	
	return Out;
}

//////////////////////////////////////////////////////////////////////////

VSOutput VS_Default(VSInput In)
{
	VSOutput Out = (VSOutput) 0;
	
	Out.Pos = mul(In.Pos, matViewProj);
	
	Out.TexCoord = In.TexCoord;

	Out.Color = In.Color;

	return Out;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

technique Tech1
{
	pass P0
	{
		Sampler[0] = <sR2>;
		
		VertexShader = compile vs_2_0 VS_Default();
		PixelShader = compile ps_2_0 PS_Default();
	}
}

technique Tech2
{
	pass P0
	{
		Sampler[0] = <sR1>;
		
		VertexShader = compile vs_2_0 VS_Default();
		PixelShader = compile ps_2_0 PS_FlowField();
	}
}