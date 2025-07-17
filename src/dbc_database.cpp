#include "dbc/dbc_database.hpp"
#include <dbcpp/database.hpp>
#include <dbcpp/message.hpp>


namespace dbc {

struct DbcDatabase::Impl {
    dbcppp::Database db;
    Impl(const std::string& fn) : db(fn) {}
};

DbcDatabase::DbcDatabase(const std::string& filename)
  : pImpl(new Impl(filename))
{}

DbcDatabase::~DbcDatabase() {
    delete pImpl;
}

std::vector<std::string> DbcDatabase::getSignals(const std::string& messageName) const {
    std::vector<std::string> names;
    if (auto msg = pImpl->db.findMessage(messageName)) {
        for (auto const& sig : msg->signals())
            names.push_back(sig.name());
    }
    return names;
}

std::map<std::string, double>
DbcDatabase::decodeMessage(const std::string& messageName,
                            const std::vector<uint8_t>& rawBytes) const {
    std::map<std::string, double> result;
    if (auto msg = pImpl->db.findMessage(messageName)) {
        auto decoded = msg->decodeFrame(rawBytes);
        for (auto const& [sig, value] : decoded)
            result[sig.name()] = value;
    }
    return result;
}

std::vector<uint8_t>
DbcDatabase::encodeMessage(const std::string& messageName,
                            const std::map<std::string, double>& signalValues) const {
    std::vector<uint8_t> raw;
    if (auto msg = pImpl->db.findMessage(messageName)) {
        auto frame = msg->createFrame();
        for (auto const& [name, val] : signalValues) {
            if (auto sig = msg->findSignal(name))
                frame.setSignalValue(*sig, val);
        }
        raw = frame.encode();
    }
    return raw;
}

std::vector<uint8_t>
DbcDatabase::encodeMessageById(uint32_t canId,
                                const std::map<std::string, double>& signalValues) const {
    std::vector<uint8_t> raw;
    if (auto msg = pImpl->db.findMessageById(canId)) {
        auto frame = msg->createFrame();
        for (auto const& [name, val] : signalValues) {
            if (auto sig = msg->findSignal(name))
                frame.setSignalValue(*sig, val);
        }
        raw = frame.encode();
    }
    return raw;
}

std::string DbcDatabase::getMessageNameById(uint32_t canId) const {
    if (auto msg = pImpl->db.findMessageById(canId))
        return msg->name();
    return std::string();
}

std::map<std::string, double>
DbcDatabase::decodeMessageById(uint32_t canId,
                                const std::vector<uint8_t>& rawBytes) const {
    std::map<std::string, double> result;
    if (auto msg = pImpl->db.findMessageById(canId)) {
        auto decoded = msg->decodeFrame(rawBytes);
        for (auto const& [sig, value] : decoded)
            result[sig.name()] = value;
    }
    return result;
}



}