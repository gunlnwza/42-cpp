#ifndef DATE_HPP
# define DATE_HPP

# include <iostream>
# include <iomanip>
# include <sstream>

# include "ft_utils.hpp"

class Date
{
    private:
        int year;
        int month;
        int day;
        
        public:
        Date();
        Date(const Date& other);
        Date& operator=(const Date& other);
        ~Date();
        
        void parse_date(const std::string& date_str);
        Date(const std::string& date_str);
        
        Date(int year, int month, int day);

        bool operator<(const Date& other) const;
        bool operator<=(const Date& other) const;
        bool operator>(const Date& other) const;
        bool operator>=(const Date& other) const;
        bool operator==(const Date& other) const;
        bool operator!=(const Date& other) const;

        int get_year() const;
        int get_month() const;
        int get_day() const;

        std::string get_string() const;
};

std::ostream& operator<<(std::ostream& os, const Date& date);

#endif
