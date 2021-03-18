//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2020 MuseScore BVBA and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//=============================================================================
#include "settingslistmodel.h"

#include "log.h"
#include "settings.h"

#include <QRegularExpression.h>

using namespace mu;
using namespace mu::framework;
using namespace mu::uicomponents;

SettingsListModel::SettingsListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

QVariant SettingsListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= rowCount()) {
        return QVariant();
    }

    const Settings::Item& item = m_items.at(index.row());
    switch (role) {
    case SectionRole: return QString::fromStdString(item.key.moduleName);
    case KeyRole: return label(item);
    case TypeRole: return typeToString(item.info ? item.info->type() : SettingsInfo::SettingType::Default, item.value.type());
    case ValRole: return item.value.toQVariant();
    case InfoRole: return typeToInfo(item);
    }
    return QVariant();
}

int SettingsListModel::rowCount(const QModelIndex&) const
{
    return m_items.count();
}

QHash<int,QByteArray> SettingsListModel::roleNames() const
{
    static const QHash<int, QByteArray> roles = {
        { SectionRole, "sectionRole" },
        { KeyRole, "keyRole" },
        { TypeRole, "typeRole" },
        { ValRole, "valRole" },
        { InfoRole, "infoRole" }
    };
    return roles;
}

void SettingsListModel::load(QString key, QString module)
{
    beginResetModel();

    m_items.clear();

    Settings::Items items = settings()->items();

    for (auto it = items.cbegin(); it != items.cend(); ++it) {
        QRegularExpressionMatch keyMatch = QRegularExpression(key).match(QString::fromStdString(it->second.key.key));
        QRegularExpressionMatch moduleMatch = QRegularExpression(module).match(QString::fromStdString(it->second.key.moduleName));

        if ((key.isEmpty() || keyMatch.hasMatch()) && (module.isEmpty() || moduleMatch.hasMatch())) {
            m_items.push_front(it->second);
        }
    }

    endResetModel();
}

void SettingsListModel::changeVal(int idx, QVariant newVal)
{
    LOGD() << "changeVal index: " << idx << ", newVal: " << newVal;
    Settings::Item& item = m_items[idx];
    Val::Type type = item.value.type();
    item.value = Val::fromQVariant(newVal);
    item.value.setType(type);

    settings()->setValue(item.key, item.value);

    emit dataChanged(index(idx), index(idx));
}

QString SettingsListModel::typeToString(SettingsInfo::SettingType settingType, Val::Type valType) const
{
    if (settingType == SettingsInfo::SettingType::Default) {
        switch (valType) {
        case Val::Type::Undefined: return "Undefined";
        case Val::Type::Bool:      return "Bool";
        case Val::Type::Int:       return "Int";
        case Val::Type::Double:    return "Double";
        case Val::Type::String:    return "String";
        case Val::Type::Color:     return "Color";
        case Val::Type::Variant:   return "Variant";
        }
    } else {
        switch (settingType) {
        case SettingsInfo::SettingType::RadioButtonGroup: return "RadioButtonGroup";
        case SettingsInfo::SettingType::NumberSpinner: return "NumberSpinner";
        case SettingsInfo::SettingType::Checkbox: return "Checkbox";
        }
    }

    return "Undefined";
}

QVariant SettingsListModel::typeToInfo(Settings::Item item) const
{
    if (!item.info) {
        return QVariant();
    }

    switch (item.info->type()) {
    case SettingsInfo::SettingType::Default:
        return QVariant::fromValue(*item.info);
    case SettingsInfo::SettingType::RadioButtonGroup:
        return QVariant::fromValue(*dynamic_cast<RadioButtonGroupInfo*>(item.info.get()));
    case SettingsInfo::SettingType::NumberSpinner:
        return QVariant::fromValue(*dynamic_cast<NumberSpinnerInfo*>(item.info.get()));
    case SettingsInfo::SettingType::Checkbox:
        return QVariant::fromValue(*dynamic_cast<CheckboxInfo*>(item.info.get()));
    }
}

QString SettingsListModel::label(Settings::Item item) const
{
    if (item.info && !item.info->label().isEmpty()) {
        return item.info->label();
    } else {
        QString name = QString::fromStdString(item.key.key).split("/", Qt::SkipEmptyParts).last();
        name.replace(QRegularExpression("([A-Z](?=[a-z]+)|[A-Z]+(?![a-z]))"), " \\1");
        return name;
    }
}
