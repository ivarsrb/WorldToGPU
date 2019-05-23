#include <exception>
#include <base/log.h>
#include "application/app.h"

int main(int argc, char* argv[]) {
    try {
        application::App app;
        app.Run();
    }
    catch (const std::exception &e) {
        base::Log::Error("Exception: ", e.what());
        return 1;
    }
    catch (...) {
        base::Log::Error("Unknown error");
        return 1;
    }

    return 0;
}