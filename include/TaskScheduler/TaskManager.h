#pragma once

#include "Task.h"
#include <Arduino.h>

class TaskManager {
    private:
        static const int TASK_COUNT = 10;
        Task* tasks[TASK_COUNT];
        int taskCount;
        
        // Запрещаем копирование
        TaskManager(const TaskManager&) = delete;
        TaskManager& operator=(const TaskManager&) = delete;

    protected:
        TaskManager();  // Конструктор protected для паттерна Singleton

    public:
        static TaskManager& getInstance();
        
        // Основные методы управления задачами
        int findTaskByName(const char* name);
        bool addTask(Task* task);
        bool removeTask(int index);
        void update();

        // Вспомогательные методы
        void printTaskList();
        int getTaskCount() const;
};