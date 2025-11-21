#pragma once

#include <string>
#include <optional>
#include <nlohmann/json.hpp>

namespace fastjsonstore {

using json = nlohmann::json;
using Key = std::string;
using Value = json;

struct StoreOptions {
    std::string persistence_file = "store.json";
    bool auto_persist = true;
    size_t max_keys = 10000;
};

enum class StoreError {
    KeyNotFound,
    MaxKeysReached,
    PersistenceFailed,
    InvalidJSON
};

} // namespace fastjsonstore