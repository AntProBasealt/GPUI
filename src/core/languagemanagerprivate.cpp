#include "languagemanagerprivate.h"

#include <QDebug>

namespace gpui
{
LanguageManagerPrivate::LanguageManagerPrivate(LanguageManager *language)
    :lang(language)
{
}

void LanguageManagerPrivate::addLang(const std::string &path, const std::string &langPlace)
{
    Q_UNUSED(langPlace);

    langPath=path;
}

void LanguageManagerPrivate::delLang(const std::string &langPlace)
{
    Q_UNUSED(langPlace);
}

void LanguageManagerPrivate::clearLang()
{
//    lang->langClear();
}
} // namespace gpui
