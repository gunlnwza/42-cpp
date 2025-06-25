#include "Date.hpp"


Date::Date() {}

Date::Date(const Date& other) { *this = other; }

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

Date::Date(int year, int month, int day) : year(year), month(month), day(day) {}

Date::Date(const std::string& date_str) { this->parse_date(date_str); }


static bool is_leap_year(int year)
{
    if (year % 400 == 0) return (true);
    if (year % 100 == 0) return (false);
    return (year % 4 == 0);
}

static bool is_valid_date(int year, int month, int day)
{
    const int MIN_YEAR = 1900;
    const int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int       max_day;

    if (year < MIN_YEAR)
        throw (std::runtime_error("invalid date: unsupported historical date"));
    if (!(1 <= month && month <= 12))
        return (false);
    max_day = days_in_month[month - 1];
    if (month == 2 && is_leap_year(year))
        max_day = 29;
    return (1 <= day && day <= max_day);
}

long parse_long(const std::string& s)  // TODO: move to utils
{
    char *ptr;
    long value;

    value = std::strtol(s.c_str(), &ptr, 10);
    if (*ptr != '\0')
        throw (std::runtime_error("invalid date: invalid number(s)"));
    return (value);
}

void Date::parse_date(const std::string& date_str)  // TODO: refactor
{
    const std::string   delimiter = "-";
    std::string         s(date_str);
    size_t              pos;
    std::string         y, m, d;

    for (size_t i = 0; i < 3; i++)  // THIS IS UNNECESSARILY COMPLICATED
    {
        pos = s.find(delimiter);
        switch (i)
        {
            case 0:
                if (pos == std::string::npos)
                    throw (std::runtime_error("invalid date: less than 3 tokens"));
                y = s.substr(0, pos);
                break ;
            case 1:
                if (pos == std::string::npos)
                    throw (std::runtime_error("invalid date: less than 3 tokens"));
                m = s.substr(0, pos);
                break ;
            case 2:
                d = s.substr(0, pos);
                break ;
        }
        s.erase(0, pos + delimiter.length());
    }
    if (pos != std::string::npos)
        throw (std::runtime_error("invalid date: more than 3 tokens"));

    this->year = parse_long(y);
    this->month = parse_long(m);
    this->day = parse_long(d);
    if (!is_valid_date(this->year, this->month, this->day))
        throw (std::runtime_error("invalid date: not a valid date"));
}


bool Date::operator<(const Date& other) const
{
    if (this->year != other.year) return (this->year < other.year);
    if (this->month != other.month) return (this->month < other.month);
    return (this->day < other.day);
}
bool Date::operator<=(const Date& other) const { return (*this < other || *this == other); }
bool Date::operator>(const Date& other) const { return (other < *this); }
bool Date::operator>=(const Date& other) const { return (*this > other || *this == other); }
bool Date::operator==(const Date& other) const { return (this->year == other.year && this->month == other.month && this->day == other.day); }
bool Date::operator!=(const Date& other) const { return (!(*this == other)); }


int Date::get_year() const { return (this->year); }
int Date::get_month() const { return (this->month); }
int Date::get_day() const { return (this->day); }


std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << std::setw(4) << std::setfill('0') << date.get_year() << "-"
       << std::setw(2) << std::setfill('0') << date.get_month() << "-"
       << std::setw(2) << std::setfill('0') << date.get_day();
    return (os);
}
