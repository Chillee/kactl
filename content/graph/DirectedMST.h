/**
 * Author: chilli, Takanori MAEHARA
 * Date: 2019-05-10
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/graph/arborescence.cc
 * Description: Edmonds' algorithm for finding the minimum spanning
 * tree/arborescence of a directed graph, given a root node. Returns (weight, parents), where
 * parents[root] = -1. If no MST exists, returns -1, \{\}.
 * Time: O(E \log V)
 * Status: Fuzz-tested, also tested on NWERC 2018 fastestspeedrun
 */
#pragma once

#include "../data-structures/UnionFind.h"

struct Edge { int a, b; ll w; };
struct Node {
	Edge key;
	Node *l, *r;
	ll delta;
	void prop() {
		key.w += delta;
		if (l) l->delta += delta;
		if (r) r->delta += delta;
		delta = 0;
	}
	Edge top() { prop(); return key; }
};
Node *merge(Node *a, Node *b) {
	if (!a || !b) return a ?: b;
	a->prop(), b->prop();
	if (a->key.w > b->key.w) swap(a, b);
	swap(a->l, (a->r = merge(b, a->r)));
	return a;
}
void pop(Node*& a) { a->prop(); a = merge(a->l, a->r); }

struct DMST {
	vector<Edge> g;
	int n;
	DMST(int _n): n(_n){}
	void addEdge(int a, int b, ll w) { g.push_back({a, b, w}); }
	pair<ll, vi> solve(int r) {
		UF uf(n);
		vector<Node*> heap(n);
		trav(e,g) heap[e.b] = merge(heap[e.b], new Node{e});
		ll res = 0;
		vi seen(n, -1), path(n), par(n, -1);
		seen[r] = r;
		rep(s,0,n) {
			int u = s, qi = 0, w;
			while (seen[u] < 0) {
				path[qi++] = u, seen[u] = s;
				if (!heap[u]) return {-1, {}};
				Edge e = heap[u]->top();
				heap[u]->delta -= e.w, pop(heap[u]);
				res += e.w, u = uf.find(e.a);
				par[e.b] = e.a;
				if (seen[u] == s) {
					Node* cyc = 0;
					do cyc = merge(cyc, heap[w = path[--qi]]);
					while (uf.join(u, w));
					u = uf.find(u);
					heap[u] = cyc, seen[u] = -1;
				}
			}
		}
		return {res, par};
	}
};