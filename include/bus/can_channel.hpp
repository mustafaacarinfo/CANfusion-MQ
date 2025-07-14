// Copyright (c) 2025 Mustafa.Acar
// SPDX-License-Identifier: MIT
// -----------------------------------------------------------------------------
// CAN channel *interface* layer (header-only)
// -----------------------------------------------------------------------------

#pragma  once

namespace canbus
{

struct Frame 
{
    uint32_t id;
    std::vector<uint8_t> data;
    uint64_t timestamp_us;
};

class ICanChannel
{

    public:

        virtual ~ICanChannel() = default;

        virtual bool open(const char* ifname, bool fd_mode=fals) = 0;
        virtual bool read(Frame& out) = 0;
        virtual void close() = 0;
}

}





























