#include <iostream>
#include <iomanip>
#include <cstring>
#include "Error.h"
namespace ict {

	Error::Error()
	{
		message_ = nullptr;
	}

	Error::Error(const char* Error)
	{
		message_ = nullptr;
		message(Error);

	}

	Error& Error:: operator=(const char* errorMessage)
	{
		clear();
		message(errorMessage);

		return *this;

	}

	Error::~Error()
	{
		delete[] message_;
		message_ = nullptr;
	}

	void Error::clear()
	{
		delete[] message_;
		message_ = nullptr;
	}

	bool Error::isClear() const
	{
		return message_ == nullptr;
	}

	void Error::message(const char* value)
	{
		delete message_;
		message_ = new char[strlen(value) + 1];
		for (unsigned int i = 0; i < strlen(value) + 1; i++)
		{
			message_[i] = value[i];
		}
	}

	const char* Error::message()const
	{
		return message_;
	}

	std::ostream& operator<<(std::ostream& os, const Error& A)
	{
		if (!(A.isClear()))
		{
			return os << A.message();
		}
		return os;

	}
}