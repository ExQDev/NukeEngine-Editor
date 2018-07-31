#pragma once
#ifndef NUKEE_EDITOR_MENU_STRIP_H
#define NUKEE_EDITOR_MENU_STRIP_H
#include "MenuItem.h"

struct MenuStrip
{
	boost::container::list<MenuItem*> strip;

	bool CheckItem(std::string path) 
	{
		for (auto x : strip) 
		{
			if (x->Check(path))
				return true;
		}
		return false;
	}

	void AddItem(std::string path, std::string name, std::function<void()> callback)
	{
		if (!path.empty()) {
			if (CheckItem(path))
				GetItem(path)->subitems.push_back(new MenuItem(name, callback));
			else 
			{
				boost::char_separator<char> sep("/");
				boost::tokenizer<boost::char_separator<char>> cnames(path, sep);
				std::string retPath = "";
				boost::container::list<std::string> tokens;
				for (auto tkn : cnames)
					tokens.push_back(tkn);
				if (auto itm = GetItem(tokens.front()))
				{
					tokens.remove(tokens.front());
					MenuItem* current = itm;
					
					for (auto pn : tokens)
					{
						if (auto item = current->Get(pn))
							current = item;
						else
						{
							MenuItem* x;
                            if (pn == tokens.back())
								x = new MenuItem(pn, 0);
							current->subitems.push_back(x);
							current = x;
                            AddItem(path, name, callback);
                            break;
						}
					}
				}
				else 
				{
					AddItem("", tokens.front(), 0);
					AddItem(path, name, callback);
				}
				
			}
		}
		else 
		{
			strip.push_back(new MenuItem(name, callback));
		}
	}
	
	MenuItem* GetItem(std::string path)
	{
		if(CheckItem(path))
			for (auto item : strip) 
			{
				if (item->Check(path))
					return item->Get(path);
			}
		return NULL;
	}
	
	void RemoveItem(std::string path)
	{
		if(CheckItem(path))
			for (auto item : strip)
				if (item->Check(path))
				{
					strip.remove(item);
					break;
				}
	}
};
#endif // !NUKEE_EDITOR_MENU_STRIP_H
