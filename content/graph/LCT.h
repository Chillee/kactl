/**
 * Author:
 * Description: link-cut Tree. Supports BST-like augmentations. (Can be used in place of HLD).
 * Current implementation supports update value at a node, and query max on a path.
 * For details about the structure, refer to https://en.wikipedia.org/wiki/Link/cut_tree
 * Tested on: http://acm.timus.ru/problem.aspx?num=1553
 * Status: Passes existing fuzz tests (with function names modified).
 */
int gid = 0;
struct Node {
	bool flip = 0;
	 // pp = path parent, p = splay tree parent
	Node *pp, *p, *c[2];
	// add stuff
	int val = 0, cval = 0, id = gid++;
	Node() { pp = p = c[0] = c[1] = 0; }
	void push() {
		if (flip) {
			trav(x, c) if (x) x->flip ^= 1;
			swap(c[0], c[1]); flip = 0;
		}
	}
	void pull() {
		push(), cval = val;
		if(c[0]) c[0]->push(), cval = max(cval, c[0]->cval);
		if(c[1]) c[1]->push(), cval = max(cval, c[1]->cval);
	}
	void rot(bool t) {
		Node *y = p, *z = y->p, *&w = c[t];
		if (z) z->c[z->c[1] == y] = this;
		if (w) w->p = y;
		y->c[!t] = w;
		w = y; p = z;
		y->p = this; y->pull();
	}
	void g() { if (p) p->g(), pp = p->pp; push(); }
	void splay() {
		g();
		while (p) {
			Node* y = p; Node *z = y->p;
			bool t1 = (y->c[1] != this);
			bool t2 = z && (z->c[1] != y) == t1;
			if (t2) y->rot(t1);
			rot(t1);
			if (z && !t2) rot(!t1);
		}
		pull();
	}
	Node* access() {
		for (Node *y = 0, *z = this; z; y = z, z = z->pp) {
			z->splay();
			if (z->c[1]) z->c[1]->pp = z, z->c[1]->p = 0;
			if (y) y->p = z;
			z->c[1] = y; z->pull();
		}
		splay();
		return this;
	}
	Node* makeRoot() {
		access(), flip ^= 1;
		return this;
	}
};
struct LinkCut {
	vector<Node> ns;
	LinkCut(int N) : ns(N) {}
	bool cut(int u) {
		Node *y = ns[v].makeRoot();
		Node *x = ns[u].access();
		if (x->c[0] != y || y->c[1]) return false;
		x->c[0] = y->p = y->pp = 0;
		x->pull();
		return true;
	}
	bool isConnected(int u, int v) {
		Node *x = ns[u].access();
		Node *y = ns[v].access();
		return x == y || x -> pp || x->p;
	}
	int lca(int u, int v) {
		Node *x = ns[u].access(), *y = ns[v].access();
		if (!(x == y || x->pp || x->p)) return -1;
		x->splay();
		return (x->pp ? x->pp : x)->id;
	}
	bool link(int u, int v) {
		if (lca(u, v) != -1) return false;
		auto t = ns[u].makeRoot();
		t->pp = &ns[v];
		return true;
	}
	void update(int u, int c) {
		auto t = ns[u].access();
		t->val += c;
	}
	int query(int u, int v) { // Find max on the path.
		ns[v].makeRoot();
		return ns[u].access()->cval;
	}
};
