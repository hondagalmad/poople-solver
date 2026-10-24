#ifndef BFS_HPP
#define BFS_HPP

#include "../db/dp-init.hpp"
#include <algorithm>
#include <queue>
#include <stdexcept>
#include <vector>

inline std::vector<int> BFS(const int root, const int target) {
	const auto& adjacency = GetAdjacencyList();
	const std::size_t vertex_count = adjacency.size();
	if (vertex_count == 0) {
		throw std::runtime_error("cannot run BFS on an empty graph");
	}
	if (root < 0 || target < 0) {
		throw std::invalid_argument("BFS root and target must be non-negative");
	}
	if (static_cast<std::size_t>(root) >= vertex_count ||
		static_cast<std::size_t>(target) >= vertex_count) {
		throw std::out_of_range("BFS root or target is outside the graph");
	}
	for (const auto& neighbors : adjacency) {
		for (int neighbor : neighbors) {
			if (neighbor < 0 || static_cast<std::size_t>(neighbor) >= vertex_count) {
				throw std::runtime_error("adjacency list contains an out-of-range vertex index");
			}
		}
	}

	std::vector<int> parent(vertex_count, -1);
	std::queue<int> pending;
	parent[static_cast<std::size_t>(root)] = root;
	pending.push(root);

	while (!pending.empty() && parent[static_cast<std::size_t>(target)] == -1) {
		const int current = pending.front();
		pending.pop();
		for (int neighbor : adjacency[static_cast<std::size_t>(current)]) {
			const std::size_t neighbor_index = static_cast<std::size_t>(neighbor);
			if (parent[neighbor_index] == -1) {
				parent[neighbor_index] = current;
				pending.push(neighbor);
			}
		}
	}

	if (parent[static_cast<std::size_t>(target)] == -1) {
		throw std::runtime_error("target is unreachable from the BFS root");
	}

	std::vector<int> path;
	for (int current = target; current != root;
		 current = parent[static_cast<std::size_t>(current)]) {
		path.push_back(current);
	}
	path.push_back(root);
	std::reverse(path.begin(), path.end());
	return path;
}
#endif