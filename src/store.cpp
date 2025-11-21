#include "fastjsonstore/store.hpp"
#include <fstream>
#include <iostream>

namespace fastjsonstore {
Store::Store(const StoreOptions& options) 
    : options_(options) {
    if (!options_.persistence_file.empty()) {
        load_from_file();
    }
}
Store::~Store() {
  if (options_.auto_persist) {
      persist_to_file();
  }
}


void Store::set(const Key& key, const Value& value) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    if (data_.size() >= options_.max_keys && data_.find(key) == data_.end()) {
        throw std::runtime_error("Maximum number of keys reached");
    }
    
    data_[key] = value;
}

std::optional<Value> Store::get(const Key& key) const {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = data_.find(key);
    if (it != data_.end()) {
        return std::optional<Value>(it->second);
    }
    return std::nullopt;
}

bool Store::remove(const Key& key) {
    std::lock_guard<std::mutex> lock(mutex_);
    return data_.erase(key) > 0;
}

bool Store::exists(const Key& key) const {
  std::lock_guard<std::mutex> lock(mutex_);
  return data_.find(key) != data_.end();
}

}