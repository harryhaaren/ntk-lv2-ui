
// this file has the drawing code for our custom widget

#include "widget.h"

// 
#define FL_LIBRARY
#define FL_INTERNALS

#include <FL/x.H>

#include <iostream>
using namespace std;

static void button_callback(Fl_Widget *w, void *data) {
  cout << "Button clicked" << endl;
}

Widget::Widget(void* parentXwindow)
{
  frequency = 440;
  
  //Fl_Window * win = fl_find( parentXwindow );
  
  fl_open_display();
  
  Fl_Window * win = fl_find( (Window)parentXwindow );
  
  if ( win )
  {
    cout << "found win with Xid" << endl;
  }
  else
  {
    cout << "creating new window, didnt' find window with XID" << endl;
    win = new Fl_Window(400,200,"NTK LV2 GUI");
  }
  
  win->begin();
  Fl_Button* button = new Fl_Button(50,50,80,25,"caption");
  button->callback( button_callback, 0 );
  win->end();
  
  // this should be commented to stop UI showing up in its own window!
  win->show();
  
  // hack shown() to return true for embedding
  // this page  (http://www.fltk.org/doc-1.3/osissues.html)  says
  // If not shown() your implementation must call
  // either Fl_X::set_xid() or Fl_X::make_xid()
  
  //Fl_X * fl_xPtr = Fl_X::set_xid( win, (Window)parentXwindow);
  
  //Fl::lock();
  
}

void Widget::idle()
{
  // takes care of handling events
  Fl::check();
  Fl::flush();
};
