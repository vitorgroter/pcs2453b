#include "time_slice_event.h"
#include "../process_manager.h"

TimeSliceEvent::TimeSliceEvent(ProcessManager * processManager) :
							   processManager(processManager) {

}

TimeSliceEvent::~TimeSliceEvent() {

}

void TimeSliceEvent::execute() {
	processManager->timeSlice();
}

