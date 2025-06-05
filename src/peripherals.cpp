#include "peripherals.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

Mouse::mouse_coord_type* Mouse::getX_Addr(void){
    return &x;
}

Mouse::mouse_coord_type* Mouse::getY_Addr(void){ 
    return &y;
}

Keyboard* Keyboard::keyboard_{nullptr};
std::mutex Keyboard::mutex_;

Keyboard* Keyboard::getInstance(void){ 
    std::lock_guard<std::mutex> lock(mutex_);
    if (keyboard_ == nullptr)
    {
        keyboard_ = new Keyboard();
    }
    return keyboard_;
}

void Keyboard::pressKey (Key k){ 
    u_int64_t mask = getKeyMask((int)k);
    keys_ = keys_ | getKeyMask((int)k); //A XOR B
}

void Keyboard::unpressKey (Key k){ 
    u_int64_t imask = 0;
    imask--; 
    imask = imask ^ getKeyMask((int)k);
    keys_ = keys_ & imask; //A XOR B
}

void Keyboard::toggleKey (Key k){ 
    u_int64_t mask = getKeyMask((int)k);
    keys_ = keys_ ^ getKeyMask((int)k); //A XOR B
}

bool Keyboard::isPressed (Key k){ 
    return (bool)(keys_ & getKeyMask((int)k));
}

void Keyboard::doKeyUp(SDL_KeyboardEvent* event){ 
    switch(event->scancode){ 
        case(SDL_SCANCODE_UP): 
            unpressKey(Key::UP);
            break; 
        case(SDL_SCANCODE_DOWN): 
            unpressKey(Key::DOWN);
            break;
        case(SDL_SCANCODE_RIGHT):
            unpressKey(Key::RIGHT);
            break;
        case(SDL_SCANCODE_LEFT):
            unpressKey(Key::LEFT);
            break;
    }
}

void Keyboard::doKeyDown(SDL_KeyboardEvent* event){ 
    switch(event->scancode){ 
        case(SDL_SCANCODE_UP): 
            pressKey(Key::UP);
            break; 
        case(SDL_SCANCODE_DOWN): 
            pressKey(Key::DOWN);
            break;
        case(SDL_SCANCODE_RIGHT):
            pressKey(Key::RIGHT);
            break;
        case(SDL_SCANCODE_LEFT):
            pressKey(Key::LEFT);
            break;
    }
}