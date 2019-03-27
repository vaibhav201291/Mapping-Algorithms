#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>

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
  double dist;
  double min_d;
  bool operator<(node a)
  {
    return min_d < a.min_d;
  }
};

void explore(int &n, vector<node> &nodes, vector<vector<int> > &adj, vector<vector<double> > &cost, double infi)
{
  for (int i = 0; i < adj[n].size(); i++)
  {
    // cout<< "size of row "<<adj[n].size()<<endl;
    // cout << "Cost: " << nodes[adj[n][i]].key << " from " << nodes[n].key << " is " << cost[n][i] << endl;
    if (nodes[adj[n][i]].dist > cost[n][i] && nodes[i].min_d < infi)
    {
      // cout << "Improved..." << endl;
      nodes[adj[n][i]].dist = cost[n][i];
      nodes[adj[n][i]].min_d = cost[n][i];
    }
  }
  return;
}

double minimum_distance(int n, vector<int> x, vector<int> y)
{
  // cout << "In Function" << endl;
  vector<vector<int> > adj(n, vector<int>(n));
  vector<vector<double> > cost(n, vector<double>(n));
  double infi = 0;
  vector<node> nodes(adj.size());

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (i != j)
      {
        infi += sqrt(((x[i] - x[j]) * (x[i] - x[j])) + ((y[i] - y[j]) * (y[i] - y[j])));
      }
    }
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (i != j)
      {
        adj[i][j] = j;
        cost[i][j] = sqrt(((x[i] - x[j]) * (x[i] - x[j])) + ((y[i] - y[j]) * (y[i] - y[j])));
      }
      else
      {
        adj[i][j] = j;
        cost[i][j] = infi + 1;
      }
    }
    nodes[i].key = i;
    nodes[i].dist = infi;
    nodes[i].min_d = infi;
  }
  infi += 10;
  // cout << "Number of nodes: " << adj.size() << endl;
  // cout << "Number of edges in at 0: " << adj[0].size() << endl;
  // cout << "Infinite value: " << infi << endl;

  // cout<<"Queue declared"<<endl;
  nodes[0].dist = 0;
  nodes[0].min_d = 0;
  int keys;

  for (int i = 0; i < adj.size(); i++)
  {
    vector<node>::iterator min_node = min_element(nodes.begin(), nodes.end());
    if (nodes[min_node->key].min_d < infi)
    {
      // cout << "Minimum node: " << min_node->key << endl;
      nodes[min_node->key].min_d = infi + 100;
      keys = min_node->key;
      // cout << "Minimum Key is " << keys << endl;
      explore(keys, nodes, adj, cost, infi);
    }
  }

  double result = 0.00;
  for (int i = 0; i < adj.size(); i++)
  {
    result += nodes[i].dist;
    // cout << "Dist at: " << i + 1 << "  " << nodes[i].dist << endl;
  }

  //write your code here
  return result;
}

int main()
{
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++)
  {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(n, x, y) << std::endl;
}
