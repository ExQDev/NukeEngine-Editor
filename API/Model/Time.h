#pragma once
#ifndef NUKEE_TIME_H
#define NUKEE_TIME_H

class Time
{
private:
	Time() {}
	~Time() {}
public:
	static Time * getSingleton() 
	{
		static Time instance;
		return &instance;
	}
	
	//Game to real time attitude
	double gtr = 0.05;

	//Time of day
	double tod = 0;

	//Year
	int year = 2000;

	//Day of year
	int doy = 1;

	//Week of year
	int woy = 1;

	//Month of year
	int month = 1;

	//Day of month
	int day = 1;

	//Day of week
	int dow = 1;

	//Total game time
	long double totalgt = 0;
	
	//Total game days
	long long unsigned int totalgd = 0;

    int hour;
    int minute;
    int sec;

	void TickMonth() 
	{
		if (month == 12) 
		{
			year++;
			month = 1;
			woy = 1;
		}
	}

	void TickDay()
	{
		if ((doy == 366 && year % 4 == 0) || (doy == 365 && year % 4))
		{
			doy = 0;
		}
		if (dow == 7)
		{
			dow = 0;
			woy++;
		}
		if (
			(day == 31 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)) 
			||
			(day == 30 && (month == 4 || month == 6 || month == 9 || month == 11))
			||
			(day == 28 && month == 2 && year % 4)
			||
			(day == 29 && month == 2 && year % 4 == 0)) 
		{
			day = 0;
			TickMonth();
		}
		day++;
		dow++;
		doy++;
		totalgd++;
	}

	void TickHour() 
	{
		hour++;
		if (hour == 24) 
		{
			TickDay();
			hour = 0;
		}
	}

	void TickMinute() 
	{
		minute++;
		if (minute == 60) 
		{
			TickHour();
			minute = 0;
		}
	}

	void TickSecond()
	{
		sec++;
		if (sec == 60)
		{
			TickMinute();
			sec = 0;
		}
		tod = (sec + minute * 60 + hour * 3600) / 24 * 3600;
	}

	//Ticker
	void Tick() 
	{
        int toSleep = 1000 * gtr;
#ifdef WIN32
        Sleep(toSleep);
#else
        usleep(toSleep);
#endif
		TickSecond();
	}

	static int CalcDayOfYear(int day, int month, int year) 
	{
		int dayofy = 0;
		for (int i = 1; i < month; i++) 
		{
			switch (i)
			{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
				dayofy += 31;
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				dayofy += 30;
				break;
			case 2:
				if (year % 4 == 0)
					dayofy += 29;
				else 
					dayofy += 28;
				break;
			default:
				break;
			}
		}
		dayofy += day;
		return dayofy;
	}

	static int CalcWeekOfYear(int dayofyear) 
	{
		return (dayofyear / 7) + 1;
	}

	void Init() 
	{
		gtr = 0.05;
		day = 1;
		year = 2000;
		month = 1;
		woy = 1;
	}

	void Init(double gtr, int day, int month, int year) 
	{
		Time::gtr = gtr;
		Time::day = day;
		Time::year = year;
		Time::month = month;
		woy = 1;
	}
	
    void Init(double gtr, int day, int month, int year, int hour)
	{
		Time::gtr = gtr;
		Time::day = day;
		Time::year = year;
		Time::month = month;
		Time::hour = hour;
	}
	
    void Init(double gtr, int day, int month, int year, int hour, int minute)
	{
		Time::gtr = gtr;
		Time::day = day;
		Time::year = year;
		Time::month = month;
		Time::hour = hour;
		Time::minute = minute;
	}

    void Init(double gtr, int day, int month, int year, int hour, int minute, int sec)
	{
		Time::gtr = gtr;
		Time::day = day;
		Time::year = year;
		Time::month = month;
		Time::hour = hour;
		Time::minute = minute;
		Time::sec = sec;
	}

	void Run() 
	{
		Tick();
	}
};
//
//double Time::gtr = 0.05;
//double Time::tod = 0;
//int Time::year = 0;
//int Time::doy = 0;
//int Time::woy = 0;
//int Time::month = 0;
//int Time::day = 0;
//int Time::dow = 0;
//long double Time::totalgt = 0;
//long long unsigned int Time::totalgd = 0;
//int Time::hour = 0;
//int Time::minute = 0;
//int Time::sec = 0;
#endif // !NUKEE_TIME_H
