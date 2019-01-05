#ifndef Onshelf_H_
#define Onshelf_H_
#include "Good.h"
#include "Error.h"
namespace ict {
	class OnShelf :public Good {
	private:
		char recTag_;
	protected:
		Error err_;
	public:
		OnShelf();
		OnShelf(char filetag_);
		
		std::fstream& store(std::fstream& file, bool addNewLine = true)const;
		std::fstream& load(std::fstream& file);
		std::ostream& display(std::ostream& os, bool linear)const;
		std::istream& conInput(std::istream& istr);
	};
}
#endif