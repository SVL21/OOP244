// header files go here

#include "Date.h"
#include "wpgeneral.h"
#include <iostream>
#include <iomanip>
#include <cstring>

namespace ict {
	// returns a unique value representing the date
	// this value is used to compare two dates
	int Date::value()const {
		return year_ * 372 + mon_ * 31 + day_;
	}

	// bool validate(), this is an optional private function
	// for validation logic and setting the _readErrorCode.
	// see the read() function description for more details
	void Date::validate()
	{
		if (year_ >= MIN_YEAR && year_ <= MAX_YEAR)
		{
			readErrorCode_ = YEAR_ERROR;
		}
		else if (mon_ >= 1 || mon_ <= 12)
		{
			readErrorCode_ = MON_ERROR;
		}
		else if (day_ >=1 || day_ <= mdays())
		{
			readErrorCode_ = DAY_ERROR;
		}
		else
			readErrorCode_ = NO_ERROR;

	}



	// mdays():
	// returns the day of the month.
	// _mon value must be set for this function to work
	// if _mon is invalid, this function returns -1
	// leap years are considered in this logic
	int Date::mdays()const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
		mon--;
		return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
	}


	// constructors

	Date::Date()
	{
		year_ = 0;
		mon_ = 0;
		day_ = 0;
		readErrorCode_ = NO_ERROR;
	}
	Date::Date(int year, int mon, int day)
	{
		year_ = year;
		mon_ = mon;
		day_ = day;
		readErrorCode_ = NO_ERROR;

	}


	// member functions
	void Date::errCode(int errorCode)
	{
		if (errorCode >= NO_ERROR && errorCode <= DAY_ERROR)
			readErrorCode_ = errorCode;
	}

	bool Date::bad() const
	{
		return errCode() != NO_ERROR;
	}

	int Date::errCode() const
	{
		return readErrorCode_;
	}



	// operators 

	bool Date::operator==(const Date & D) const
	{
		if (this->value() == D.value())
			return true;
		else
			return false;
	}

	bool Date::operator!=(const Date & D) const
	{
		if (this->value() != D.value())
			return true;
		else
			return false;
	}
	bool Date::operator<(const Date& D)const
	{
		if (this->value()< D.value())
			return true;
		else
			return false;
	}

	bool Date::operator>(const Date & D) const
	{
		if (this->value() > D.value())
			return true;
		else
			return false;
	}

	bool Date::operator<=(const Date & D) const
	{
		if (this->value() <= D.value())
			return true;
		else
			return false;
	}

	bool Date::operator>=(const Date & D) const
	{
		if (this->value() >= D.value())
			return true;
		else
			return false;
	}


	// IO functions
	std::istream & Date::read(std::istream & istr)
	{

		if (!(istr.fail()))
		{
			validate();
			
		}
		else 
		{ 
			readErrorCode_ = CIN_FAILED;
		}

		return istr;
	}

	std::ostream& Date::write(std::ostream& ostr) const
	{
		return ostr << std::right << std::setfill('0') << std::setw(2) << year_ << '/' << std::setfill('0') << std::setw(2) << mon_ << '/' << std::setfill('0') << std::setw(2) << day_;
	}
	

	// non-memeber operator overloads

	std::istream & operator >> (std::istream & is, Date & D)
	{
		return D.read(is);
	}

	std::ostream & operator<<(std::ostream & os, const Date & D)
	{
		return D.write(os);
	}


}
