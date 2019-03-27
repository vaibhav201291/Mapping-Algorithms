#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>

using std::cout;
using std::endl;
using std::min_element;
using std::pair;
using std::vector;

class cedge
{
public:
  int n1;
  int n2;
  double dist;
  bool operator<(cedge b)
  {
    return dist < b.dist;
  }
};

int find(vector<int> &parent, vector<int> &nodes, int node)
{
  int n = node;
  int p = parent[n];
  while (p != -1)
  {
    n = p;
    p = parent[n];
  }
  return n;
}

bool merge(vector<int> &parent, vector<int> &nodes, vector<int> &height, int n1, int n2)
{
  int p1 = find(parent, nodes, n1);
  int p2 = find(parent, nodes, n2);
  if (p1 == -1 && p2 == -1)
  {
    parent[n1] = p2;
    height[p2] += 1;
    return true;
  }
  if (p1 == p2)
  {
    return false;
  }
  else
  {
    if (height[p1] == height[p2])
    {
      parent[n1] = p2;
      height[p2] += 1;
      return true;
    }
    else if (height[p1] < height[p2])
    {
      parent[n1] = p2;
      height[p2] += 1;
      return true;
    }
    else
    {
      parent[n2] = p1;
      height[p1] += 1;
      return true;
    }
  }
}

double clustering(vector<int> x, vector<int> y, int k)
{
  int n = x.size();
  vector<cedge> edge;

  // cout << "Number of points: " << n << endl;
  // cout << "Clusters needed: " << k << endl;
  for (int i = 0; i < n; i++)
  {
    for (int j = i; j < n; j++)
    {
      if (i != j)
      {
        cedge e;
        e.dist = sqrt(((x[i] - x[j]) * (x[i] - x[j])) + ((y[i] - y[j]) * (y[i] - y[j])));
        e.n1 = i;
        e.n2 = j;
        edge.push_back(e);
      }
    }
  }
  // cout << "Number of edges: " << edge.size() << endl;
  std::sort(edge.begin(), edge.end());
  for (int i = 0; i < edge.size(); i++)
  {
    // cout << "Edge: " << i << "   " << edge[i].dist << endl;
  }

  vector<int> parent(n);
  vector<int> nodes(n);
  vector<int> height(n);
  for (int i = 0; i < n; i++)
  {
    parent[i] = -1;
    nodes[i] = i;
    height[i] = 0;
  }

  int count = 0;
  int index = 0;
  for (int i = 0; i < n; i++)
  {
    if (parent[i] == -1)
    {
      count++;
    }
  }
  // cout << "Number of cluster:  " << count << endl;

  while (count >= k)
  {
    if (merge(parent, nodes, height, edge[index].n1, edge[index].n2))
    {
      count--;
    }
    // cout << "Index working: " << index << endl;
    // cout << "Number of cluster:  " << count << endl;
    index++;
  }

  return edge[index - 1].dist;
}

int main()
{
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++)
  {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
