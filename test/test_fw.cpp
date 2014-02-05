#include "test_fw.h"
#include <chrono>

TestFW::TestFW(const std::string& label, logxx::LogLevel l) : label(label), desiredLevel(l) {

}

TestFW::~TestFW() {
}

bool TestFW::RunTests() {
        logxx::Log log("TestFw::RunTests");
        log(logxx::info, label) << "Starting test" << logxx::endl;
        auto startPoint = std::chrono::steady_clock::now();
        
        auto storedLevel = logxx::GlobalLogLevel();
        if (storedLevel != desiredLevel)
                logxx::GlobalLogLevel(desiredLevel);
        bool res = Tests();
        logxx::GlobalLogLevel(storedLevel);
        
        std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - startPoint;
        auto &s = log(logxx::info, label) << "Test ";
        if (res)
                s << "PASSED";
        else
                s << "FAILED";
        s << " in " << elapsed.count() << "s" << logxx::endl;
        return res;
}

std::string TestFW::GetLabel() const {
        return label;
}


