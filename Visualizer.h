#pragma once

#include "D3DWrapper.h"
#include "D3DImage.h"	//Include render-to-texture class wrapper

#include "VectorGraphics.h"	//For drawing "input"

#include "RandomVariable.h"	//Wraps a variable up to be randomized on a timer

#include "CritSection.h"

//////////////////////////////////////////////////////////////////////////

//Reference the D3DEffect
class Effect;

class CVisualizer
{
	friend class CLayerProps;
public:
	//Foreground mode
	enum EFGMode
	{
		eFGM_None,

		eFGM_XLines,
		eFGM_RotateLine,
		eFGM_RotateX,

		eFGM_BouncingLines,

		eFGM_Spiral,

		eFGM_BezierSpokes,

		eFGM_GridPoints,

		eFGM_NumModes,	//ALWAYS LAST

		eFGM_First = 0,

		eFGM_Initial = eFGM_GridPoints //eFGM_BezierSpokes
	};

public:
	CVisualizer(void);
	~CVisualizer(void);

	//One-time init
	Int32 Init(Vec2u imgSize);

	//Every frame update (calls RenderForeground() among other things)
	Int32 Update(Float dt = 0.0f);
	
	//One-time final shutdown
	Int32 Shutdown();

	//Handle keyboard/mouse input
	Int32 HandleInput();

	//Render textures, stage determines which textures to render from/to
	Int32 Render(UInt32 stage);

	//Clears the render targets/textures
	void ClearTextures();

	//Clears the vertices from the global buffer
	void ClearVertices();

	//Plots a point
	void PlotPoint(Vec2 pos);

	//Loads a different shader file
	Bool LoadEffect(const String& strPath);

	//HACK
	//Render custom shader routine
	void CustomShader();

protected:
	//Renders the full screen quad and applies the shader
	void RenderGeometry();

	//Renders the foreground objects
	void RenderForeground(EFGMode modeOverride = eFGM_None, Color colorOverride = Color::km_Transparent);

	//Update all of the random variables
	void RandomizeValues();

	//Sets the texture wrap
	void SetUVWrap();

	//Sets the vars in the shader
	void SetShaderVars();

public:
	//For rendering the foreground objects
	CVectorGraphics vg;

protected:
	//Change with time?
	Bool		m_bRandomize;

	//Use polar coords in the shader
	Bool		m_bUsePolar;

	//////////////////////////
	//
	Bool UseSine[4];

	//0 - Scalar
	//1 - X pos,	2 - Y pos,
	//3 - Radius,	4 - Angle 
	SineArgsI ArgModeX;
	SineArgsI ArgModeY;
	SineArgsI ArgModeR;
	SineArgsI ArgModeA;

	//freq, base, amp, phase
	SineArgsF VelArgsX;
	SineArgsF VelArgsY;
	SineArgsF VelArgsR;
	SineArgsF VelArgsA;
	//
	///////////////////////////

	//Array of arguments for sine-based functions
	CDynamicArray<SineArgsF>	m_SineArgs;
	
	//Array of verts for FG objects
	TVertexArray	m_p;

	//Palette for color cycling
	Palette		m_Palette;

	//Color of foreground objects
	Color		m_cFGColor;
	//Color that the FG fades to (background color)
	Color		m_cBGColor;
	//The amount that each color channel decays
	Color		m_cColorDecay;

	//Multiply
	Float		m_fWrapScale;

	//Which flow field to use (up to four can be combined)
	Int32		m_EffectMode[4];

	//Weights for the different effects
	Float		m_EffectWeight[4];

	//Texture wrap
	Vec2		m_vUVWrap;

	//How many points in the array are active
	Int32		m_NumActivePts;

	//The foreground object to render
	EFGMode		m_eFGMode;

	//The global timer
	Timer		m_tTime;

	//Arrays of RandomVariable objects
	TRandomBoolArray	bRand;
	TRandomFloatArray	fRand;
	TRandomIntArray		nRand;
	TRandomColorArray	cRand;

	/////////////////////////

	//Back buffer size
	Vec2u		m_BufferSize;

	//Back buffers
	CD3DImage	m_Buffer[2];

	//Pointer to shader to use
	Effect*		m_pEffect;

public:
	//Critical section for multithreading
	CCritSection	m_CS;
};