#include "ofxDmxSuidi.h"

ofxDmxSuidi::ofxDmxSuidi(){
    // initialize dmx block
    for(int i=0; i<DMX_MAXCHANNEL; i++){
        dmxBlock[i] = 0;
    }
}

bool ofxDmxSuidi::loadRuntimeLibrary(){
    g_dasusbdll = LoadLibraryA("DasHard2006.dll");
	if (g_dasusbdll){
        ofLogNotice("DasHard2006.dll loaded OK");
	}
	else{
        ofLogError("DasHard2006.dll load ERROR");
        return false;
	}

	DasUsbCommand  = (DASHARDCOMMAND)::GetProcAddress((HMODULE)g_dasusbdll, "DasUsbCommand");
	if (DasUsbCommand){
	    ofLogNotice("GetProcAddress obtained DasUsbCommand OK");
	}
	else{
        ofLogError("GetProcAddress didn't obtained DasUsbCommand ERROR");
        return false;
	}

    int dll_version = DasUsbCommand(DHC_INIT,0, NULL);
    if (dll_version > 0){
	    ofLogNotice("DHC_INIT OK dll version " + ofToString(dll_version) );
	}
	else{
        ofLogError("DHC_INIT ERROR");
        return false;
	}

	return true;
}

bool ofxDmxSuidi::openInterface(){
    int res_interface_open = DasUsbCommand(DHC_OPEN,0,0);
    if (res_interface_open == DHE_OK){
        ofLogNotice("DHC_OPEN OK and dmxBlock initialized");
        return true;
    }
    else{
        ofLogError("DHC_OPEN ERROR");
        return false;
    }
}

void ofxDmxSuidi::closeInterface(){
    DasUsbCommand(DHC_CLOSE, 0, 0);
    DasUsbCommand(DHC_EXIT, 0, NULL);
}

bool ofxDmxSuidi::dmxPortConfig(){
    unsigned short config = 0;
	for(int i=0 ; i<NB_PORT ; i++){
		if(port_out[i])
			config += (int)pow((double)2, (i+8));
		if(out_mode[i])
			config += (int)pow((double)2, i);
	}
	int res_port_config = DasUsbCommand(DHC_PORTCONFIG, config, 0);
	if(res_port_config){
	    return true;
	}
	else{
        return false;
	}
}

void ofxDmxSuidi::updateDmxChannel(int channel, int value){
    dmxBlock[channel] = value;
}

bool ofxDmxSuidi::sendDmxBlockOut(){
    int res_dmx_out = DasUsbCommand(DHC_DMXOUT, DMX_MAXCHANNEL, dmxBlock);
    if(res_dmx_out == DHE_OK){
       ofLogNotice("DHC_DMXOUT dmxBlock OK at frame " + ofToString(ofGetFrameNum()) );
       return true;
    }
    else if(res_dmx_out == DHE_ERROR_NOTOPEN){
        ofLogError("DHC_DMXOUT dmxBlock DHE_ERROR_NOTOPEN at frame " + ofToString(ofGetFrameNum()) );
        return false;
    }
    else if(res_dmx_out == DHE_ERROR_COMMAND){
        ofLogError("DHC_DMXOUT dmxBlock DHE_ERROR_COMMAND at frame " + ofToString(ofGetFrameNum()) );
        return false;
    }
    else{
        ofLogError("DHC_DMXOUT dmxBlock UNKNOWN ERROR at frame " + ofToString(ofGetFrameNum()) );
        return false;
    }
}

