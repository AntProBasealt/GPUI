#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include <iostream>
#include <memory>
#include "languagemanagerprivate.h"

namespace gpui {

class LanguageManagerPrivate;

class LanguageManager
{
public:
    LanguageManager();
    virtual ~LanguageManager();

public:
    std::unique_ptr<LanguageManagerPrivate> d;

//    void langAdd(const std::string &language);
	void langAdd();
    void langDel();
    void langClear();
//	std::string language() const;

private:
	LanguageManager(const LanguageManager &lang);
	const LanguageManager& operator=(const LanguageManager &lang);

};
}
#endif // LANGUAGEMANAGER_H
