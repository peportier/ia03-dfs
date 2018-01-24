/*
Copyright 2018 Pierre-Edouard Portier
peportier.me

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
)
*/

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <stack>
#include <functional>
#include <limits>

using namespace std;

struct
node
{
  int val;
  vector< node* > nei;
  node() {};
  node(int i) : val(i) {}
};

typedef function<void(node*)> Visitor;

void
depth( node* src, Visitor f )
{
  set<node*> x; 
  stack< pair< node* , vector<node*>::iterator > > y; 

  y.push( { src, src->nei.begin() } );          // initially the source is grey
  x.insert(src);                                // x contains the black and grey nodes

  while( !y.empty() )                           // while there are still grey nodes...
  {
    node* u = y.top().first;                    // u is the grey node we will make black 
                                                // by exploring his sons

    if( y.top().second != u->nei.end() )        // if u has still unexplored sons
    {
      node* next = *(y.top().second);           // next is a son of u
      ++(y.top().second);

      if( x.end() == x.find(next) )             // if this son of u is white
      {
        y.push( { next, next->nei.begin() } );  // it becomes grey
        x.insert(next);
      }
    }
    else                                        // u has no more unexplored sons.
    {
      f(u);                                     // we can visit u
      y.pop();                                  // u becomes black
    }
  }
}

Visitor visit = [](node* v){
  cout << v->val << " ; ";
};

void
depthrec0( node* src, Visitor visit, set<node*>& x )
{
  x.insert(src);

  for( node* n : src->nei )
  {
    if( x.end() == x.find(n) )
    {
      depthrec0( n, visit, x );
    }
  }

  visit(src);
}

void
depthrec( node* src, Visitor visit )
{
  set<node*> x;
  depthrec0(src, visit, x);
}
int
main()
{
  // example of a graph
  node n1(1); node n2(2); node n3(3);
  node n4(4); node n5(5); node n6(6);
  n1.nei.push_back( &n2 );
  n1.nei.push_back( &n3 );
  n2.nei.push_back( &n4 );
  n4.nei.push_back( &n3 );
  n4.nei.push_back( &n5 );
  n5.nei.push_back( &n2 );
  n5.nei.push_back( &n6 );
  
  depth(&n1, visit); cout << endl;
  depthrec(&n1, visit); cout << endl;
  
  return 0;
}
