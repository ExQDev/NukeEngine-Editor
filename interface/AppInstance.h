#pragma once
#ifndef NUKEE_APPINSTANCE_H
#define NUKEE_APPINSTANCE_H
#include <boost/thread.hpp>
#include "../API/Model/Camera.h"
#include "../API/Model/Scene.h"
#include "../input/keyboard.h"
#include "../input/mouse.h"
#include "../render/irender.h"
#include "../render/opengl/nukeogl.h"

class AppInstance
{
protected:
	AppInstance() 
	{
		currentScene = new Scene();
        keyboard = KeyBoard::getSingleton();
        mouse = Mouse::getSingleton();
        render = iRender::getSingleton();
	}
	~AppInstance() {}
public:
	
	Scene* currentScene;
    KeyBoard* keyboard;
    Mouse* mouse;
    iRender* render;

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
