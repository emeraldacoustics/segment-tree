#include <vector>

using namespace std;

/*
 * build: set f to x
 * modify: add qry to all values in [ql, qr)
 * query: returns minimum value in [ql, qr)
 */

template <class T>
class SegmentTree
{
public:
	class Node
	{
	public:
		T f;
		T g;

		Node(void) : f(0), g(0)
		{

		}

		T get_value(void) const
		{
			return f + g;
		}

		bool operator < (const Node & rhs) const
		{
			return get_value() < rhs.get_value();
		}
	};

	int n;
	vector<Node> nodes;
	int ql, qr;
	T qry;

	SegmentTree(void)
	{

	}

	void resize(const int & n)
	{
		this->n = n;
		int h = 0;
		for (; 1 << h < n; h++);
		nodes.resize(1 << h + 1);
	}

	void push_up(const int & u)
	{
		auto & mne = min(nodes[u << 1], nodes[u << 1 | 1]);
		nodes[u].f = mne.get_value();
		nodes[u].g = 0;
	}

	void push_down(const int & u)
	{
		for (int i = 0; i < 2; i++)
			nodes[u << 1 | i].g += nodes[u].g;
		nodes[u].g = 0;
	}

	void build(const int & u, const int & l, const int & r)
	{
		if (l + 1 == r)
		{
			nodes[u].f = x[l];
			nodes[u].g = 0;
		}
		else if (l < r)
		{
			int m = l + r >> 1;
			build(u << 1, l, m);
			build(u << 1 | 1, m, r);
			push_up(u);
		}
	}

	void modify(const int & u, const int & l, const int & r)
	{
		if (ql <= l && r <= qr)
			nodes[u].g += qry;
		else
		{
			int m = l + r >> 1;
			push_down(u);
			if (ql < m)
				modify(u << 1, l, m);
			if (m < qr)
				modify(u << 1 | 1, m, r);
			push_up(u);
		}
	}

	T query(const int & u, const int & l, const int & r)
	{
		if (ql <= l && r <= qr)
			return nodes[u].get_value();
		else
		{
			int m = l + r >> 1;
			push_down(u);
			T ans = inf;
			if (ql < m)
				ans = min(ans, query(u << 1, l, m));
			if (m < qr)
				ans = min(ans, query(u << 1 | 1, m, r));
			return ans;
		}
	}
};

