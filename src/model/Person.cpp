#include "../../include/model/Person.h"

Person::Person(const std::string& name, const std::string& email, const std::string& phone)
    : name(name), email(email), phone(phone) {}

std::string Person::getContactInfo() const {
    return "Име: " + name + " | Email: " + email + " | Тел: " + phone;
}