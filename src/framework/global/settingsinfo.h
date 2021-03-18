#ifndef MU_FRAMEWORK_SETTINGSINFO_H
#define MU_FRAMEWORK_SETTINGSINFO_H

#include <memory>

#include <QList>
#include <QMap>
#include <QObject>
#include <QVariant>

namespace mu::framework {
class SettingsInfo
{
    Q_GADGET

    Q_PROPERTY(QString label READ label)

public:
    enum class SettingType
    {
        Default,
        RadioButtonGroup,
        NumberSpinner,
        Checkbox
    };

    typedef std::shared_ptr<SettingsInfo> SettingsInfoPtr;

    SettingsInfo();
    SettingsInfo(QString label);

    QString label() const;

    virtual SettingType type() const;

private:
    QString m_label;
};

class RadioButtonGroupInfo : public SettingsInfo
{
    Q_GADGET

    Q_PROPERTY(QList<int> options READ options)
    Q_PROPERTY(QList<QVariantMap> labels READ labels)

public:
    RadioButtonGroupInfo();
    RadioButtonGroupInfo(QString label, QList<int> options, QMap<int, QString> optionLabels);

    QList<int> options() const;
    QList<QVariantMap> labels() const;

    virtual SettingType type() const override;

private:
    QList<int> m_options;
    QMap<int, QString> m_optionLabels;
};

class NumberSpinnerInfo : public SettingsInfo
{
    Q_GADGET

    Q_PROPERTY(int min READ min)
    Q_PROPERTY(int max READ max)
    Q_PROPERTY(int step READ step)
    Q_PROPERTY(QString suffix READ suffix)

public:
    NumberSpinnerInfo();
    NumberSpinnerInfo(QString label, int min, int max, int step = 1, QString suffix = QString(""));

    int min() const;
    int max() const;
    int step() const;
    QString suffix() const;

    virtual SettingType type() const override;

private:
    int m_min;
    int m_max;
    int m_step;

    QString m_suffix;
};

class CheckboxInfo : public SettingsInfo
{
    Q_GADGET

    Q_PROPERTY(QString option READ option)

public:
    CheckboxInfo();
    CheckboxInfo(QString label, QString option);

    QString option() const;

    virtual SettingType type() const override;

private:
    QString m_option;
};
}

Q_DECLARE_METATYPE(mu::framework::SettingsInfo)
Q_DECLARE_METATYPE(mu::framework::RadioButtonGroupInfo)
Q_DECLARE_METATYPE(mu::framework::NumberSpinnerInfo)
Q_DECLARE_METATYPE(mu::framework::CheckboxInfo)

#endif // MU_FRAMEWORK_SETTINGSINFO_H
