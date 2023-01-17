#ifndef TRANSLATORSTORAGE_H
#define TRANSLATORSTORAGE_H

#include "core.h"
#include <QString>
#include <QTranslator>
#include <vector>
#include <bits/unique_ptr.h>

namespace gpui
{
/**
 * Хранит список файлов переводов. Класс должен распологаться в библиотеке core.
 * В идеале класс используется 1 раз в функции MainWindow::оnLanguageChange().
 * Для тестирования класса реализовать отладочный вывод в консоль.
 */
class TranslatorStorage
{
public:
    /**
     * Загружает список файлов переводов из ресурсов которые заканчиваются на название языка.
     * Пример gui_ru.qm - где ru - название языка.
     * Загружает системные файлы переводов для указанного языка используя: loadQtTranslators.
     *
     * @param language - язык для файлов переводов.
     */
    void loadTranslators(const QString& language);

    /**
     * Очищает список файлов переводов.
     */
    void clear();

    /**
     * Реализация паттерна singleton.
     */
    static TranslatorStorage* instance()
    {
        static TranslatorStorage s;
        return &s;
    }

private:    
    TranslatorStorage();

    /**
     * Загружает Qt5 translator "qtbase_" с указанного локального пути
     * или системного пути по умолчанию, если локальный путь не был указан.
     *
     * @param language - язык для файла переводов.
     * @param path - путь к файлу переводов если пустой, то заменяется на стандартный QLibraryInfo::location(QLibraryInfo::TranslationsPath).
     * @return - возвращает статус загрузки файла переводов true - успешно, false - нет.
     */
    bool loadQtTranslators(const QString& language,  QString path);

private:
    std::vector<std::unique_ptr<QTranslator>> translators;
    // Это список файлов перевода.-> Возможно стоит перенести в Private class подумать, решение аргументировать.

private:
    // Отключить кострукторы копирования и перемещеиния, а так же соответсвующие операторы.
    TranslatorStorage(const TranslatorStorage &) = delete;      //copy ctor
    TranslatorStorage(TranslatorStorage &&)      = delete;      //move ctor
    TranslatorStorage operator=(TranslatorStorage &) = delete;  //copy assignment
    TranslatorStorage operator=(TranslatorStorage &&) = delete; //move assignment
};
}
#endif // TRANSLATORSTORAGE_H
