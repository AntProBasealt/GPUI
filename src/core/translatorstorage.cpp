#include "translatorstorage.h"
#include <QCoreApplication>
#include <QLibraryInfo>

namespace gpui
{
void TranslatorStorage::loadTranslators(const QString &language)
{
    loadQtTranslators(language, "");
}

bool TranslatorStorage::loadQtTranslators(const QString &language, QString path)
{
    if(path.isEmpty())
    {
        path = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    }

    std::unique_ptr<QTranslator> qtTranslator = std::make_unique<QTranslator>();
    bool loadResult                           = qtTranslator->load("qtbase_" + language + ".qm", path);
    if (loadResult)
    {
        QCoreApplication::installTranslator(qtTranslator.get());
       translators.push_back(std::move(qtTranslator));
    }
    return loadResult;
}

TranslatorStorage::TranslatorStorage(): translators(std::vector<std::unique_ptr<QTranslator>>{})
{

}

void TranslatorStorage::clear()
{
    for (const auto &translator : translators)
    {
        QCoreApplication::removeTranslator(translator.get());
    }
    translators.clear();
}
}
