#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <mutex>
#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

mutex mtx;
condition_variable cv;
queue<int> avalible_cores;

struct Core{
    int id;
    thread worker;
};

