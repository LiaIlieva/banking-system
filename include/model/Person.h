#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
protected:
    std::string name;
    std::string email;
    std::string phone;

public:
    Person(const std::string& name, const std::string& email, const std::string& phone);
    virtual ~Person() = default; // Задължителен виртуален деструктор за абстрактен клас

    virtual std::string getContactInfo() const;
    virtual bool validate() const = 0; // Чисто виртуален метод (Прави класа абстрактен)
};

#endif // PERSON_H