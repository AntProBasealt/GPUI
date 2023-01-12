#ifndef LANGUAGEMANAGERPRIVATE_H
#define LANGUAGEMANAGERPRIVATE_H

#include <QObject>
#include "languagemanager.h"

namespace gpui
{

class LanguageManagerPrivate : public QObject
{
    Q_OBJECT
public:
    QLocale locale;
//    std::vector<std::unique_ptr<QTranslator>> translators{};
//    LanguageManager *language;

public slots:
    void addLang();

public:
    LanguageManagerPrivate(LanguageManager *langManager);

private:
    LanguageManagerPrivate(const LanguageManagerPrivate &) = delete;      //copy ctor
    LanguageManagerPrivate(LanguageManagerPrivate &&)      = delete;      //move ctor
    LanguageManagerPrivate operator=(LanguageManagerPrivate &) = delete;  //copy assignment
    LanguageManagerPrivate operator=(LanguageManagerPrivate &&) = delete; //move assignment

};
}

#endif // LANGUAGEMANAGERPRIVATE_H
