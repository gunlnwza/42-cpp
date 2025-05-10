#include "Date.hpp"


Date::Date() {}

Date::Date(const Date& other)
{
    *this = other;
}

Date& Date::operator=(const Date& other)
{
    if (this == &other)
        return (*this);
    this->year = other.year;
    this->month = other.month;
    this->day = other.day;
    return (*this);
}

Date::~Date() {}


void Date::parse_date(const std::string& date_str)
{
    // parse
    const std::string   delimiter = "-";
    std::string         s(date_str);
    size_t              pos;
    std::string         y, m, d;

    for (size_t i = 0; i < 3; i++)
    {
        pos = s.find(delimiter);
        switch (i)
        {
            case 0: y = s.substr(0, pos); break ;        
            case 1: m = s.substr(0, pos); break ;
            case 2: d = s.substr(0, pos); break ;
        }
        s.erase(0, pos + delimiter.length());
    }
    if (pos != std::string::npos)
        throw (std::runtime_error("more than 2 tokens"));

    // validate
    char *ptr;

    this->year = std::strtol(y.c_str(), &ptr, 10);
    this->month = std::strtol(m.c_str(), &ptr, 10);
    this->day = std::strtol(d.c_str(), &ptr, 10);

    if (this->year <= 1970
        || this->month <= 0 || this->month >= 13
        || this->day <= 0 || this->day >= 31)
        throw (std::runtime_error("invalid date"));
}

Date::Date(const std::string& date_str)
{
    this->parse_date(date_str);
}

bool Date::operator<(const Date& other) const
{
    if (this->year != other.year)
        return (this->year < other.year);
    if (this->month != other.month)
        return (this->month < other.month);
    return (this->day < other.day);
}


int Date::get_year() const { return (this->year); }
int Date::get_month() const { return (this->month); }
int Date::get_day() const { return (this->day); }


std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << date.get_year() << "-" << date.get_month() << "-" << date.get_day();
    return (os);
}
