#include <iostream>
#include "bus/can_channel.hpp"
#include "bus/socket_can_channel.hpp"

using namespace std;
using namespace canmqtt::bus;

int main()
{
    SocketCanChannel channel;

    if (!channel.open("vcan0")) 
    {
        perror("socket"); return false;
    }
    
    Frame frame;

    while (channel.read(frame)) 
    {
        cout << "Received CAN frame: ID = " << frame.id << ", Data = ";
        for (auto byte : frame.data) 
        {
            cout << std::hex << static_cast<int>(byte) << " ";
        }
        cout << ", Timestamp = " << frame.ts.count() << " us" << endl;
    }


    cout << "end of the main program , Hello, CAN MQTT!" << endl;




}