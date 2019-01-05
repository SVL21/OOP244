#include <fstream>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "OnShelf.h"
namespace ict {
	OnShelf::OnShelf() : Good("", "", 0, 1, true) 
	{
		recTag_ = 'O';
	}

	OnShelf::OnShelf(char filetag_) : Good("", "", 0, 1, true)
	{
		if (filetag_ == 'C' || filetag_ == 'O')
			
			recTag_ = filetag_;

	}

	std::fstream & OnShelf::store(std::fstream & file, bool addNewLine) const
	{

		file << recTag_ << "," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity() << "," << qtyNeeded();

		if (addNewLine = true)
		{
			file << std::endl;
		}
		return file;

	}
	std::fstream & OnShelf::load(std::fstream & file)
	{
		char sk2[MAX_SKU_LEN +1];
		char n2[MAX_LEN];
		double p2;
		bool t2;
		int qty2;
		int qN2;

		file.getline(sk2, MAX_SKU_LEN + 1, ','); //getline (char* s, streamsize n, char delim );
		file.getline(n2, MAX_LEN, ',');
		file >> p2;
		file.ignore();
		file >> t2;
		file.ignore();
		file >> qty2;
		file.ignore();
		file >> qN2;
		file.ignore();


		sku(sk2);
		name(n2);
		price(p2);
		taxed(t2);
		quantity(qty2);
		qtyNeeded(qN2);

		return file;

	}
	std::ostream & OnShelf::display(std::ostream & os, bool linear) const
	{
		if (err_.isClear() ==false)
		{
			os << err_.message();
		}
		else if (linear == true)
		{
			os << std::setfill(' ') << std::left << std::setw(MAX_SKU_LEN) << sku() << '|' << std::setw(20)
				<< name() << '|' << std::right << std::setw(7) << std::fixed << std::setprecision(2) << cost() << '|';
			if (taxed() == true)
			{
				os << " t |";
			}
			else
			{
				os << "   |";
			}

			os << std::setw(4) << quantity() << '|' << std::setw(4) << qtyNeeded() << '|' << std::endl;

		}
		else {
			os << "sku: " << sku() << std::endl
				<< "Name: " << name() << std::endl
				<< "Price: " << price() << std::endl;
			if (taxed() == true)
			{
				os << "Price after tax: " << ((TAX * price()) + price()) << std::endl;
			}
			else
			{
				os << "Price after tax: N/A" << std::endl;
			}
			os << "Quantity on Hand: " << quantity() << std::endl
				<< "Quantity Needed: " << qtyNeeded();
		}
		return os;
	}

	std::istream& OnShelf::conInput(std::istream& istr)
	{
		char sk2[MAX_SKU_LEN + 1];
		char n2[MAX_LEN];
		char t2;
		double p2;
		int qty2;
		int qN2;



		if (istr.fail() == false)
		{
			err_.clear();
			std::cout << "SKU: ";
			istr >> sk2;
			if (istr.fail() == false)
			{
				sku(sk2);
			}

			std::cout << "Name: ";
			istr >> n2;
			if (istr.fail() == false)
			{
				name(n2);
			}

			std::cout << "Price: ";
			istr >> p2;
			if (istr.fail())
			{
				err_.message("Invalid Price Entry");
			}
			else
			{
				price(p2);
			}

			if (err_.isClear())
			{

				{
					std::cout << "Taxed: ";
					istr >> t2;
					if (t2 == 'Y' || t2 == 'y')
					{
						taxed(true);
					}
					else if (t2 == 'N' || t2 == 'n')
					{
						taxed(false);
					}
					else
					{
						err_.message("Only (Y)es or (N)o are acceptable");
						istr.setstate(std::ios::failbit);
					}
				}

				if (err_.isClear())
				{
					std::cout << "Quantity On Hand: ";
					istr >> qty2;
					if (istr.fail())
					{
						err_.message("Invalid Quantity Entry");
					}
					else
					{
						quantity(qty2);
					}
				}

				if (err_.isClear())
				{
					std::cout << "Quantity Needed: ";
					istr >> qN2;
					if (istr.fail())
					{
						err_.message("Invalid Quantity Needed Entry");
					}
					else
					{
						qtyNeeded(qN2);
					}
				}

			}

			return istr;
		}

	}

}