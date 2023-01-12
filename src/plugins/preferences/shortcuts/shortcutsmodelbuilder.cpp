/***********************************************************************************************************************
**
** Copyright (C) 2021 BaseALT Ltd. <org@basealt.ru>
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 2
** of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
**
***********************************************************************************************************************/

#include "shortcutsmodelbuilder.h"

#include "shortcutscontaineritem.h"
#include "shortcutsitem.h"

#include "common/commonitem.h"

#include "keysequenceencoder.h"

namespace
{
enum WindowMode
{
    WINDOWED  = 0,
    MINIMIZED = 1,
    MAXIMIZED = 2,
};

std::vector<std::string> locations = {
    "%DesktopDir%",
    "%StartMenuDir%",
    "%ProgramsDir%",
    "%StartUpDir%",
    "%FavoritesDir%",
    "%FavoritesDir%",
    "%SendToDir%",
    "%RecentDocumentsDir%",
    "%AppDataDir%",
    "%NetPlacesDir%",
    "%CommonDesktopDir%",
    "%CommonStartMenuDir%",
    "%CommonProgramsDir%",
    "%CommonStartUpDir%",
    "%CommonFavoritesDir%",
};

enum TargetType
{
    FILESYSTEM = 0,
    URL        = 1,
    SHELL      = 2,
};

} // namespace

namespace preferences
{
ShortcutsModelBuilder::ShortcutsModelBuilder()
    : BaseModelBuilder()
{}

std::unique_ptr<PreferencesModel> ShortcutsModelBuilder::schemaToModel(std::unique_ptr<Shortcuts> &shortcutsSource)
{
    auto model = std::make_unique<PreferencesModel>();

    for (const auto &shortcutsSchema : shortcutsSource->Shortcut())
    {
        auto properties = shortcutsSchema.Properties();
        for (const auto &currentProperties : properties)
        {
            auto actionState = getActionCheckboxState(getOptionalPropertyData(currentProperties.action()).c_str());
            int iconIndex    = static_cast<int>(getOptionalPropertyData(currentProperties.iconIndex()));

            auto sessionItem = model->insertItem<ShortcutsContainerItem>(model->rootItem());
            sessionItem->setupListeners();

            auto path = QString::fromStdString(currentProperties.shortcutPath());

            auto location     = path.section('\\', 0, 0);
            auto index        = decodeLocation(location.toStdString());
            auto shortcutPath = path.section('\\', 1).toStdString();

            if (shortcutPath.empty())
            {
                shortcutPath = currentProperties.shortcutPath().c_str();
            }

            int targetType = decodeTargetType(currentProperties.targetType());

            auto shortcuts = sessionItem->getShortcuts();
            shortcuts->setProperty(ShortcutsItem::ACTION, actionState);
            shortcuts->setProperty(ShortcutsItem::PIDL, getOptionalPropertyData(currentProperties.pidl()).c_str());
            shortcuts->setProperty(ShortcutsItem::SHORTCUT_PATH, shortcutPath);
            shortcuts->setProperty(ShortcutsItem::TARGET_TYPE, targetType);
            shortcuts->setProperty(ShortcutsItem::TARGET_PATH, currentProperties.targetPath().c_str());
            shortcuts->setProperty(ShortcutsItem::LOCATION, index);
            shortcuts->setProperty(ShortcutsItem::ARGUMENTS,
                                   getOptionalPropertyData(currentProperties.arguments()).c_str());
            shortcuts->setProperty(ShortcutsItem::START_IN,
                                   getOptionalPropertyData(currentProperties.startIn()).c_str());
            shortcuts->setProperty(ShortcutsItem::WINDOW,
                                   decodeWindowMode(getOptionalPropertyData(currentProperties.window()).c_str()));
            shortcuts->setProperty(ShortcutsItem::COMMENT, getOptionalPropertyData(currentProperties.comment()).c_str());
            shortcuts->setProperty(ShortcutsItem::ICON_PATH,
                                   getOptionalPropertyData(currentProperties.iconPath()).c_str());
            shortcuts->setProperty(ShortcutsItem::ICON_INDEX, std::to_string(iconIndex));

            auto shortcutKey = getOptionalPropertyData(currentProperties.shortcutKey());

            shortcuts->setProperty(ShortcutsItem::SHORTCUT_KEY, decodeShortcutKey(shortcutKey));

            auto common = sessionItem->getCommon();
            setCommonItemData(common, shortcutsSchema);
        }
    }

    return model;
}

std::unique_ptr<Shortcuts> ShortcutsModelBuilder::modelToSchema(std::unique_ptr<PreferencesModel> &model)
{
    auto shortcuts = std::make_unique<Shortcuts>("{872ECB34-B2EC-401b-A585-D32574AA90EE}");

    for (const auto &containerItem : model->topItems())
    {
        if (auto shortcutsContainer = dynamic_cast<ShortcutsContainerItem *>(containerItem); shortcutsContainer)
        {
            auto shortcutModel = shortcutsContainer->getShortcuts();
            auto commonModel   = shortcutsContainer->getCommon();

            std::string key = shortcutModel->property<std::string>(ShortcutsItem::SHORTCUT_KEY);

            auto prefix = encodeLocation(shortcutModel->property<int>(ShortcutsItem::LOCATION));

            auto shortcut = Shortcut_t("", "", "");
            commonModel->setProperty(CommonItem::propertyToString(CommonItem::CLSID),
                                     "{4F2F7C55-2790-433e-8127-0739D1CFA327}");
            commonModel->setProperty(CommonItem::propertyToString(CommonItem::CHANGED), createDateOfChange());
            commonModel->setProperty(CommonItem::propertyToString(CommonItem::NAME),
                                     shortcutModel->property<std::string>(ShortcutsItem::SHORTCUT_PATH));

            auto shortcutPath = prefix + shortcutModel->property<std::string>(ShortcutsItem::SHORTCUT_PATH);

            std::string targetType = encodeTargetType(shortcutModel->property<int>(ShortcutsItem::TARGET_TYPE));

            auto properties = ShortcutsProperties_t(targetType,
                                                    shortcutModel->property<std::string>(ShortcutsItem::TARGET_PATH),
                                                    shortcutPath);
            properties.action(getActionCheckboxModel(shortcutModel->property<int>(ShortcutsItem::ACTION)));
            properties.pidl(shortcutModel->property<std::string>(ShortcutsItem::PIDL));
            properties.arguments(shortcutModel->property<std::string>(ShortcutsItem::ARGUMENTS));
            properties.startIn(shortcutModel->property<std::string>(ShortcutsItem::START_IN));
            properties.window(encodeWindowMode(shortcutModel->property<int>(ShortcutsItem::WINDOW)));
            properties.comment(shortcutModel->property<std::string>(ShortcutsItem::COMMENT));
            properties.iconPath(shortcutModel->property<std::string>(ShortcutsItem::ICON_PATH));
            properties.shortcutKey(encodeShortcutKey(shortcutModel->property<std::string>(ShortcutsItem::SHORTCUT_KEY)));

            setCommonModelData(shortcut, commonModel);
            shortcut.Properties().push_back(properties);

            shortcuts->Shortcut().push_back(shortcut);
        }
    }

    return shortcuts;
}

std::string ShortcutsModelBuilder::decodeShortcutKey(uint32_t shortcutKey)
{
    KeySequenceEncoder encoder;

    QKeySequence sequence = encoder.decode(shortcutKey);

    return sequence.toString().toStdString();
}

uint32_t ShortcutsModelBuilder::encodeShortcutKey(std::string shortcutKey)
{
    QString code = QString::fromStdString(shortcutKey);

    KeySequenceEncoder encoder;

    return encoder.encode(QKeySequence(code));
}

std::string ShortcutsModelBuilder::encodeLocation(const int targetType)
{
    std::string result = "";

    if (targetType <= 0 || targetType >= static_cast<int>(locations.size()))
    {
        return result;
    }

    return locations[targetType - 1] + '\\';
}

int ShortcutsModelBuilder::decodeLocation(const std::string &type)
{
    for (size_t index = 0; index < locations.size(); ++index)
    {
        const auto &currentLocation = locations[index];

        if (currentLocation.compare(type) == 0)
        {
            return ++index;
        }
    }

    return 0;
}

int ShortcutsModelBuilder::decodeTargetType(const std::string &type)
{
    if (type.compare("URL") == 0)
    {
        return URL;
    }

    if (type.compare("SHELL") == 0)
    {
        return SHELL;
    }

    return FILESYSTEM;
}

std::string ShortcutsModelBuilder::encodeTargetType(const int type)
{
    std::string result = "FILESYSTEM";

    switch (type)
    {
    case URL:
        result = "URL";
        break;
    case SHELL:
        result = "SHELL";
        break;
    case FILESYSTEM:
    default:
        break;
    }

    return result;
}

int ShortcutsModelBuilder::decodeWindowMode(const std::string &windowMode)
{
    if (windowMode.compare("MIN") == 0)
    {
        return MINIMIZED;
    }

    if (windowMode.compare("MAX") == 0)
    {
        return MAXIMIZED;
    }

    return WINDOWED;
}

std::string ShortcutsModelBuilder::encodeWindowMode(const int &windowMode)
{
    if (windowMode == MINIMIZED)
    {
        return "MIN";
    }

    if (windowMode == MAXIMIZED)
    {
        return "MAX";
    }

    return "";
}

} // namespace preferences
