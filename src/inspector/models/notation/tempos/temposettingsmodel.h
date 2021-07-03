/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef MU_INSPECTOR_TEMPOSETTINGSMODEL_H
#define MU_INSPECTOR_TEMPOSETTINGSMODEL_H

#include "models/abstractinspectormodel.h"

namespace mu::inspector {
class TempoSettingsModel : public AbstractInspectorModel
{
    Q_OBJECT

    Q_PROPERTY(PropertyItem * isDefaultTempoForced READ isDefaultTempoForced CONSTANT)
    Q_PROPERTY(PropertyItem * tempo READ tempo CONSTANT)
    Q_PROPERTY(PropertyItem * equation READ equation CONSTANT)
    Q_PROPERTY(PropertyItem * isEquationVisible READ isEquationVisible CONSTANT)

public:
    explicit TempoSettingsModel(QObject* parent, IElementRepositoryService* repository);

    void createProperties() override;
    void requestElements() override;
    void loadProperties() override;
    void resetProperties() override;

    PropertyItem* isDefaultTempoForced() const;
    PropertyItem* tempo() const;
    PropertyItem* equation() const;
    PropertyItem* isEquationVisible() const;

private:
    PropertyItem* m_isDefaultTempoForced = nullptr;
    PropertyItem* m_tempo = nullptr;
    PropertyItem* m_equation = nullptr;
    PropertyItem* m_isEquationVisible = nullptr;
};
}

#endif // MU_INSPECTOR_TEMPOSETTINGSMODEL_H
