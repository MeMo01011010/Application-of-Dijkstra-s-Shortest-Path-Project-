/****************************
Templated created by Kazumi Slott
CS311

Your name: ???
Your programmer number: ???
Hours spent: ???
Any difficulties?:
*****************************/
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <string>

#include "minHeap-graph.h"

using namespace std;

//I decided to make this function a stand alone function.
//It doesn't have anything to do with the graph class.
template<class T>
void displayQueue(queue<T>& q)
{
  while(!q.empty())
    {
      cout << q.front() << ",";
      q.pop();
    }
  cout << endl;
}

//Provide function for consistent format
void formatEdge(int v1, int v2, queue<string> &q)
{
  q.push(to_string(v1) + "->" + to_string(v2));
}

//dijkstra's algorithm calculates the shortest distance from start to every other vertex
//This stand alone function shows the shortest path from start to destination in the following format.
//  The shortest path from 3 to 5 is 3 0 4 5
//  The distance is 8
void showShortestDistance(int* curDist, int* predecessor, int start)
{
  int dest; //destination

  cout << "Enter the destination: ";
  cin >> dest;

  //trace the shortest path from dest back to start
  int u = dest;
  string path;
  path = to_string(u);
  while(predecessor[u] != start && predecessor[u] != -1)
    {
      path.insert(0, " ");
      path.insert(0, to_string(predecessor[u]));
      u = predecessor[u];
    }
  path.insert(0, " ");
  path.insert(0, to_string(start));

  cout << "The shortest path from " << start << " to " << dest << " is " << path;
  cout << "\nThe distance is " << curDist[dest] << endl;
}

class edge
{
  friend class graph;
  int neighbor; //adjacent vertex
  int wt; //weight of the edge
 public:
  edge() { neighbor = -999, wt = -999;};
  edge(int u, int w)
  {
    neighbor = u;
    wt = w;
  }
};

class graph
{
  int num_ver; //the total number of vertices in the graph
  //pointer to the dynamic array that holds linked lists.
  //The element of a node in a linked list is a pointer to an edge object
  list<edge*>* ver_ar;
  void DFT_helper(int v, int& i, int* num, queue<string>& q);

 public:
  graph(int V);
  ~graph();
  //If the weight is not given, 1 is used for wt.
  void addEdge(int v, int u, int w=1);
  void BFT(int start);
  void DFT(int start);
  //return 0 or distance from start to end
  int DijkstraShortestPath(int start, int end, stack<int>& s);
};

//constructor: num is the number of vertices
graph::graph(int num)
{
  //make a dynamic array with num slots where each slot holds a list object.
  //The element of a node in the linked list is a pointer to an edge object
  num_ver = num;
  ver_ar = new list<edge*>[num];
}

graph::~graph()
{
  for(int v = 0; v < num_ver; v++)
    {
      while(!ver_ar[v].empty())
        {
          delete ver_ar[v].front();
          ver_ar[v].pop_front();
        }
    }
  delete [] ver_ar;
}


//add an edge from v to u with weight w into the graph
void graph::addEdge(int v, int u, int w)
{
  ver_ar[v].push_back(new edge(u, w));
}

void graph::DFT_helper(int v, int& i, int* num, queue<string>& q)
{
  num[v] = i++;
  cout << v << " ";
  for(auto u = ver_ar[v].begin(); u != ver_ar[v].end(); u++)
    {
      if (num[(*u)->neighbor] == 0)
        {
          formatEdge(v, (*u)->neighbor, q);
          DFT_helper((*u)->neighbor, i, num, q);
        }
    }
}

//start Traversal at start
void graph::DFT(int start)
{
  queue<string> q_str;
  int num[num_ver];
  for(int u = 0; u < num_ver; u++)
     num[u] = 0;

  int i = 1;
  for(int v = start; v < num_ver; v++)
    {
      if(num[v] != 0) continue;
      DFT_helper(v, i, num, q_str);
    }
  displayQueue<string>(q_str);
}

//start is the index for the start vertex
void graph::BFT(int start)
{
  queue<string> q_str;
  int num[num_ver];
  for(int u = 0; u < num_ver; u++)
     num[u] = 0;

  int i = 1;
  for(int s = start; s < num_ver; s++)
    {
      if(num[s] != 0) continue;
      queue<int> q;
      num[s] = i++;
      q.push(s);

      while(!q.empty())
        {
          // Dequeue a vertex from queue and print it
          int v = q.front();
          cout << v << " ";
          q.pop();

          for(auto u = ver_ar[v].begin(); u != ver_ar[v].end(); u++)
            {
              if (num[(*u)->neighbor] == 0)
                {
                  num[(*u)->neighbor] = i++;
                  q.push((*u)->neighbor);
                  formatEdge(v, (*u)->neighbor, q_str);
                }
            }
        }
    }
  displayQueue<string>(q_str);
}

//Dijkstra's shortest path.
//This function will generate a table that contains the shortest distance from
//start to every other vertex and the predecessor of each vertex.
int graph::DijkstraShortestPath(int start, int end, stack<int>& s)
{
  minHeap<int> toBeChecked(num_ver);
  int * curDist = new int[num_ver];
  int * predecessor = new int[num_ver];
  int * locator = new int[num_ver];

  for(int i = 0; i < num_ver; i++)
    {
      curDist[i] = 999;
      predecessor[i] = -1;
      locator[i] = i;
    }

  //Must set this before insert
  curDist[start] = 0;
  //insert all vetices into toBeChecked heap: [0, 1, 2, 3, 4, ...]
  //the numbers are vertex numbers
  for(int i = 0; i < num_ver; i++)
    {
      toBeChecked.insert(curDist, locator, i);
    }

  while(toBeChecked.getNum())    // while not empty
    {
      int v;
      v = toBeChecked.getMin(curDist, locator);
      if(v < 0)
        {
           cout << "getMin() return " << v << endl;
           return 0;
        }

      //for all vertices u which are adjacent to v and also in toBeChecked
      for(auto u = ver_ar[v].begin(); u != ver_ar[v].end(); u++)
        {
           int u_index = toBeChecked.find((*u)->neighbor);
           if (u_index >= 0 && u_index < num_ver)
             {
               if(curDist[(*u)->neighbor] > curDist[v] + (*u)->wt)
                 {
                   curDist[(*u)->neighbor] = curDist[v] + (*u)->wt;
                   predecessor[(*u)->neighbor] = v;
                   toBeChecked.fixHeap(curDist, locator, locator[(*u)->neighbor]);
                 }
             }
        }
    }
 




  int i = end;
 // stack<int> s;

  while(i != start){
    s.push(i);
    i = predecessor[i];
  }
  s.push(i);

      /*                                    
  cout << "The shortest path from " << start << " to " << dest << " is ";
  while(!s.empty()){
   // cout << s.pop();
    cout << s.top() << " ";
    s.pop();
  } 
 
  cout << "\nThe distance is " << curDist[dest] << endl;   



  
  //trace the shortest path from end back to start
  int u = end;
  route.push_front(u);
  while(predecessor[u] != start && predecessor[u] != -1)
    {
      route.push_front(predecessor[u]);
      u = predecessor[u];
    }
  route.push_front(start);

  int distance;
  if(route.empty())
    distance = 0;
  else
    distance = curDist[end];
*/
  int distance = curDist[end];
  delete [] curDist;
  delete [] predecessor;
  delete [] locator;

  return distance;
}

#endif
