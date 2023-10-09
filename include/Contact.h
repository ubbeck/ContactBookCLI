#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>

class Contact{

    private:
        std::string name;
        std::string surname;
        std::string email;
        int phone;

    public:
        Contact(const std::string &n = "", 
        const std::string &s = "", 
        const std::string &e = "", 
        int p = 0)
        : name(n), surname(s), email(e), phone(p) {}
    
        // Getters
        std::string getName() const {
            return name;
        }

        std::string getSurname() const {
            return surname;
        }

        std::string getEmail() const {
            return email;
        }

        int getPhone() const {
            return phone;
        }

        // Setters
        void setName(const std::string& n) {
            name = n;
        }

        void setSurname(const std::string& s) {
            surname = s;
        }

        void setEmail(const std::string& e) {
            email = e;
        }

        void setPhone(int p) {
            phone = p;
        }

        static Contact loadContact(std::ifstream &f){
            Contact contact;
            std::getline(f, contact.name);
            std::getline(f, contact.surname);
            std::getline(f, contact.email);
            f >> contact.phone;
            return contact;
        }

        static void writeContact(std::ofstream &f, const Contact &contact){
            f << contact.getName();
            f << "\n";
            f << contact.getSurname();
            f << "\n";
            f << contact.getEmail();
            f << "\n";
            f << contact.getPhone();
        }
};

bool operator==(Contact c1, Contact c2){
    return ((c1.getName() == c2.getName() && c1.getSurname() == c2.getSurname())
            && (c1.getEmail() == c2.getEmail() || c1.getPhone() == c2.getPhone()));
}

std::ostream& operator<<(std::ostream &os, const Contact &c){
    os << "Name: " << c.getName() << "\n"
              << "Surname: " << c.getSurname() << "\n"
              << "Email: " << c.getEmail() << "\n"
              << "Phone: " << c.getPhone() << "\n";
    return os;
}

#endif // CONTACT_H