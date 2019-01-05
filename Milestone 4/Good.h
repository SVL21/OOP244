#ifndef ICT_GOOD_H__
#define ICT_GOOD_H__
#include "ReadWritable.h"
#include "wpgeneral.h"

namespace ict{
	class Good : public ReadWritable {
		char sku_[MAX_SKU_LEN+1];
		char* name_;
		double price_;
		bool taxed_;
		int quantity_;
		int qtyNeeded_;

	public:
		Good();
		Good(const char* a, const char* b, double c, int d, bool e = true);
		Good(const Good& A);
		Good& operator=(const Good& A);
		virtual ~Good();
		
		//setter
		void sku(const char*);
		void name(const char*);
		void price(double);
		void taxed(bool);
		void quantity(int);
		void qtyNeeded(int);
		
		//getter
		const char* sku()const;
		const char* name() const;
		double price()const;
		bool taxed()const;
		int quantity()const;
		int qtyNeeded()const;
		double cost()const;

		bool operator==(const char*);
		int operator+=(int);

	};
	double operator+=(double&, const Good&);

}

std::ostream & operator<<(std::ostream & os, const ict::Good & A);
std::istream & operator>>(std::istream & is, ict::Good & B);


#endif