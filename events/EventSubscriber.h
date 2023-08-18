#pragma once
#include "Event.h"

#include <iostream>

class event_subscriber
{
public:
	virtual ~event_subscriber() = default;
	virtual void on_event(const event& e) = 0;
};

class test_system : public event_subscriber
{
public:
	virtual void on_event(const event& e) override
	{
		std::cout << e << std::endl;
	}
};