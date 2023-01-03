#ifndef CITY_H
#define CITY_H
#include <list>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

// Using trailing "_" (underscore) to indicate member variable

struct cityData{
  int id_;
  string code_;
  string name_;
  unsigned int population_;
  int elevation_;
  };

class cityInfo
{
cityData curCity[20];

public:
  friend ostream& operator<<(ostream& os, const cityInfo & city);
  void collect_data(istream& input, unsigned& n);
  int getID(unsigned n, const string& s);
  string getName(unsigned n, const string& s);
  string getNameFromID(unsigned n, const int& s);
  cityData getCityData(int i) {return curCity[i];}
};

//This function outputs info abou the given city
ostream& operator<<(ostream& os, const cityData city)
{
  os << "City: " << city.name_ << ", "
     << "population " << city.population_ << ", "
     << "elevation " << city.elevation_;
  return os;
}


//this function collects all of the data from the input file and stores it in an array of cityInfo structs
void cityInfo::collect_data(istream& input, unsigned& n){
  while(!input.eof()){
    input >> curCity[n].id_;
    input >> curCity[n].code_;
    input >> curCity[n].name_;
    input >> curCity[n].population_;
    input >> curCity[n].elevation_;
    n++;
  }
}


//This function returns the cities ID(int) which is neccessary for dijkstras start and end parameters
int cityInfo::getID(unsigned n, const string& s){
  bool found = false; 
  double returnValue;
  int pos;
  for(int i = 0; i < n && !found; i++){ 
    if(curCity[i].code_ == s){
      found = true;
      pos = i;
      returnValue = curCity[pos].id_;
    }
  }

 if(found){ //if a match was found return the corresponding value
   return returnValue;
 } 
 else { //if no match was found return -1
   return -1;
 }
}

//This function gets the cities name(string) from it's city code(2 letter string)
string cityInfo::getName(unsigned n, const string& s){ 
  bool found = false; 
  string returnValue = "";
  int pos;
  for(int i = 0; i < n && !found; i++){ 
    if(curCity[i].code_ == s){
      found = true;
      pos = i;
      returnValue = curCity[pos].name_;
    }
  }

  return returnValue;
}



//This function returns the citys name(string) from its id(int)
string cityInfo::getNameFromID(unsigned n, const int& s){ 
  bool found = false; 
  string returnValue = "";
  int pos;
  for(int i = 0; i < n && !found; i++){ 
    if(curCity[i].id_ == s){
      found = true;
      pos = i;
      returnValue = curCity[pos].name_;
    }
  }

  return returnValue;
}

#endif