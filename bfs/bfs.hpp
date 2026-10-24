#ifndef BFS_HPP
#define BFS_HPP
#include "../db/dp-init.hpp"
#include <queue>
#include <stdexcept>
#include <vector>
  const auto& adjacency = GetAdjacencyList();
inline std::vector<int> BFS(const int root) {
	const std::size_t vertex_count = adjacency.size();
	if (vertex_count == 0) {
		throw std::runtime_error("cannot run BFS on an empty graph");
	}
	if (root < 0) {
		throw std::invalid_argument("BFS root must be non-negative");
	}
	if (static_cast<std::size_t>(root) >= vertex_count) {
		throw std::out_of_range("BFS root is outside the graph");
	}
	for (const auto& neighbors : adjacency) {
		for (int neighbor : neighbors) {
			if (neighbor < 0 || static_cast<std::size_t>(neighbor) >= vertex_count) {
				throw std::runtime_error("adjacency list contains an out-of-range vertex index");
			}
		}
	}
	std::vector<int> traversal;
	std::vector<bool> visited(vertex_count, false);
	std::queue<int> pending;
	visited[static_cast<std::size_t>(root)] = true;
	pending.push(root);
	while (!pending.empty()) {
		const int current = pending.front();
		pending.pop();
		traversal.push_back(current);
		for (int neighbor : adjacency[static_cast<std::size_t>(current)]) {
			const std::size_t neighbor_index = static_cast<std::size_t>(neighbor);
			if (!visited[neighbor_index]) {
				visited[neighbor_index] = true;
				pending.push(neighbor);
			}
		}
	}
	return traversal;
}
#endif