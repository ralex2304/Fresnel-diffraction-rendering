#pragma once

#include <string>

namespace FdrParameters {

class ParameterRenewer {
public:
    virtual ~ParameterRenewer() {};

    virtual void renew(const std::string& name, bool  value) const noexcept = 0;
    virtual void renew(const std::string& name, int   value) const noexcept = 0;
    virtual void renew(const std::string& name, float value) const noexcept = 0;
};

template <typename T>
class Parameter {
public:
    Parameter(const ParameterRenewer& renewer, const std::string& name) noexcept;
    Parameter(const ParameterRenewer& renewer, const std::string& name, const T& value) noexcept;

    T get() const noexcept;

    void set_and_renew(const T& value) noexcept;
    void set_and_renew_if_changed(const T& value) noexcept;

private:
    const std::string name_;
    const ParameterRenewer& renewer_;

    T value_;
};

}; //< namespace FdrParameters

