#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class PhoneBook
{
    public:
        PhoneBook(void);
        
        void main_loop(void);

    private:
        Contact contacts[8];
        int     n;
        int     i;  // index to save to

        bool add(void);
        bool search(void);
        bool exit(void);
};

#endif
