//COMSC-210 | Lab 34 | Eric-Giulio Hedes
#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;
//Global constants
const int SIZE = 9;
//Define the Edge struct
struct Edge
{
    int src, dest, weight;
};
//Create alias 'Pair' for the pair<int,int> data
typedef pair<int, int> Pair;
//Create vector names
const vector<string> HUBNAMES = 
{
    "Central Station Core",
    "Southwest Gate",
    "East Plaza",
    "University District",
    "Art Gallery",
    "West Mall",
    "Lakeside Park",
    "Near Central Terminal",
    "Northern Gymnasium"
};

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
            for (int i = 0; i < 35; i++) cout << "=";
            cout << endl << "Metro Transit Network Topology:" << endl;
            for (int i = 0; i < 35; i++) cout << "=";
            cout << endl;

            for (int i = 0; i < adjList.size(); i++)
            {
                cout << "Station " << i << " (" << HUBNAMES[i] << ") connects to:" << endl;
                for (Pair v : adjList[i])
                {
                    cout << "  -> Station " << v.first << " (" << HUBNAMES[v.first] << ")";
                    cout << " [Distance: " << v.second << " km]" << endl;
                }
                cout << endl;
            }
        }
        //Set up functions for DFS and BFS
        void dfsRec(vector<bool> &visit, int s, vector<int> &r);
        void dfs(int start);
        vector<int> bfs(int start);
};

//Now here's the functions for the DFS and BFS
//Define dfsRec()
void Graph::dfsRec(vector<bool> &visit, int s, vector<int> &res)
{
    visit[s] = true;
    cout << "[Inspecting - Station " << s << " (" << HUBNAMES[s] << ")]" << endl;

    for (const Pair &i : adjList[s]) {
        if (!visit[i.first]) {
            cout << "  -> Station " << i.first << " (" << HUBNAMES[i.first] << ")";
            cout << "[Distance: " << i.second << " km]" << endl;
            dfsRec(visit, i.first, res);
        }
    }
}

//define dfs()
void Graph::dfs(int start)
{
    if (start < 0 || start >= SIZE) return;
    cout << "Track Inspection Crew Order (Starting from " << start << " [" << HUBNAMES[start] << "])" << endl;
    cout << "(Purpose: )" << endl;
    vector<bool> visit(SIZE, false);
    vector<int> res;
    dfsRec(visit, start, res);
}

//define bfs()
vector<int> Graph::bfs(int start)
{
    if (start < 0 || start >= SIZE) return { };
    vector<bool> visit(SIZE, false);
    vector<int> res;
    queue<int> q;

    visit[start] = true;
    q.push(start);
    //Loop through vertices
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        res.push_back(cur);

        for (const Pair &i : adjList[cur])
        {
            if (!visit[i.first])
            {
                visit[i.first] = true;
                q.push(i.first);
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
    {0,1,12},{3,0,4},{2,3,6},
    {5,6,6},{4,5,9},{2,4,4},
    {2,5,5},{0,8,5},{0,4,2},
    {2,7,15},{1,2,12},{3,6,1}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    //Print DFS results
    graph.dfs(0);
    //Print BFS results
    graph.bfs(0);

    return 0;
}