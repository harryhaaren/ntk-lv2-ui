
// this file has the drawing code for our custom widget

#include "widget.h"

#include "xembed.cc"

#include <iostream>
using namespace std;

static void button_callback(Fl_Widget *w, void *data) {
  cout << "Button clicked" << endl;
}

Widget::Widget(void* parentXwindow)
{
  frequency = 440;
  
  // In case FLTK hasn't set up yet
  fl_open_display();
  
  win = new Xembed((uintptr_t)parentXwindow, 400,200);
  
  win->begin();
  Fl_Button* button = new Fl_Button(50,50,80,25,"caption");
  button->callback( button_callback, 0 );
  win->end();
  
  // here the window recieves a X window is, before this call the xid() returns 0
  
  win->size(600,600);
  win->show();
  XMapRaised(fl_display, fl_xid( win ));
}

void Widget::idle()
{
  // takes care of handling events
  Fl::check();
  Fl::flush();
};
