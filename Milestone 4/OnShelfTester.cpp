// Final Project Milestone 4
// OnShelf Tester program
// File OnShelfTester.cpp
// Version 1.0
// Date 2016/11/16
// Author Fardad Soleimanloo
//
/////////////////////////////////////////////////////////////////
#include "OnShelf.h"
using namespace ict;
using namespace std;
#define FileName "filetest.txt"
void piv(const char* upc, const char* name, const char* price = "", const char* taxed = "", const char* qty = "", const char* qtyNd = "", const char* date = ""){
  cout
    << "Enter the following: " << endl
    << "Sku: " << upc << endl
    << "Name: " << name << endl;
  if (price[0]) cout << "Price: " << price << endl;
  if (taxed[0]) cout << "Taxed: " << taxed << endl;
  if (qty[0]) cout << "Quantity on hand: " << qty << endl;
  if (qtyNd[0]) cout << "Quantity needed: " << qtyNd << endl;
  if (date[0]) cout << "Delivery date: " << date << endl;
  cout << endl;
}
void dumpFile(const char* fname){
  ifstream f(fname);
  char ch;
  while (!f.get(ch).fail()){
    cout.put(ch);
  }
  f.clear();
  f.close();
}
void _pause(){
  cout << "****press enter to continue...";
  cin.ignore(1000, '\n');
}

int main(){
  fstream onShfile(FileName, ios::out);
  OnShelf onSh;
  bool ok = true;
  int i;
  cout << "--OnShelf test:" << endl;
  cout << "----Price validation test:" << endl;
  piv("abc", "abc", "abc");
  cin >> onSh;
  if (cin.fail()){
    cin.clear();
    cin.ignore(2000, '\n');
    cout << "Passed " << onSh << endl;
  }
  else{
    ok = false;
    cout << "Price validation failed" << endl;
  }
  _pause();
  if (ok){
    cout << "----Taxed validation test:" << endl;
    piv("abc", "abc", "10", "abc");
    cin >> onSh;
    if (cin.fail()){
      cin.clear();
      cin.ignore(2000, '\n');
      cout << "Passed " << onSh << endl;
    }
    else{
      ok = false;
      cout << "Quantity validaton failed" << endl;
    }
  }
  _pause();
  if (ok){
    cout << "----Quantity validation test:" << endl;
    piv("abc", "abc", "10", "y", "abc");
    cin >> onSh;
    if (cin.fail()){
      cin.clear();
      cin.ignore(2000, '\n');
      cout << "Passed " << onSh << endl;
    }
    else{
      ok = false;
      cout << "Quantity validaton failed" << endl;
    }
  }
  _pause();
  if (ok){
    cout << "----Quantity Needed validation test:" << endl;
    piv("abc", "abc", "10", "n", "10", "abc");
    cin >> onSh;
    if (cin.fail()){
      cin.clear();
      cin.ignore(2000, '\n');
      cout << "Passed " << onSh << endl;
    }
    else{
      ok = false;
      cout << "Quantity Needed validaton failed" << endl;
    }
  }
  _pause();
  if (ok){
    cout << "----Display test, the output of the Program and yours must match:" << endl;
    piv("1234", "Box", "123.45", "y", "1", "5");
    cin >> onSh;
    cin.ignore(1000, '\n');
    cout << "--Linear------------" << endl;
    cout << "Program: 1234|Box                 | 139.50| t |   1|   5|" << endl;
    cout << "  Yours: " << onSh << endl;
    cout << "--Form Display------" << endl;
    cout << "--Program: " << endl;
    cout << "upc: 1234" << endl;
    cout << "name: Box" << endl;
    cout << "price: 123.45" << endl;
    cout << "Price after tax: 139.50" << endl;
    cout << "Quantity On Hand: 1" << endl;
    cout << "Quantity Needed: 5" << endl;
    cout << "--Yours: " << endl;
    onSh.display(cout, false) << endl;
  }
  _pause();
  if (ok){
    cout << "----Storage and loading test, the output of the Program and yours must match:" << endl;
    OnShelf tonSh;
    onSh.taxed(false);
    onSh.store(onShfile);
    onSh.store(onShfile);
    onShfile.close();
    cout << "--Store OnShelf, program: " << endl
      << "O,1234,Box,123.45,0,1,5" << endl
      << "O,1234,Box,123.45,0,1,5" << endl;
    cout << "--Store OnShelf, yours: " << endl;
    dumpFile(FileName);
    cout << "--Load OnShelf: " << endl;
    onShfile.open(FileName, ios::in);
    onShfile.ignore(2);
    tonSh.load(onShfile);
    cout << "Program: 1234|Box                 | 123.45|   |   1|   5|" << endl;
    cout << "  Yours: " << tonSh << endl;
    onShfile.clear();
    onShfile.close();
  }
  return 0;
}