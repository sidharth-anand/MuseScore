#ifndef MU_FRAMEWORK_ABSTRACTOPTIONITEM_H
#define MU_FRAMEWORK_ABSTRACTOPTIONITEM_H

#include "settings.h"
#include "async/asyncable.h"

namespace mu::framework {
class AbstractOptionItem : public async::Asyncable
{
signals:
    void valueChanged();

public:
    enum class Type {
        RadioButtonGroup,
    };

    AbstractOptionItem(Settings::Key key, std::string label);

    virtual Type type() const = 0;

    QString typeToString() const;

    QVariant value() const;
    void setValue(QVariant value);

private:
    Settings::Key m_key;
    std::string m_label;
};

template<typename T>
class RadioButtonGroupItem : public AbstractOptionItem
{
public:
    RadioButtonGroupItem(Settings::Key key, std::string label, std::list<T> options, std::map<T, std::string> optionLabels);

    Type type() const override;

private:
    std::list<T> m_options;
    std::map<T, std::string> m_optionLabels;
};
}

#endif // MU_FRAMEWORK_ABSTRACTOPTIONITEM_H
