#pragma once
#ifndef NUKE_MODULAR_H
#define NUKE_MODULAR_H
#include <interface/NUKEEInteface.h>

#include <interface/EditorInstance.h>

#define BOOST_FILESYSTEM_VERSION 3
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

#include <boost/container/vector.hpp>
namespace bc = boost::container;


#include <boost/dll.hpp>
#include <boost/thread.hpp>

#ifdef USE_WINAPI
#include <Windows.h>
#endif // USE_WINAPI

bc::vector<boost::shared_ptr<NUKEModule>> modules;


void InitModules(EditorInstance* instance) 
{
	if (!bfs::exists(bfs::path(bfs::current_path().concat("/modules"))))
	{
		bfs::create_directory(bfs::current_path().concat("/modules"));
        cout << "directory created!" << endl;
	}

	for (auto & p : boost::filesystem::directory_iterator(bfs::current_path().concat("/modules")))
	{
		if (!bfs::is_directory(p.path()))
		{
            //cout << p.path().extension().concat("\n").generic_string().c_str() << endl;
            if (p.path().extension() == ".so")
			{
                cout << p.path().filename().concat("\n").generic_string().c_str() << endl;
                boost::shared_ptr<NUKEModule> plugin;
                std::string s = "";
                plugin = dll::import<NUKEModule>("modules/" + p.path().filename().generic_string(), "plugin");
                cout << plugin << endl;
				plugin.get()->modulePath = p.path().generic_string();
				modules.push_back(plugin);
                boost::thread(boost::bind(&NUKEModule::Run, plugin.get(), instance));
			}
		}
	}
}
void UnloadModules() 
{
	for (auto i : modules)
	{
		if (i) {
			i.get()->Shutdown();
		}
	}
	modules.clear();
}
#endif // !NUKE_MODULAR_H

