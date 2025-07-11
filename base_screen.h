#ifndef BASE_SCREEN_H
#define BASE_SCREEN_H

#include <LiquidCrystal.h>
struct DisplayContext;

class BaseScreen {
public:

    /**
      * @brief Draws the screen's contents to the display.
      * @note This is a "pure virtual" function. Any class that inherits from BaseScreen
      *       MUST provide its own implementation of this function. The "= 0" is what
      *       makes it pure virtual and makes BaseScreen an abstract class.
      */
    virtual void draw(const DisplayContext& context) = 0;

    /**
     * @brief A virtual destructor.
     * @note This is a C++ rule: If a class has any virtual functions (like draw()),
     *       it MUST have a virtual destructor to ensure proper cleanup when working
     *       with pointers. It's a critical piece of boilerplate for safe polymorphism.
     */
    virtual ~BaseScreen() {}
};

#endif