#include "TaskScheduler/Task.h"

Task::Task(const String& name, unsigned long delayMs, bool isUnique)
    : name(name), unique(isUnique) 
{
    unsigned long currentTimeMillis = millis();

    if ((ULONG_MAX - currentTimeMillis) < delayMs) {    
        this->executeAtMs =  delayMs - (ULONG_MAX - currentTimeMillis);
    } else {
        this->executeAtMs =  currentTimeMillis + delayMs;
    }
}

Task::~Task() {}

String Task::getName() const {
    return this->name;
}

bool Task::isUnique() const {
    return this->unique;
}

unsigned long Task::getExecuteTime() const {
    return this->executeAtMs;
}
