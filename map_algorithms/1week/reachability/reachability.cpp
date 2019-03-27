#include <iostream>
#include <vector>
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

int reach(vector<vector<int> > &adj, int x, int y)
{
  // cout << "In Function" << endl;
  // cout << "Number of nodes: " << adj.size() << endl;
  // cout << "Number of edges in at x: " << adj[x].size() << endl;

  if (!adj[x].size())
  {
    return 0;
  }

  if (!adj[y].size())
  {
    return 0;
  }

  vector<node> nodes(adj.size());
  for (int i = 0; i < adj.size(); i++)
  {
    nodes[i].key = i;
  }

  for (int i = 0; i < adj[x].size(); i++)
  {
    // cout << i << "  " << adj[x][i] << endl;
    if ((adj[x][i]) == y)
    {
      return 1;
    }
  }

  stack<node> pile;
  // cout<<"Stack declared"<<endl;
  node top;
  top.key = 0;

  int keys = x;
  pile.push(nodes[x]);
  while (pile.size())
  {
    // cout << "In while loop and size of stack " << pile.size() << endl;
    top = explore(keys, nodes, adj);
    if (top.key == y)
    {
      // cout<<"The key matches " << top.key <<endl;
      return 1;
    }
    else if (top.key == -1)
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
  // }

  return 0;
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
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
  cout << endl;
}
