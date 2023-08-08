#ifndef _DUSK_UTILS_INDEXED_MAP_HPP_
#define _DUSK_UTILS_INDEXED_MAP_HPP_

#include <vector>
#include <unordered_map>

#include <dusk/common.hpp>
#include <dusk/log.hpp>

DUSK_NAMESPACE_BEGIN

template <typename Key, typename Value>
class IndexedMap {
private:
    std::vector<Key> keys;
    std::unordered_map<Key, Value> map;
    std::size_t select_idx{ 0 };

public:
    IndexedMap() = default;
    IndexedMap(std::initializer_list<std::pair<Key, Value>> init_list) {
        for (auto const& [key, value] : init_list) {
            this->emplace(key, value);
        }
    }

public:
    bool contains(Key const& key) const {
        return this->map.find(key) != this->map.end();
    }

    auto size() const {
        return this->keys.size();
    }

    void emplace(Key const& key, Value const& value) {
        if (this->contains(key)) {
            DUSK_CORE_WARN("IndexedMap::emplace: Key '{}' already exists, ignore it.", key);
            return;
        }
        this->keys.emplace_back(key);
        this->map[key] = value;
    }

    auto get(Key const& key) const {
        if (!this->contains(key)) {
            DUSK_CORE_ERROR("IndexedMap::get: Key '{}' does not exist!", key);
            return Value{};
        }
        return this->map.at(key);
    }

    auto get(std::size_t index) const {
        if (index >= this->size()) {
            DUSK_CORE_ERROR("IndexedMap::get: Index '{}' out of range!", index);
            return std::make_pair(Key{}, Value{});
        }
        return std::make_pair(this->keys[index], this->map.at(this->keys[index]));
    }

    auto get_selected() const {
        return this->get(this->select_idx);
    }

    auto get_selected_index() const {
        return this->select_idx;
    }

    void set_selected_index(std::size_t index) {
        if (index >= this->size()) {
            DUSK_CORE_ERROR("IndexedMap::set_selected: Index '{}' out of range!", index);
            return;
        }
        this->select_idx = index;
    }

    auto begin() { return this->map.begin(); }
    auto end() { return this->map.end(); }
    auto begin() const { return this->map.begin(); }
    auto end() const { return this->map.end(); }
};

DUSK_NAMESPACE_END

#endif // !_DUSK_UTILS_INDEXED_MAP_HPP_
