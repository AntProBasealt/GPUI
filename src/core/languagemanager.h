#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include <iostream>
#include "languagemanagerprivate.h"

namespace gpui {

class LanguageManager
{
public:
    LanguageManager();
    virtual ~LanguageManager();

public:
    LanguageManagerPrivate *d;

	void addLang(const std::string &language);
//	std::string language() const;

private:
	LanguageManager(const LanguageManager &lang);
	const LanguageManager& operator=(const LanguageManager &lang);

};
}
#endif // LANGUAGEMANAGER_H
