#pragma once
#ifndef NUKEE_ID_H
#define NUKEE_ID_H

class ID {
public:
    long id;

	ID()
	{
		generate();
	}

    ID(long id)
	{
		this->id = id;
	}

	void generate() 
	{
        id = reinterpret_cast<long>(this);
	}
};
#endif // !NUKEE_ID_H
