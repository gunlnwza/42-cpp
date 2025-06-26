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


static bool have_three_tokens(const std::string& row, const std::string& delim)
{
    size_t idx;

    idx = row.find(delim);
    if (idx == std::string::npos)
        return (false);
    idx = row.find(delim, idx + delim.length());
    if (idx == std::string::npos)
        return (false);
    idx = row.find(delim, idx + delim.length());
    return (idx == std::string::npos);
}

static void split_three(const std::string& row, const std::string& delim, std::string& left, std::string& mid, std::string& right)
{
    size_t idx[2];
    
    idx[0] = row.find(delim);
    idx[1] = row.find(delim, idx[0] + delim.length());
    left = row.substr(0, idx[0]);
    mid = row.substr(idx[0] + delim.length(), idx[1] - (idx[0] + delim.length()));
    right = row.substr(idx[1] + delim.length());
}

static bool is_leap_year(int year)
{
    if (year % 400 == 0)
        return (true);
    if (year % 100 == 0)
        return (false);
    return (year % 4 == 0);
}

static bool is_valid_date(int year, int month, int day)
{
    const int min_year = 1000;
    const int max_year = 9999;
    const int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int       max_day;

    if (!(min_year <= year && year <= max_year))
        return (false);
    if (!(1 <= month && month <= 12))
        return (false);
    max_day = days_in_month[month - 1];
    if (month == 2 && is_leap_year(year))
        max_day = 29;
    return (1 <= day && day <= max_day);
}

void Date::parse_date(const std::string& date_str)
{
    const std::string delim = "-";
    std::string y, m, d;

    if (!have_three_tokens(date_str, "-"))
        throw (std::runtime_error("invalid date format \"" + date_str + "\""));
    split_three(date_str, delim, y, m, d);

    this->year = parse_int(y);
    this->month = parse_int(m);
    this->day = parse_int(d);
    if (!is_valid_date(this->year, this->month, this->day))
        throw (std::runtime_error("not a valid date \"" + date_str + "\""));
}


bool Date::operator<(const Date& other) const
{
    if (this->year != other.year)
        return (this->year < other.year);
    if (this->month != other.month)
        return (this->month < other.month);
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


std::string Date::get_string() const
{
    std::stringstream ss;

    ss << std::setw(4) << std::setfill('0') << this->get_year() << "-"
       << std::setw(2) << std::setfill('0') << this->get_month() << "-"
       << std::setw(2) << std::setfill('0') << this->get_day();
    return (ss.str());
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << date.get_string();
    return (os);
}
