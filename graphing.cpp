//COMSC-210 | Lab 34 | Eric-Giulio Hedes
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
//Global constants
const int SIZE = 7;
//Define the Edge struct
struct Edge
{
    int src, dest, weight;
};
//Create alias 'Pair' for the pair<int,int> data
typedef pair<int, int> Pair;

class Graph
{
    public:
        // a vector of vectors of Pairs to represent an adjacency list
        vector<vector<Pair>> adjList;
        // Graph Constructor
        Graph(vector<Edge> const &edges)
        {
            // resize the vector to hold SIZE elements of type vector<Edge>
            adjList.resize(SIZE);
            // add edges to the directed graph
            for (auto &edge: edges)
            {
                int src = edge.src;
                int dest = edge.dest;
                int weight = edge.weight;
                // insert at the end
                adjList[src].push_back(make_pair(dest, weight));
                // for an undirected graph, add an edge from dest to src also
                adjList[dest].push_back(make_pair(src, weight));
            }
        }
        // Print the graph's adjacency list
        void printGraph()
        {
            cout << "Graph's adjacency list:" << endl;
            for (int i = 0; i < adjList.size(); i++)
            {
                cout << i << " --> ";
                for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
                cout << endl;
            }
        }
        //Set up functions for DFS and BFS
        void dfsRec(vector<vector<Pair>> &a, vector<bool> &visit, int s, vector<int> &r);
        vector<int> dfs(vector<vector<Pair>> &a);
        vector<int> bfs(vector<vector<Pair>> &a);
};

//Now here's the functions for the DFS and BFS
//Define dfsRec()
void Graph::dfsRec(vector<vector<Pair>> &a, vector<bool> &visit, int s, vector<int> &res)
{
    visit[s] = true;
    res.push_back(s);
    for (Pair &i : a[s]) {
        if (!visit[i.first])
            dfsRec(a, visit, i.first, res);
    }
}

//define dfs()
vector<int> Graph::dfs(vector<vector<Pair>> &a)
{
    vector<bool> visit(a.size(), false);
    vector<int> res;
    for (int i = 0; i < a.size(); i++) {
        if (!visit[i])
            dfsRec(a, visit, i, res);
    }
    return res;
}

//define bfs()
vector<int> Graph::bfs(vector<vector<Pair>> &a)
{
    int size = a.size();
    vector<bool> visit(a.size(), false);
    vector<int> res;
    queue<int> q;

    //Loop through vertices
    for (int i = 0; i < size; i++)
    {
        if (!visit[i])
        {
            visit[i] = true;
            q.push(i);
        }
        //Check if the queue is not empty
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            res.push_back(cur);
            //Visit all vertices
            for (Pair n : a[cur])
            {
                int fir = n.first;
                if (!visit[fir])
                {
                    visit[fir] = true;
                    q.push(fir);
                }
            }
        }
    }

    return res;
}

//Start of main()
int main()
{
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
    // (x, y, w) —> edge from x to y having weight w
    {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    //Print DFS results
    vector<int> dfsRes = graph.dfs(graph.adjList);
    cout << endl << "DFS starting from vertex 0:" << endl;
    for (int i : dfsRes) cout << i << " ";

    //Print BFS results
    vector<int> bfsRes = graph.bfs(graph.adjList);
    cout << endl << "BFS starting from vertex 0:" << endl;
    for (int j : bfsRes) cout << j << " ";

    return 0;
}