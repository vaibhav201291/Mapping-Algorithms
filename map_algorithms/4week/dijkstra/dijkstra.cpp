#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <vector>

using std::cout;
using std::endl;
using std::min_element;
using std::pair;
using std::priority_queue;
using std::queue;
using std::vector;

class node
{
public:
  int key;
  bool visited;
  int dist;
  int min_d;
  bool operator<(node a)
  {
    return min_d < a.min_d;
  }
};

void explore(int &n, vector<node> &nodes, vector<vector<int> > &adj, vector<vector<int> > &cost, queue<node> &pile)
{
  // cout << "Exploring ...." << endl;
  // nodes[n].visited = true;
  for (int i = 0; i < adj[n].size(); i++)
  {
    int min_dist = nodes[n].dist + cost[n][i];
    // cout<< "size of row "<<adj[n].size()<<endl;
    if (nodes[adj[n][i]].dist > min_dist)
    {
      pile.push(nodes[adj[n][i]]);
      nodes[adj[n][i]].dist = min_dist;
      nodes[adj[n][i]].min_d = min_dist;
      // cout << "Node: " << adj[n][i] + 1 << " has distance: " << nodes[adj[n][i]].dist;
    }
  }
  return;
}

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int x, int y, int infi)
{

  // cout << "In Function" << endl;
  // cout << "Number of nodes: " << adj.size() << endl;
  // cout << "Number of edges in at x: " << adj[x].size() << endl;

  vector<node> nodes(adj.size());
  for (int i = 0; i < adj.size(); i++)
  {
    nodes[i].key = i;
    nodes[i].dist = infi;
    nodes[i].min_d = infi;
  }

  queue<node> pile;
  // cout<<"Queue declared"<<endl;
  nodes[x].dist = 0;
  nodes[x].min_d = 0;
  node top;

  for (int i = 0; i < adj.size(); i++)
  {
    vector<node>::iterator min_node = min_element(nodes.begin(), nodes.end());
    if (min_node->min_d < infi)
    {
      nodes[min_node->key].min_d = infi + 10;
      int keys;
      keys = min_node->key;
      pile.push(nodes[keys]);
      while (!pile.empty())
      {
        // cout << "In while loop and size of stack " << pile.size() << endl;
        top = pile.front();
        keys = top.key;
        pile.pop();
        explore(keys, nodes, adj, cost, pile);
      }
    }
  }

  return nodes[y].dist;
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  infi += 10;
  int dijkstr_dist = distance(adj, cost, s, t, infi);
  if (dijkstr_dist < infi)
  {
    cout << dijkstr_dist;
  }
  else
  {
    cout << -1;
  }
}
