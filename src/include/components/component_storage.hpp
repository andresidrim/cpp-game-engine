#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <unordered_map>

class ComponentStorage {
public:
  template <typename T> void Add(const T &component) {
    auto key = std::type_index(typeid(T));
    if (Has<T>()) {
      throw std::runtime_error(std::string("Duplicated component: ") +
                               typeid(T).name());
    }

    componentStorage[key] = std::make_unique<ComponentWrapper<T>>(component);
  }

  template <typename T> bool Has() const {
    auto key = std::type_index(typeid(T));
    return componentStorage.find(key) != componentStorage.end();
  }

  template <typename T> T &Get() const {
    auto key = std::type_index(typeid(T));
    auto it = componentStorage.find(key);
    if (it == componentStorage.end()) {
      throw std::runtime_error(std::string("Component not found: ") +
                               typeid(T).name());
    }

    auto *wrapper = static_cast<ComponentWrapper<T> *>(it->second.get());
    return wrapper->component;
  }

  template <typename T> void Remove() {
    componentStorage.erase(std::type_index(typeid(T)));
  }

  void Clear() { componentStorage.clear(); }

private:
  struct IComponentWrapper {
    virtual ~IComponentWrapper() = default;
  };

  template <typename T> struct ComponentWrapper : IComponentWrapper {
    T component;
    explicit ComponentWrapper(const T &comp) : component(comp) {}
  };

  mutable std::unordered_map<std::type_index,
                             std::unique_ptr<IComponentWrapper>>
      componentStorage;
};
