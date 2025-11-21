#pragma once

#include "types.hpp"
#include <unordered_map>
#include <mutex>
#include <memory>
#include <expected>

namespace fastjsonstore {

class Store {
public:
    explicit Store(const StoreOptions& options = StoreOptions{});
    ~Store();

    void set(const Key& key, const Value& value);
    std::optional<Value> get(const Key& key) const;
    bool remove(const Key& key);
    bool exists(const Key& key) const;
    size_t size() const;
    void clear();

    bool save() const;
    bool load();
    
    std::vector<Key> keys() const;

private:
    mutable std::mutex mutex_;
    std::unordered_map<Key, Value> data_;
    StoreOptions options_;

    bool persist_to_file() const;
    bool load_from_file();
};

} // namespace fastjsonstore