#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include <iostream>
#include <memory>
#include "languagemanagerprivate.h"
#include "abstractsnapin.h"

namespace gpui {

class LanguageManagerPrivate;

class LanguageManager
{
public:
    LanguageManager();

    void add(std::string langPath, AbstractSnapIn *snapIn, const std::string &locale);

    void del();

    void clear(AbstractSnapIn *snapIn);

private:
    std::unique_ptr<LanguageManagerPrivate> d;

};
}
#endif // LANGUAGEMANAGER_H
