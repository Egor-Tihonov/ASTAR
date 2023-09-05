#include <queue>
#include "math.h"
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

class Node
{
public:
	double x, y, f, g, h;
	Node* parent;
	Node(double _x = 0, double _y = 0, double _g = 0, double _h = 0, double _f = 0) {
		x = _x;
		y = _y;
		g = _g;
		h = _h;
		f = _f;
	};

	bool operator == (const Node& node) const {
		return x == node.x && y == node.y;
	}

	bool operator < (const Node& node) const {
		return f < node.f;
	}

	void setparent(Node* node) {
		parent = node;
	}
};

bool isSafe(vector<vector<int>>& matr, int i, int j)
{
	return (
		i >= 0 && i < matr.size() && j >= 0 && j < matr[0].size() && matr[i][j] == 1);
}
int main()
{
	vector<vector<int>> matr =
	{
		{1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
		{0, 0, 1, 0, 1, 1, 1, 0, 0, 1},
		{1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
		{0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
		{1, 0, 1, 1, 1, 0, 0, 1, 1, 0},
		{0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
		{0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
		{0, 0, 1, 0, 0, 1, 1, 0, 0, 1},
	};

	Node start_node(9, 2, 0, 12, 12);
	Node end_node(1, 5);

	vector<Node>* open_list;
	open_list = new vector<Node>;
	(*open_list).push_back(start_node);
	int count = 0;
	set<Node> closed_set;
	while (!(*open_list).empty())
	{
		count++;
		sort((*open_list).begin(), (*open_list).end());
		Node* current_node;
		current_node = new Node;
		*current_node = (*open_list).front();

		if ((*current_node) == end_node)
		{
			vector<pair<int, int>> path{};
			while ((*current_node).parent != nullptr) {
				path.push_back(make_pair((*current_node).x, (*current_node).y));
				(*current_node) = *(*current_node).parent;
			}

			path.push_back(make_pair(start_node.x, start_node.y));

			for (int i = path.size() - 1; i >= 0; i--)
			{
				cout << "[" << path[i].first << "; " << path[i].second << "]" << "->";
			}

			delete open_list;
			return 0;
		}

		closed_set.insert((*current_node));
		int dx = 0, dy = 0;
		vector<Node> neighbors;

		if (isSafe(matr, (*current_node).x + 1, (*current_node).y))
		{
			dx = 1;
			dy = 0;
			Node neighbor((*current_node).x + dx, (*current_node).y + dy);
			neighbors.push_back(neighbor);
		}
		if (isSafe(matr, (*current_node).x - 1, (*current_node).y))
		{
			dx = -1;
			dy = 0;
			Node neighbor((*current_node).x + dx, (*current_node).y + dy);
			neighbors.push_back(neighbor);
		}
		if (isSafe(matr, (*current_node).x, (*current_node).y + 1))
		{
			dx = 0;
			dy = 1;
			Node neighbor((*current_node).x + dx, (*current_node).y + dy);
			neighbors.push_back(neighbor);
		}
		if (isSafe(matr, (*current_node).x, (*current_node).y - 1))
		{
			dx = 0;
			dy = -1;
			Node neighbor((*current_node).x + dx, (*current_node).y + dy);
			neighbors.push_back(neighbor);
		}

		vector<Node>::iterator it;

		for (Node neighbor : neighbors)
		{
			if (closed_set.find(neighbor) != closed_set.end())
			{
				continue;
			}

			int new_g = (*current_node).g + 1;

			auto pos_2 = find((*open_list).begin(), (*open_list).end(), neighbor);
			if (pos_2 != (*open_list).end())
			{
				if (new_g < neighbor.g)
				{
					neighbor.g = new_g;
					neighbor.h = abs(end_node.x - neighbor.x) + abs(end_node.y - neighbor.y);
					neighbor.f = neighbor.h + neighbor.g;
					neighbor.parent = &(*current_node);
					sort((*open_list).begin(), (*open_list).end());
				}
			}
			else
			{
				neighbor.g = new_g;
				neighbor.h = abs(end_node.x - neighbor.x) + abs(end_node.y - neighbor.y);
				neighbor.f = neighbor.h + neighbor.g;
				neighbor.parent = &(*current_node);
				(*open_list).push_back(neighbor);
			}
		}
		remove((*open_list).begin(), (*open_list).end(), (*current_node));
	}
}