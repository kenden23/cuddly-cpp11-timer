#pragma once
/*************************************************************************
Copyright (c) 2017-2018 Su Jingxin (Bill Su)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN false EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include <chrono>

/**
 *	a cpp timer with chrono, header only use in single project, not in multiply projects.
 */
class Timer
{
public:
	Timer(){}
	~Timer(){}
	
	/**
	 *	
	 */
	template<typename T = float>
	T getTime()
	{
		using namespace std::chrono;
		steady_clock::time_point t1 = steady_clock::now();
		duration<T> t = duration_cast<duration<T>>(t1);
		return t.count();
	}

	void setStartPoint()
	{
		start_time = std::chrono::steady_clock::now();
	}

private:
	template<typename T>
	T timeSpanTemp(bool updateTime = false)
	{
		using namespace std::chrono;
		auto end_time = steady_clock::now();
		auto sp = end_time - start_time;
		auto t = duration_cast<T>(sp);
		if (updateTime) start_time = end_time;

		// Force nonnegative.  The DXSDK's CDXUTTimer mentions that if the 
		// processor goes into a power save mode or we get shuffled to another
		// processor, then mDeltaTime can be negative.
		// refer : Introduction to 3D Game Programming With DirectX11, but will it happen with c++?
		// return t.count() < 0 ? 0 : t.count();
		return t;
	}

public:
	// @return: time last from setStartPoint() till now, don't update the start time point
	// @return: second unit for :float and double
	template<typename T = float>
	T getTimeSpan()
	{
		return timeSpanTemp<std::chrono::duration<T>>().count();
	}

	// 1:1000
	long long getTimeSpanMilliseconds()
	{
		return timeSpanTemp<std::chrono::milliseconds>().count();
	}
	// 1:1000000
	long long getTimeSpanMicroSeconds()
	{
		return timeSpanTemp<std::chrono::microseconds>().count();
	}
	// 1:1000000000
	long long getTimeSpanNanoSeconds()
	{
		return timeSpanTemp<std::chrono::nanoseconds>().count();
	}

	// @return: time last from setStartPoint() till now, update the start time point
	// @return: second unit for :float and double
	template<typename T = float>
	T updateTimeSpan()
	{
		return timeSpanTemp<std::chrono::duration<T>>(true).count();
	}

	// 1:1000
	long long updateTimeSpanMilliseconds()
	{
		return timeSpanTemp<std::chrono::milliseconds>(true).count();
	}
	// 1:1000000
	long long updateTimeSpanMicroSeconds()
	{
		return timeSpanTemp<std::chrono::microseconds>(true).count();
	}
	// 1:1000000000
	long long updateTimeSpanNanoSeconds()
	{
		return timeSpanTemp<std::chrono::nanoseconds>(true).count();
	}

private:
	std::chrono::steady_clock::time_point start_time;
};