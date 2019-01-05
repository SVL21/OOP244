#include "OnShelf.h"
#include "CustomMade.h"
#include <iomanip>

namespace ict {
	CustomMade::CustomMade() : OnShelf('C')
	{
		
	}
	void CustomMade::delivery(const Date & value)
	{
		delivery_ = value;

	}
	const Date & CustomMade::delivery() const
	{
		return delivery_;
	}
	std::fstream & CustomMade::store(std::fstream & file, bool addNewLine) const
	{
		OnShelf::store(file, false);
		file << ",";
		delivery_.write(file);

		if (addNewLine) 
		{
			file << std::endl;
		}
		
		return file;
	}
	std::fstream & CustomMade::load(std::fstream & file)
	{
		OnShelf::load(file);
		file.ignore();
		delivery_.read(file);
		return file;

	}

	std::ostream& CustomMade::display(std::ostream& os, bool linear)const
	{
		if (err_.isClear() == false)
		{
			os << err_.message();
		}
		else if (linear == true) {
			os << std::setfill(' ') << std::left << std::setw(MAX_SKU_LEN) << sku()
				<< '|' << std::setw(20) << name() << '|' << std::right << std::setw(7)
				<< std::fixed << std::setprecision(2) << price() << '|';
			if (taxed())
			{
				os << " t |";
			}
			else
			{
				os << "   |";
			}
			os << std::setw(4) << quantity() << '|' << std::setw(4) << qtyNeeded() << '|' << delivery();
		}
		else {
			os << "Sku: " << sku() << std::endl
				<< "Name: " << name() << std::endl
				<< "Price: " << price() << std::endl;
			if (taxed() == true)
			{
				os << "Price after tax: " << (TAX *price()) + price() << std::endl;  
			}
			else
			{
				os << "Price after tax: N/A" << std::endl;
			}
			os << "Quantity On Hand: " << quantity() << std::endl
				<< "Quantity Needed: " << qtyNeeded() << std::endl
				<< "delivery date: " << delivery(); 

		}
	return os;
	}

	std::istream& CustomMade::conInput(std::istream& istr) 
	{
		OnShelf::conInput(istr);
		if (err_.isClear())
		{
			std::cout << "delivery date (YYYY/MM/DD) : ";

			Date D;
			istr >> D;

			if (D.errCode() == CIN_FAILED) 
			{
				err_.message("Invalid Date Entry");
				istr.setstate(std::ios::failbit);
			}
			else if (D.errCode() == YEAR_ERROR)
			{
				err_.message("Invalid Year in Date Entry");
				istr.setstate(std::ios::failbit);
			}
			else if (D.errCode() == MON_ERROR)
			{
				err_.message("Invalid Month in Date Entry");
				istr.setstate(std::ios::failbit);
			}
			else if (D.errCode() == DAY_ERROR) 
			{
				err_.message("Invalid Day in Date Entry");
				istr.setstate(std::ios::failbit);
			}
			else 
			{
				delivery(D);
			}
		}

		return istr;
	}
}
