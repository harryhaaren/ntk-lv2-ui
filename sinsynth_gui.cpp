

// please see this link for details about the GUI aspect of LV2 programming
// http://harryhaaren.blogspot.ie/2012/07/writing-lv2-guis-making-it-look-snazzy.html

#include <string>
#include <iostream>

// X window ID
#include <FL/x.H>

// include the URI and global data of this plugin
#include "sinsynth.h"

// this is our custom widget include
#include "widget.h"

// core spec include
#include "lv2/lv2plug.in/ns/lv2core/lv2.h"

// GUI
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

using namespace std;

typedef struct {
    Widget* widget;
} SinSynthGUI;


static LV2UI_Handle instantiate(const struct _LV2UI_Descriptor * descriptor,
                const char * plugin_uri,
                const char * bundle_path,
                LV2UI_Write_Function write_function,
                LV2UI_Controller controller,
                LV2UI_Widget * widget,
                const LV2_Feature * const * features) {

    if (strcmp(plugin_uri, SINSYNTH_URI) != 0) {
        fprintf(stderr, "SORCER_URI error: this GUI does not support plugin with URI %s\n", plugin_uri);
        return NULL;
    }
    
    SinSynthGUI* self = (SinSynthGUI*)malloc(sizeof(SinSynthGUI));
    
    cout << "Allocated SourceGUI!" << endl;
    
    if (self == NULL) return NULL;
    
    cout << "Creating UI!" << endl;
    self->widget = new Widget();
    
    
    cout << "Writing controller f(x)!" << endl;
    
    self->widget->controller = controller;
    self->widget->write_function = write_function;
    
    cout << "returning..." << int(self->widget->getXID()) << endl;
    
    return (LV2UI_Handle)self->widget->getXID();
}

static void cleanup(LV2UI_Handle ui) {
    printf("cleanup()\n");
    SinSynthGUI *pluginGui = (SinSynthGUI *) ui;
    delete pluginGui->widget;
    free( pluginGui);
}

static void port_event(LV2UI_Handle ui,
               uint32_t port_index,
               uint32_t buffer_size,
               uint32_t format,
               const void * buffer)
{
    SinSynthGUI *self = (SinSynthGUI *) ui;
    
    cout << "Port event on index " << port_index << "  Format is " << format << endl;
    
      
    /*
    Fl::lock();
    ui->filterLowpass->value( argv[0]->f );
    Fl::unlock();
    Fl::awake();
    */
    
    /*
    if ( format == 0 )
    {
      float value =  *(float *)buffer;
      switch ( port_index )
      {
        case REFRACTOR_CONTROL_RETRIGGER:
            cout << "Refractor: Retrigger control event, value = " << value << endl;
            //self->guiState->retrigger = value;
            //self->widget->redraw();
            break;
        case REFRACTOR_MASTER_VOLUME:
            cout << "Refractor: Master volume event, value = " << value << endl;
            self->guiState->masterVol = value;
            self->widget->redraw();
      }
    }
    else
    {
      LV2_ATOM_SEQUENCE_FOREACH( (LV2_Atom_Sequence*)buffer, ev)
      {
        //self->frame_offset = ev->time.frames;
        
        if (ev->body.type == self->guiState->uris.midiEvent)
        {
          cout << "Refractor GUI got MIDI event!" << endl;
          //uint8_t* const data = (uint8_t* const)(ev + 1);
        }
      }
    }
    */
    
    return;
}

static LV2UI_Descriptor descriptors[] = {
    {SINSYNTH_UI_URI, instantiate, cleanup, port_event, NULL}
};

const LV2UI_Descriptor * lv2ui_descriptor(uint32_t index) {
    printf("lv2ui_descriptor(%u) called\n", (unsigned int)index); 
    if (index >= sizeof(descriptors) / sizeof(descriptors[0])) {
        return NULL;
    }
    return descriptors + index;
}
