
// this file has the drawing code for our custom widget

#include "widget.h"

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>


#define FL_INTERNALS 1
#include <FL/x.H>
//#include "xembed.cc"

#include <iostream>
using namespace std;

static void button_callback(Fl_Widget *w, void *data) {
  cout << "Button clicked" << endl;
}

Widget::Widget(void* parentXwindow)
{
  // In case FLTK hasn't set up yet
  fl_open_display();
  
  win = new Fl_Double_Window(300, 300);
  
  win->begin();
  Fl_Button* button = new Fl_Button(0,0,80,25,"caption");
  button->callback( button_callback, 0 );
  win->end();
  
  //win->show();
  
  fl_embed( win, (Window)parentXwindow );
}

void Widget::idle()
{
  // takes care of handling events
  Fl::check();
  Fl::flush();
};
