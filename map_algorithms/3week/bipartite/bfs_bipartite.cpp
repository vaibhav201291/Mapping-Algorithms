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

int distance(vector<vector<int> > &adj, int x, int y)
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

    int keys, layer, ind, bkeys;
    nodes[x].dist = 0;
    pile.push(nodes[x]);
    layer = 1;
    while (!pile.empty())
    {
        // cout << "In while loop and size of stack " << pile.size() << endl;
        top = pile.front();
        keys = top.key;
        pile.pop();

        // cout<< "size of row "<<adj[n].size()<<endl;
        if (nodes[keys].dist == layer)
        {
            while(!pile.empty())
            {
                nd.push_back(pile.front().key);
                pileT.push(pile.front());
                pile.pop();
            }
            pile = pileT;

            for(int i = 0; i < nd.size(); i++){
                for(int j = i+1; j < nd.size(); j++){
                    for(int k = 0; k < adj[i].size(); k++){
                        if(nd[j] == adj[i][k]){
                            return 0;
                        }
                    }
                }
            }
            layer++;
        }


        explore(keys, nodes, adj, pile);
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
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, s, t);
}
