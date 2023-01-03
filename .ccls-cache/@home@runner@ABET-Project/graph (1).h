/****************************
Templated created by Kazumi Slott
CS311

Your name: William Cassel
Your programmer number: 6
Hours spent: 3.5 on part 1. 10+ on part 2 (I lost track)
Any difficulties?: I ran into quite a few little issues while during part 2 and had to go to the stem center for some help. One of the biggest problems I had was checking if u was present in toBeChecked. I ultimately changed the minHeap find function to bool and used that. 
*****************************/
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <queue>
#include <list>
#include <stack>
#include "minHeap-graph.h"
using namespace std;

class edge
{
  friend class graph;  //You want to access the private members of edge class from graph class
  int neighbor; //adjacent vertex
  int wt; //weight of the edge
 public:
  edge() { neighbor = -999, wt = -999;};
  edge(int u, int w) { this->neighbor = u, this->wt = w;};
};

class graph
{
  int num_ver; //the total number of vertices in the graph
  list<edge*>* ver_ar; //pointer to the dynamic array that holds linked lists. The element of a node in a linked list is a pointer to an edge object 
                       //Let's use the library's list class. It is actually a doubly linked list. 
  int nextUnvisitedNodes(int* num, int start, int s);
  void DFT_helper(int v, int& i, int* num, queue<string>& q);
 public:
  graph(int V);
  ~graph();
  void addEdge(int v, int u, int w=1);  //If the weight is not given, 1 is used for wt.
  void BFT(int start);
  void DFT(int start);
  void DijkstraShortestPath(int start);
};

//constructor: num is the number of vertices
graph::graph(int num)
{
  this->num_ver = num;
  this->ver_ar = new list<edge*>[num];
  //make a dynamic array with num slots where each slot holds a list object. 
  //The element of a node in the linked list is a pointer to an edge object 
}

graph::~graph()
{
  //destroy all the edge objects created in heap                                                                                                        
  //For each vertex in ver_ar
  
  for(list<edge*>::iterator u =ver_ar[0].begin(); u != ver_ar[0].end(); u++){
    delete (*u);
  }
  //    go through each node in the linked list. The element field of each node points to an edge object created with "new". You need to delete these.  

  //The library's list class has a destructor. All nodes belonging to the list will be destroyed by the destructor.
  //https://www.cplusplus.com/reference/list/list/~list/

  //destroy the ver_ar dynamic array
  delete[] ver_ar;
}


//add an edge from v to u with weight w into the graph
void graph::addEdge(int v, int u, int w)
{
  this->ver_ar[v].push_back(new edge(u, w));
  //We are using the list class from the library. Which member function do you need to use to add a node at the end of the list?
  //https://www.cplusplus.com/reference/list/list/
  //Don't create an edge object statically, then it would get destroyed as soon as you leave this function. You need to create an edge object dymamically in heap, which will remain in heap even after you leave this function.. Remember "new" operator returns the memory address of the newly created object.
  //I have one line of code in this function.
}

//I decided to make this function a stand alone function. It doesn't have anything to do with the graph class.                                
template<class T>
void diplayQueue(queue<T>& q)
{
  while(!q.empty())
    {
      cout << q.front() << ",";
      q.pop();
    }
}

//start Traversal at start
void graph::DFT(int start)
{
  //The algorithm is in my lecture notes.
  //I made dynamic array called "num"
  int *num = new int[num_ver];
  //I created a queue object of string data type from the library's queue class to save all the paths.
  queue<string> edges;
  for(int v = 0; v < this->num_ver; v++){
    num[v] = 0;
  }

  int i = 1;
  int tempVer = start;
  do{
    DFT_helper(tempVer, i, num, edges);
    tempVer = nextUnvisitedNodes(num, start, start);
    
  } while(tempVer != -1);
  //I used do-while
  //I am calling nextUnvisitedNodes() to see if there are more unvisited nodes.


  //You could call displayQueue() implemented above to display all the paths. 
  diplayQueue(edges);
  //Don't forget to destroy the dynamic array
  delete[] num;
}

//I made the following function to see if there are still unvisited nodes. Start checking at s, which is the one after the vertext we started last time                       
//num points to an array containing visit numbers. 0 indicates, the vertex hasn't been visited yet.                                           
//s is the vertext right after the vertex we started last time                         
int graph::nextUnvisitedNodes(int* num, int start, int s) 
{ 
  int index = -1;

  //go through the num array to see if you find a vertext with num=0. If so, return the index. If all visited, return -1.

  for(int i =s; i != start; i=(i+1) % this->num_ver){
    if(num[i] == 0){
      index = i;
      return index;
    }
  }
  /*
  for(int i = s; i < num_ver; i++){
    if(num[i] == 0){
      index = i;
      return index;
    }
  }
  */
  return index;
}


void graph::DFT_helper(int v, int& i, int* num, queue<string>& q)
{
  num[v] = i++;
  cout << v << " ";
  
  //The algorithm is in my lecture notes

  //The following shows how to iterate the library's linked list. You use an iterator.
  //https://www.cplusplus.com/reference/list/list/end/ 
  //iterator class is nested inside list class
  for (list<edge*>::iterator u =ver_ar[v].begin(); u != ver_ar[v].end(); u++)
    {
      if(num[(*u)->neighbor] == 0){ // if u's neighbor(adjacent vertice) is 0 then connect it
        q.push(to_string(v) + "->" + to_string((*u)->neighbor));
        DFT_helper((*u)->neighbor, i, num, q);
      }
      //From the example on https://www.cplusplus.com/reference/list/list/end/
      //Notice *u gives you the element of the node pointed to by u. The element is a pointer to an edge object.
      //Between * and -> operator, -> has higher precedence. You need to use () around *u to get the element first.  

      //push each path e.g. 0->1 into q. to_string(int) converts the int to a string. 
      //to_string() is in c++11, so compile with the option. g++ -std=c++11 graphClient.cpp     
    }

  /***********************************************************************************************
   **********************************************************************************************
    Compile with a c++11 option if you are using to_string()
        g++ -std=c++11 graphClient.cpp 
   **********************************************************************************************
   ***********************************************************************************************/
}

//start is the index for the start vertex
void graph::BFT(int start)
{
  int *num = new int[num_ver];
  //The algorithm is in my lecture notes
  for(int i = 0; i < num_ver; i++){
    num[i] = 0;
  }
  //Use the queue class from the library
  queue<int> q;
  //I used another queue of strings to save all the paths. 
  queue<string> edges;
  int v = start;
  int i = 1;
  do{
    num[v] = i++;
    q.push(v);
     while(!q.empty()){
      v = q.front();
      q.pop();
      cout << v << " ";
      for(list<edge*>::iterator u =ver_ar[v].begin(); u != ver_ar[v].end(); u++){  //
      
        if(num[(*u)->neighbor] == 0){
          num[(*u)->neighbor] = i++;
          q.push((*u)->neighbor);
          edges.push(to_string(v) + "->" + to_string((*u)->neighbor)); //
        }
    }  
  } 
      v = nextUnvisitedNodes(num, start, start);
    }while(v != -1);
  //I used do-while to visit all unconnected graphs. Call nextUnvisitedNodes() to check to see if there are more unvisited verteces.

diplayQueue(edges);

  //Check the manual to figure out what member functions of the queue class you need to use.
  // https://www.cplusplus.com/reference/queue/queue/

  //You could call show all paths by calling displayQueue()                                                                     

  //Don't forget to destroy the dynamic array if you used one
  delete[] num;
}

void showShortestDistance(int* curDist, int* predecessor, int start) // change to include end vert
{
  int dest; //destination                                                                                         //trace the shortest path from dest back to start  
  //I suggest you use either library's stack or queue. Which one will work?
 // int totalDistance = 0;
  cout << "Enter the destination: ";                                                                          
  cin >> dest;
  int i = dest;
  stack<int> s;

  while(i != start){
    s.push(i);
    i = predecessor[i];
  }
  s.push(i);

                                          
  cout << "The shortest path from " << start << " to " << dest << " is ";
  while(!s.empty()){
   // cout << s.pop();
    cout << s.top() << " ";
    s.pop();
  }
 
  cout << "\nThe distance is " << curDist[dest] << endl;   
                                   
}


void printHeapArrays(const minHeap<int>& h, int* curDist, int* locator, int* predecessor, int num_ver)
{
  cout << "heap ------" << endl;
  cout << h << endl;  //This works if you made operator<<() to display a heap

  cout << "locator ------" << endl;
  for(int i = 0; i < num_ver; i++)                                                                                          
    cout << locator[i] << " ";                                                                                               
  cout << endl;

  cout << "curDist ------- " << endl;                                                                                           
  for(int i = 0; i < num_ver; i++)                                                                                          
    cout << curDist[i] << " ";                                                                                               
  cout << endl << endl;

  cout << "Predecessor ------- " << endl;                                                                                      
  for(int i = 0; i < num_ver; i++)                                                                                         
    cout << predecessor[i] << " ";                                                                                             
  cout << endl << endl;
}

void graph::DijkstraShortestPath(int start) // include end vert
{
  minHeap<int> toBeChecked(num_ver); //the top of this heap has the vertex with the shortest distance
//  declare a dynamic array called curDist //contains the current shortest distance from start to every other vertex
  int *curDist = new int[num_ver];
  int *predecessor = new int[num_ver];
  int *locator = new int[num_ver];
  //declare a dynamic array called predecessor //contains the predecessor of each vertex
  //declare a dynamic array called locator //tells where each vertex exists within the heap. e.g. heap [v3, v1, v2, v4, v0] locator [4, 1, 2, 0, 3] <== vertext 0 can be found at index 4 in heap, vertex 3 can be found at index 0 in heap

  //The algorithm is in my lecture notes. Make sure you understand how each array and heap changes by reading my homework document posted on Canvas.
  for(int i = 0; i < num_ver; i++){
    curDist[i] = 999;
  }
  //initialize each array
  //curDist should be 999 for all vertices to start with 
  
  //populate toBeChecked heap 
  //insert all vetices into toBeChecked heap: [0, 1, 2, 3, 4, ...] the numbers are vertex numbers
  //to start with, locator [0, 1, 2, 3, 4, ...] 
  for(int i =0; i < num_ver; i++){
    locator[i] = i;
  }
  //Initialize predecessor for each vertex to -1
  for(int i = 0; i < num_ver; i++){
    predecessor[i] = -1;
  }
  for(int i = 0; i < num_ver; i++){
    toBeChecked.insert(curDist, locator, i);
  }
  curDist[start] = 0; //curDist(first) = 0;
  int v = start;
  while(toBeChecked.getNum() != 0){ 
    //while toBeChecked is not empty
    toBeChecked.fixHeap(curDist, locator, locator[v]);
    v = toBeChecked.getMin(curDist, locator); //v = a vertex in toBeChecked with minimum currDist(v)
   // toBeChecked.remove(curDist, locator, 0); //remove v from toBeChecked, since v is min then removing element at pos 0 will remove V
    for(list<edge*>::iterator u = ver_ar[v].begin(); u != ver_ar[v].end(); u++){//for all vertices u adjacent to v 
      //bool Checked = false;
     //need to check if u is in toBeChecked
      if(toBeChecked.find((*u)->neighbor) != false ){
            if(curDist[(*u)->neighbor] > curDist[v] + (*u)->wt){ 
          curDist[(*u)->neighbor] = curDist[v] + (*u)->wt; 
          predecessor[(*u)->neighbor]  = v; //predecessor(u) = v 
          toBeChecked.fixHeap(curDist, locator, locator[(*u)->neighbor]); //curDist was altered, must fix heap
          }
      }

    //  }
  //A lof of code here - check the algorithm in my lecture notes	


  //Now currDist and predecessor have the info about the shortest distance from start to every other vertex and the predecessor of each vertex
//print the result
    
  }
    }
  showShortestDistance(curDist, predecessor, start);
  delete[] curDist;
  delete[] predecessor;
  delete[] locator;

  }
#endif
