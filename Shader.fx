//////////////////////////////////////////////////////////////////////////

#define PS	0x30

#include "Globals.fx"

//////////////////////////////////////////////////////////////////////////

texture pTexture1 <>;
texture pTexture2 <>;

#define DEFAULT		LINEAR
#define FILTER1		DEFAULT
#define FILTER2		DEFAULT

#define ADD_MODE	CLAMP

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

float wrapScale = 162.0f;//Appx divides screen space into 2PI

float minx = 0.0061728395061728395061728395061728;
float miny = 0.0061728395061728395061728395061728;
float minavg = 0.0061728395061728395061728395061728;

bool bUsePolar = false;

float2 g_Origin = float2(0.5f, 0.5f);
float2 RefPt	= float2(0, 0);

float4 g_FGColor = float4(0.0f, 0.0f, 1.0f, 1.0f);
float4 g_BGColor = float4(0.0f, 1.0f, 0.0f, 1.0f);

static const float decay = 0.00375f;
float4 g_ColorDecay = float4(decay, decay, decay, 0.0f);

bool UseSineX = false;
bool UseSineY = false;
bool UseSineR = false;
bool UseSineA = false;

//0 - Scalar
//1 - X pos,	2 - Y pos,
//3 - Radius,	4 - Angle 
//row_major			
int4x4 ArgMode = {		0,	0,	0,	2,		//X Args
						0,	0,	0,	1,		//Y Args
						0,	0,	0,	3,		//R Args
						0,	0,	0,	3};		//A Args

//freq, base, amp, phase
//row_major
float4x4 VelArgs = {	10,	0,	0,	1,		//X Args
						10,	0,	0,	1,		//Y Args
						10,	0,	0,	1,		//R Args
						10,	0,	1,	1};		//A Args

const float fPhase = PI * 0.5f;

//////////////////////////////////////////////////////////////////////////

float4 GetArgs(int argSet, float2 Vel, float2 PolarCoord)
{
	float4 args = float4(0, 0, 0, 0);
	
	//Freq
	if (ArgMode[argSet].x == 1)
 		args.x = fmod(Vel.x, fPhase) * VelArgs[argSet].x;
 	else if (ArgMode[argSet].x == 2)
 		args.x = fmod(Vel.y, fPhase) * VelArgs[argSet].x;
	else if (ArgMode[argSet].x == 3)
 		args.x = fmod(PolarCoord.x, fPhase) * VelArgs[argSet].x;
 	else if (ArgMode[argSet].x == 4)
 		args.x = fmod(PolarCoord.y, fPhase) * VelArgs[argSet].x;
	else
		args.x = VelArgs[argSet].x;		
		
	//Base
	if (ArgMode[argSet].y == 1)
 		args.y = fmod(Vel.x, fPhase) * VelArgs[argSet].y;
 	else if (ArgMode[argSet].y == 2)
 		args.y = fmod(Vel.y, fPhase) * VelArgs[argSet].y;
	else if (ArgMode[argSet].y == 3)
 		args.y = fmod(PolarCoord.x, fPhase) * VelArgs[argSet].y;
 	else if (ArgMode[argSet].y == 4)
 		args.y = fmod(PolarCoord.y, fPhase) * VelArgs[argSet].y;
	else
		args.y = VelArgs[argSet].y;
	
	
	//Amp	
	if (ArgMode[argSet].z == 1)
		args.z = fmod(Vel.x, fPhase) * VelArgs[argSet].z;
	else if (ArgMode[argSet].z == 2)
		args.z = fmod(Vel.y, fPhase) * VelArgs[argSet].z;
	else if (ArgMode[argSet].z == 3)
		args.z = fmod(PolarCoord.x, fPhase) * VelArgs[argSet].z;
	else if (ArgMode[argSet].z == 4)
		args.z = fmod(PolarCoord.y, fPhase) * VelArgs[argSet].z;
	else
		args.z = VelArgs[argSet].z;
	
	
	//Phase
	if (ArgMode[argSet].w == 1)
		args.w = fmod(Vel.x, fPhase) * VelArgs[argSet].w;
	else if (ArgMode[argSet].w == 2)
		args.w = fmod(Vel.y, fPhase) * VelArgs[argSet].w;
	else if (ArgMode[argSet].w == 3)
		args.w = fmod(PolarCoord.x, fPhase) * VelArgs[argSet].w;
	else if (ArgMode[argSet].w == 4)
		args.w = fmod(PolarCoord.y, fPhase) * VelArgs[argSet].w;
	else
		args.w = VelArgs[argSet].w;
		
	return args;
}

//////////////////////////////////////////////////////////////////////////

float2 DoVel(float2 Pos, float2 PolarCoord)
{
	float2 Vel = float2(0, 0);

	float2 wrapTC = Pos * wrapScale;

	VelArgs[0] = GetArgs(0, Pos, PolarCoord);
	VelArgs[1] = GetArgs(1, Pos, PolarCoord);

	if (UseSineX)
		Vel.x = minx * Sine(VelArgs[0]);
	else
		Vel.x = minx * VelArgs[0].z;
		
	if (UseSineY)
		Vel.y = miny * Sine(VelArgs[1]);
	else
		Vel.y = miny * VelArgs[1].z;

	return Vel;
}

float2 DoPolarVel(float2 Pos, float2 PolarCoord)
{
	float2 PolarVel = float2(0, 0);

	VelArgs[2] = GetArgs(2, Pos, PolarCoord);
	VelArgs[3] = GetArgs(3, Pos, PolarCoord);

	if (UseSineR)
		PolarVel.x = -minavg * Sine(VelArgs[2]);
	else
		PolarVel.x = -minavg * VelArgs[2].z;
		
	if (UseSineA)
		PolarVel.y = minavg * Sine(VelArgs[3]);
	else
		PolarVel.y = minavg * VelArgs[3].z;

	//Assign polar coords
	PolarCoord += PolarVel;
	
	//Check for negative radii
	if (PolarCoord.x < 0)
	{
		clip(-1);
	}
	else
	{
		PolarVel.x = PolarCoord.x * cos(PolarCoord.y) + RefPt.x;	
		PolarVel.y = PolarCoord.x * sin(PolarCoord.y) + RefPt.y;
	}

	return PolarVel;
}

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

	float2 TexCoord		= In.TexCoord /*+ halfpixel*/;

	float2	PolarCoord	= float2(0, 0), 
			PolarCoord2	= float2(0, 0);
	
	//Set the ref point as the origin for now
	RefPt = g_Origin;
	
	//Set up the polar coord based on the ref point
	PolarCoord2 = TexCoord - RefPt;
	
	//Get the radius
	PolarCoord.x = distance(TexCoord, RefPt);
	
	//If it's not exactly at the orgin but close enough, assume the angle is 0
	if (any(PolarCoord2))
		PolarCoord.y = atan2(PolarCoord2.y, PolarCoord2.x);
	
	//Set up a temp vector of the cartesian and polar coordinates
	float2	Vel			=	float2(0,0), 
			PolarVel	=	float2(0,0);
							
	//Perform pixel flow on this pixel
	Vel = DoVel(TexCoord, PolarCoord);
	
	if (bUsePolar)
		TexCoord = DoPolarVel(TexCoord, PolarCoord);
		
	//auto correction?
	Vel += float2(0.0007f, 0.0007f);

	//Assign cartesian coords
	TexCoord += Vel;

	Out.Color.a = 1.0f;
	Out.Color.rgb = tex2D(sR1, TexCoord);
	
	Out.Color2 = lerp(Out.Color, g_BGColor, g_ColorDecay);

	Out.Color.rgb = Out.Color2.rgb;
	
	return Out;
}

//////////////////////////////////////////////////////////////////////////

VSOutput VS_Default(VSInput In)
{
	VSOutput Out = (VSOutput) 0;
	
	Out.Pos = mul(In.Pos, matViewProj);
	
	Out.TexCoord = In.TexCoord ;//* 50.0f;

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
		PixelShader = compile ps_3_0 PS_Default();
	}
}

technique Tech2
{
	pass P0
	{
		Sampler[0] = <sR1>;
		
		VertexShader = compile vs_2_0 VS_Default();
		PixelShader = compile ps_3_0 PS_FlowField();
	}
}