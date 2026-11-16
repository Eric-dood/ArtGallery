//COMSC-210 | Lab 34 | Eric-Giulio Hedes
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
using namespace std;
//Global constants
const int SIZE = 9;
//Function prototype
void printBorder();
void borderedMessage(string msg);
//Define the Edge struct
struct Edge {
    int src, dest, weight;
};
//Create alias 'Pair' for the pair<int,int> data
typedef pair<int, int> Pair;
//Create vector names for the hubs/locations
const vector<string> HUBNAMES = 
{
    "Central Train Station",
    "Southwest Gate",
    "East Plaza",
    "University District",
    "Art Gallery",
    "West Mall",
    "Lakeside Park",
    "Near Central Terminal",
    "Northern Gymnasium"
};

//Define the Graph class
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
            borderedMessage("Metro Transit Network Topology:");
            cout << endl;

            //Use a for loop to traverse through the list
            for (int i = 0; i < adjList.size(); i++)
            {
                //Print a station
                cout << "Station " << i << " (" << HUBNAMES[i] << ") connects to:" << endl;
                //Go through the entire list to print each pair
                for (Pair &v : adjList[i])
                {
                    cout << "  -> Station " << v.first << " (" << HUBNAMES[v.first] << ")";
                    cout << " [Distance: " << v.second << " km]" << endl;
                }
                //Leave extra space
                cout << endl;
            }
        }
        //Set up functions for DFS and BFS
        void dfsRec(vector<bool> &visit, int s);
        void dfs(int start);
        void bfs(int start);
        void shortPath(int start);
        void minSpanTree(int start);
};

//Now here's the functions for the DFS and BFS
//Define dfsRec()
void Graph::dfsRec(vector<bool> &visit, int s)
{
    //Always set the starting element to true
    visit[s] = true;
    //Print the station name & number
    cout << "Inspecting - Station " << s << " (" << HUBNAMES[s] << ")" << endl;
    //Use a station name to 
    for (const Pair &i : adjList[s]) {
        if (!visit[i.first]) {
            cout << "  -> Station " << i.first << " (" << HUBNAMES[i.first] << ") - ";
            cout << "[Distance: " << i.second << " km]" << endl;
            dfsRec(visit, i.first);
        }
    }
}

//define dfs()
void Graph::dfs(int start)
{
    //Validation check for error prevention
    if (start < 0 || start >= SIZE)
    {
        cout << "ERROR: Station is out of bounds or does not exist." << endl;
        return;
    }

    printBorder();
    cout << "Track Inspection Crew Order (DFS) from Station " << start << " [" << HUBNAMES[start] << "]" << endl;
    cout << "(Purpose: Follows rail lines to the end before backtracking)" << endl;
    printBorder();
    vector<bool> visit(SIZE, false);
    dfsRec(visit, start);
    cout << endl;
}

//define bfs()
void Graph::bfs(int start)
{
    //Validation check for error prevention
    if (start < 0 || start >= SIZE)
    {
        cout << "ERROR: Station is out of bounds or does not exist." << endl;
        return;
    }

    vector<bool> visit(SIZE, false);
    queue<int> q;

    printBorder();
    cout << "Alert Propagation (BFS) from " << start << " [" << HUBNAMES[start] << "]" << endl;
    cout << "(Purpose: Notifies neighboring stations at first, then expands to the other stations.)" << endl;
    printBorder();

    visit[start] = true;
    q.push(start);
    //Loop through vertices
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        cout << "Alerting - Station " << cur << " (" << HUBNAMES[cur] << ")" << endl;

        for (const Pair &i : adjList[cur])
        {
            if (!visit[i.first])
            {
                visit[i.first] = true;
                cout << "  -> Next station: " << i.first << " (" << HUBNAMES[i.first] << ") - ";
                cout << "[Distance: " << i.second << "]" << endl;
                q.push(i.first);
            }
        }
    }
}

//Define shortestPath()
void Graph::shortPath(int start)
{
    //Validation check for error prevention
    if (start < 0 || start >= SIZE)
    {
        cout << "ERROR: Station is out of bounds or does not exist." << endl;
        return;
    }

    vector<int> dis(SIZE, INT_MAX);
    vector<int> par(SIZE, -1);
    priority_queue<Pair, vector<Pair>, greater<Pair>> pq;

    dis[start] = 0;
    pq.push({0, start});

    borderedMessage("Calculating the shortest Station paths...");

    while (!pq.empty())
    {
        int u = pq.top().second, d = pq.top().first;
        pq.pop();

        if (d > dis[u]) continue;

        for (const Pair &i : adjList[u])
        {
            int vertex = i.first;
            if (dis[u] + i.second < dis[vertex])
            {
                dis[vertex] = dis[u] + i.second;
                par[vertex] = u;
                pq.push({dis[vertex], vertex});
            }
        }
    }
    cout << "Shortest path from Station " << start << ":" << endl;
    for (int i = 0; i < SIZE; i++)
        cout << start << "  -> " << i << ": " << dis[i] << endl;
}

//define minSpanTree()
void Graph::minSpanTree(int start)
{
    //Validation check for error prevention
    if (start < 0 || start >= SIZE)
    {
        cout << "ERROR: Station is out of bounds or does not exist." << endl;
        return;
    }

    vector<int> key(SIZE, INT_MAX), par(SIZE, -1), order;
    vector<bool> inMST(SIZE, false);
    priority_queue<Pair, vector<Pair>, greater<Pair>> pq;

    key[start] = 0;
    pq.push({0, start});

    borderedMessage("Finding the Minimum Spanning Tree...");

    while(!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        if (par[u] != -1)
            order.push_back(u);

        for (const Pair &i : adjList[u])
        {
            int v = i.first;
            if (!inMST[v] && i.second < key[v])
            {
                key[v] = i.second;
                par[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    cout << "Minimum Spanning Tree edges:" << endl;
    //Print the edges' minimum spanning tree
    for (int i : order) {
        cout << "Edge from Station " << i << " (" << HUBNAMES[i] << ") to Station ";
        cout << par[i] << " (" << HUBNAMES[par[i]] << "):" << endl;
        cout << "  -> Capacity: " << key[i] << " km." << endl;
    }
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

    //Define the choice, which will be used for validation looping and selections
    int choice = -1, input = 0;

    //Print the menu
    cout << "Welcome to the Metro Transit Network program! Feel free to enter any of the options below:" << endl;
    while (choice != 0)
    {
        cout << endl << "Menu:" << endl;
        cout << "[1] Display the transit newtork" << endl;
        cout << "[2] Track Inspection Crew Order (DFS)" << endl;
        cout << "[3] Set up the Alert Propagation (BFS)" << endl;
        cout << "[4] Calculate the shortest paths" << endl;
        cout << "[5] Find the Minimum Spanning Tree" << endl;
        cout << "[0] Exit the program" << endl;
        cout << "Choice --> ";
        //Make the user pick each option
        cin >> choice;
        cin.ignore(1000, 10);
        //If the choice is higher than 2, prit
        if (choice >= 2)
        {
            cout << "Select a Station: ";
            cin >> input;
            cin.ignore(1000, 10);
        }
        //Use switch statements to call the respective function based on choice
        switch (choice)
        {
            case 1: //Prints adjacency list representation of graph
                graph.printGraph();
                break;
            case 2: //Print DFS results
                graph.dfs(input);
                break;
            case 3: //Print BFS results
                graph.bfs(input);
                break;
            case 4: //Print the shortest path
                graph.shortPath(input);
                break;
            case 5: //Print the minimum spanning tree
                graph.minSpanTree(input);
                break;
        }
    }

    //Print a thank you message
    cout << "Thank you for checking out my program!" << endl;

    return 0;
}

//Define printBorder()
void printBorder() {
    //Use a range-based loop to print the bar
    for (int i = 0; i < 35; i++) cout << "=";
    //Leave extra space
    cout << endl;
}

//Define borderedMessage()
void borderedMessage(string msg)
{
    printBorder();
    //Print the message
    cout << msg << endl;
    printBorder();
}