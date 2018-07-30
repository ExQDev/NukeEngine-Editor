#pragma once
#ifndef GDK_EDITOR_MENU_ITEM_H
#define GDK_EDITOR_MENU_ITEM_H
#include <vector>
#include <boost/container/list.hpp>
#include <boost/tokenizer.hpp>
#include <functional>

struct MenuItem
{
	std::string name;
	//boost::function<void> b_callback;
	typedef void (*mi_callback)();
	std::function<void()> callback;
	//mi_callback callback;
	boost::container::list<MenuItem*> subitems;

	MenuItem* GetTopWithName(std::string name) 
	{
		for (auto itm : subitems) 
		{
			if (itm->name == name)
				return itm;
		}
		return 0;
	}

	MenuItem* Get(std::string path) 
	{
		if (Check(path))
		{
			boost::char_separator<char> sep("/");
			boost::tokenizer<boost::char_separator<char>> cnames(path, sep);
			std::string retPath = "";
			boost::container::list<std::string> tokens;
			for (auto tkn : cnames)
				tokens.push_back(tkn);
			if (tokens.front() == this->name)
			{
				tokens.remove(tokens.front());
				if (tokens.size() == 0)
					return this;

				std::string npath = "";
				for (auto t : tokens)
					if (t != tokens.back())
						npath += t + "/";
					else
						npath += t;
				return Get(npath);
			}
			else
			{
				std::vector<MenuItem*> mis;
				for (auto mi : subitems)
					mis.push_back(mi);

				if (MenuItem* mi = GetTopWithName(tokens.front()))
					return mi->Get(path);
				else
					return 0;
			}
		}
		return 0;
	}

	bool Check(std::string path) 
	{
		boost::char_separator<char> sep("/");
		boost::tokenizer<boost::char_separator<char>> cnames(path, sep);
		std::string retPath = "";
		boost::container::list<std::string> tokens;
		for (auto tkn : cnames)
			tokens.push_back(tkn);
		if (tokens.front() == this->name)
		{
			tokens.remove(tokens.front());
			if (tokens.size() == 0)
				return true;

			std::string npath = "";
			for (auto t : tokens)
				if (t != tokens.back())
					npath += t + "/";
				else
					npath += t;
			return Check(npath);
		}
		else 
		{
			std::vector<MenuItem*> mis;
			for (auto mi : subitems)
				mis.push_back(mi);
			
			if (MenuItem* mi = GetTopWithName(tokens.front()))
				return mi->Check(path);
			else
				return false;
		}
	}

	MenuItem(std::string name, std::function<void()> callback) 
	{
		//this->path = path;
		this->callback = callback;
		boost::char_separator<char> sep("/");
		boost::tokenizer<boost::char_separator<char>> cnames(name, sep);
		std::string retPath = "";
		for (auto tkn : cnames) 
		{
			if (this->name.empty())
				this->name = tkn;
			else
				if (tkn != *cnames.end())
					retPath += tkn + "/";
				else
					retPath += tkn;
		}
		
	}


};
#endif // !GDK_EDITOR_MENU_ITEM_H
