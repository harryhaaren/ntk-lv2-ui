
// This is the header for our custom widget.
// We override the on_expose_event function so GTK calls into this class
// to draw the widget

#ifndef WIDGET
#define WIDGET

#include <FL/Fl.H>
#include <FL/Fl_Single_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>


#include <pthread.h>

// LV2UI stuff
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

class Xembed;

class Widget
{
  public:
    
    // public Lv2 communication stuff
    LV2UI_Controller controller;
    LV2UI_Write_Function write_function;
    
    
    Widget(void* x);
    void idle();

  protected:
    pthread_t fl_thread;
    
    Xembed* win;
    
    // stores frequency we're currently at.
    float frequency;
    
    Window xWindowID;
    
    
    
    //static void* callback(void*);
    
    //bool on_expose_event(GdkEventExpose* event);
    //bool on_button_press_event(GdkEventButton* event);
};

#endif
