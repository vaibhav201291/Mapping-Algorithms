#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using std::cout;
using std::endl;
using std::pair;
using std::stack;
using std::vector;

class node
{
public:
  int key;
  bool visited;
  int cc;
};

node explore(int &n, vector<node> &nodes, vector<vector<int> > &adj)
{
  nodes[n].visited = true;
  for (int i = 0; i < adj[n].size(); i++)
  {
    // cout<< "size of row "<<adj[n].size()<<endl;
    if (!nodes[adj[n][i]].visited)
    {
      return nodes[adj[n][i]];
    }
  }
  node dead;
  dead.key = -1;
  dead.visited = true;
  dead.cc = -1;
  return dead;
}

int number_of_strongly_connected_components(vector<vector<int> > adj, vector<vector<int> > adjR)
{
  int result = 0;

  // cout << "In Function" << endl;
  // cout << "Number of nodes: " << adj.size() << endl;
  // cout << "Number of edges in at x: " << adj[x].size() << endl;

  vector<node> nodes(adj.size());
  for (int i = 0; i < adj.size(); i++)
  {
    nodes[i].key = i;
  }

  stack<node> pileR;
  vector<int> order;
  // cout<<"Stack declared"<<endl;
  node topR;
  topR.key = 0;
  int cCntr = 0;

  for (int i = 0; i < adj.size(); i++)
  {
    if (!nodes[i].visited)
    {
      int keys = i;
      pileR.push(nodes[i]);
      while (pileR.size())
      {
        // cout << "In while loop and size of stack " << pile.size() << endl;
        topR = explore(keys, nodes, adjR);
        if (topR.key == -1)
        {
          // cout << "Trying to pop" << endl;
          order.push_back(pileR.top().key);
          pileR.pop();
          if (pileR.size())
            keys = pileR.top().key;
          // cout<<"Keys after pop "<<keys<<endl;
        }
        else
        {
          // cout << "trying to push" << endl;
          pileR.push(topR);
          keys = topR.key;
          // cout<<"Keys after push "<<keys<<endl;
        }
      }
    }
  }
  std::reverse(order.begin(),order.end());
  // cout << "Size of order : " << order.size() << endl;
  //  for (int i = 0; i < order.size(); i++)
  // {
  //   cout << order[i] << "  " ;
  // }
  // cout << endl;

  for(int i = 0; i < adj.size(); i++){
    nodes[i].visited = false;
  }

  stack<node> pile;
  // cout<<"Stack declared"<<endl;
  node top;
  top.key = 0;

  for (int i = 0; i < order.size(); i++)
  {
    // cout << "Visiting: " << nodes[order[i]].key << endl;
    if (!nodes[order[i]].visited)
    {
      cCntr++;
      int keys = order[i];
      pile.push(nodes[order[i]]);
      while (pile.size())
      {
        // cout << "In while loop and size of stack " << pile.size() << endl;
        top = explore(keys, nodes, adj);
        if (top.key == -1)
        {
          // cout << "Trying to pop" << endl;
          pile.pop();
          if (pile.size())
            keys = pile.top().key;
          // cout<<"Keys after pop "<<keys<<endl;
        }
        else
        {
          // cout << "trying to push" << endl;
          pile.push(top);
          keys = top.key;
          // cout<<"Keys after push "<<keys<<endl;
        }
      }
    }
  }

  return cCntr;
}

int main()
{
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > adjR(n, vector<int>());
  for (size_t i = 0; i < m; i++)
  {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adjR[y - 1].push_back(x - 1);
  }
  std::cout << number_of_strongly_connected_components(adj, adjR);
}
