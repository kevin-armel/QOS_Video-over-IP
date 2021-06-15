/* ***** BEGIN LICENSE BLOCK *****
 *
 * THIS FILE IS PART OF THE MOZILLA NPAPI SDK BASIC PLUGIN SAMPLE
 * SOURCE CODE. USE, DISTRIBUTION AND REPRODUCTION OF THIS SOURCE
 * IS GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS 
 * SOURCE IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.
 *
 * THE MOZILLA NPAPI SDK BASIC PLUGIN SAMPLE SOURCE CODE IS
 * (C) COPYRIGHT 2008 by the Mozilla Corporation
 * http://www.mozilla.com/
 *
 * Contributors:
 *  Josh Aas <josh@mozilla.com>
 *
 * ***** END LICENSE BLOCK ***** */

// This just needs to include NPAPI headers, change the path to whatever works
// for you. Note that "XP_MACOSX=1" is defined in the project so that the NPAPI
// headers know we're compiling for Mac OS X.

#include "ScriptableObject.h"

#define NPP_API_VERSION 11

#define NPP_API_PLUGIN_NAME "LiveVideoPlugin"

#define NPP_API_PLUGIN_DESC "LiveVideoPlugin (c) IVèS 2006-2020"

class DoubPluginView;
class LVPluginEventPump;

class NPPlugin
{
public:
	static NPError GetEntryPoints(NPPluginFuncs* p_pluginFuncs);
	
	NPPlugin(NPP p_instance);	
	virtual ~NPPlugin();
	
	/* surcharge des operateur new et delete pour utiliser la NPN API */
	void* operator new(size_t size) throw();
	void operator delete(void*);
	NPRect * GetPluginRect() { return &m_rect; };
	LVPluginEventPump * GetPump() { return m_pump; }
	
protected:
	static NPError New(NPMIMEType pluginType, NPP instance, uint16_t mode, int16_t argc, char* argn[], char* argv[], NPSavedData* saved);
	static NPError Destroy(NPP instance, NPSavedData** save);
	static NPError SetWindow(NPP instance, NPWindow* window);
	static NPError NewStream(NPP instance, NPMIMEType type, NPStream* stream, NPBool seekable, uint16_t* stype);
	static NPError DestroyStream(NPP instance, NPStream* stream, NPReason reason);
	static int32_t WriteReady(NPP instance, NPStream* stream);
	static int32_t Write(NPP instance, NPStream* stream, int32_t offset, int32_t len, void* buffer);
	static void    StreamAsFile(NPP instance, NPStream* stream, const char* fname);
	static void    Print(NPP instance, NPPrint* platformPrint);
	static int16_t HandleEvent(NPP instance, void* event);
	static void    URLNotify(NPP instance, const char* URL, NPReason reason, void* notifyData);
	static NPError GetValue(NPP instance, NPPVariable variable, void *value);
	static NPError SetValue(NPP instance, NPNVariable variable, void *value);

#ifdef XP_MACOSX	
	// Specific for Mac for InvalidatingCoreAnimation
	// Called by NPLayer when calling setNeedDisplay
	static void	InvalidateDisplay(void * p_data);
#endif
	
private:
	//Reference sur la NPN API
	static NPNetscapeFuncs* npnapi;
	friend NPNetscapeFuncs* GetNpnApi();
	friend void SetNpnApi(NPNetscapeFuncs* p_npnapi);

	NPP npp;
	NPScriptableObject * sobj;
	NPRect m_rect;
	
	LVPluginEventPump * m_pump;

public:
	DoubPluginView * m_view;
};

