#pragma once
#ifndef NUKEE_EDITOR_INSTANCE_H
#define NUKEE_EDITOR_INSTANCE_H
#include <API/Model/Include.h>
#include "EditorMenu/MenuStrip.h"

class EditorInstance : public AppInstance
{
protected:
	EditorInstance() {}
	~EditorInstance() {}
public:
//	struct nkc* nkc_handle;

	MenuStrip* menuStrip;
	GameObject* selectedInHieararchy;
	
	static EditorInstance* GetSingleton() 
	{
		static EditorInstance instance;
		return &instance;
	}
};

#endif // !NUKEE_EDITOR_INSTANCE_H
