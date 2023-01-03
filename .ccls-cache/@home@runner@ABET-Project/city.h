#ifndef CITY_H
#define CITY_H

#include <list>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

// Using trailing "_" (underscore) to indicate member variable
struct cityInfo
{
  string code_;
  string name_;
  unsigned int population_;
  int elevation_;
};

ostream& operator<<(ostream& os, const cityInfo & city)
{
  os << "City: " << city.name_ << ", "
     << "population " << city.population_ << ", "
     << "elevation " << city.elevation_;
  return os;
}

class cityDBase
{
   const static int MAX_CITIES = 20;

public:
  cityDBase(const char *input_file)
  {
    num_ = 0;

    ifstream fin;
    fin.open(input_file);

    if(!fin)
      cout << input_file << " doesn't exist" << endl;
    else
      {
        int id;
        cityInfo city;
        fin >> id >> city.code_ >> city.name_ >> city.population_ >> city.elevation_;
        while(fin && num_ < MAX_CITIES)
          {
            num_++;
            
            cities_[id] = city;
            fin >> id >> city.code_ >> city.name_ >> city.population_ >> city.elevation_;
          }
      }

    fin.close();
  }

  cityDBase() : cityDBase("city.txt") {};

  ~cityDBase() {};

  int id(string city_code) //takes city code and returns index
  {
    int i = 0;
    while(i < num_)
      {
        if(city_code.compare(cities_[i].code_) == 0) //not sure how .compare works
          {
            return i;
          }
        i++;
      }
    return -1;
  }

  const cityInfo * city(int id)
  {
    if(id < num_)
      return &cities_[id];

    return NULL;
  }

  void city_codes(list<string> & codes)  
  {
    for(int i = 0; i < num_; i++)
      {
        codes.push_back(cities_[i].code_);
      }
  }

  const char * city_name(int id)
  {
    if(id < num_)
      return cities_[id].name_.c_str();

    return NULL;
  }

  int size () const
  {
     return num_;
  }

private:
  int num_; //current number of entries
  //array of cities, the index is the city Id/VERFEX
  cityInfo cities_[MAX_CITIES];
};

#endif
