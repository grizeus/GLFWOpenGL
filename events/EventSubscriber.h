#pragma once
#include "Event.h"

#include <iostream>

class event_subscriber
{
public:
	virtual ~event_subscriber() = default;
	virtual void on_event(const event& e) = 0;
};
