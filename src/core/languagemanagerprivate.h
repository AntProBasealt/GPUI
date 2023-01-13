#ifndef LANGUAGEMANAGERPRIVATE_H
#define LANGUAGEMANAGERPRIVATE_H

#include <QObject>
#include <QTranslator>
#include "languagemanager.h"

namespace gpui
{
class LanguageManager;

class LanguageManagerPrivate : public QObject
{
    Q_OBJECT
public:
    LanguageManager *lang;
    std::string langPath{};
    std::vector<std::unique_ptr<QTranslator>> translators{};
//    QLocale locale;
//    LanguageManager *language;

public:
    void addLang(const std::string &path, const std::string &langPlace);
    void delLang(const std::string &langPlace);
    void clearLang();

public:
    LanguageManagerPrivate(LanguageManager *langManager);

private:
    LanguageManagerPrivate(const LanguageManagerPrivate &) = delete;      //copy ctor
    LanguageManagerPrivate(LanguageManagerPrivate &&)      = delete;      //move ctor
    LanguageManagerPrivate operator=(LanguageManagerPrivate &) = delete;  //copy assignment
    LanguageManagerPrivate operator=(LanguageManagerPrivate &&) = delete; //move assignment

};
} //namespace gpui

#endif // LANGUAGEMANAGERPRIVATE_H
