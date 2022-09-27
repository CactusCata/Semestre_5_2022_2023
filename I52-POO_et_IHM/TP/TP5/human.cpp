#include "human.cpp"

Human::Human(std::string firstname, std::string lastname, unsigned short age) {
    this->m_firstname = firstname;
    this->m_lastname = lastname;
    this->m_age = age;
}

Human::Human():
Human("?", "?", 0)
{}

Human::Human(const Human &human):
Human(human.getFirstname(), human.getLastname(), human.getAge())
{}

std::string Human::getFirstname() {
    return this->m_firstname;
}

std::string Human::getLastname() {
    return this->m_lastname;
}

unsigned short Human::getAge() {
    return this->m_age;
}
