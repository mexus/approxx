#ifndef TEST_FW_H
#define	TEST_FW_H

#include "../source/logxx/logxx.h"

class TestFW {
public:
        TestFW(const std::string& label, logxx::LogLevel = logxx::warning);
        TestFW(const TestFW& ) = delete;
        virtual ~TestFW();
        
        bool RunTests();
        std::string GetLabel() const;
protected:
        virtual bool Tests() = 0;
private:
        const std::string label;
        logxx::LogLevel desiredLevel;

};

#endif	/* TEST_FW_H */

