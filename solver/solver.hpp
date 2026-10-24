#ifndef SOLVER_HPP
#define SOLVER_HPP
#include "../bfs/bfs.hpp"
#include <cctype>
const auto &words = GetVals();
int GetPoopleIdx(){
    auto it = std::find(words.begin(),words.end(),"poop");
     if(it == words.end()) throw std::runtime_error("Target word not found\n");
     return it - words.begin();
}
int GetWordIdx(const std::string &s){
    std::string normalized = s;
    std::transform(normalized.begin(), normalized.end(), normalized.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    auto it = std::find(words.begin(),words.end(),normalized);
     if(it == words.end()) throw std::runtime_error("Target word not found\n");
     return it - words.begin();
}
std::vector<int> path(std::string s){
    if(s.empty())throw std::runtime_error("No string have been provided\n");
    auto paths = BFS(GetPoopleIdx(), GetWordIdx(s));
    std::reverse(paths.begin(), paths.end());
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
