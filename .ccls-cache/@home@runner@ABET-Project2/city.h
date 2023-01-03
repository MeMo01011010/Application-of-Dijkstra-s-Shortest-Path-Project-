#include <list>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

// Using trailing "_" (underscore) to indicate member variable
struct cityInfo
{
  int id_;
  string code_;
  string name_;
  unsigned int population_;
  int elevation_;
};

//This function outputs info abou the given city
ostream& operator<<(ostream& os, const cityInfo & city)
{
  os << "City: " << city.name_ << ", "
     << "population " << city.population_ << ", "
     << "elevation " << city.elevation_;
  return os;
}


//this function collects all of the data from the input file and stores it in an array of cityInfo structs
void collect_data(istream& input, cityInfo arr[], unsigned& n){
  while(!input.eof()){
    input >> arr[n].id_;
    input >> arr[n].code_;
    input >> arr[n].name_;
    input >> arr[n].population_;
    input >> arr[n].elevation_;
    n++;
  }
}


//This function returns the cities ID(int) which is neccessary for dijkstras start and end parameters
int getID(const cityInfo arr[], unsigned n, const string& s){
  bool found = false; 
  double returnValue;
  int pos;
  for(int i = 0; i < n && !found; i++){ 
    if(arr[i].code_ == s){
      found = true;
      pos = i;
      returnValue = arr[pos].id_;
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
string getName(const cityInfo arr[], unsigned n, const string& s){ 
  bool found = false; 
  string returnValue = "";
  int pos;
  for(int i = 0; i < n && !found; i++){ 
    if(arr[i].code_ == s){
      found = true;
      pos = i;
      returnValue = arr[pos].name_;
    }
  }

  return returnValue;
}



//This function returns the citys name(string) from its id(int)
string getNameFromID(const cityInfo arr[], unsigned n, const int& s){ 
  bool found = false; 
  string returnValue = "";
  int pos;
  for(int i = 0; i < n && !found; i++){ 
    if(arr[i].id_ == s){
      found = true;
      pos = i;
      returnValue = arr[pos].name_;
    }
  }

  return returnValue;
}
