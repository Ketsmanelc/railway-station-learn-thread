#include <iostream>
#include <mutex>
#include <thread>
#include <cassert>
std::mutex station_access;

void Travel(char trainName, int time)
{
    //assert(time > 0);
    std::this_thread::sleep_for(std::chrono::seconds(time));
    station_access.lock();
    std::cout << "Train  " << trainName << " has arrived" << "\n";
    std::string cmd = "";
    while(cmd != "depart") std::cin >> cmd;
    std::cout << "Train  " << trainName << " has departed" << "\n";
    station_access.unlock();
}


int main() {
    int travelTime[3];
    for (int i = 0; i < 3; i++) {
        std::cin >> travelTime[i];
    }
    std::cout << "Start!!!" << std::endl;
    std::thread train_1(Travel, 'A', travelTime[0]);
    std::thread train_2(Travel, 'B', travelTime[1]);
    std::thread train_3(Travel, 'C', travelTime[2]);
    train_1.join();
    train_2.join();
    train_3.join();
    return 0;
}