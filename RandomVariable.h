#pragma once

//////////////////////////////////////////////////////////////////////////

template <typename Type = Float>
class RandomVariable
{
public:
	RandomVariable()	{	}
	
	RandomVariable(Type& _init, Float maxTime = -1.0f, UInt32 oneInChance = 100)
	{
		m_pObj = &_init;
		m_Min = 0.0f;
		m_Max = 1.0f;
		m_MaxTime = maxTime;
		m_OneInChance = oneInChance;
	}
	
	RandomVariable(Type& _init, const Type& _min, const Type& _max, Float maxTime /*= -1.0f*/, UInt32 oneInChance = 100)
	{
		m_pObj = &_init;
		m_Min = _min;
		m_Max = _max;
		m_MaxTime = maxTime;
		m_OneInChance = oneInChance;
	}

	void SetTimerMax(Float maxTime)
	{
		if (maxTime == -1.0f)
			m_MaxTime = -1.0f;
		else
			m_MaxTime = Max(maxTime, 0.0f);
	}

	Float GetTimerMax() const
	{
		return m_MaxTime;
	}

	void SetOneInChance(UInt32 oneInChance)
	{
		m_OneInChance = oneInChance;
	}

	UInt32 GetOneInChance() const
	{
		return m_OneInChance;
	}

	void Randomize()
	{
		*m_pObj = Random(m_Max, m_Min);
	}

	void Update()
	{
		if (m_MaxTime != -1.0f && m_Timer >= m_MaxTime)
		{
			if (Random(3) == 0)
			{
				Randomize();
				m_Timer.Reset();
			}
		}
		else
		{
			if (Random(m_OneInChance) == 0)
			{
				Randomize();
				m_Timer.Reset();
			}
		}
	}

protected:
	//Pointer to the variable
	Type*	m_pObj;

	//Min and max values
	Type	m_Min;
	Type	m_Max;

	//Change timer
	Timer	m_Timer;
	//Max time before forcing randomization
	Float	m_MaxTime;

	//Represents the one in ?what? chance of randomizing
	UInt32	m_OneInChance;
};

//Special case for bool type random vars
void RandomVariable<Bool>::Randomize()
{
	*m_pObj = !(*m_pObj);
}

//Special case for colors
void RandomVariable<Color>::Randomize()
{
	m_pObj->Randomize();
}

//Some typedefs
typedef CDynamicArray<RandomVariable<Bool> > TRandomBoolArray;
typedef CDynamicArray<RandomVariable<Float> > TRandomFloatArray;
typedef CDynamicArray<RandomVariable<Int32> > TRandomIntArray;
typedef CDynamicArray<RandomVariable<Color> > TRandomColorArray;