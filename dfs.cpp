#include <iostream>
#include <stack>
#include <vector>
#include <omp.h>
using namespace std;

/* vector<int> dfs(vector<vector<int>>& graph, int start, vector<bool>& visited)
{
    stack<int> s;
    s.push(start);
    visited[start] = true;
    vector<int> result;
    while(!s.empty())
    {
        int top = s.top();
        result.push_back(top);
        s.pop();
        for(auto it: graph[top])
        {
            if(visited[it] == false)
            {
                s.push(it);
                visited[it] = true;
            }
        }
    }
    return result;
} */

void dfs(vector<vector<int>>& graph, stack<int>& s, vector<bool>& visited)
{
    if(s.empty())
    {
        return;
    }
    #pragma omp parallel
    {
        #pragma omp single
        {
            int top = s.top();
            cout<< top << " ";
            s.pop();
            #pragma omp firstprivate(top)
            {
                for(auto it: graph[top])
                {
                    if(visited[it] == false)
                    {
                        s.push(it);
                        visited[it] = true;
                    }
                }
            }
            #pragma omp task
            {
                dfs(graph, s, visited);
            }
        }
        
    }
    
}

int main(){
    /* Traverse/visit an undirected(why only undirected? ChatGPT)
    graph or tree using dfs algo*/
    vector<vector<int>> graph;
    graph = {{4, 3, 1}, {6, 5, 2}, {1}, {0}, {0}, {1}, {1}};
    int start = 0;
    vector<bool> visited(graph.size(), false);
    vector<int> result;
    stack<int> s;
    s.push(start);
    visited[start] = true;
    dfs(graph, s, visited);
    /* result = dfs(graph, start, visited);
    for(auto it: result)
    {
        cout<< it << " ";
    } */

    cout<< "\n";
    return 0;
}