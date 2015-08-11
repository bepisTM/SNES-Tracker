#include "core/timer/Timer.h"
#include <unistd.h>

Uint32 Timer_SDL::eventType(registerEventType());
Uint32 Timer_SDL::registerEventType()
{
	Uint32 _eventType = SDL_RegisterEvents(1);
	if (_eventType == ((Uint32)-1))
	{
		fprintf(stderr, "Error: Couldn't register a new event type for timers:[\n");
		fprintf(stderr, "\tUsing UserEvent type");
		_eventType = SDL_USEREVENT;
	}
	return _eventType;
}

Timer_SDL::Timer_SDL() : single(false), threaded(true)
{
}

Timer_SDL::~Timer_SDL()
{
}

// STATIC - gets called in Timer Thread
uint32_t Timer_SDL::staticCallback(uint32_t interval, void *param)
{
	return ((Timer_SDL*)param)->internalCallback(interval,param);
}
// Gets called in Timer Thread
uint32_t Timer_SDL::internalCallback(uint32_t interval, void *param)
{
	uint32_t ret_interval = interval;
	callback.interval = interval;

	if (threaded)
	{
		ret_interval = callback();
	}
	else
	{
		// Push the eventType
		SDL_Event event;
    	SDL_zero(event);
    	event.type = eventType;
	    event.user.code = 0;	// don't care
	    event.user.data1 = &callback;
	    SDL_PushEvent(&event);
	}

	if (single)
		return 0;
	return ret_interval;
}

void Timer_SDL::start(int msec)
{
	// this is good incase start() is called multiple times on the same timer before stop()
    stop();
    timerid = SDL_AddTimer(inter=msec, staticCallback, this);

    if (!timerid)
    {
#		ifdef ST_DEBUG
    		fprintf(stderr, "SDL_AddTimer failed : %s\n", SDL_GetError());
#		endif
    }
}

void Timer_SDL::start()
{
	start(inter);
}

void Timer_SDL::stop()
{
	if (!timerid)
		return;

	bool success = SDL_RemoveTimer(timerid);

	if (!success)
	{
#		ifdef ST_DEBUG
			// should be using DEBUGLOG
			fprintf(stderr, "SDL_Remove Timer failed on ID %d : %s\n", timerid, SDL_GetError());
			// use SDL function to get more error info
#		endif
	}
	timerid = 0;
}

void Timer_SDL::setCallback(timer_callback_t _callback, void *param)
{
	callback.func = _callback;
	callback.param = param;
}


/* Example Program

Demonstrates Super-Awesomeness

export DYLD_LIBRARY_PATH=~/Code/SDL2-2.0.3/build/.libs
g++ -g -std=c++11 Timer.cpp -I../.. -DTIMER_SDL \
-L$HOME/Code/SDL2-2.0.3/build/.libs -I$HOME/Code/SDL2-2.0.3/include -lSDL2

*/

uint32_t cb(uint32_t interval, void *p)
{
    volatile int &var = *(volatile int *)p;
    fprintf(stderr, "%d..", var++);
    if (var == 2+1 || var == 6+1)
    	return 0;
    return interval;
}

void poll(Timer &t)
{
	SDL_Event ev;
	if (SDL_PollEvent(&ev))
	{
  		if (ev.type == Timer_SDL::eventType)
		{
			Timer_SDL::Callback &tcb = *(Timer_SDL::Callback *)ev.user.data1;
			int i = tcb();
			if (!i)
			{
				t.stop();
			}
			else if (i != tcb.interval)
			{
				t.start(i);
			}
  		}
  	}
}

int main()
{
    Timer t;
    volatile int var=0;

    if (SDL_InitSubSystem(SDL_INIT_TIMER | SDL_INIT_EVENTS))
    {
    	fprintf(stderr, "SDL subsystem init failed! : %s\n", SDL_GetError());
    }
    t.setInterval(100);
    t.setSingleShot(false);
    t.setCallback(cb, (void*)&var);
    t.setThreaded(false);


    fprintf(stderr, "Main-thread: ");
    t.start();
    
  	while (var <= 2)
  	{
  		poll(t);
  	}
  	fprintf(stderr, "\n\tsingle-shot: ");
  	t.setSingleShot(true);
  	t.start();
  	while (var == 3)
  	{
  		poll(t);
  	}
  	t.setSingleShot(false);
  	fprintf(stderr, "\nTimer-Thread: ");
  	t.setThreaded(true);
  	t.start();
  	while (var <= 6);

  	fprintf(stderr, "\n\tsingle-shot: ");
  	t.setSingleShot(true);
  	t.start();
  	while (var <= 7);

  	SDL_QuitSubSystem(SDL_INIT_TIMER | SDL_INIT_EVENTS);
  	SDL_Quit();
    return 0;
}






