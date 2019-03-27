#include <iostream>
#include <vector>
#include <queue>

using std::cout;
using std::endl;
using std::pair;
using std::queue;
using std::vector;

class node
{
public:
  int key;
  bool visited;
  int cc;
  int dist;
};

void explore(int &n, vector<node> &nodes, vector<vector<int> > &adj, queue<node> &pile)
{
  // cout << "Exploring ...." << endl;
  // nodes[n].visited = true;
  for (int i = 0; i < adj[n].size(); i++)
  {
    if (nodes[adj[n][i]].dist == nodes[n].dist)
    {
      // cout << n << " is eq " << adj[n][i]<< endl;
      while (!pile.empty())
      {
        pile.pop();
      }
      node def;
      def.key = -1;
      pile.push(def);
      return;
    }
    // cout<< "size of row "<<adj[n].size()<<endl;
    if (nodes[adj[n][i]].dist == -1)
    {
      pile.push(nodes[adj[n][i]]);
      nodes[adj[n][i]].dist = nodes[n].dist + 1;
      // cout << "Node: " << adj[n][i] + 1 << " has distance: " << nodes[adj[n][i]].dist;
    }
  }
  return;
}

int bipartite(vector<vector<int> > &adj)
{

  // cout << "In Function" << endl;
  // cout << "Number of nodes: " << adj.size() << endl;
  // cout << "Number of edges in at x: " << adj[x].size() << endl;

  vector<node> nodes(adj.size());
  for (int i = 0; i < adj.size(); i++)
  {
    nodes[i].key = i;
    nodes[i].dist = -1;
  }

  queue<node> pile, pileT;
  // cout<<"Queue declared"<<endl;
  node top, btop;
  vector<int> nd;
  int keys, layer, ind, bkeys, x;

  for (int i = 0; i < adj.size(); i++)
  {
    if (nodes[i].dist == -1)
    {
      x = i;
      nodes[x].dist = 0;
      pile.push(nodes[x]);
      layer = 1;
      while (!pile.empty())
      {
        // cout << "In while loop and size of pile " << pile.size() << endl;
        top = pile.front();
        keys = top.key;

        pile.pop();
        explore(keys, nodes, adj, pile);
        if (pile.front().key == -1)
        {
          return 0;
        }
      }
    }
  }

  return 1;
}

int main()
{
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++)
  {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
