
#ifndef WIDGET
#define WIDGET

#include <FL/Fl.H>
#include <FL/Fl_Single_Window.H>

// LV2UI stuff
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

class Widget
{
  public:
    
    // public Lv2 communication stuff, gets set in instantiate
    LV2UI_Controller controller;
    LV2UI_Write_Function write_function;
    
    // xWindowID to embed into
    Widget(void* xWindowID);
    
    // gets called repeatedly to update the UI
    void idle();
    
    int getWidth() {return win->w();}
    int getHeight(){return win->h();}
  
  protected:
    Fl_Window* win;
    
    // stores frequency we're currently at.
    float frequency;
};

#endif
