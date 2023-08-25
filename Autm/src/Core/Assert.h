#ifndef AUTM_ASSERT_H
#define AUTM_ASSERT_H

#include <filesystem>
#include <iostream>

#define NOT_IMPLEMENTED() \
do {                      \
    std::cerr << "[" << std::filesystem::path(__FILE__).filename().string().c_str() << ":" <<  __LINE__ << "]: " << "Not Implemented" << "\n"; \
    abort();              \
} while (0)\

#define TODO(msg) \
do {                      \
    std::cerr << "[" << std::filesystem::path(__FILE__).filename().string().c_str() << ":" << __LINE__ << "]: " << "TODO: " << msg << "\n"; \
    abort();              \
} while (0)\

#endif //AUTM_ASSERT_H
