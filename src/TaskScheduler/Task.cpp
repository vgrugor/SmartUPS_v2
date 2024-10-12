#include "TaskScheduler/Task.h"

Task::Task(
    const char* taskName, 
    unsigned long delay, 
    bool unique
) : name(taskName), 
    delayTime(delay), 
    startTime(millis()), 
    unique(unique)
{}

bool Task::isReady() {
    return millis() - this->startTime >= this->delayTime;
}

const char* Task::getName() {
    return this->name;
}

bool Task::isUnique() {
    return this->unique;
}
