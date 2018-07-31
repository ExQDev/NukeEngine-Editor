#pragma once
#ifndef NUKEE_APPINSTANCE_H
#define NUKEE_APPINSTANCE_H
#include <boost/thread.hpp>
#include "../API/Model/Camera.h"
#include "../API/Model/Scene.h"

class AppInstance
{
protected:
	AppInstance() 
	{
		currentScene = new Scene();
	}
	~AppInstance() {}
public:
	
	Scene* currentScene;
    virtual bool isEditor(){ return false ;}
	static AppInstance* GetSingleton() 
	{
		static AppInstance instance;
		return &instance;
	}
	
	void UpdateThread()
	{
		while (true)
		{
			try
			{
				currentScene->Update();
				boost::this_thread::sleep(boost::posix_time::milliseconds(40));
			}
			catch (const std::exception&)
			{

			}
		}
		
	}

	void StartUpdateThread() 
	{
		boost::thread updt(boost::bind(&AppInstance::UpdateThread, this));
	}
};

#endif // !NUKEE_APPINSTANCE_H
