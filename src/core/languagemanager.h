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

    void langAdd(std::string langPath, AbstractSnapIn *snapIn, const std::string &locale);

    void langDel();

    void langClear(AbstractSnapIn *snapIn);

private:
    std::unique_ptr<LanguageManagerPrivate> d;

};
}
#endif // LANGUAGEMANAGER_H
