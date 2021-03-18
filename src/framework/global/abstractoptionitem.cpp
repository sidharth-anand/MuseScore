#include "abstractoptionitem.h"

using namespace mu;
using namespace mu::framework;

AbstractOptionItem::AbstractOptionItem(Settings::Key key, std::string label)
    : m_key(key)
    , m_label(label)
{
    settings()->valueChanged(m_key).onReceive(this, [this](const Val&) {
        emit valueChanged();
    });
}

QString AbstractOptionItem::typeToString() const
{
    switch (type()) {
    case Type::RadioButtonGroup:
        return "RadioButtonGroup";
    }

    return "Undefined";
}

QVariant AbstractOptionItem::value() const
{
    return settings()->value(m_key).toQVariant();
}

void AbstractOptionItem::setValue(QVariant value)
{
    settings()->setValue(m_key, Val::fromQVariant(value));
}

void AbstractOptionItem::valueChanged()
{
}

template<typename T>
RadioButtonGroupItem<T>::RadioButtonGroupItem(Settings::Key key, std::string label, std::list<T> options, std::map<T,
                                                                                                                   std::string> optionalLabels)
    : AbstractOptionItem(key, label)
    , m_options(options)
    , m_optionLabels(optionLabels)
{
}

template<typename T>
AbstractOptionItem::Type RadioButtonGroupItem<T>::type() const
{
    return AbstractOptionItem::Type::RadioButtonGroup;
}
