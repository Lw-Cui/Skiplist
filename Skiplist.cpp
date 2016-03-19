#include "Skiplist.h"
#include "interface.h"

std::shared_ptr<Baselist> Baselist::make_Skiplist() {
	return std::shared_ptr<Baselist>(new Skiplist());
	//return std::make_shared<Baselist>(new Skiplist());
}

Skiplist::Node::Node(int d, int l)
:data(d), array(l) {
}

Skiplist::Node::~Node() {
}

Skiplist::Skiplist():root(new Node(-MAX)), end(new Node(MAX)) {
	root->array[0] = end;
}

Skiplist::~Skiplist() {
}

bool Skiplist::del(int k) {
	if (!find(k)) return false;
	int level = root->array.size() - 1;
	std::shared_ptr<Node> p = root;
	while (true) {
		if (p->array[level]->data > k) {
			/* If (in level) the data of right element of p larger than k,
			from which we could know that the k is in the interval.
			So we decrease level */
			level--;
		} else if (p->array[level]->data == k) {
			/* If (in level) the data of right element of p equal to k,
			then we should move p down to discard all connect to p->array[level],
			and delete it in the end.
			*/
			while (level >= 0) {
				p->array[level] = p->array[level]->array[level];
				level--;
			}
			return true;
		} else {
			/* If (in level) the data of right element of p smaller than k,
			which means that the interval is small, 
			then we could move p to its right to include k.
			*/
			p = p->array[level];
		}
	}
}

bool Skiplist::insert(int k) {
	if (find(k)) return false;
	std::shared_ptr<Node> new_node(new Node(k, get_level()));
	// If cnt is large to root->level then root should increase its level.
	if (new_node->array.size() > root->array.size())
		increase_root_level();
	int level = new_node->array.size() - 1;
	std::shared_ptr<Node> p(root);
	while (true) {
		if (p->array[level]->data > k) {
			/* If (in level) the data of right element of p larger than k,
			from which we could know that the k is in the interval.
			So we insert k into the interval */
			new_node->array[level] = p->array[level];
			p->array[level] = new_node;
			if (--level < 0) return true;//TODO
		} else {
			/* If (in level) the data of right element of p smaller than k,
			which means that the interval is small, 
			then we could move p to its right to include k.
			*/
			p = p->array[level];
		}
	}
}

std::shared_ptr<Skiplist::Node> Skiplist::find_pos(int k) const{
	int level = root->array.size() - 1;
	std::shared_ptr<Node> p(root);
	while (true) {
		if (p->data == k) {
			return p;
		} else if (p->array[level]->data > k) {
			/* If (in level) the data of right element of p larger than k,
			from which we could know that the interval is too much large. 
			So we decrease level to reduce it. */
			if (--level < 0) return p;
		} else {
			/* If (in level) the data of right element of p smaller than k,
			which means that the interval is small, then we could move p
			to its right to include k.
			*/
			p = p->array[level];
		}
	}
}

void Skiplist::increase_root_level() {
	root->array.push_back(end);
}

// Return the level of inserted elements. 
int Skiplist::get_level() const {
	int cnt = 1;
	/* The max level of elements shouldn't larger
	 than root->level + 1 before updating it */
	while (rand() % 2 && cnt != root->array.size() + 1) cnt++;
	return cnt;
}
