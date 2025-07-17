#pragma once

#include <string>
#include <vector>
#include <map>
#include <cstdint>

namespace dbc {

class DbcDatabase {
    public:
        explicit DbcDatabase(const std::string& filename);
        ~DbcDatabase();


        std::vector<std::string> getSignals(const std::string& messageName) const;


        std::map<std::string, double>
        decodeMessage(const std::string& messageName,
                    const std::vector<uint8_t>& rawBytes) const;


        std::vector<uint8_t>
        encodeMessage(const std::string& messageName,
                    const std::map<std::string, double>& signalValues) const;
        
        std::string getMessageNameById(uint32_t canId) const;

    private:
        struct Impl;
        Impl* pImpl;
};

} // namespace dbc
