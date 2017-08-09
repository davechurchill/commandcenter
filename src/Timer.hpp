#pragma once

#include <functional>
#include <thread>
#include <chrono>

#ifdef WIN32   // Windows system specific
	#include <windows.h>
#else          // Unix based system specific
	#include <sys/time.h>
#endif

class Timer
{
 	double startTimeInMicroSec;                 // starting time in micro-second
    double endTimeInMicroSec;                   // ending time in micro-second
    int    stopped;                             // stop flag 
	#ifdef WIN32
		LARGE_INTEGER frequency;                    // ticks per second
		LARGE_INTEGER startCount;                   //
		LARGE_INTEGER endCount;                     //
	#else
		timeval startCount;                         //
		timeval endCount;                           //
	#endif

public:

	Timer()
	{
		#ifdef WIN32
			QueryPerformanceFrequency(&frequency);
			startCount.QuadPart = 0;
			endCount.QuadPart = 0;
		#else
			startCount.tv_sec = startCount.tv_usec = 0;
			endCount.tv_sec = endCount.tv_usec = 0;
		#endif

		stopped = 0;
		startTimeInMicroSec = 0;
		endTimeInMicroSec = 0;
		
		start();
	}
	
    ~Timer() {}                                 // default destructor

    void start()
	{
		stopped = 0; // reset stop flag
		
		#ifdef WIN32
			QueryPerformanceCounter(&startCount);
		#else
			gettimeofday(&startCount, NULL);
		#endif
	}
	
    void stop()
	{
		stopped = 1; // set timer stopped flag

		#ifdef WIN32
			QueryPerformanceCounter(&endCount);
		#else
			gettimeofday(&endCount, NULL);
		#endif
	}
	
    double getElapsedTimeInMicroSec()
	{
		#ifdef WIN32
			if(!stopped)
				QueryPerformanceCounter(&endCount);

			startTimeInMicroSec = startCount.QuadPart * (1000000.0 / frequency.QuadPart);
			endTimeInMicroSec = endCount.QuadPart * (1000000.0 / frequency.QuadPart);
		#else
			if(!stopped)
				gettimeofday(&endCount, NULL);

			startTimeInMicroSec = (startCount.tv_sec * 1000000.0) + startCount.tv_usec;
			endTimeInMicroSec = (endCount.tv_sec * 1000000.0) + endCount.tv_usec;
		#endif

		return endTimeInMicroSec - startTimeInMicroSec;
	}
	 
	double getElapsedTimeInMilliSec()
	{
		return this->getElapsedTimeInMicroSec() * 0.001;
	}


	double getElapsedTimeInSec()
	{
		return this->getElapsedTimeInMicroSec() * 0.000001;
	}

	double getElapsedTime()
	{
		return this->getElapsedTimeInSec();
	}

    template <class T>
    static void TimeFunction(std::function<T> function, ...)
    {
        Timer t;
        t.start();
        va_list args;
        va_start(args, function);
        va_end(args);

        double ms = t.getElapsedTimeInMilliSec();
        std::cout << "Function ran in " << ms << "ms\n";
    }
};

