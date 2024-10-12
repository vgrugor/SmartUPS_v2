#include "TaskScheduler/TaskManager.h"

TaskManager::TaskManager() : taskCount(0) {
    for(int i = 0; i < TASK_COUNT; i++) {
        tasks[i] = nullptr;
    }
}

TaskManager& TaskManager::getInstance() {
    static TaskManager instance;
    return instance;
}

int TaskManager::findTaskByName(const char* name) {
    if (!name) {
        Serial.println(F("findTaskByName: получен nullptr"));
        return -1;
    }

    for (int i = 0; i < taskCount; i++) {
        if (!tasks[i]) continue;
        
        const char* taskName = tasks[i]->getName();
        if (taskName && strcmp(taskName, name) == 0) {
            return i;
        }
    }
    return -1;
}

bool TaskManager::addTask(Task* task) {
    if (!task) {
        Serial.println(F("addTask: попытка добавить nullptr задачу"));
        return false;
    }

    // Проверяем уникальность
    if (task->isUnique()) {
        const char* name = task->getName();
        if (name) {
            int index = findTaskByName(name);
            if (index != -1) {
                if (!removeTask(index)) {
                    Serial.println(F("addTask: ошибка при удалении существующей задачи"));
                    return false;
                }
            }
        }
    }

    if (taskCount >= TASK_COUNT) {
        Serial.println(F("addTask: список задач переполнен"));
        return false;
    }

    tasks[taskCount] = task;
    taskCount++;
    
    const char* taskName = task->getName();
    if (taskName) {
        Serial.print(F("Задача добавлена: "));
        Serial.println(taskName);
    }

    return true;
}

bool TaskManager::removeTask(int index) {
    if (index < 0 || index >= taskCount) {
        Serial.println(F("removeTask: неверный индекс задачи"));
        return false;
    }

    if (!tasks[index]) {
        Serial.println(F("removeTask: попытка удалить nullptr задачу"));
        return false;
    }

    // Сохраняем имя до удаления
    const char* taskName = tasks[index]->getName();
    String nameBuffer;
    if (taskName) {
        nameBuffer = String(taskName);
    }

    // Удаляем задачу
    delete tasks[index];
    tasks[index] = nullptr;

    // Сдвигаем оставшиеся задачи
    for (int i = index; i < taskCount - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    tasks[taskCount - 1] = nullptr;
    taskCount--;

    if (nameBuffer.length() > 0) {
        Serial.print(F("Задача удалена: "));
        Serial.println(nameBuffer);
    }

    return true;
}

void TaskManager::update() {
    for (int i = 0; i < taskCount; i++) {
        if (!tasks[i]) {
            Serial.println(F("update: обнаружен nullptr в списке задач"));
            removeTask(i);
            i--;
            continue;
        }

        //try {
            if (tasks[i]->isReady()) {
                tasks[i]->execute();
                if (!removeTask(i)) {
                    Serial.println(F("update: ошибка при удалении выполненной задачи"));
                }
                i--;
            }
        //} catch (...) {
            //Serial.println(F("update: исключение при выполнении задачи"));
            //removeTask(i);
            //i--;
        //}
    }
}

void TaskManager::printTaskList() {
    Serial.println(F("Список задач:"));
    Serial.printf("Всего задач: %d\n", taskCount);
    
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i]) {
            const char* name = tasks[i]->getName();
            Serial.printf("%d: %s\n", i, name ? name : "Без имени");
        } else {
            Serial.printf("%d: nullptr!\n", i);
        }
    }
}

int TaskManager::getTaskCount() const {
    return taskCount;
}
