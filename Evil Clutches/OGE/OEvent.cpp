#include "OEvent.h"

OEvent::OEvent() {}

OEvent::~OEvent() {}

void OEvent::OnEvent(SDL_Event* event)
{
	switch (event->type)
	{
		//Handle Window Evnets
	case SDL_WINDOWEVENT:
			switch(event->window.event)
			{
				//Mouse enter
			case SDL_WINDOWEVENT_ENTER:
				OnMouseFocus();
				break;

				//Mouse exit
			case SDL_WINDOWEVENT_LEAVE:
				OnMouseBlur();
				break;

				//Keyboard focus grained
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				OnInputFocus();
				break;

			case SDL_WINDOWEVENT_FOCUS_LOST:
				OnInputBlur();
				break;

				//Window minimized
			case SDL_WINDOWEVENT_MINIMIZED:
				OnMinimize();
				break;

				//Window restored
			case SDL_WINDOWEVENT_RESTORED:
				OnRestore();
				break;
			}//end window switch
		break;

	case SDL_KEYDOWN:
		OnKeyDown(event->key.keysym.sym, event->key.keysym.mod, event->key.keysym.scancode);
		break;

	case SDL_KEYUP:
		OnKeyUp(event->key.keysym.sym, event->key.keysym.mod, event->key.keysym.scancode);
		break;

	case SDL_MOUSEMOTION:
		OnMouseMove(event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel,
			(event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT)) != 0,
			(event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0,
			(event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
		break;

	case SDL_MOUSEBUTTONDOWN:
		switch (event->button.button) {
		case SDL_BUTTON_LEFT:
			OnLButtonDown(event->button.x, event->button.y);
			break;

		case SDL_BUTTON_RIGHT:
			OnRButtonDown(event->button.x, event->button.y);
			break;

		case SDL_BUTTON_MIDDLE:
			OnMButtonDown(event->button.x, event->button.y);
			break;
		}
		break;

	case SDL_MOUSEBUTTONUP:
		switch (event->button.button) {
		case SDL_BUTTON_LEFT:
			OnLButtonUp(event->button.x, event->button.y);
			break;

		case SDL_BUTTON_RIGHT:
			OnRButtonUp(event->button.x, event->button.y);
			break;

		case SDL_BUTTON_MIDDLE:
			OnMButtonUp(event->button.x, event->button.y);
			break;
		}
		break;

	case SDL_JOYAXISMOTION:
		OnJoyAxis(event->jaxis.which, event->jaxis.axis, event->jaxis.value);
		break;

	case SDL_JOYBALLMOTION:
		OnJoyBall(event->jaxis.which, event->jball.ball, event->jball.xrel, event->jball.yrel);
		break;

	case SDL_JOYHATMOTION:
		OnJoyHat(event->jhat.which, event->jhat.hat, event->jhat.value);
		break;

	case SDL_JOYBUTTONDOWN:
		OnJoyButtonDown(event->jbutton.which, event->jbutton.button);
		break;

	case SDL_JOYBUTTONUP:
		OnJoyButtonUp(event->jbutton.which, event->jbutton.button);
		break;

	case SDL_QUIT:
		OnExit();
		break;

	case SDL_SYSWMEVENT:
		//Ignore
		break;

	case SDL_WINDOWEVENT_RESIZED:
		OnResize(event->window.data1, event->window.data2);
		break;

	case SDL_WINDOWEVENT_EXPOSED:
		OnExpose();
		break;

	default:
		OnUser(event->user.type, event->user.code, event->user.data1, event->user.data2);
		break;
	}//end switch
}//end OnEvent

void OEvent::OnInputFocus()
{/*Pure virtual, do nothing*/ }

void OEvent::OnInputBlur()
{/*Pure virtual, do nothing*/ }

void OEvent::OnKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 unicode)
{/*Pure virtual, do nothing*/}

void OEvent::OnKeyUp(SDL_Keycode sym, Uint16 mod, Uint16 unicode)
{/*Pure virtual, do nothing*/}

void OEvent::OnMouseFocus()
{/*Pure virtual, do nothing*/}

void OEvent::OnMouseBlur()
{/*Pure virtual, do nothing*/}

void OEvent::OnMouseMove(int mX, int mY, int relX, int relY, bool left, bool right, bool middle)
{/*Pure virtual, do nothing*/}

void OEvent::OnMouseWheel(bool up, bool down)
{/*Pure virtual, do nothing*/}

void OEvent::OnLButtonDown(int mX, int mY)
{/*Pure virtual, do nothing*/}

void OEvent::OnLButtonUp(int mX, int mY)
{/*Pure virtual, do nothing*/}

void OEvent::OnRButtonDown(int mX, int mY)
{/*Pure virtual, do nothing*/}

void OEvent::OnRButtonUp(int mX, int mY)
{/*Pure virtual, do nothing*/}

void OEvent::OnMButtonDown(int mX, int mY)
{/*Pure virtual, do nothing*/}

void OEvent::OnMButtonUp(int mX, int mY)
{/*Pure virtual, do nothing*/}

void OEvent::OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value)
{/*Pure virtual, do nothing*/}

void OEvent::OnJoyButtonDown(Uint8 which, Uint8 button)
{/*Pure virtual, do nothing*/}

void OEvent::OnJoyButtonUp(Uint8 which, Uint8 button)
{/*Pure virtual, do nothing*/}

void OEvent::OnJoyHat(Uint8 which, Uint8 hat, Uint8 value)
{/*Pure virtual, do nothing*/}

void OEvent::OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel)
{/*Pure virtual, do nothing*/}

void OEvent::OnMinimize()
{/*Pure virtual, do nothing*/}

void OEvent::OnRestore()
{/*Pure virtual, do nothing*/}

void OEvent::OnResize(int w, int h)
{/*Pure virtual, do nothing*/}

void OEvent::OnExpose()
{/*Pure virtual, do nothing*/}

void OEvent::OnExit()
{/*Pure virtual, do nothing*/}

void OEvent::OnUser(Uint8 type, int code, void* data1, void* data2)
{/*Pure virtual, do nothing*/}