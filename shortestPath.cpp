#include <iostream>
#include <fstream>
#include <stack>
#include "city.h"
#include "graph.h"


int main(int num_args, char* arg[])
{
  cityInfo cities; //create array of cities 
  ifstream input("city.txt");
  if(!input.is_open()){
    cout << "Error, file not found!";
    return 1;
  }
  
  if(num_args < 3) // if there is less than 3 arguments (a.out, fromCity, toCity)  then exit with error
    {
      exit(-1);
    }
 
  unsigned currentSize = 0;
  cities.collect_data(input, currentSize); //fill cities array
  int orig_cityID = cities.getID(currentSize, arg[1]); // if equal to -1, then invalid 
  int dest_cityID = cities.getID(currentSize, arg[2]); //set id values by calling getID
  if(orig_cityID == -1){ //check if argument 1 is valid
    cout << "Invalid city code: " << arg[1];
    return -1;
  }
  if(dest_cityID == -1){ //check if arugment 2 is invalid
    cout << "Invalid city code: " << arg[2];
    return -1;
  }
  
  
  string orig_cityName = cities.getName(currentSize, arg[1]); //set city names by calling getName
  string dest_cityName = cities.getName(currentSize, arg[2]);

  //populate graph
  graph g(20); //change to currentSize

  ifstream fin;
  fin.open("road.txt");
  int v, u, w;    // vertex, neighbor, weight

  if(!fin)
    cout << "road.txt doesn't exist" << endl;
  else
    {
      fin >> v >> u >> w;
      while(fin)
        {
          g.addEdge(v, u, w);
          fin >> v >> u >> w;
        }
    }

  fin.close();

  int distance;
  stack<int> r; //create stack to pass through to dijkstras
  
  distance = g.DijkstraShortestPath(orig_cityID, dest_cityID, r);

  cout << "Description : Program to find the shortest route between cities" << endl;
  cout << "----------------------------------------------------------------" << endl;
  cout << "From " << cities.getCityData(orig_cityID) << endl; //cities[orig_cityID]
  cout << "To " << cities.getCityData(dest_cityID) << endl;

  if(distance > 0){
    cout << "The shortest distance from " << orig_cityName << " to " << dest_cityName << " is " << distance << endl;
    cout << "through the route\n";
    while(!r.empty()){ //while stack is not empty, output city names
      int temp = r.top(); 
      string tempName = cities.getNameFromID(currentSize, temp); //call getNameFromID to get names from stack 
      cout << tempName << "->"; 
      r.pop();
    }
    
  }
  else{
    cout << "No route from " << orig_cityName << " to " << dest_cityName << endl;
  }
  return 0;
}
