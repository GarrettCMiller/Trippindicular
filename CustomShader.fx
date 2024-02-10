//////////////////////////////////////////////////////////////////////////

#include "Globals.fx"

//////////////////////////////////////////////////////////////////////////

typedef float Float;
typedef float2	Float2;

bool bJulia = false;

Float2 J = {0.8, 0.156};

Float fOffset = 0.33;//1.0f / 3.0f;
Float fScaleFactor = 5.0;

static const int nMaxIters = 1024;

static int numIters = 0;

int GnumIters = 0;

texture pTexture <>;

sampler sFractal = sampler_state
{
	Texture = <pTexture>;
	
	AddressU = WRAP;
	AddressV = WRAP;
	
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	//MipFilter = LINEAR;
};

bool bTEST = true;
//////////////////////////////////////////////////////////////////////////

PSOutput PS_Mandelbrot(PSInput In)
{
	PSOutput Out = (PSOutput) 0;
	
	Out.Color.a = 1.0f;
	
	Float2 p = In.TexCoord;
				//* In.Pos;
	
	p.x -= 0.75f;
	p.y -= 0.5f;
	//p *= 0.00001f;
	
	Float2 c = p;
	
	if (bJulia)
		c = J;
	
	Float2 z = p;
	Float2 t = z;
	
	Float orbit;
	int i = 0;
	int n = 0;
	
	for (i = 0; i < nMaxIters; i++)
	{		
		orbit = z.x * z.x + z.y * z.y;
		
		if (orbit > 4.0)
		{
			n = i;
			i = nMaxIters; //HACK, no break statements
		}
		else
		{
			t.x = z.x * z.x - z.y * z.y + c.x;	//- (c.x / (c.x * c.x + c.y * c.y));
			t.y = 2.0 * z.x * z.y + c.y;		//- (-c.y / (c.x * c.x + c.y * c.y));
			
			z = t;
		}
	}
	
	i = n;

	Float tCoord;
	
	if (bTEST)
	{
		for (int extra = 0; extra < 2; extra++, n++)
		{		
			t.x = z.x * z.x - z.y * z.y + c.x;
			t.y = 2.0 * z.x * z.y + c.y;
			z = t;
		}
		
		orbit = z.x * z.x + z.y * z.y;
		
		tCoord =	n + 1 - (log(log(orbit)) / log(2.0));
						//float(n) / float(nMaxIters);
	}
	else
		tCoord = n;
	
	tCoord *= fScaleFactor;
	tCoord += fOffset;
	
	numIters += i;
	
	if (i == 0)
		Out.Color.rgb = 0.0f;
	else
		Out.Color.rgb = tex1D(sFractal, tCoord);
		
	return Out;
}

//////////////////////////////////////////////////////////////////////////

VSOutput VS_Mandelbrot(VSInput In)
{
	VSOutput Out = (VSOutput) 0;
	
	Out.Pos = mul(In.Pos, matViewProj);
	
	Out.TexCoord = In.TexCoord;
	
	//GnumIters = numIters;
	
	return Out;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

technique Mandelbrot
{
	pass P0
	{		
		VertexShader = compile vs_2_0 VS_Mandelbrot();
		PixelShader = compile ps_3_0 PS_Mandelbrot();
	}
}