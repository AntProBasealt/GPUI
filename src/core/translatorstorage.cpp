#include "translatorstorage.h"
#include <QCoreApplication>

namespace gpui
{
void TranslatorStorage::loadTranslators(const QString &language)
{
    std::unique_ptr<QTranslator> qtTranslator = std::make_unique<QTranslator>();
    QString language = qtTranslator->load("gui_" + language + ".qm", ":/");
    QCoreApplication::installTranslator(qtTranslator.get());
    translators.push_back(std::move(qtTranslator));
//    qWarning() << "Load language " << language << loadResult;

}

bool TranslatorStorage::loadQtTranslators(const QString &language, const QString &path)
{

}

TranslatorStorage::TranslatorStorage(): translators(std::vector<std::unique_ptr<QTranslator>>{})
{

}

void TranslatorStorage::clear()
{

}
}
