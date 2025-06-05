#ifndef PERIPHERALS_H 
#define PERIPHERALS_H

#include <mutex>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

class Mouse { 
    public: 
    typedef float mouse_coord_type; 

    Mouse() = default;
    mouse_coord_type* getX_Addr(void);
    mouse_coord_type* getY_Addr(void);

    private:
    mouse_coord_type x; 
    mouse_coord_type y; 
};

#define getKeyMask(i) (u_int64_t)(2<<i)
class Keyboard{ 
    public: 
    enum Key{ 
        UP, 
        DOWN, 
        LEFT,
        RIGHT
    };

    u_int64_t keys_ = 0; 
    static Keyboard* getInstance(void);
    void toggleKey (Key k);
    bool isPressed (Key k);
    void pressKey (Key k);
    void unpressKey (Key k);
    void doKeyUp(SDL_KeyboardEvent* event);
    void doKeyDown(SDL_KeyboardEvent* event);

    protected: 
    private:
    Keyboard(){};
    ~Keyboard(){};
    Keyboard(Keyboard& other) = delete; 
    void operator=(Keyboard& other) = delete;
    static Keyboard* keyboard_; 
    static std::mutex mutex_;
};

#endif 
