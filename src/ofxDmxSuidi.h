#include "ofMain.h"

#include "Windows.h"
#include "_DasHard.h"

#define DMX_MAXCHANNEL		512					// dmx standard
#define DMX_MAXVALUE		255					// dmx standard
#define NB_PORT				8					// number of ports on Ref. SIUDI

class ofxDmxSuidi{
    public:
        ofxDmxSuidi();

        HINSTANCE g_dasusbdll;
        //int DasUsbCommand( int command, int param, unsigned char *bloc );
        typedef int (*DASHARDCOMMAND)(int, int, unsigned char*);
        DASHARDCOMMAND  DasUsbCommand;

        unsigned char dmxBlock[DMX_MAXCHANNEL];
        bool port_out[NB_PORT];
        bool out_mode[NB_PORT];

        bool loadRuntimeLibrary();
        bool openInterface();
        void closeInterface();
        bool dmxPortConfig();
        void updateDmxChannel(int channel, int value);
        bool sendDmxBlockOut();

    protected:
};
