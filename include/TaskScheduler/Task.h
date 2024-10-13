#ifndef TASK_H
    #define TASK_H

    #include <WString.h>
    #include <Arduino.h>
    #include <climits>

    class Task {
        public:
            Task(const String& name, unsigned long delayMs, bool isUnique = false);
            virtual ~Task();
            String getName() const;
            bool isUnique() const;
            unsigned long getExecuteTime() const; // Время, когда задача должна быть выполнена
            virtual void execute() = 0; // Чисто виртуальная функция для выполнения задачи

        protected:
            String name;
            bool unique;
            unsigned long executeAtMs; // Время выполнения задачи
    };

#endif // TASK_H
