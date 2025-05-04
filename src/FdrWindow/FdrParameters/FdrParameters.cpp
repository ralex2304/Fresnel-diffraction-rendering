#include <string>

#include "FdrWindow/FdrParameters/FdrParameters.hpp"

namespace FdrParameters {

template <typename T>
Parameter<T>::Parameter(const ParameterRenewer& renewer, const std::string& name) noexcept
        : Parameter(renewer, name, T()) {}

template <typename T>
Parameter<T>::Parameter(const ParameterRenewer& renewer, const std::string& name, const T& value) noexcept
        : name_(name)
        , value_(value)
        , renewer_(renewer) {

    renewer_.renew(name_, value_);
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
    if (value_ != value)
        renewer_.renew(name_, value_ = value);
}

template class FdrParameters::Parameter<float>;
template class FdrParameters::Parameter<bool>;

}; //< namespace FdrParameters

