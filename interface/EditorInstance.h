#pragma once
#ifndef NUKEE_EDITOR_INSTANCE_H
#define NUKEE_EDITOR_INSTANCE_H
#include "AppInstance.h"
#include "EditorMenu/MenuStrip.h"

class EditorInstance : public AppInstance
{
protected:
    EditorInstance() {
        if(!menuStrip)
            menuStrip = new MenuStrip();
    }
	~EditorInstance() {}
public:
    bool isEditor(){ return true; }
	MenuStrip* menuStrip;
	GameObject* selectedInHieararchy;
	
	static EditorInstance* GetSingleton() 
	{
		static EditorInstance instance;
		return &instance;
	}
};

#endif // !NUKEE_EDITOR_INSTANCE_H
