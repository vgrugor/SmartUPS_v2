#ifndef TASK_H
    #define TASK_H

    #include <Arduino.h>

    class Task {
        public:
            Task(const char* taskName, unsigned long delay, bool unique = false);
            bool isReady();
            virtual void execute() = 0;
            const char* getName();
            bool isUnique();
            virtual ~Task() = default;
        protected:
            const char* name;
            unsigned long delayTime;
            unsigned long startTime;
            bool unique;
    };

#endif
