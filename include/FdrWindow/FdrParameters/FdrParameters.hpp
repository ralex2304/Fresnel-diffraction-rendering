#pragma once

#include <string>
#include <vector>
#include <type_traits>

namespace FdrParameters {

class ParameterRenewer {
public:
    virtual ~ParameterRenewer() = default;
    virtual void renew(const std::string& name, bool value) const noexcept = 0;
    virtual void renew(const std::string& name, int value) const noexcept = 0;
    virtual void renew(const std::string& name, float value) const noexcept = 0;
};

class ParameterBase {
public:
    virtual ~ParameterBase() = default;
    virtual const std::string& display_name() const noexcept = 0;
    virtual void drawImGuiWidget() = 0;
};

template <typename T>
class Parameter : public ParameterBase {
public:
    Parameter(
        const ParameterRenewer& renewer,
        const std::string& name,
        const std::string& display_name,
        const T& value = T()
    );

    const std::string& name() const noexcept;
    const std::string& display_name() const noexcept override;

    T get() const noexcept;
    void set_and_renew(const T& value) noexcept;
    void set_and_renew_if_changed(const T& value) noexcept;

    void drawImGuiWidget() override;

private:
    const ParameterRenewer& renewer_;
    const std::string name_;
    const std::string display_name_;
    T value_;
};

template<>
void Parameter<float>::drawImGuiWidget();

template<>
void Parameter<bool>::drawImGuiWidget();

class ParametersStorage {
public:
    class Iterator {
    public:
        Iterator(typename std::vector<ParameterBase*>::iterator it);
        ParameterBase* operator*();
        Iterator& operator++();
        bool operator!=(const Iterator& other) const;

    private:
        typename std::vector<ParameterBase*>::iterator current_it_;
    };

    template <typename T>
    void add(Parameter<T>& param);

    Iterator begin() noexcept;
    Iterator end() noexcept;

private:
    std::vector<ParameterBase*> params_;
};

extern template class Parameter<float>;
extern template class Parameter<bool>;

} // namespace FdrParameters