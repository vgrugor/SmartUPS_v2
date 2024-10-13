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
    Serial.println("Start get task name ");
    String name = task->getName();
    Serial.println("Name getted " + task->getName());

    Serial.print("Free heap: ");
    Serial.println(ESP.getFreeHeap());

    if (task->isUnique()) {
        auto it = this->tasks.find(name);

        if (it != this->tasks.end()) {
            delete it->second;
            this->tasks.erase(it);
        }
    }

    this->tasks[name] = task;

    Serial.println("Task added: " + task->getName());
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
