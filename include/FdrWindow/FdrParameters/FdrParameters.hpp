#pragma once

#include <string>
#include <unordered_map>

namespace FdrParameters {

class ParameterRenewer {
public:
    virtual ~ParameterRenewer() = default;
    virtual void renew(const std::string& name, bool value) const noexcept = 0;
    virtual void renew(const std::string& name, int value) const noexcept = 0;
    virtual void renew(const std::string& name, float value) const noexcept = 0;
};

template <typename T>
class Parameter {
public:
    Parameter(const ParameterRenewer& renewer, const std::string& name,
             const T& value, const std::string& label)
        : name(name)
        , label(label)
        , renewer_(renewer)
        , value_(value) {}

    const std::string name;
    const std::string label;

    const T& get() const {
        return value_;
    }

    void set(const T& value) {
        renewer_.renew(name, value_ = value);
    }

private:
    const ParameterRenewer& renewer_;
    T value_;
};

class ParametersStorage {
public:
    template <typename T>
    constexpr std::unordered_map<std::string, Parameter<T>>& storage() {
        if      constexpr (std::is_same_v<T, int>)   return int_params_;
        else if constexpr (std::is_same_v<T, float>) return float_params_;
        else if constexpr (std::is_same_v<T, bool>)  return bool_params_;
        else static_assert(0, "Unknown params type");
    }

    template <typename T>
    void add_parameter(const ParameterRenewer& renewer_, const std::string& name,
                       const T& value, const std::string& label) {
        storage<T>().insert({name, Parameter(renewer_, name, value, label)});
        renewer_.renew(name, value);
    }

private:
    std::unordered_map<std::string, Parameter<int>>   int_params_;
    std::unordered_map<std::string, Parameter<float>> float_params_;
    std::unordered_map<std::string, Parameter<bool>>  bool_params_;
};

}; //< namespace FdrParameters

