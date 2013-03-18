
// this file has the drawing code for our custom widget

#include "widget.h"

#include <iostream>
using namespace std;

void* Widget::callback(void*)
{
  //Widget* self = (Widget*)s;
  
  Fl::lock();
  
  while (Fl::wait() > 0) {
    if (Fl::thread_message()) {
      /* process your data */
    }
  }
  
  cout << "Error, FL thread running out of loop" << endl;
  
}

Widget::Widget()
{
  frequency = 440;
  
  win = new Fl_Window(400,200,"NTK LV2 GUI");
  
  win->begin();
  
  Fl_Button* button = new Fl_Button(50,50,80,25,"caption");
  
  win->end();
  win->show();
  
  win->damage( FL_DAMAGE_ALL );
  
  //Fl::run();
  
  pthread_create((pthread_t*)&fl_thread, 0, &Widget::callback, 0);
  
  //std::thread draw( &Widget::callback );
  
  //Fl::repeat_timeout( 1 / 30.f, &callback, this);
}



Window Widget::getXID()
{
  return xWindowID = fl_xid( win );
}





/*
bool Widget::on_expose_event(GdkEventExpose* event)
{
  // This is where we draw on the window
  Glib::RefPtr<Gdk::Window> window = get_window();
  if(window)
  {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    // coordinates for the center of the window
    int xc, yc;
    xc = width / 2;
    yc = height / 2;

    Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
    cr->set_line_width(10.0);

    // clip to the area indicated by the expose event so that we only redraw
    // the portion of the window that needs to be redrawn
    cr->rectangle(event->area.x, event->area.y,
            event->area.width, event->area.height);
    cr->clip();
    
    // make background black
    cr->rectangle(event->area.x, event->area.y,
            event->area.width, event->area.height);
    cr->set_source_rgb(0.1, 0.1, 0.1);
    cr->fill();
    
    // draw vertical grey line down the middle
    cr->set_source_rgb(0.3, 0.3, 0.3);
    cr->move_to(xc, 0);
    cr->line_to(xc, height);
    cr->stroke();
    
    // draw horizontal blue at frequency height
    float freqPix = height - (height*(frequency-40)/840.f); // convert to pix
    std::cout << "FreqPix " << freqPix << std::endl;
    cr->set_source_rgba(0.1, 0.1, 0.8,0.6);
    cr->move_to(20      , freqPix);
    cr->line_to(width-20, freqPix);
    cr->stroke();
  }

  return true;
}
*/

