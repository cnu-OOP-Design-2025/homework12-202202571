
#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <string>

using namespace std;
class Logger {
private:
    static std::unique_ptr<Logger> instance;
    static std::mutex init_mtx;
    static std::mutex write_mtx;
    std::ofstream logFile;
    Logger(){
        logFile.open("Test/output2.txt",std::ios::trunc);
        if(!logFile.is_open()){
            throw std::runtime_error("Failed to open log file");
        }
        logFile<<"[Init] Logger started."<<endl;
    }

public:
    static Logger* getInstance(const std::string& filename = "Test/output2.txt") {
        std::lock_guard<std::mutex> lock(init_mtx);
        if(!instance){
            instance.reset(new Logger());
        }
        return instance.get();
    }

    void log(const std::string& message) {
        /* TODO */
        std::lock_guard<std::mutex> lock(write_mtx);
        if(logFile.is_open()){
            logFile << message <<endl;
        }
    }
    ~Logger(){
        if(logFile.is_open()){
            logFile<<"[Shutdown] Logger closed."<<endl;
            logFile.close();
        }
    }

};

std::unique_ptr<Logger> Logger::instance;
std::mutex Logger::init_mtx;
std::mutex Logger::write_mtx;

