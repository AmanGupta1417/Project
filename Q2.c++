#include <event2/event.h>

void timeout_cb(evutil_socket_t fd, short event, void *arg)
{
	std::cout << "Timeout occurred!" << std::endl;
}

int main(int argc, char **argv)
{
	// Create an event base
	std::unique_ptr<event_base, decltype(&event_base_free)> base(event_base_new(), event_base_free);
	if (!base)
	{
		std::cerr << "Failed to create event base" << std::endl;
		return 1;
	}

	// Create a timer event with a 5-second timeout
	std::unique_ptr<event, decltype(&event_free)> timer_event(evtimer_new(base.get(), timeout_cb, NULL), event_free);
	if (!timer_event)
	{
		std::cerr << "Failed to create timer event" << std::endl;
		return 1;
	}

	// Add the timer event to the event base
	struct timeval five_seconds = {5, 0};
	event_add(timer_event.get(), &five_seconds);

	// Start the event loop
	event_base_dispatch(base.get());

	    return 0;
}