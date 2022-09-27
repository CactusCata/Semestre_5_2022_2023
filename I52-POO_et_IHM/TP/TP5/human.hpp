#ifndef HUMAN_HPP
#define HUMAN_HPP

class Human {

    private:
      std::string m_firstname, m_lastname;
      unsigned short m_age;

    public:
      Human(std::string firstname, std::string lastname, unsigned short age);
      Human();
      Human(const Human &human);

      std::string getFirstname();
      std::string getLastname();
      unsigned short getAge();

};

#endif
