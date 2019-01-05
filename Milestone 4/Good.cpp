#include <cstring>
#include <iostream>
#include "wpgeneral.h"
#include "Good.h"

namespace ict{

	Good::Good()
	{
		sku_[0] = '\0';
		name_ = nullptr;
		price_ = 0;
		taxed_ = false;
		quantity_ = 0;
		qtyNeeded_ = 0;
	}
	Good::Good(const char* a, const char* b, double c, int d, bool e)
	{
		sku(a);
		name(b);
		price(c);
		qtyNeeded(d);
		taxed(e);
	}

	Good::Good(const Good& A)
	{
		operator=(A);
		
	}

	Good & Good::operator=(const Good & A)
	{
		if (this != &A)
		{
			sku(A.sku_);
			name(A.name_);
			price(A.price_);
			taxed(A.taxed_);
			quantity(A.quantity_);
			qtyNeeded(A.qtyNeeded_);
		}
		return *this;

	}


	Good::~Good()
	{
		if (name_ != nullptr)
		{
			delete name_;
		}
	}
	
	void Good::sku(const char* sku)
	{
		strncpy(sku_, sku, MAX_SKU_LEN +1);
	}
	void Good::name(const char *_name)
	{
		name_= new char[strlen(_name) + 1];
		if (name_ != nullptr)
		{
			strncpy(name_, _name, (strlen(_name) + 1));
		}
	}
	void Good::price(double price)
	{
		price_ = price;
	}
	void Good::taxed(bool tax)
	{
		taxed_ = tax;
	}
	void Good::quantity(int quantity)
	{
		quantity_ = quantity;
	}
	void Good::qtyNeeded(int qtyNeeded)
	{
		qtyNeeded_ = qtyNeeded;
	}
	const char * Good::sku() const
	{
		return sku_;
	}
	const char * Good::name() const
	{
		return name_;
	}

	double Good::price()const
	{
		return price_;
	}

	bool Good::taxed()const
	{
		return taxed_;
	}

	int Good::quantity()const
	{
		return quantity_;
	}
	int Good::qtyNeeded() const
	{
		return qtyNeeded_;
	}
	double Good::cost() const
	{
		double cost = price_;
		if (taxed_)
		{
			cost = (cost * TAX) + cost;
		}

		return cost;
	}
	bool Good::operator==(const char * A)
	{
		if (strcmp(A, sku_) == 0)
		{
			return true;
		}
		else
			return false;
	}
	int Good::operator+=(int A)
	{
		return quantity_ += A;
	}
	double operator+=(double& A, const ict::Good& B)
	{
		A += (B.cost() * B.quantity());
		return A;
	}
}

std::ostream & operator<<(std::ostream & os, const ict::Good & A)
{
	return A.display(os, true);
}

std::istream & operator >> (std::istream & is, ict::Good & B)
{
	return B.conInput(is);
}
