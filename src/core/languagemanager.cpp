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

void LanguageManager::langAdd(std::string langPath, AbstractSnapIn *snapIn, const std::string &locale)
{
    langClear(snapIn);

    QString language = QString::fromStdString(locale).split("-")[0];

    QDirIterator it(QString(langPath.c_str()), QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        if (!it.fileInfo().isFile())
        {
            it.hasNext();
        }

        if (it.fileName().endsWith(language + ".qm"))
        {
            std::unique_ptr<QTranslator> qtTranslator = std::make_unique<QTranslator>();
            bool loadResult                           = qtTranslator->load(it.fileName(), ":/");
            if (loadResult)
            {
                QCoreApplication::installTranslator(qtTranslator.get());
                snapIn->getTranslators().push_back(std::move(qtTranslator));
//                snapIn->
            }
        }

        it.next();
    }
}

void LanguageManager::langDel()
{
}

void LanguageManager::langClear(AbstractSnapIn *snapIn)
{
    for (const auto &translator : snapIn->getTranslators())
    {
        QCoreApplication::removeTranslator(translator.get());
    }
    snapIn->getTranslators().clear();
}

}
