#include "event_handler.h"

std::queue <Event> event_instances_queue;
SDL_Event sdl_event;

char* inputChar;

char *text;
char *composition;
Sint32 cursor;
Sint32 selection_len;


//function to set event 
void run_event_handler()
{
    while( SDL_PollEvent(&sdl_event) != 0)
    {
        readAndSetEventQueue(&sdl_event);
    }
}

void readAndSetEventQueue(SDL_Event* sdl_event_ptr)
{
	//Special text input event
	if( sdl_event_ptr->type == SDL_TEXTINPUT )
	{
		//Not copy or pasting
		if( !( SDL_GetModState() & KMOD_CTRL && ( sdl_event_ptr->text.text[ 0 ] == 'c' || sdl_event_ptr->text.text[ 0 ] == 'C' || sdl_event_ptr->text.text[ 0 ] == 'v' || sdl_event_ptr->text.text[ 0 ] == 'V' ) ) )
		{
			//Assign character
			pushEventInstance(Event::TEXT_IN);
			inputChar = sdl_event_ptr->text.text;
		}
	}
    else if(sdl_event_ptr->type == SDL_QUIT){pushEventInstance(Event::QUIT_WINDOW);}
    //If key was pressed
    else if(sdl_event_ptr->type == SDL_KEYDOWN && sdl_event_ptr->key.repeat == 0)
    {
        switch(sdl_event_ptr->key.keysym.sym)
        {
            case SDLK_UP: {pushEventInstance(Event::UP_ARROW); break;}
            case SDLK_w: {pushEventInstance(Event::UP_ARROW); break;}
            
            case SDLK_DOWN: {pushEventInstance(Event::DOWN_ARROW); break;}
            case SDLK_s: {pushEventInstance(Event::DOWN_ARROW); break;}
            
            case SDLK_LEFT: {pushEventInstance(Event::LEFT_ARROW); break;}
            case SDLK_a: {pushEventInstance(Event::LEFT_ARROW); break;}
            
            case SDLK_RIGHT: {pushEventInstance(Event::RIGHT_ARROW); break;}
            case SDLK_d: {pushEventInstance(Event::RIGHT_ARROW); break;}
            
            case SDLK_SPACE:{ pushEventInstance(Event::SPACE); break;}
            case SDLK_RETURN:{pushEventInstance(Event::ENTER); break;}
            case SDLK_ESCAPE:{pushEventInstance(Event::ESCAPE); break;}
            case SDLK_g:{pushEventInstance(Event::G); break;}
            case SDLK_v:{pushEventInstance(Event::V); break;}
            case SDLK_b:{pushEventInstance(Event::B); break;}
            case SDLK_n:{pushEventInstance(Event::N); break;}
            case SDLK_r:{pushEventInstance(Event::R); break;}
            case SDLK_SLASH:{pushEventInstance(Event::SLASH); break;}
            case SDLK_BACKSPACE:{ pushEventInstance(Event::BACKSPACE); break;}
            default:{pushEventInstance(Event::NONE); break;}
        }
    }
    //if key was pressed and repeated
    else if(sdl_event_ptr->type == SDL_KEYDOWN && sdl_event_ptr->key.repeat >= 1)
    {
        switch(sdl_event_ptr->key.keysym.sym)
        {
            case SDLK_UP: {pushEventInstance(Event::UP_ARROW_REPEAT); break;}
            case SDLK_w: {pushEventInstance(Event::UP_ARROW_REPEAT); break;}
            
            case SDLK_DOWN: {pushEventInstance(Event::DOWN_ARROW_REPEAT); break;}
            case SDLK_s: {pushEventInstance(Event::DOWN_ARROW_REPEAT); break;}
            
            case SDLK_LEFT: {pushEventInstance(Event::LEFT_ARROW_REPEAT); break;}
            case SDLK_a: {pushEventInstance(Event::LEFT_ARROW_REPEAT); break;}
            
            case SDLK_RIGHT: {pushEventInstance(Event::RIGHT_ARROW_REPEAT); break;}
            case SDLK_d: {pushEventInstance(Event::RIGHT_ARROW_REPEAT); break;}
            
            case SDLK_SPACE:{ pushEventInstance(Event::SPACE_REPEAT); break;}
            //Handle backspace
			
            default:{pushEventInstance(Event::NONE); break;}
        }
    }
    //if a key was released
    else if(sdl_event_ptr->type == SDL_KEYUP && sdl_event_ptr->key.repeat == 0)
    {
        switch(sdl_event_ptr->key.keysym.sym )//slow down dot if key is released
        {
            case SDLK_UP: {pushEventInstance(Event::UP_ARROW_RELEASE); break;}
            case SDLK_w: {pushEventInstance(Event::UP_ARROW_RELEASE); break;}
            
            case SDLK_DOWN: {pushEventInstance(Event::DOWN_ARROW_RELEASE); break;}
			case SDLK_s: {pushEventInstance(Event::DOWN_ARROW_RELEASE); break;}
			
            case SDLK_LEFT: {pushEventInstance(Event::LEFT_ARROW_RELEASE); break;}
			case SDLK_a: {pushEventInstance(Event::LEFT_ARROW_RELEASE); break;}
			
            case SDLK_RIGHT: {pushEventInstance(Event::RIGHT_ARROW_RELEASE); break;}
            case SDLK_d: {pushEventInstance(Event::RIGHT_ARROW_RELEASE); break;}
  
            case SDLK_SPACE:{ pushEventInstance(Event::SPACE_RELEASE); break;}
            default:{pushEventInstance(Event::NONE); break;}
        }
    }
    else if(sdl_event_ptr->type == SDL_MOUSEMOTION 
			|| sdl_event_ptr->type == SDL_MOUSEBUTTONDOWN 
			|| sdl_event_ptr->type == SDL_MOUSEBUTTONUP)
    {
		switch(sdl_event_ptr->type)
		{
			case SDL_MOUSEMOTION :{ pushEventInstance(Event::MOUSE_MOTION); break;}
			case SDL_MOUSEBUTTONDOWN:{ pushEventInstance(Event::MOUSE_DOWN); break;}
			case SDL_MOUSEBUTTONUP:{ pushEventInstance(Event::MOUSE_UP); break;}
		}
	}
    else{pushEventInstance(Event::NONE);}
}

void pushEventInstance(Event thisEvent){event_instances_queue.push(thisEvent);}
void popEventInstanceFromFront(){event_instances_queue.pop();}

Event& getEventInstanceFront(){return event_instances_queue.front();}

bool isEventQueueEmpty(){return event_instances_queue.empty();}

void clearEventsQueue()
{
    std::queue <Event> empty_queue;
    //swap with empty queue
    event_instances_queue.swap(empty_queue);
}

char* getInputCharFromTextInputEvent(){return inputChar;}
