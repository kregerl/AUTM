#ifndef AUTM_UUID_H
#define AUTM_UUID_H

#include <cstdint>

class UUID {
public:
    UUID();

    UUID(const UUID&) = default;

    explicit UUID(uint64_t uuid);

    explicit operator uint64_t() const { return m_uuid; }

    bool operator==(const UUID& other) const {
        return m_uuid == other.m_uuid;
    }

private:
    uint64_t m_uuid;
};

namespace std {
    template<typename T>
    struct hash;

    template<>
    struct hash<UUID> {
        std::size_t operator()(const UUID& uuid) const {
            return static_cast<uint64_t>(uuid);
        }
    };
}


#endif //AUTM_UUID_H
