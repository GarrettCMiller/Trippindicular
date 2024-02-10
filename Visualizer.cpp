#include "StdAfx.h"
#include "Visualizer.h"

#include "EffectMgr.h"

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

CVisualizer::CVisualizer(void) : 
	m_eFGMode(eFGM_Initial),
	m_fWrapScale(162.0f),
	m_bRandomize(false),
	m_NumActivePts(3),
	m_bUsePolar(false)
{
	 m_EffectMode[0] = -1;
	 m_EffectMode[1] = -1;
	 m_EffectMode[2] = -1;
	 m_EffectMode[3] = -1;

	 m_vUVWrap = Vec2(5.0f, 5.0f);

	 //m_SineArgs.Resize(5);

	 m_SineArgs.Push(SineArgsF(0.5f, 0.0f, 0.5f));
	 m_SineArgs.Push(SineArgsF(0.5f, 0.0f, 0.5f));
	 m_SineArgs.Push(SineArgsF(100.0f, 0.0f, 1.0f));
	 m_SineArgs.Push(SineArgsF(100.0f, 0.5f, 0.5f));

	 Bool UseSine[4]	= {false, false, true, true};

	//0 - Scalar
	//1 - X pos,	2 - Y pos,
	//3 - Radius,	4 - Angle 
	ArgModeX = SineArgsI(0, 0, 0, 2);
	ArgModeY = SineArgsI(0, 0, 0, 1);	
	ArgModeR = SineArgsI(0, 0, 0, 3);	
	ArgModeA = SineArgsI(0, 0, 0, 3);	

	//freq, base, amp, phase
	VelArgsX = SineArgsF(10, 0, 0, 0);
	VelArgsY = SineArgsF(10, 0, 0, 0);
	VelArgsR = SineArgsF(10, 0, 1, 0);
	VelArgsA = SineArgsF(10, 0, 1, 0);
	 
	m_p.Resize(50);
}

CVisualizer::~CVisualizer(void)
{
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

Bool CVisualizer::LoadEffect(const String& strPath)
{
	UInt32 id = -1;

	if ((id = g_EffectMgr->LoadEffect(strPath)) == -1)
		return false;

	m_pEffect = &g_EffectMgr->GetEffect(id);

	return true;
}

//////////////////////////////////////////////////////////////////////////

Int32 CVisualizer::Init(Vec2u imgSize)
{
	ASSERT(imgSize.X > 0 && imgSize.Y > 0);

	m_BufferSize = imgSize;

	m_Buffer[0].Init(imgSize);
	m_Buffer[1].Init(imgSize);

	if (!LoadEffect("Shader.fx"))
		return -1;	

	m_pEffect->Shader->GetVector("g_FGColor", (Vec4*)&m_cFGColor);
	m_pEffect->Shader->GetVector("g_BGColor", (Vec4*)&m_cBGColor);
	m_pEffect->Shader->GetVector("g_ColorDecay", (Vec4*)&m_cColorDecay);

	m_pEffect->Shader->SetTexture("pTexture1", m_Buffer[0]);
	m_pEffect->Shader->SetTexture("pTexture2", m_Buffer[1]);

	D3DMatrix mat;

	m_pEffect->Shader->GetMatrix("ArgMode", &mat);

	ArgModeX.freq	= mat.m[0][0];
	ArgModeX.base	= mat.m[0][1];
	ArgModeX.amp	= mat.m[0][2];
	ArgModeX.phase	= mat.m[0][3];

	ArgModeY.freq	= mat.m[1][0];
	ArgModeY.base	= mat.m[1][1];
	ArgModeY.amp	= mat.m[1][2];
	ArgModeY.phase	= mat.m[1][3];

	ArgModeR.freq	= mat.m[2][0];
	ArgModeR.base	= mat.m[2][1];
	ArgModeR.amp	= mat.m[2][2];
	ArgModeR.phase	= mat.m[2][3];

	ArgModeA.freq	= mat.m[3][0];
	ArgModeA.base	= mat.m[3][1];
	ArgModeA.amp	= mat.m[3][2];
	ArgModeA.phase	= mat.m[3][3];
	
	m_pEffect->Shader->GetMatrix("VelArgs", &mat);

	VelArgsX.freq	= mat.m[0][0];
	VelArgsX.base	= mat.m[0][1];
	VelArgsX.amp	= mat.m[0][2];
	VelArgsX.phase	= mat.m[0][3];

	VelArgsY.freq	= mat.m[1][0];
	VelArgsY.base	= mat.m[1][1];
	VelArgsY.amp	= mat.m[1][2];
	VelArgsY.phase	= mat.m[1][3];

	VelArgsR.freq	= mat.m[2][0];
	VelArgsR.base	= mat.m[2][1];
	VelArgsR.amp	= mat.m[2][2];
	VelArgsR.phase	= mat.m[2][3];

	VelArgsA.freq	= mat.m[3][0];
	VelArgsA.base	= mat.m[3][1];
	VelArgsA.amp	= mat.m[3][2];
	VelArgsA.phase	= mat.m[3][3];
	
	g_D3D->GetDevice()->SetRenderState(D3DRS_POINTSIZE, ReinterpretCast<DWORD>(5.0f));

	if (!vg.Init())
		return -1;

	UInt32 chance = 75;

	fRand.Push(RandomVariable<Float>(m_SineArgs[0].amp, 0.0f, 2.5f, 5.0f, chance));
	fRand.Push(RandomVariable<Float>(m_SineArgs[0].freq, 0.05f, 2.5f, 5.0f, chance));
	//fRand.Push(RandomVariable<Float>(m_SineArgs[0].base, -0.5f, 0.5f, -1.0f, chance));
	fRand.Push(RandomVariable<Float>(m_fWrapScale, 40.5f, 648.0f, 30.0f, chance));
	//fRand.Push(RandomVariable<Float>(m_vUVWrap.X, 0.01f, 50.0f, -1.0f, chance));
	//fRand.Push(RandomVariable<Float>(m_vUVWrap.Y, 0.01f, 50.0f, -1.0f, chance));

	//nRand.Push(RandomVariable<Int32>(m_EffectMode[0], 0, 6, 20.0f, chance));
	//nRand.Push(RandomVariable<Int32>(m_EffectMode[1], 0, 6, 20.0f, chance));
	//nRand.Push(RandomVariable<Int32>(m_EffectMode[2], 0, 5, 20.0f, chance)); //polar
	//nRand.Push(RandomVariable<Int32>(m_EffectMode[3], 0, 5, 20.0f, chance)); //polar
	nRand.Push(RandomVariable<Int32>(m_NumActivePts, 2, 4, 45.0f, chance));

	nRand.Push(RandomVariable<Int32>(ArgModeX.amp, 0, 4, 20.0f, chance));
	nRand.Push(RandomVariable<Int32>(ArgModeX.base, 0, 4, 20.0f, chance));
	nRand.Push(RandomVariable<Int32>(ArgModeX.freq, 0, 4, 20.0f, chance));
	nRand.Push(RandomVariable<Int32>(ArgModeX.phase, 0, 4, 20.0f, chance));
	nRand.Push(RandomVariable<Int32>(ArgModeY.amp, 0, 4, 20.0f, chance));
	nRand.Push(RandomVariable<Int32>(ArgModeY.base, 0, 4, 20.0f, chance));
	nRand.Push(RandomVariable<Int32>(ArgModeY.freq, 0, 4, 20.0f, chance));
	nRand.Push(RandomVariable<Int32>(ArgModeY.phase, 0, 4, 20.0f, chance));
	nRand.Push(RandomVariable<Int32>(ArgModeR.amp, 0, 4, 20.0f, chance));
	nRand.Push(RandomVariable<Int32>(ArgModeR.base, 0, 4, 20.0f, chance));
	nRand.Push(RandomVariable<Int32>(ArgModeR.freq, 0, 4, 20.0f, chance));
	nRand.Push(RandomVariable<Int32>(ArgModeR.phase, 0, 4, 20.0f, chance));
	nRand.Push(RandomVariable<Int32>(ArgModeA.amp, 0, 4, 20.0f, chance));
	nRand.Push(RandomVariable<Int32>(ArgModeA.base, 0, 4, 20.0f, chance));
	nRand.Push(RandomVariable<Int32>(ArgModeA.freq, 0, 4, 20.0f, chance));
	nRand.Push(RandomVariable<Int32>(ArgModeA.phase, 0, 4, 20.0f, chance));
	
	bRand.Push(RandomVariable<Bool>(m_bUsePolar, 20.0f, chance));

	cRand.Push(RandomVariable<Color>(m_cFGColor, 20.0f, chance));
	cRand.Push(RandomVariable<Color>(m_cBGColor, 20.0f, chance));
	cRand.Push(RandomVariable<Color>(m_cColorDecay, 20.0f, chance));

	return 0;
}

//////////////////////////////////////////////////////////////////////////

void CVisualizer::SetUVWrap()
{
	//m_Buffer[0].m_Vertices[1].tu = m_Buffer[0].m_Vertices[2].tu = m_vUVWrap.X;
	//m_Buffer[0].m_Vertices[2].tv = m_Buffer[0].m_Vertices[3].tv = m_vUVWrap.Y;
}

//////////////////////////////////////////////////////////////////////////

void CVisualizer::CustomShader()
{
	m_CS.Lock();

	String tech = "Mandelbrot";
	UInt32 numPasses = 0;

	if (SUCCEEDED(m_pEffect->Shader->SetTechnique(tech.c_str())))
	{
		SetShaderVars();

		if (SUCCEEDED(m_pEffect->Shader->Begin(&numPasses, 0)))
		{
			for (UInt32 p = 0; p < numPasses; p++)
			{
				if (SUCCEEDED(m_pEffect->Shader->BeginPass(p)))
				{
					RenderGeometry();

					m_pEffect->Shader->EndPass();
				}
			}
		}

		m_pEffect->Shader->End();
	}

	m_CS.Unlock();
}

//////////////////////////////////////////////////////////////////////////

Int32 CVisualizer::Update(Float dt /* = 0.0f */)
{
	m_CS.Lock();

	if (m_bRandomize)
		RandomizeValues();

	//SetUVWrap();

	if (!g_D3D->PushRenderTarget(m_Buffer[0]))
		return -1;

	if (dt == -1.0f)
		g_D3D->BeginScene(true, false);

	RenderForeground();

	if (dt == -1.0f)
		g_D3D->EndScene(false);

	g_D3D->PopRenderTarget();

	m_CS.Unlock();
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////

void CVisualizer::RenderForeground(EFGMode modeOverride /* = eFGM_None */, Color colorOverride /* = Color::km_Transparent */)
{
	static Float x = 0.0f, y = 1.0f, z = 0.0f;
	static Timer t;

	UInt32 mode = (modeOverride != eFGM_None				? modeOverride	: m_eFGMode);
	Color color = (colorOverride == Color::km_Transparent	? m_cFGColor	: colorOverride);

	switch (mode)
	{
	case eFGM_None:
		{
			vg.DrawCurrentPointList();
		}
		break;

	case eFGM_XLines:
		{
			y = Sine(m_SineArgs[0].freq, 0.5f, 0.5f, (float)t);

			m_p[0].position = Vec3(x, 1.0f - y, z);
			m_p[1].position = Vec3(1.0f - x, y, z);
			m_p[2].position = Vec3(x, y, z);
			m_p[3].position = Vec3(1.0f - x, 1.0f - y, z);

			vg.CreateLine(m_p[0].position, m_p[1].position, color);
			vg.CreateLine(m_p[2].position, m_p[3].position, color);
		}
		break;

	case eFGM_RotateLine:
		{
			x = Cosine(m_SineArgs[0].freq, m_SineArgs[0].base, m_SineArgs[0].amp, (float)t);
			y = Sine(m_SineArgs[0].freq, m_SineArgs[0].base, m_SineArgs[0].amp, (float)t);

			m_p[0].position = Vec3(0.5f - x, 0.5f - y, z);
			m_p[1].position = Vec3(0.5f + x, 0.5f + y, z);

			vg.CreateLine(m_p[0].position, m_p[1].position, color);
		}
		break;

	case eFGM_RotateX:
		{
			x = Cosine(m_SineArgs[0].freq, m_SineArgs[0].base, m_SineArgs[0].amp, (float)t);
			y = Sine(m_SineArgs[0].freq, m_SineArgs[0].base, m_SineArgs[0].amp, (float)t);

			m_p[0].position = Vec3(0.5f + x, 0.5f - y, z);
			m_p[1].position = Vec3(0.5f - x, 0.5f + y, z);
			m_p[2].position = Vec3(0.5f + x, 0.5f + y, z);
			m_p[3].position = Vec3(0.5f - x, 0.5f - y, z);

			vg.CreateLine(m_p[0].position, m_p[1].position,	color);
			vg.CreateLine(m_p[2].position, m_p[3].position,	color);
		}
		break;

	case eFGM_BouncingLines:
		{
			static Vec3 p1v = Vec3(0.01f, -0.02f) /** 0.04f*/, p2v = Vec3(-0.03f, 0.04f) /** 0.04f*/;
			static Vec3 p1 = Vec3(0.0f, 0.0f, z), p2 = Vec3(1.0f, 1.0f, z);

			p1 += p1v * t;
			p2 += p2v * t;

			if ((p1.x >= 1.0f && p1v.x > 0) || (p1.x <= 0.0f && p1v.x < 0))
				p1v.x *= -1.0f;
			if ((p1.y >= 1.0f && p1v.y > 0) || (p1.y <= 0.0f && p1v.y < 0))
				p1v.y *= -1.0f;

			if ((p2.x >= 1.0f && p2v.x > 0) || (p2.x <= 0.0f && p2v.x < 0))
				p2v.x *= -1.0f;

			if ((p2.y >= 1.0f && p2v.y > 0) || (p2.y <= 0.0f && p2v.y < 0))
				p2v.y *= -1.0f;
		
			vg.CreateLine(p1, p2, color);
		}
		break;

	case eFGM_Spiral:
		{
			Float ct = fabsf(Sine(0.25f, 0.0f, 2.0f, t.Get()));

			for (UInt32 i = 0; i < m_p.Size(); i++)
			{
				m_p[i].position.x = i * Cosine(m_SineArgs[1].freq, m_SineArgs[1].base, m_SineArgs[1].amp * 0.01f, /*0.5f **/ (i / TWOPI) - t/** ct*/);
				m_p[i].position.y = i * Sine(m_SineArgs[1].freq, m_SineArgs[1].base, m_SineArgs[1].amp * 0.01f, /*0.5f **/ (i / TWOPI) - t/** ct*/);

				m_p[i].position += Vec2(0.5f, 0.5f);
				
				m_p[i].color = color;
			}

			vg.DrawLineStrip(m_p, false);
		}
		break;

	case eFGM_BezierSpokes:
		{
			for (UInt32 spoke = 0; spoke < 5; spoke++)
			{
				switch (m_NumActivePts)
				{
				case 4:
					m_p[3].position.x = Cosine(m_SineArgs[0].freq, 0.25f, 0.25f, t.Get() + spoke * TWOPI / 5);
					m_p[3].position.y = Sine(m_SineArgs[0].freq, 0.25f, 0.25f, t.Get() + spoke * TWOPI / 5);
					//Intentional fallthrough

				case 3:
					m_p[2].position.x = Cosine(m_SineArgs[0].freq, 0.5f, 0.25f, t.Get() + spoke * TWOPI / 5);
					m_p[2].position.y = Sine(m_SineArgs[0].freq, 0.5f, 0.25f, t.Get() + spoke * TWOPI / 5);
					//Intentional fallthrough

				default:
					m_p[0] = Vec3(0.5f, 0.5f, z);
					
					m_p[1].position.x = Cosine(m_SineArgs[0].freq, 0.5f, 0.2f, t.Get() - (PI / 4) + spoke * TWOPI / 5);
					m_p[1].position.y = Sine(m_SineArgs[0].freq, 0.5f, 0.2f, t.Get() - (PI / 4) + spoke * TWOPI / 5);
					
				}

				switch (m_NumActivePts)
				{
				case 2:
					vg.DrawBezier2(m_p[0].position, m_p[1].position, 
									0, color);
					break;

				case 3:
					vg.DrawBezier3(m_p[0].position, m_p[1].position, m_p[2].position, 
									0, color);
					break;

				case 4:
					vg.DrawBezier4(m_p[0].position, m_p[1].position, m_p[2].position, m_p[3].position, 
									0, color);
					break;
				}
			}
		}
		break;

	case eFGM_GridPoints:
		{
			static const UInt32 numPts = 20;
			static const Float nAdj = 1.0f / numPts;

			static TVertexArray tempV(numPts * numPts);
			
			for (UInt32 yi = 0; yi < numPts; yi++)
				for (UInt32 xi = 0; xi < numPts; xi++)
					tempV[yi * numPts + xi] = CVertex(Vec3((xi + 0.5f) * nAdj, (yi + 0.25f) * nAdj - 0.1f, z), color);

			vg.DrawPointList(tempV);
		}
		break;
	}

	//RenderForeground(2);
}

//////////////////////////////////////////////////////////////////////////

Int32 CVisualizer::Render(UInt32 stage)
{
	m_CS.Lock();

	UInt32 numPasses = 0;
	CD3DImage& buffer = m_Buffer[stage];

	if (!g_D3D->SetRenderTarget(buffer, 1))
		return -1;
	
	String tech = (stage == 0 ? "Tech1" : "Tech2");

	if (SUCCEEDED(m_pEffect->Shader->SetTechnique(tech.c_str())))
	{
		SetShaderVars();

		if (SUCCEEDED(m_pEffect->Shader->Begin(&numPasses, 0)))
		{
			for (UInt32 p = 0; p < numPasses; p++)
			{
				if (SUCCEEDED(m_pEffect->Shader->BeginPass(p)))
				{
					RenderGeometry();

					m_pEffect->Shader->EndPass();
				}
			}
		}

		m_pEffect->Shader->End();
	}

	g_D3D->SetRenderTarget(NULL, 1);

	m_CS.Unlock();

	return 0;
}

//////////////////////////////////////////////////////////////////////////

Int32 CVisualizer::Shutdown()
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////

void CVisualizer::SetShaderVars()
{
	D3DMatrix mat = g_D3D->GetViewProj();
	m_pEffect->Shader->SetMatrix("matViewProj", &mat);

	m_pEffect->Shader->SetVector("g_ColorDecay", (Vec4*)&m_cColorDecay);
	m_pEffect->Shader->SetVector("g_BGColor", (Vec4*)&m_cBGColor);

	m_pEffect->Shader->SetBool("bUsePolar", m_bUsePolar);

	m_pEffect->Shader->SetBool("UseSineX", UseSine[0]);
	m_pEffect->Shader->SetBool("UseSineY", UseSine[1]);
	m_pEffect->Shader->SetBool("UseSineR", UseSine[2]);
	m_pEffect->Shader->SetBool("UseSineA", UseSine[3]);

	m_pEffect->Shader->SetFloat("g_Time", m_tTime.Get());
	m_pEffect->Shader->SetFloat("wrapScale", m_fWrapScale);

	mat.m[0][0] = ArgModeX.freq;
	mat.m[0][1] = ArgModeX.base;
	mat.m[0][2] = ArgModeX.amp;
	mat.m[0][3] = ArgModeX.phase;

	mat.m[1][0] = ArgModeY.freq;
	mat.m[1][1] = ArgModeY.base;
	mat.m[1][2] = ArgModeY.amp;
	mat.m[1][3] = ArgModeY.phase;

	mat.m[2][0] = ArgModeR.freq;
	mat.m[2][1] = ArgModeR.base;
	mat.m[2][2] = ArgModeR.amp;
	mat.m[2][3] = ArgModeR.phase;

	mat.m[3][0] = ArgModeA.freq;
	mat.m[3][1] = ArgModeA.base;
	mat.m[3][2] = ArgModeA.amp;
	mat.m[3][3] = ArgModeA.phase;

	m_pEffect->Shader->SetMatrix("ArgMode", &mat);

	mat.m[0][0] = VelArgsX.freq;
	mat.m[0][1] = VelArgsX.base;
	mat.m[0][2] = VelArgsX.amp;
	mat.m[0][3] = VelArgsX.phase;

	mat.m[1][0] = VelArgsY.freq;
	mat.m[1][1] = VelArgsY.base;
	mat.m[1][2] = VelArgsY.amp;
	mat.m[1][3] = VelArgsY.phase;

	mat.m[2][0] = VelArgsR.freq;
	mat.m[2][1] = VelArgsR.base;
	mat.m[2][2] = VelArgsR.amp;
	mat.m[2][3] = VelArgsR.phase;

	mat.m[3][0] = VelArgsA.freq;
	mat.m[3][1] = VelArgsA.base;
	mat.m[3][2] = VelArgsA.amp;
	mat.m[3][3] = VelArgsA.phase;

	m_pEffect->Shader->SetMatrix("VelArgs", &mat);
}

//////////////////////////////////////////////////////////////////////////

Int32 CVisualizer::HandleInput()
{
	static Timer inputTimer;
	static const Float inputTime = 0.25f;

	UInt32 mode = m_eFGMode;

	m_CS.Lock();

	//KEYSTATE HACK
	if (KEYDOWN(VK_ADD) && inputTimer > inputTime)
	{
		if (++mode == eFGM_NumModes)
			mode = eFGM_First;

		inputTimer.Reset();
	}

	if (KEYDOWN(VK_SUBTRACT) && inputTimer > inputTime)
	{
		if (mode == eFGM_First)
			mode = eFGM_NumModes - 1;
		else
			--mode;

		inputTimer.Reset();
	}

	/*if (KEYDOWN(VK_HOME) && inputTimer > inputTime)
	{
		if (++m_EffectMode[0] == 7)
			m_EffectMode[0] = -1;

		inputTimer.Reset();
	}

	if (KEYDOWN(VK_END) && inputTimer > inputTime)
	{
		if (m_EffectMode[0] <= -1)
			m_EffectMode[0] = 6;
		else
			--m_EffectMode[0];

		inputTimer.Reset();
	}

	if (KEYDOWN(VK_PRIOR) && inputTimer > inputTime)
	{
		if (++m_EffectMode[1] >= 7)
			m_EffectMode[1] = -1;

		inputTimer.Reset();
	}

	if (KEYDOWN(VK_NEXT) && inputTimer > inputTime)
	{
		if (m_EffectMode[1] <= -1)
			m_EffectMode[1] = 6;
		else
			--m_EffectMode[1];

		inputTimer.Reset();
	}

	if (KEYDOWN(VK_UP) && inputTimer > inputTime)
	{
		if (++m_EffectMode[2] >= 8)
			m_EffectMode[2] = -1;

		inputTimer.Reset();
	}

	if (KEYDOWN(VK_DOWN) && inputTimer > inputTime)
	{
		if (m_EffectMode[2] <= -1)
			m_EffectMode[2] = 7;
		else
			--m_EffectMode[2];

		inputTimer.Reset();
	}

	if (KEYDOWN(VK_RIGHT) && inputTimer > inputTime)
	{
		if (++m_EffectMode[3] >= 8)
			m_EffectMode[3] = -1;

		inputTimer.Reset();
	}

	if (KEYDOWN(VK_LEFT) && inputTimer > inputTime)
	{
		if (m_EffectMode[3] <= -1)
			m_EffectMode[3] = 7;
		else
			--m_EffectMode[3];

		inputTimer.Reset();
	}*/

	if (KEYDOWN(VK_INSERT) && inputTimer > inputTime)
	{
		m_cFGColor.Randomize();

		inputTimer.Reset();
	}

	if (KEYDOWN(VK_DELETE) && inputTimer > inputTime)
	{
		m_cBGColor.Randomize();

		inputTimer.Reset();
	}

	if (KEYDOWN(VK_RETURN) && inputTimer > inputTime)
	{
		m_bUsePolar = !m_bUsePolar;

		inputTimer.Reset();
	}

	if (KEYDOWN(VK_PRIOR) && inputTimer > inputTime)
	{
		m_bRandomize = !m_bRandomize;

		inputTimer.Reset();
	}


	m_eFGMode = static_cast<EFGMode>(mode);

	m_CS.Unlock();

	return 0;
}

//////////////////////////////////////////////////////////////////////////

void CVisualizer::RandomizeValues()
{
	static Timer t;
	static const Int32 chance = 75;

	if (t > 0.5f)
	{
		FOR_EACH(i, bRand)
			bRand[i].Update();

		FOR_EACH(i, cRand)
			cRand[i].Update();

		FOR_EACH(i, fRand)
			fRand[i].Update();
		
		FOR_EACH(i, nRand)
			nRand[i].Update();
		
		if (Random(chance) == 0)
			m_eFGMode = static_cast<EFGMode>(Random(eFGM_NumModes - 1));

		t.Reset();
	}
}

//////////////////////////////////////////////////////////////////////////

void CVisualizer::RenderGeometry()
{
	g_D3D->GetDevice()->SetStreamSource(0,	m_Buffer[0], 0, sizeof(CVertex));
	g_D3D->GetDevice()->SetIndices(			m_Buffer[0]);

	if (FAILS(g_D3D->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2)))
	{
		DxErr;
	}
}

//////////////////////////////////////////////////////////////////////////

void CVisualizer::ClearTextures()
{
	m_Buffer[0].Fill(Color::km_Black);
	m_Buffer[1].Fill(Color::km_Black);
}

//////////////////////////////////////////////////////////////////////////

void CVisualizer::ClearVertices()
{
	vg.PurgeVertices();
}

//////////////////////////////////////////////////////////////////////////

void CVisualizer::PlotPoint(Vec2 pos)
{
	vg.PushVertex(CVertex(pos, m_cFGColor));
}

//////////////////////////////////////////////////////////////////////////
