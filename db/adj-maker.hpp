#ifndef ADJ_MAKER_HPP
#define ADJ_MAKER_HPP
#include <bits/stdc++.h>
#include <exception>
#include <stdexcept>
const std:: string poople = "poop";
bool Is_Valid_Edge(const std::string &s, const std::string &k){
    if((int)s.size() != 4 || (int)k.size() != 4)throw std::runtime_error("invalid word in the db\n");
  for(int i = 0; i < 4; i++)
     if(k[i] == poople[i] && k[i] != s[i]) return false;
   return true;
}
std::vector<std::vector<int>> ValidEdges(const std::vector<std::string> &vals){
    if(vals.empty()) throw std::runtime_error("db is empty\n");
    int n = (int) vals.size();
    std::vector<std::vector<int>> adj(n);
    for(int i = 0; i < n; i++)
       for(int j = 0; j < n; j++){
        if(i == j) continue;    
        if(Is_Valid_Edge(vals[i], vals[j])) adj[i].push_back(j);
       }
       return adj;
}
#endif