Timer_SDL::Timer_SDL() : single(false), threaded(true)
{
	/*mutex = SDL_CreateMutex();
	if (!mutex) {
	  fprintf(stderr, "Error: Couldn't create mutex\n");
	}*/
}

Timer_SDL::~Timer_SDL()
{
	//SDL_DestroyMutex(mutex);
}

// using the mutex

	int status = SDL_TryLockMutex(mutex);
	if (status == 0) {
		
  		SDL_UnlockMutex(mutex);
	}
	else if (status == SDL_MUTEX_TIMEDOUT) {
		// more important function start() / stop() has the context
		// forget about whatever we were aiming to do here..
	} 
	else {
  		fprintf(stderr, "Error: Couldn't lock mutex | %s\n", SDL_GetError());
	}
  	

  	reset_active_timerid();
  	SDL_Delay(1000);