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

vector<int> toposort(vector<vector<int> > adj)
{
  // cout << "In Function" << endl;
  // cout << "Number of nodes: " << adj.size() << endl;
  // cout << "Number of edges in at x: " << adj[x].size() << endl;

  vector<node> nodes(adj.size());
  for (int i = 0; i < adj.size(); i++)
  {
    nodes[i].key = i;
  }

  stack<node> pile;
  vector<int> order;
  // cout<<"Stack declared"<<endl;
  node top;
  top.key = 0;
  int cCntr = 0;

  for (int i = 0; i < adj.size(); i++)
  {
    if (!nodes[i].visited)
    {
      cCntr++;
      int keys = i;
      pile.push(nodes[i]);
      while (pile.size())
      {
        // cout << "In while loop and size of stack " << pile.size() << endl;
        top = explore(keys, nodes, adj);
        if (top.key == -1)
        {
          // cout << "Trying to pop" << endl;
          order.push_back(pile.top().key);
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
  std::reverse(order.begin(),order.end());
  return order;
}

int main()
{
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++)
  {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++)
  {
    std::cout << order[i] + 1 << " ";
  }
}
