class Solution {
public:
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
       int N = graph.size();
       vector<int> clean(N,1);
       for(auto i : initial) clean[i]=0;
       vector<vector<int>> infectedBy(N);
       for(auto u : initial){
           unordered_map<int> set;
           dfs(graph,clean,u,set);
           for(auto v : set){
               infectedBy[v].push_back(u);//v被u感染
           }
       }
       vector<int> contribution(N,0);
       for(int v=0;v<N;v++){
           if(infectedBy[v].size == 1){//只被一个感染
               contribution[infectedBy[i][0]]++;//只受u感染的节点个数
           }
       }
       int ans=0,mix_index=0;
       for(int i=0;i<N;i++){
          if(ans<contribution[i])
          {
              ans=contribution[i];
              mix_index=i;
          }
       }
       return mix_index;
    }
    private void dfs(vector<vector<int>>& graph,vector<int>& clean,int u,unordered_map<int>& set){
        for(int v=0;v<graph.size();v++){
            if(graph[u][v] && clean[v] && !set.contains(v)){
                set.insert(v);
                dfs(graph,clean,u,set);
            }
        }
    }
}