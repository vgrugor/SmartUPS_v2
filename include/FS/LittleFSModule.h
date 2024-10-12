#ifndef LITTLEFSMODULE_H
    #define LITTLEFSMODULE_H

    #include <FS.h>
    #include <LittleFS.h>

    class LittleFSModule {
        public:
            LittleFSModule();
            void begin();
            bool exists(const String& path);
            File open(const String& path, const char* mode);
    };

#endif
