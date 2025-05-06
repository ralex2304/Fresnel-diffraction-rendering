#include "FdrWindow/FdrParameters/FdrParameters.hpp"
#include <imgui.h>

namespace FdrParameters {

template <typename T>
Parameter<T>::Parameter(
    const ParameterRenewer& renewer,
    const std::string& name,
    const std::string& display_name,
    const T& value
) : renewer_(renewer), name_(name), display_name_(display_name), value_(value) {
    renewer_.renew(name_, value_);
}

template <typename T>
const std::string& Parameter<T>::name() const noexcept {
    return name_;
}

template <typename T>
const std::string& Parameter<T>::display_name() const noexcept {
    return display_name_;
}

template <typename T>
T Parameter<T>::get() const noexcept {
    return value_;
}

template <typename T>
void Parameter<T>::set_and_renew(const T& value) noexcept {
    renewer_.renew(name_, value_ = value);
}

template <typename T>
void Parameter<T>::set_and_renew_if_changed(const T& value) noexcept {
    if (value_ != value) {
        renewer_.renew(name_, value_ = value);
    }
}

template <>
void Parameter<float>::drawImGuiWidget() {
    float value = get();
    if (ImGui::InputFloat(display_name().c_str(), &value)) {
        set_and_renew(value);
    }
}

template <>
void Parameter<bool>::drawImGuiWidget() {
    bool value = get();
    if (ImGui::Checkbox(display_name().c_str(), &value)) {
        set_and_renew(value);
    }
}

template class Parameter<float>;
template class Parameter<bool>;

template void ParametersStorage::add<float>(Parameter<float>&);
template void ParametersStorage::add<bool>(Parameter<bool>&);

ParametersStorage::Iterator::Iterator(typename std::vector<ParameterBase*>::iterator it) 
    : current_it_(it) {}

ParameterBase* ParametersStorage::Iterator::operator*() {
    return *current_it_;
}

ParametersStorage::Iterator& ParametersStorage::Iterator::operator++() {
    ++current_it_;
    return *this;
}

bool ParametersStorage::Iterator::operator!=(const Iterator& other) const {
    return current_it_ != other.current_it_;
}

template <typename T>
void ParametersStorage::add(Parameter<T>& param) {
    params_.push_back(static_cast<ParameterBase*>(&param));
}

ParametersStorage::Iterator ParametersStorage::begin() noexcept {
    return Iterator(params_.begin());
}

ParametersStorage::Iterator ParametersStorage::end() noexcept {
    return Iterator(params_.end());
}

} // namespace FdrParameters
