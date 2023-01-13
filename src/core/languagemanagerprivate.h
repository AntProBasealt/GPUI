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
    LanguageManagerPrivate();

private:
    LanguageManagerPrivate(const LanguageManagerPrivate &) = delete;      //copy ctor
    LanguageManagerPrivate(LanguageManagerPrivate &&)      = delete;      //move ctor
    LanguageManagerPrivate operator=(LanguageManagerPrivate &) = delete;  //copy assignment
    LanguageManagerPrivate operator=(LanguageManagerPrivate &&) = delete; //move assignment

};
} //namespace gpui

#endif // LANGUAGEMANAGERPRIVATE_H
