#include <iostream>
#include <thread>
//#include <semaphore> //c++20信号量库
#include <vector>
#include  <fstream>
using namespace std;


class LOG {
public:
    LOG(const string& filename) {
        if (!filename.empty()) {
            logFile.open(filename, ios::app);
            if (!logFile) {
                cerr << "无法打开日志文件：" << filename << endl;
            }
        }
    }
    template <class T>
    LOG& operator<<(const T& mess) {
        //cout  << mess <<endl;
        if(logFile.is_open()) {
            logFile << mess << endl;
        }
    }
private:
    ofstream logFile;
};

int main () {
    LOG log("./logfile.txt");
    log << "第一条日志";
    return 0;
}

