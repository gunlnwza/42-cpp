#include <iostream>
#include "PhoneBook.hpp"
#include "utils.hpp"

#define STOP false
#define KEEP_RUNNING true

PhoneBook::PhoneBook(void)
    : n(0), i(0)
{}

bool PhoneBook::add(void)
{
    std::string fields[5];
    std::string field_names[5] = {
        "First Name",
        "Last Name",
        "Nickname",
        "Phone Number",
        "Darkest Secret"
    };
    std::cout << "Please enter all of the following infomation." << std::endl;
    for (int i = 0; i < 5; i++)
    {
        std::cout << "- " << field_names[i] << ": ";
        if (!std::getline(std::cin, fields[i]))
            return (STOP);

        fields[i] = ft_strtrim(fields[i], " /n/t/r");
        if (fields[i] == "")
        {
            log_error("adding contact but field is empty, stop");
            return (KEEP_RUNNING);
        }
    }

    this->contacts[i].set_fields(fields);
    if (this->n < 8)
        this->n++;
    this->i = (this->i + 1) % 8;
    std::cout << "Contact added." << std::endl;
    return (KEEP_RUNNING);
}

bool PhoneBook::search(void)
{
    std::string indexes("01234567");
    display_row("Index", "First Name", "Last Name", "Nickname");
    for (int i = 0; i < this->n; i++)
        display_row(indexes.substr(i, 1), contacts[i].first_name, contacts[i].last_name, contacts[i].nickname);

    if (this->n == 0)
    {
        std::cout << "Phonebook is empty." << std::endl;
        return (KEEP_RUNNING);
    }

    std::string input;
    std::cout << "Please enter the index of the entry to display." << std::endl
              << "- Index: ";
    if (!std::getline(std::cin, input))
        return (STOP);
    input = ft_strtrim(input, " /n/t/r");
    if (!(input.size() == 1 && '0' <= input[0] && input[0] < this->n + '0'))
    {
        log_error(input + ": No such index");
        return (KEEP_RUNNING);
    }

    int i = input[0] - '0';
    std::cout << "- First Name: " << contacts[i].first_name << std::endl
              << "- Last Name: " << contacts[i].last_name << std::endl
              << "- Nickname: " << contacts[i].nickname << std::endl
              << "- Phone Number: " << contacts[i].phone_number << std::endl
              << "- Darkest Secret: " << contacts[i].darkest_secret << std::endl;
    return (KEEP_RUNNING);
}

bool PhoneBook::exit(void)
{
    std::cout << "EXIT" << std::endl;
    return (STOP);
}

void PhoneBook::main_loop(void)
{
    std::string command;
    int         is_running;

    is_running = KEEP_RUNNING;
    while (is_running)
    {
        std::cout << ">>> ";
        if (!std::getline(std::cin, command))
        {
            std::cout << std::endl;
            break ;
        }
        command = ft_strtrim(command, " /n/t/r");
        if (command == "")
            continue ;

        if (command == "ADD" || command == "SEARCH" || command == "EXIT")
        {
            if (command == "ADD")
                is_running = this->add();
            else if (command == "SEARCH")
                is_running = this->search();
            else
                is_running = this->exit();
        }
        else
            log_error(command + ": command not found");
    }
}
