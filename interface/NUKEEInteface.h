#pragma once
#ifndef NUKEE_INTERFACE_H
#define NUKEE_INTERFACE_H
#include <boost/dll.hpp>
using namespace boost;

#include "AppInstance.h"
#include "EditorInstance.h"

#define API extern "C" BOOST_SYMBOL_EXPORT

class NUKEModule {
public:
	//Title of the plugin
	char title[256];
	
	//Description of the plugin
	char description[4096];
	
	//Author name
	char author[256];

	//Author or plugin site
	char site[1024];

	//Plugin version
	char version[30];

	//Path to the plugin, filled by runtime
	std::string modulePath;

	//Main process instance. Used by plugin from code.
	AppInstance* instance;

	//When Shutdown() called turn this to true, please. Otherwise plugin will work incorrectly.
	bool stopped;

	//Function for run plugin. Runs in the background thread.
	virtual void Run(AppInstance* instance) = 0;

	//Returns true if mod has settings
	virtual bool HasSettings() = 0;

	//Opens menu if plugin has settings
	virtual void Settings() = 0;

	//Function that calls before plugin unloading. E.g. when app closes.
	virtual void Shutdown() = 0;
};

#endif
