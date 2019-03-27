#include <iostream>
#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <time.h>

using namespace std;

// External vector of size 2 - for forward and backward search.
// Internal 2-dimensional vector is vector of adjacency lists for each node.
typedef vector<vector<vector<int> > > Adj;

// Distances can grow out of int type
typedef long long Len;

// Vector of two priority queues - for forward and backward searches.
// Each priority queue stores the closest unprocessed node in its head.
typedef vector<priority_queue<pair<Len, int>, vector<pair<Len, int> >, greater<pair<Len, int> > > > Queue;

const Len INFINITY = numeric_limits<Len>::max() / 4;

class Bidijkstra
{
    // Number of nodes
    int n_;
    // Graph adj_[0] and cost_[0] correspond to the initial graph,
    // adj_[1] and cost_[1] correspond to the reversed graph.
    // Graphs are stored as vectors of adjacency lists corresponding
    // to nodes.
    // Adjacency list itself is stored in adj_, and the corresponding
    // edge costs are stored in cost_.
    Adj adj_;
    Adj cost_;
    // distance_[0] stores distances for the forward search,
    // and distance_[1] stores distances for the backward search.
    vector<vector<Len> > distance_;
    // Stores all the nodes visited either by forward or backward search.
    vector<int> workset_;
    // Stores a flag for each node which is True iff the node was visited
    // either by forward or backward search.
    vector<bool> visited_;
    vector<vector<bool> > side_visited_;

  public:
    Bidijkstra(int n, Adj adj, Adj cost)
        : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n, INFINITY)), visited_(n), side_visited_(2, vector<bool>(n))
    {
        workset_.reserve(n);
    }

    // Initialize the data structures before new query,
    // clear the changes made by the previous query.
    void clear()
    {
        for (int i = 0; i < workset_.size(); ++i)
        {
            int v = workset_[i];
            distance_[0][v] = distance_[1][v] = INFINITY;
            visited_[v] = false;
            side_visited_[0][v] = side_visited_[1][v] = false;
        }
        workset_.clear();
    }

    // Processes visit of either forward or backward search
    // (determined by value of side), to node v trying to
    // relax the current distance by dist.
    void visit(Queue &q, int side, int v, Len dist)
    {
        visited_[v] = true;
        side_visited_[side][v] = true;
        distance_[side][v] = dist;
        // cout << "Nodes connected: " << adj_[side][v].size() << endl;
        for (int i = 0; i < adj_[side][v].size(); i++)
        {
            int expNode = adj_[side][v][i];
            Len actDist = distance_[side][adj_[side][v][i]];
            Len relexDist = dist + cost_[side][v][i];
            if (actDist > relexDist && !side_visited_[side][expNode])
            {
                distance_[side][expNode] = relexDist;
                // cout << "Now " << i + 1 << " added: " << expNode + 1 << " with dist " << relexDist << endl;
                workset_.push_back(expNode);
                pair<Len, int> node(distance_[side][expNode], expNode);
                q[side].push(node);
            }
        }
    }

    // Returns the distance from s to t in the graph.
    Len query(int s, int t)
    {
        clear();
        Queue q(2);
        Len minDist = -1;
        if (s == t)
        {
            minDist = 0;
        }
        else
        {
            workset_.push_back(s);
            workset_.push_back(t);
            visit(q, 0, s, 0);
            visit(q, 1, t, 0);
            while (!q[0].empty() && !q[1].empty())
            {
                pair<Len, int> tFwd, tBkd;
                tFwd = q[0].top();
                // cout << endl;
                // cout << "Closest Node fwd :  " << tFwd.second + 1 << endl;
                tBkd = q[1].top();
                // cout << "Closest Node bkd :  " << tBkd.second + 1 << endl;
                // cout << endl;
                if (side_visited_[1][tFwd.second] || side_visited_[0][tBkd.second])
                {
                    visit(q, 0, tFwd.second, tFwd.first);
                    visit(q, 1, tBkd.second, tBkd.first);
                    break;
                }
                q[0].pop();
                q[1].pop();
                if (!side_visited_[0][tFwd.second])
                {
                    visit(q, 0, tFwd.second, tFwd.first);
                }
                if (!side_visited_[1][tBkd.second])
                {
                    visit(q, 1, tBkd.second, tBkd.first);
                }
            }
            cout << "Size of the workset: " << workset_.size() << endl;
            minDist = distance_[0][workset_[0]] + distance_[1][workset_[0]];
            for (int i = 0; i < workset_.size(); i++)
            {
                Len intDist = distance_[0][workset_[i]] + distance_[1][workset_[i]];
                // cout << "For node : " << workset_[i] + 1 << " distance: " << intDist << endl;
                if (minDist > intDist)
                {
                    // cout << "______minimum encountered______" << endl;
                    minDist = intDist;
                }
            }

            if (minDist >= INFINITY)
            {
                minDist = -1;
            }
        }
        // cout << "infinty is : " << INFINITY << endl;
        return minDist;
    }
};

int main()
{
    clock_t ct;
    int n, m;
    scanf("%d%d", &n, &m);
    Adj adj(2, vector<vector<int> >(n));
    Adj cost(2, vector<vector<int> >(n));
    for (int i = 0; i < m; ++i)
    {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        adj[0][u - 1].push_back(v - 1);
        cost[0][u - 1].push_back(c);
        adj[1][v - 1].push_back(u - 1);
        cost[1][v - 1].push_back(c);
    }

    Bidijkstra bidij(n, adj, cost);

    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        // ct = clock();
        printf("%lld\n", bidij.query(u - 1, v - 1));
    }
    // ct = clock() - ct;
    // cout << "Running time: " << ct << endl;
}
