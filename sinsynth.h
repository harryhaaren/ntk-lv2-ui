
// its good practice to put the "global" things like this plugins URI in
// a header file. That way the GUI and DSP file can include it, and you
// know they'll always be up to date with eachother.

#ifndef SIN_SYNTH
#define SIN_SYNTH

#include "lv2/lv2plug.in/ns/lv2core/lv2.h"

#define SINSYNTH_URI "http://lv2plug.in/plugins/eg-fltksynth"
#define SINSYNTH_UI_URI "http://lv2plug.in/plugins/eg-fltksynth/fltkgui"


#endif
