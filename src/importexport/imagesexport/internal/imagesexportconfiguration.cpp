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
#include "imagesexportconfiguration.h"

#include "settings.h"
#include "settingsinfo.h"

#include "libmscore/mscore.h"

using namespace mu::framework;
using namespace mu::iex::imagesexport;

static const Settings::Key EXPORT_PNG_USE_TRASNPARENCY_KEY("iex_imagesexport", "export/png/useTransparency");
static const Settings::Key EXPORT_PDF_COMBINE("iex_imagesexport", "export/pdf/combine");
static const Settings::Key EXPORT_PNG_DPI_RESOLUTION_KEY("iex_imagesexport", "export/png/resolution");
static const Settings::Key EXPORT_PDF_DPI_RESOLUTION_KEY("iex_imagesexport", "export/pdf/dpi");

void ImagesExportConfiguration::init()
{
    settings()->setDefaultValue(EXPORT_PNG_DPI_RESOLUTION_KEY, Val(Ms::DPI));
    settings()->setDefaultValue(EXPORT_PNG_USE_TRASNPARENCY_KEY, Val(true));
    settings()->setDefaultValue(EXPORT_PDF_DPI_RESOLUTION_KEY, Val(Ms::DPI));
    settings()->setDefaultValue(EXPORT_PDF_COMBINE, Val(1));

    settings()->setInfo(EXPORT_PDF_DPI_RESOLUTION_KEY,
                        SettingsInfo::SettingsInfoPtr(new NumberSpinnerInfo("Export Resolution", 72, 2400, 1, "DPI")));

    settings()->setInfo(EXPORT_PDF_COMBINE, SettingsInfo::SettingsInfoPtr(new RadioButtonGroupInfo("Export Scores:", { 1, 2 }, {
        { 1, "As separate files" },
        { 2, "Combined into a single file" }
    })));

    settings()->setInfo(EXPORT_PNG_USE_TRASNPARENCY_KEY,
                        SettingsInfo::SettingsInfoPtr(new CheckboxInfo("Background", "Export with a transparent background")));
}

int ImagesExportConfiguration::exportPdfDpiResolution() const
{
    return settings()->value(EXPORT_PDF_DPI_RESOLUTION_KEY).toInt();
}

void ImagesExportConfiguration::setExportPngDpiResolution(std::optional<float> dpi)
{
    m_customExportPngDpi = dpi;
}

float ImagesExportConfiguration::exportPngDpiResolution() const
{
    if (m_customExportPngDpi) {
        return m_customExportPngDpi.value();
    }

    return settings()->value(EXPORT_PNG_DPI_RESOLUTION_KEY).toFloat();
}

bool ImagesExportConfiguration::exportPngWithTransparentBackground() const
{
    return settings()->value(EXPORT_PNG_USE_TRASNPARENCY_KEY).toBool();
}
