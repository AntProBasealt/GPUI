#include "languagemanager.h"
#include <QDebug>
#include <QFile>

#include "../core/compositesnapindetailsdialog.h"
#include "../core/pluginstorage.h"
#include "../core/snapindetailsdialog.h"
#include "../core/snapindetailsfactory.h"
#include "../core/snapinloader.h"
#include "../core/snapinmanager.h"

#include "../gui/commandlineparser.h"
#include "../gui/mainwindow.h"

#include "abstractsnapin.h"

#include <QApplication>
#include <QString>

namespace gpui
{
LanguageManager::LanguageManager() : d(std::make_unique<LanguageManagerPrivate>())
{
}

void LanguageManager::add(std::string langPath, AbstractSnapIn *snapIn, const std::string &locale)
{

}

void LanguageManager::del()
{
}

void LanguageManager::clear(AbstractSnapIn *snapIn)
{

}
}
