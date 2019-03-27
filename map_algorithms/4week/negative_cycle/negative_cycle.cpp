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
  int prev;
  int dist;
};

void explore(int &n, vector<node> &nodes, vector<vector<int> > &adj, vector<vector<int> > &cost)
{
  for (int i = 0; i < adj[n].size(); i++)
  {
    // cout<< "size of row "<<adj[n].size()<<endl;
    if (nodes[adj[n][i]].dist > nodes[n].dist + cost[n][i])
    {
      // cout << "Cost: " << nodes[adj[n][i]].key << " from " << nodes[n].key << " is " << nodes[n].dist + cost[n][i] << endl;
      nodes[adj[n][i]].dist = nodes[n].dist + cost[n][i];
    }
  }
  return;
}

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost, int infi)
{

  // cout << "In Function" << endl;
  // cout << "Number of nodes: " << adj.size() << endl;
  // cout << "Number of edges in at x: " << adj[x].size() << endl;

  vector<node> nodes(adj.size());
  vector<node> nodes_vth(adj.size());
  for (int i = 0; i < adj.size(); i++)
  {
    nodes[i].key = i;
    nodes_vth[i].key = i;
    nodes[i].dist = infi;
    nodes_vth[i].dist = infi;
  }

  nodes[0].prev = -1;
  nodes[0].dist = 0;

  for (int i = 0; i < adj.size() - 1; i++)
  {
    // cout << "Outer loop staarts..." << endl;
    for (int j = 0; j < adj.size(); j++)
    {
      // cout << "Loop for v starts." << endl;
      explore(j, nodes, adj, cost);
    }
  }

  nodes_vth = nodes;
  // cout << "CHECK FOR THE LAST LOOP......" << endl;
  for (int j = 0; j < adj.size(); j++)
  {
    explore(j, nodes, adj, cost);
  }

  for (int i = 0; i < adj.size(); i++)
  {
    if(nodes_vth[i].dist != nodes[i].dist){
      return 1;
    }
  }
  return 0;
}

int main()
{
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  int infi = 0;
  for (int i = 0; i < m; i++)
  {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
    infi += w;
  }
  infi += 10;
  std::cout << negative_cycle(adj, cost, infi);
}
