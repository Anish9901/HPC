#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>

using namespace std;

/* vector<int> bfs(vector<vector<int>>& graph, int start, vector<bool>& visited)
{
    queue<int> q;
    vector<int> result;
    q.push(start);
    visited[start] = true;
    while(!q.empty())
    {
        int front = q.front();
        result.push_back(front);
        q.pop();
        for(auto it: graph[front])
        {
            if(visited[it] == false)
            {
                q.push(it);
                visited[it] = true;
            }
        }
    }
    return result;
} */

void bfs(vector<vector<int>>& graph, queue<int>& q, vector<bool>& visited)
{
    if(q.empty()){
        return;
    }
    #pragma omp parallel
    {
        #pragma omp single
        {
            int front = q.front();
            q.pop();
            cout<< front << " ";
            #pragma omp task firstprivate(front)
            {
                for(auto it: graph[front])
                {
                    if(visited[it] == false)
                    {
                        q.push(it);
                        visited[it] = true;
                    }
                }
                #pragma omp task
                {
                    bfs(graph, q, visited);
                }
            }
        }
    }
}

/* void bfs(vector<vector<int>>& graph, queue<int>& q, vector<bool>& visited)
{
    if(q.empty()){
        return;
    }

            int front = q.front();
            q.pop();
            cout<< front << " ";
            {
                for(auto it: graph[front])
                {
                    if(visited[it] == false)
                    {
                        q.push(it);
                        visited[it] = true;
                        
                        
                    }
                }
                bfs(graph, q, visited);
            }
} */

int main(){
    /* Traverse/visit an undirected(why only undirected? ChatGPT)
    graph or tree using bfs algo */
    vector<vector<int>> graph;
    graph = {{1, 3, 4}, {2, 5, 6}, {1}, {0}, {0}, {1}, {1}};
    int start = 0;
    vector<bool> visited(graph.size(), false);
    vector<int> result;
    /* bfs(graph, start, visited); */
    queue<int> q;
    q.push(start);
    visited[start] = true;
    bfs(graph, q, visited);
    cout<< "\n";
    return 0;
}