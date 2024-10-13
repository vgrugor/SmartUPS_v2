#include "TaskScheduler/Scheduler.h"

Scheduler::Scheduler() {}

Scheduler::~Scheduler() {
    for (auto it = this->tasks.begin(); it != this->tasks.end(); ++it) {
        delete it->second;
    }

    this->tasks.clear();
}

Scheduler& Scheduler::getInstance() {
    static Scheduler instance;
    return instance;
}

void Scheduler::addTask(Task* task) {
    String name = task->getName();

    Serial.println(task->getName());
/*
    if (task->isUnique()) {
        auto it = this->tasks.find(name);

        if (it != this->tasks.end()) {
            delete it->second;
            this->tasks.erase(it);
        }
    }
*/
    this->tasks[name] = task;
}

void Scheduler::removeTask(const String& taskName) {
    auto it = this->tasks.find(taskName);

    if (it != this->tasks.end()) {
        delete it->second;
        this->tasks.erase(it);
    }
}

void Scheduler::executeTasks() {
    unsigned long currentMillis = millis();

    for (auto it = this->tasks.begin(); it != this->tasks.end(); ) {
        Task* task = it->second;
        unsigned long executeTime = task->getExecuteTime();

        // Проверяем, пришло ли время выполнить задачу, учитывая переполнение millis()
        if ((long)(currentMillis - executeTime) >= 0) {
            task->execute();
            delete task;
            it = this->tasks.erase(it); // Удаляем задачу из списка
        } else {
            ++it;
        }
    }
}
