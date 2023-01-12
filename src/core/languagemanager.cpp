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

#include <QApplication>

namespace gpui
{
LanguageManager::LanguageManager()
{

}

LanguageManager::~LanguageManager()
{
    delete d;
}

void LanguageManager::addLang(const std::string &locale)
{
//    d->addLang() = locale;
    std::unique_ptr<QTranslator> qtTranslator = std::make_unique<QTranslator>();
    qtTranslator->load(locale, "gui", "_", ":/");
    std::unique_ptr<QTranslator> qtTranslator2 = std::make_unique<QTranslator>();
    qtTranslator2->load(QString("qt_").append(QLocale::system().name()),
                        QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    QCoreApplication::installTranslator(qtTranslator.get());
    QCoreApplication::installTranslator(qtTranslator2.get());
}

}
