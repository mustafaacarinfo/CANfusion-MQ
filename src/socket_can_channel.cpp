#include "bus/can_channel.hpp"


#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>


namespace canmqtt::bus 
{
    class SocketCanChannel : public ICanChannel
    {
        public:
            SocketCanChannel()  = default;
            ~SocketCanChannel() override { close(); }

            virtual bool open(std::string_view ifname, bool fd_mode = false) = 0;
            {
                if (fd_ != -1) return false;
                fd_ = ::socket(PF_CAN, SOCK_RAW, CAN_RAW);
                if (fd_ < 0) return false;
                
                ifreq ifr{};
                std::strncpy(ifr.ifr_name, ifname.data(), IFNAMSIZ - 1);
                if (ioctl(fd_, SIOCGIFINDEX, &ifr) < 0) return false;

                sockaddr_can addr{AF_CAN, ifr.ifr_ifindex};
                return ::bind(fd_, reinterpret_cast<sockaddr*>(&addr),
                sizeof(addr)) == 0;
            }

            virtual bool read(Frame& out) override
            {
                can_frame raw{};
                ssize_t n = ::recv(fd_, &raw, sizeof(raw), 0);
                if (n != sizeof(raw)) return false;

                out.id  = raw.can_id & CAN_EFF_MASK;
                out.data.assign(raw.data, raw.data + raw.can_dlc);
                out.ts = std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::steady_clock::now().time_since_epoch());
               
                return true;
            }

            virtual void close() override
            {
                if (fd_ != -1) { ::close(fd_); fd_ = -1; }

            }
        private:
            int fd_ = -1;

    }




}







