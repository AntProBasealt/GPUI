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
//    virtual ~LanguageManager();
    void langAdd(const std::string &langPath, AbstractSnapIn *snapIn);

    void langDel();

    void langClear();

private:
    std::unique_ptr<LanguageManagerPrivate> d;

//    void langAdd(const std::string &language);

//	std::string language() const;

//private:
//	LanguageManager(const LanguageManager &lang);
//	const LanguageManager& operator=(const LanguageManager &lang);

};
}
#endif // LANGUAGEMANAGER_H
