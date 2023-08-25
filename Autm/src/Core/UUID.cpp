#include "UUID.h"
#include <random>

static std::random_device s_random_device;
static std::mt19937_64 s_random_engine(s_random_device());
static std::uniform_int_distribution<uint64_t> s_uniform_distribution;

// Maybe use uuid_t instead of a uint64_t
UUID::UUID() : m_uuid(s_uniform_distribution(s_random_engine)) {}

UUID::UUID(uint64_t uuid) : m_uuid(uuid) {}
