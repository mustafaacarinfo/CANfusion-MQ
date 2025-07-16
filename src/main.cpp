#include <iostream>
#include "bus/can_channel.hpp"
#include "bus/socket_can_channel.hpp"
#include <iomanip>
#include <thread>

using namespace std;
using namespace canmqtt::bus;
using std::cout;
using std::endl;

int main()
{
    SocketCanChannel channel;

    if (!channel.open("vcan0")) 
    {
        perror("socket"); return false;
    }
    else
    {
        cout << "Socket CAN channel opened successfully." << endl;
    }
    
    channel.setCallback([](const Frame& frame) 
    {
        std::cout << "Received CAN frame: ID = " << frame.id << ", Data = ";
        for (auto byte : frame.data) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
        }
        std::cout << ", Timestamp = " << frame.ts.count() << " us" << std::endl;
    });

    channel.startListening();

    while (true) 
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}