#ifndef SCHEDULER_H
    #define SCHEDULER_H

    #include <map>
    #include <WString.h>
    #include "Task.h"

    class Scheduler {
        public:
            //Scheduler();
            ~Scheduler();
            void addTask(Task* task);
            void removeTask(const String& taskName);
            void executeTasks();
            Scheduler(const Scheduler&) = delete;
            Scheduler& operator=(const Scheduler&) = delete;
            static Scheduler& getInstance();

        protected:
            Scheduler();  // Конструктор protected для паттерна Singleton

        private:
            std::map<String, Task*> tasks;
    };
#endif // SCHEDULER_H
