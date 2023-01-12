#include "languagemanagerprivate.h"

#include <QDebug>

namespace gpui
{
LanguageManagerPrivate::LanguageManagerPrivate(LanguageManager *language)
    :lang(language)
{

}

void LanguageManagerPrivate::addLang()
{
    lang->langAdd();
}

void LanguageManagerPrivate::delLang()
{
    lang->langDel();
}

void LanguageManagerPrivate::clearLang()
{
    lang->langClear();
}
}
