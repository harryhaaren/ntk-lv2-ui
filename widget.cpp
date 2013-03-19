
// this file has the drawing code for our custom widget

#include "widget.h"

#define FL_LIBRARY

#include <FL/x.H>

#include <iostream>
using namespace std;


Widget::Widget(void* parentXwindow)
{
  frequency = 440;
  
  //Fl_Window * win = fl_find( parentXwindow );
  
  fl_open_display();
  
  //Fl_Window * win = fl_find( (Window)parentXwindow );
  
  Fl_Window * win = new Fl_Window(400,200,"NTK LV2 GUI");
  win->begin();
  Fl_Button* button = new Fl_Button(50,50,80,25,"caption");
  win->end();
  win->show();
  
  
  // hack shown() to return true for embedding
  //Fl_X * fl_xPtr = Fl_X::set_xid( win, (Window)parentXwindow);
  
  Fl::lock();
  
}

void Widget::idle()
{
  cout << "idle" << endl;
  
  Fl::check();
  
  Fl::flush();
  
  /*
  while( Fl::wait() > 0 )
  {
    if (Fl::thread_message()) {
      
    }
  }
  */
};
