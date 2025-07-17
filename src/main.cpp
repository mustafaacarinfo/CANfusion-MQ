#include <iostream>
#include "bus/can_channel.hpp"
#include "bus/socket_can_channel.hpp"
#include <thread>
#include <iomanip>
#include "dbc/dbc_database.hpp"

using namespace std;
using namespace canmqtt::bus;
using std::cout;
using std::endl;

int main()
{
    dbc::DbcDatabase db("path/to/file.dbc");

    SocketCanChannel channel;
    if (!channel.open("vcan0")) {
        perror("socket");
        return 1;
    }
    cout << "Socket CAN channel opened successfully." << endl;
    
    channel.setCallback([&db](const Frame& frame) 
    {
        auto name = db.getMessageNameById(frame.id);
        cout << "Received Message: " << name
             << " (ID=0x" << hex << frame.id << dec << ")";
        // Decode signals
        auto values = db.decodeMessageById(frame.id, frame.data);
        cout << " Signals: {";
        bool first = true;
        for (auto const& kv : values) {
            if (!first) cout << ", ";
            cout << kv.first << "=" << kv.second;
            first = false;
        }
        cout << " }" << endl;
    });

    channel.startListening();

    while (true) 
    {
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        
        cout << "main thread..." << endl;
    }

    return 0;
}