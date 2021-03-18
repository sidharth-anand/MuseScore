#include "settingsinfo.h"

using namespace mu;
using namespace mu::framework;

SettingsInfo::SettingsInfo()
    : m_label("")
{
}

SettingsInfo::SettingsInfo(QString label)
    : m_label(label)
{
}

QString SettingsInfo::label() const
{
    return m_label;
}

SettingsInfo::SettingType SettingsInfo::type() const
{
    return SettingType::Default;
}

RadioButtonGroupInfo::RadioButtonGroupInfo()
    : SettingsInfo("")
    , m_options()
    , m_optionLabels()
{
}

RadioButtonGroupInfo::RadioButtonGroupInfo(QString label, QList<int> options, QMap<int, QString> optionLabels)
    : SettingsInfo(label)
    , m_options(options)
    , m_optionLabels(optionLabels)
{
}

QList<int> RadioButtonGroupInfo::options() const
{
    return m_options;
}

QList<QVariantMap> RadioButtonGroupInfo::labels() const
{
    QList<QVariantMap> labels;
    foreach (int option, m_optionLabels.keys()) {
        QVariantMap map;
        map["valueRole"] = option;
        map["textRole"] = m_optionLabels[option];

        labels << map;
    }

    return labels;
}

SettingsInfo::SettingType RadioButtonGroupInfo::type() const
{
    return SettingsInfo::SettingType::RadioButtonGroup;
}

NumberSpinnerInfo::NumberSpinnerInfo()
    : SettingsInfo("")
    , m_min(0)
    , m_max(100)
    , m_step(1)
    , m_suffix("")
{
}

NumberSpinnerInfo::NumberSpinnerInfo(QString label, int min, int max, int step, QString suffix)
    : SettingsInfo(label)
    , m_min(min)
    , m_max(max)
    , m_step(step)
    , m_suffix(suffix)
{
}

int NumberSpinnerInfo::min() const
{
    return m_min;
}

int NumberSpinnerInfo::max() const
{
    return m_max;
}

int NumberSpinnerInfo::step() const
{
    return m_step;
}

QString NumberSpinnerInfo::suffix() const
{
    return m_suffix;
}

SettingsInfo::SettingType NumberSpinnerInfo::type() const
{
    return SettingsInfo::SettingType::NumberSpinner;
}

CheckboxInfo::CheckboxInfo()
    : SettingsInfo("")
    , m_option("")
{
}

CheckboxInfo::CheckboxInfo(QString label, QString option)
    : SettingsInfo(label)
    , m_option(option)
{
}

QString CheckboxInfo::option() const
{
    return m_option;
}

SettingsInfo::SettingType CheckboxInfo::type() const
{
    return SettingsInfo::SettingType::Checkbox;
}
