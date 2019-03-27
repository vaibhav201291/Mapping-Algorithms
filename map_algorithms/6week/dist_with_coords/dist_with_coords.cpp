#include <iostream>
#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <math.h>
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

const Len INFINITY_L = numeric_limits<Len>::max() / 2;

class AStar
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
    Adj cost_i;
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
    // Coordinates of the nodes
    std::vector<std::pair<Len, Len> > xy_;
    // The potential based on the distances between the coordinates
    vector<Len> pot_;
    // vector<Len> pot_1;

  public:
    AStar(int n, Adj adj, Adj cost, std::vector<std::pair<Len, Len> > xy)
        : n_(n), adj_(adj), cost_i(cost), cost_(cost), distance_(2, vector<Len>(n_, INFINITY_L)), visited_(n), xy_(xy)
    {
        workset_.reserve(n);
        pot_.reserve(n);
        // pot_1.reserve(n);
        side_visited_.resize(2);
        for (int i = 0; i < 2; ++i)
        {
            side_visited_[i].resize(n);
        }
    }

    // See the description of this method in the starter for friend_suggestion
    void clear()
    {
        for (int i = 0; i < n_; ++i)
        {
            int v = i; //workset_[i];
            distance_[0][v] = distance_[1][v] = INFINITY_L;
            visited_[v] = false;
            side_visited_[0][v] = side_visited_[1][v] = false;
        }
        for(int i = 0; i < n_; i++)
        {
            pot_[i] = 0;
            // pot_1[i] = 0;
        }
        cost_ = cost_i;
        workset_.clear();
    }

    // See the description of this method in the starter for friend_suggestion
    void visit(Queue &q, int side, int v, Len dist)
    {
        visited_[v] = true;
        side_visited_[side][v] = true;
        workset_.push_back(v);
        distance_[side][v] = dist;
        // cout << "Potential for  " << v + 1 << " : " << pot_[v] << endl;
        // cout << "Original Dist: " << dist << endl;
        // cout << "and distance becomes: " << distance_[side][v] << endl;
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
                // cout << "Dist in queue: " << (distance_[side][expNode] + pot_[expNode]) << endl;
                // cout << "Potential : " << pot_[expNode] << endl;
                // workset_.push_back(expNode);
                pair<Len, int> node(distance_[side][expNode], expNode);
                q[side].push(node);
            }
        }
    }

    // Returns the distance from s to t in the graph
    Len query(int s, int t)
    {
        clear();
        Queue q(2);

        Len pot_dist, pot_distR;
        // Len pot_1dist, pot_1distR, dA, dV, dAR;
        for (int i = 0; i < n_; i++)
        {
            pot_dist = sqrt(pow((xy_[t].first - xy_[i].first), 2) + pow((xy_[t].second - xy_[i].second), 2));
            pot_distR = sqrt(pow((xy_[s].first - xy_[i].first), 2) + pow((xy_[s].second - xy_[i].second), 2));
            // dV = sqrt(pow(xy_[0].first - xy_[i].first, 2) + pow(xy_[0].second - xy_[i].second, 2) );
            // dA = sqrt(pow(xy_[0].first - xy_[t].first, 2) + pow(xy_[0].second - xy_[t].second, 2) );
            // dAR = sqrt(pow(xy_[0].first - xy_[s].first, 2) + pow(xy_[0].second - xy_[s].second, 2) );
            // pot_1dist = dA - dV;
            // pot_1distR = dAR - dV;
            pot_[i] = (pot_dist - pot_distR) / 2;
            // cout << "pot func: " << pot_[i] << endl;
            // pot_1[i] = (pot_dist - pot_distR) / 2;
        }

        for(int i = 0; i < n_; i++){
            for(int j = 0; j < cost_[0][i].size(); j++)
            {
                cost_[0][i][j] = cost_i[0][i][j] - pot_[i] + pot_[adj_[0][i][j]];
                // cout << "Cost F: " << cost_[0][i][j] << endl;
                // cost_[0][i][j] = cost_[0][i][j] - pot_1[i] + pot_1[adj_[0][i][j]];// + cost_i[0][i][j];
            }
            for(int j = 0; j < cost_i[1][i].size(); j++)
            {
                cost_[1][i][j] = cost_i[1][i][j] + pot_[i] - pot_[adj_[1][i][j]];
                // cout << "Cost B: " << cost_[1][i][j] << endl;
                // cost_[1][i][j] = cost_[1][i][j] + pot_1[i] - pot_1[adj_[1][i][j]];// + cost_i[1][i][j];
            }
        }

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
                // cout << "Clsest Node bkd :  " << tBkd.second + 1 << endl;
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
                    // cout << "F Dist with potential: " << tFwd.first << endl;
                    // cout << "F Dist without potential: " << tFwd.first - pot_[tFwd.second] << endl;
                    visit(q, 0, tFwd.second, tFwd.first);
                }
                if (!side_visited_[1][tBkd.second])
                {
                    // cout << "B Dist with potential: " << tBkd.first << endl;
                    // cout << "B Dist without potential: " << tBkd.first - pot_[tBkd.second] << endl;
                    visit(q, 1, tBkd.second, tBkd.first);
                }
            }
            // cout << "Size of the workset: " << workset_.size() << endl;

            minDist = distance_[0][workset_[0]] + distance_[1][workset_[0]];
            for (int i = 0; i < workset_.size(); i++)
            {
                Len intDist = distance_[0][workset_[i]] + distance_[1][workset_[i]];
                // cout << "For node : " << workset_[i] + 1 << " distance: " << intDist + pot_[s] - pot_[t] << endl;
                // cout << "Potential : " << pot_[i] * 2 << endl;
                if (minDist > intDist)
                {
                    // cout << "______minimum encountered______" << endl;
                    minDist = intDist;
                }
            }

            if (minDist >= INFINITY_L)
            {
                minDist = -1;
            }
        }
        // cout << "infinty is : " << INFINITY << endl;
        // cout << "Pot of s: " << pot_[s] << "  Pot of t: " << pot_[t] << endl;
        return minDist + pot_[s] - pot_[t];// + pot_1[s] - pot_1[t];
    }
};

int main()
{
    clock_t ct;
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<std::pair<Len, Len> > xy(n);
    for (int i = 0; i < n; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        xy[i] = make_pair(a, b);
    }
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

    AStar astar(n, adj, cost, xy);

    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        // ct = clock();
        printf("%lld\n", astar.query(u - 1, v - 1));
    }
    // ct = clock() - ct;
    // cout << "Running time: " << ct << endl;
}
