#include <iostream>
#include "Account.hpp"

int Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

int	Account::getNbAccounts( void )
{
    return (Account::_nbAccounts);
}

int	Account::getTotalAmount( void )
{
    return (Account::_totalAmount);
}

int	Account::getNbDeposits( void )
{
    return (Account::_totalNbDeposits);
}

int	Account::getNbWithdrawals( void )
{
    return (Account::_totalNbWithdrawals);
}

void	Account::displayAccountsInfos( void )
{
    Account::_displayTimestamp();
    std::cout << " accounts:" << Account::_nbAccounts << ";"
              << "total:" << Account::_totalAmount << ";"
              << "deposits:" << Account::_totalNbDeposits << ";"
              << "withdrawals:" << Account::_totalNbWithdrawals << std::endl;
}


Account::Account( int initial_deposit )
    : _accountIndex(Account::_nbAccounts), _amount(initial_deposit),
      _nbDeposits(0), _nbWithdrawals(0)
{
    Account::_nbAccounts++;
    Account::_totalAmount += initial_deposit;

    Account::_displayTimestamp();
    std::cout << " index:" << this->_accountIndex << ";"
              << "amount:" << this->_amount << ";"
              << "created" << std::endl;
}

Account::~Account( void )
{
    Account::_displayTimestamp();
    std::cout << " index:" << this->_accountIndex << ";"
              << "amount:" << this->_amount << ";"
              << "closed" << std::endl;
}


void	Account::makeDeposit( int deposit )
{
    Account::_totalAmount += deposit;
    Account::_totalNbDeposits++;

    int prev_amount = this->_amount;
    this->_amount += deposit;
    this->_nbDeposits++;

    Account::_displayTimestamp();
    std::cout << " index:" << this->_accountIndex << ";"
              << "p_amount:" << prev_amount << ";"
              << "deposit:" << deposit << ";"
              << "amount:" << this->_amount << ";"
              << "nb_deposits:" << this->_nbDeposits << std::endl;
}

bool	Account::makeWithdrawal( int withdrawal )
{
    int prev_amount = this->_amount;

    if (this->_amount >= withdrawal)
    {
        Account::_totalAmount -= withdrawal;
        Account::_totalNbWithdrawals++;
    
        this->_amount -= withdrawal;
        this->_nbWithdrawals++;

        Account::_displayTimestamp();
        std::cout << " index:" << this->_accountIndex << ";"
                << "p_amount:" << prev_amount << ";"
                << "withdrawal:" << withdrawal << ";"
                << "amount:" << this->_amount << ";"
                << "nb_withdrawals:" << this->_nbWithdrawals << std::endl;
    }
    else
    {
        Account::_displayTimestamp();
        std::cout << " index:" << this->_accountIndex << ";"
                << "p_amount:" << prev_amount << ";"
                << "withdrawal:" << "refused" << std::endl;
    }
    return (false);
}

int		Account::checkAmount( void ) const
{
    return (this->_amount);
}

void	Account::displayStatus( void ) const
{
    Account::_displayTimestamp();
    std::cout << " index:" << this->_accountIndex << ";"
              << "amount:" << this->_amount << ";"
              << "deposits:" << this->_nbDeposits << ";"
              << "withdrawals:" << this->_nbWithdrawals << std::endl;
}


void	Account::_displayTimestamp( void )
{
    std::cout << "[19920104_091532]";
}
