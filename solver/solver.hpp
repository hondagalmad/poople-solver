#ifndef SOLVER_HPP
#define SOLVER_HPP
#include "../bfs/bfs.hpp"
const auto &words = GetVals();
int GetPoopleIdx(){
    auto it = std::find(words.begin(),words.end(),"poop");
     if(it == words.end()) throw std::runtime_error("Target word not found\n");
     return it - words.begin();
}
int GetWordIdx(const std::string &s){
    auto it = std::find(words.begin(),words.end(),s);
     if(it == words.end()) throw std::runtime_error("Target word not found\n");
     return it - words.begin();
}
 std::vector<int> path(std::string s){
    if(s.empty())throw std::runtime_error("No string have been provided\n");
    auto paths = BFS(GetWordIdx(s), GetPoopleIdx());
    return paths;
}
std::vector<std::string> solution(const std::vector<int> &path){
    if(path.empty()) throw std::runtime_error("no path found\n");
    std::vector<std::string> ans;
    for(int i = 0; i < (int)path.size(); i++)
        ans.push_back(words[path[i]]);
    return ans;
}
#endif