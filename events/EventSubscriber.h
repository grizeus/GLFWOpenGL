#pragma once
#include "Event.h"

#include <iostream>

class event_subscriber
{
public:
	virtual ~event_subscriber() = default;
	virtual void on_event(const event& e) = 0;
};

// TODO inherit old camera
class camera_sub : public event_subscriber
{
public:
	virtual void on_event(const event& e) override
	{
		// TODO logic here
	}
};