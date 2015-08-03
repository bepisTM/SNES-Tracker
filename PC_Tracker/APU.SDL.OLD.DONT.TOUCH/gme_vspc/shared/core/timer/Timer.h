#pragma once

/*
  Todo: 

  . up for debate : Abstract IDs
*/

#include <stdint.h>

typedef uint32_t (*timer_callback_t)( uint32_t interval, void *param );

// An Abstract notion of a Timer
class AbstractTimer
{
public:
	virtual int interval() const { return 0; }
    virtual inline bool isActive() const { return false; }
	virtual inline bool isSingleShot() const { return false; }
	virtual inline void	setInterval(int msec) {}
	virtual inline void	setSingleShot(bool singleShot) {}
    virtual inline void setThreaded(bool threaded) {}
	//void	setTimerType(Qt::TimerType atype);
	virtual int	timerId() const { return 0; }
	//Qt::TimerType	timerType() const;
	//void start(unsigned interval_ms, bool oneshot=false);
	//int	remainingTime() const;
	virtual void start(int msec) {}
    virtual void start() {}
    virtual void stop() {}
    virtual void setCallback(timer_callback_t callback, void *param) {}
    // Virtual destructors are useful when you can delete an instance of a 
    // derived class through a pointer to base class
    virtual ~AbstractTimer() {}
};

#ifdef TIMER_SDL
#   include <SDL2/SDL.h>
    class Timer_SDL : public AbstractTimer
    {
    public:
        Timer_SDL();
        ~Timer_SDL();
    	int interval() const { return inter; }
        inline bool isActive() const { return timerid ? true : false; }
    	inline bool isSingleShot() const { return single; }
    	inline void	setInterval(int msec) { inter = msec; }
    	inline void	setSingleShot(bool singleShot) { single = singleShot; }
    	//void	setTimerType(Qt::TimerType atype);
    	//int	timerId() const;
    	//Qt::TimerType	timerType() const;
    	//void start(unsigned interval_ms, bool oneshot=false);
    	//int	remainingTime() const;
    	inline int timerId() const { return timerid; }
    	void start(int msec);
        void start();
        void stop();
        void setCallback(timer_callback_t callback, void *param);
        inline void setThreaded(bool _threaded) { threaded = _threaded; }
        
        // timer callback, dont worry about this
        static uint32_t staticCallback(Uint32 interval, void *param);
        uint32_t internalCallback(Uint32 interval, void *param);
        //Uint32 cursor_timer(Uint32 interval);
        inline Uint32 eventType_() const { return eventType; }
        static Uint32 eventType;  // the SDL Event that will be pushed
        struct Callback
        {
            timer_callback_t func;
            void *param;
            Uint32 interval;
            Uint32 operator()(void) { return func(interval, param); }
        } callback;

    private:
        static Uint32 registerEventType();

        int inter;
        
        SDL_TimerID timerid;
        
        uint single     : 1;
        uint threaded   : 1;
    };
#endif /* TIMER_SDL */

// A wrapper class
class Timer
{
public:
	Timer() : p(0)
	{
#		if defined(TIMER_QT)
			p = new Timer_QT;
#		elif defined(TIMER_SDL)
			p = new Timer_SDL;
#		else
			p = new AbstractTimer;
#		endif
	}
	~Timer()
	{
		if (p)
		{
			delete p;
			p = 0;
		}
	}
	int interval() const { return p->interval(); }
	inline bool isSingleShot() const { return p->isSingleShot(); }
	inline void	setInterval(int msec) { p->setInterval(msec); }
	inline void	setSingleShot(bool singleShot) { p->setSingleShot(singleShot); }
    inline void setThreaded(bool threaded) { p->setThreaded(threaded); }
	//void	setTimerType(Qt::TimerType atype);
	inline int	timerId() const { return p->timerId();};
	//Qt::TimerType	timerType() const;
	//void start(unsigned interval_ms, bool oneshot=false);
	//int	remainingTime() const;
	void start(int msec) { p->start(msec); };
    void start() { p->start(); };
    void stop() { p->stop(); };
    void setCallback(timer_callback_t callback, void *param) { p->setCallback(callback, param); };
private:
    int inter;
    uint single : 1;
    void *callback_param;
    timer_callback_t callback;

    AbstractTimer *p;	// This can become implemented timers
    //uint nulltimer : 1;
    //uint type : 2;
    // reserved : 28
};
