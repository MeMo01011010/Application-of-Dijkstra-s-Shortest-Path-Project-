#include <iostream>
#include <fstream>

#include "city.h"
#include "graph.h"

void usage(const char *prog, const list<string> & codes)
{
  cout << endl;
  cout << prog << " ORIGINATION-CODE DESTINATION-CODE" << endl;
  cout << "    ORIGINATION-CODE - the 2 characters originating city code" << endl;
  cout << "    DESTINATION-CODE - the 2 characters destination city code" << endl;
  cout << "Valid codes:" << endl;
  for (auto itr = codes.begin(); itr != codes.end(); itr++)
  {
     cout << *itr << " ";
  }
  cout << endl;
}

int main(int argc, char** argv) //she has it as   char* arg[]    in her example
{
  cityDBase cities;

  if(argc < 3) // if there is less than 3 arguments (a.out, fromCity, toCity)  then exit with error
    {
      list<string> codes;
      cities.city_codes(codes);
      usage(argv[0], codes);
      exit(-1);
    }

  string orig_code = argv[1];
  string dest_code = argv[2];

  int orig_id = cities.id(orig_code); //calling .id to return index from orig_code
  if(orig_id < 0)
    {
      cout << "Invalid originating city code " << orig_code << endl;
      exit(-1);
    }

  int dest_id = cities.id(dest_code);
  if(dest_id < 0)
    {
      cout << "Invalid destinating city code " << dest_code << endl;
      exit(-1);
    }

  const cityInfo * orig_city = cities.city(orig_id);
  const cityInfo * dest_city = cities.city(dest_id);
  //populate graph
  graph g(cities.size());

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
  list<int> route;
  distance = g.DijkstraShortestPath(orig_id, dest_id, route);

  /// fixme
  cout << "Author: xxxxxx and xxxxxxx" << endl;
  cout << "Date: xx/xx/20xx" << endl;

  cout << "Course: CS311 (Data structures and Algorithms)" << endl;
  cout << "Description : Program to find the shortest route between cities" << endl;
  cout << "----------------------------------------------------------------" << endl;
  cout << "From " << *orig_city << endl;
  cout << "To " << *dest_city << endl;

  if(distance > 0)
    {
      cout << "The shortest distance from " << orig_city->name_ <<
              " to " << dest_city->name_ << " is " << distance << endl;
      cout << "through the route:" << endl;
      for(auto itr = route.begin(); itr != route.end(); itr++)
        {
          if(itr != route.begin())
            cout << "->";
          cout << cities.city_name(*itr);
        }
      cout << endl;
    }
  else
    {
      cout << "No route from " << orig_city->name_ << " to " << dest_city->name_ << endl;
    }

  return 0;
}
