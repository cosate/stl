#ifndef GRTW_STL_RBTREE_H
#define GRTW_STL_RBTREE_H

#include"stl_algorithms.h"
#include"stl_allocator.h"
#include"stl_construct.h"
#include"stl_function.h"
#include"stl_iterator.h"
#include"stl_pair.h"

namespace grtw
{
	using RBTreeColorType = bool;
	const RBTreeColorType rb_tree_red = false;
	const RBTreeColorType rb_tree_black = true;

	template<class T>
	struct RBTreeNode
	{
		T value;
		RBTreeColorType color;
		RBTreeNode* parent;
		RBTreeNode* left;
		RBTreeNode* right;

		RBTreeNode() : value(T()), parent(nullptr), left(nullptr), right(nullptr) {}
		~RBTreeNode() { destroy(&value); }
	};

	template<class T, class Reference, class Pointer>
	class RBTree_iterator
	{
	public:
		using iterator_category = bidireactional_iterator_tag;
		using difference_type = ptrdiff_t;
		using value_type = T;
		using reference = Reference;
		using pointer = Pointer;

		using Self = RBTree_iterator<T, Reference, Pointer>;
		using iterator = RBTree_iterator<T, T&, T*>;
		using const_iterator = RBTree_iterator<T, const T&, const T*>;

	private:
		RBTreeNode<T>* node;

	public:
		RBTree_iterator() : node(nullptr) {};

		RBTree_iterator(RBTreeNode<T>* x) : node(x) {}

		RBTree_iterator(const iterator& x) : node(x.getNative()) {}

		RBTreeNode<T>* getNative() { return node; }

		reference operator*() const { return node->value; }

		pointer operator->() const { return &(operator*()); }

		RBTree_iterator& operator=(const iterator& other)
		{
			node = other.node;
			return *this;
		}

		Self& operator++()
		{
			increment();
			return *this;
		}

		Self operator++(int)
		{
			Self tmp = *this;
			increment();
			return tmp;
		}

		Self& operator--()
		{
			decrement();
			return *this;
		}

		Self operator--(int)
		{
			Self tmp = *this;
			decrement();
			return tmp;
		}

		bool operator==(const RBTree_iterator& other) { return node == other.node; }

		bool operator!=(const RBTree_iterator& other) { return node != other.node; }

	private:
		void increment()
		{
			if(node->right != nullptr)
			{
				node = node->right;
				while(node->left != nullptr)
					node = node->left;
			}
			else
			{
				RBTreeNode<T>* p = node->parent;
				while(node == p->right)
				{
					node = p;
					p = p->parent;
				}
				if(node->right != p)
					node = p;
			}
		}

		void decrement()
		{
			if(node->color == rb_tree_red && node->parent->parent == node)
				node = node->right;
			else if(node->left != nullptr)
			{
				RBTreeNode<T>* l = node->left;
				while(l->right != nullptr)
					l = l->right;
				node = l;
			}
			else
			{
				RBTreeNode<T>* p = node->parent;
				while(node == p->left)
				{
					node = p;
					p = p->parent;
				}
				node = p;
			}
		}
	};

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc = allocator<RBTreeNode<Value>>>
	class RBTree
	{
	public:
		using value_type = Value;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const reference;
		using size_type = size_t;
		using difference_type = ptrdiff_t;

		using iterator = RBTree_iterator<value_type, reference, pointer>;
		using const_iterator = RBTree_iterator<value_type, const_reference, const_pointer>;
		using reverse_iterator = reverse_iterator<iterator>;
		using const_reverse_iterator = reverse_iterator<const_iterator>;

	private:
		RBTreeNode<value_type>* header;
		size_type node_count;
		Compare comp;

	private:
		static const Key& getKeyOfValue(RBTreeNode<value_type>* n) { return KeyOfValue()(n->value); }

		RBTreeNode<value_type>* leftmost() { return header->left; }
		RBTreeNode<value_type>* rightmost() { return header->right; }

		RBTreeNode<value_type>* minimum()
		{
			RBTreeNode<value_type>* root = header->parent;
			if(root == nullptr)
				return header;
			else
			{
				while(root->left != nullptr)
					root = root->left;
				return root;
			}
		}

		RBTreeNode<value_type>* maximum()
		{
			RBTreeNode<value_type>* root = header->parent;
			if(root == nullptr)
				return header;
			else
			{
				while(root->right != nullptr)
					root = root->right;
				return root;
			}
		}

		void rotate_left(RBTreeNode<value_type>* node)
		{
			if(node != header)
			{
				RBTreeNode<value_type>* r = node->right;
				RBTreeNode<value_type>* p = node->parent;

				node->right = r->left;
				node->parent = r;

				if(r->left != nullptr)
					r->left->parent = node;

				if(p == header)
					header->parent = r;
				else if(p->left == node)
					p->left = r;
				else
					p->right = r;

				r->left = node;
				r->parent = p;
			}
		}

		void rotate_right(RBTreeNode<value_type>* node)
		{
			if(node != header)
			{
				RBTreeNode<value_type>* l = node->left;
				RBTreeNode<value_type>* p = node->parent;

				node->left = l->right;
				node->parent = l;

				if(l->right != nullptr)
					l->right->parent = node;

				if(p == header)
					header->parent = l;
				else if(p->right == node)
					p->right = l;
				else
					p->left = l;

				l->right = node;
				l->parent = p;
			}
		}
		
		void empty_initialize()
		{
			header->color = rb_tree_red;
			header->parent = nullptr;
			header->left = header;
			header->right = header;
		}

		RBTreeNode<value_type>* create_node(const value_type& v)
		{
			RBTreeNode<value_type>* tmp = Alloc::allocate(1);
			construct(&(tmp->value), v);
			return tmp;
		}

		RBTreeNode<value_type>* clone_node(RBTreeNode<value_type>* other)
		{
			RBTreeNode<value_type>* tmp = create_node(other->value);
			tmp->color = other->color;
			tmp->left = other->left;
			tmp->right = other->right;
			return tmp;
		}

		void destroy_node(RBTreeNode<value_type>* node)
		{
			destroy(node);
			Alloc::deallocate(node);
		}

		void clear(RBTreeNode<value_type>* root)
		{
			if(root != nullptr)
			{
				clear(root->left);
				clear(root->right);
				destroy_node(root);
			}
		}

		void rebalance_insert(RBTreeNode<value_type>*);
		void rebalance_erase(RBTreeNode<value_type>*);
		RBTreeNode<value_type>* copy(RBTreeNode<value_type>*);

		iterator insert(RBTreeNode<value_type>*, const value_type&);

	public:
		RBTree() : header(nullptr), node_count(0), comp()
		{
			header = Alloc::allocate(1);
			empty_initialize();
		}

		RBTree(const Compare& c) : header(nullptr), node_count(0), comp(c)
		{
			header = Alloc::allocate(1);
			empty_initialize();
		}

		RBTree(const RBTree<Key, Value, KeyOfValue, Compare, Alloc>& other) : header(nullptr), node_count(0), comp(other.comp)
		{
			header = Alloc::allocate(1);
			if(other.node_count == 0)
				empty_initialize();
			else
			{
				header->color = rb_tree_red;
				header->parent = copy((other.header)->parent);
				header->left = minimum();
				header->right = maximum();
			}
			node_count = other.node_count;
		}

		RBTree<Key, Value, KeyOfValue, Compare, Alloc>& operator=(const RBTree<Key, Value, KeyOfValue, Compare, Alloc>& other)
		{
			if(this != &other)
			{
				clear();
				node_count = 0;
				comp = other.comp;
				if(other.header->parent == nullptr)
				{
					header->parent = nullptr;
					header->left = header;
					header->right = header;
				}
				else
				{
					header->parent = copy((other.header)->parent);
					header->left = minimum();
					header->right = maximum();
					node_count = other.node_count;
				}
			}
			return *this;
		}

		~RBTree() { clear(); }

		bool operator==(const RBTreeNode<Key, Value, KeyOfValue, Compare, Alloc>& other)
		{
			return size() == other.size() && equal(begin(), end(), other.begin())
		}

		bool operator!=(const RBTreeNode<Key, Value, KeyOfValue, Compare, Alloc>& other)
		{
			return !((*this) == other);
		}

		Compare key_comp() const { return comp; }

		iterator begin() { return leftmost(); }
		iterator end() { return header; }
		const_iterator begin() const { return leftmost(); }
		const_iterator end() const { return header; }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		bool empty() const { return node_count == 0; }
		size_type size() const { return node_count; }

		iterator insert_equal(const value_type& v);
		void insert_equal(const_iterator, const_iterator);
		void insert_equal(const value_type*, const value_type*);

		pair<iterator, bool> insert_unique(const value_type& v);
		void insert_unique(const_iterator, const_iterator);
		void insert_unique(const value_type*, const value_type*);

		void erase(iterator);
		void erase(iterator, iterator);
		size_type erase(const Key&);
		void erase(const Key*, const Key*);
		void clear();

		iterator find(const Key&);
		const_iterator find(const Key&) const;
		size_type count(const Key&) const;
		iterator lower_bound(const Key&);
		const_iterator lower_bound(const Key&) const;
		iterator upper_bound(const Key&);
		const_iterator upper_bound(const Key&) const;
		pair<iterator, iterator> equal_range(const Key&);
		pair<const_iterator, const_iterator> equal_range(const Key&) const;
	};

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	RBTreeNode<typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::value_type>*
	RBTree<Key, Value, KeyOfValue, Compare, Alloc>::copy(RBTreeNode<value_type>* other_root)
	{
		RBTreeNode<value_type>* my_root = clone_node(other_root);
		if(other_root->right)
		{
			my_root->right = copy(other_root->right);
			my_root->right->parent = my_root;
		}
		if(other_root->left)
		{
			my_root->left = copy(other_root->left);
			my_root->left->parent = my_root;
		}
		return my_root;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	void RBTree<Key, Value, KeyOfValue, Compare, Alloc>::rebalance_insert(RBTreeNode<value_type>* node)
	{
		RBTreeNode<value_type>* root = header->parent;
		node->color = rb_tree_red;
		while(node != root && node->parent->color == rb_tree_red)
		{
			RBTreeNode<value_type>* pa = node->parent;
			RBTreeNode<value_type>* grandpa = pa->parent;
			if(grandpa->left == pa)
			{
				RBTreeNode<value_type>* unc = grandpa->right;
				if(unc != nullptr && unc->color == rb_tree_red)
				{
					pa->color = rb_tree_black;
					unc->color = rb_tree_black;
					grandpa->color = rb_tree_red;
					node = grandpa;
				}
				else
				{
					if(node == pa->right)
					{
						node = pa;
						rotate_left(node);
						pa = node->parent;
					}
					pa->color = rb_tree_black;
					grandpa->color = rb_tree_red;
					rotate_right(grandpa);
				}
			}
			else
			{
				RBTreeNode<value_type>* unc = grandpa->left;
				if(unc != nullptr && unc->color == rb_tree_red)
				{
					pa->color = rb_tree_black;
					unc->color = rb_tree_black;
					grandpa->color = rb_tree_red;
					node = grandpa;
				}
				else
				{
					if(node == pa->left)
					{
						node = pa;
						rotate_right(node);
						pa = node->parent;
					}
					pa->color = rb_tree_black;
					grandpa->color = rb_tree_red;
					rotate_left(grandpa);
				}
			}
		}
		node->color = rb_tree_black;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	RBTreeNode<typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::value_type>*
	RBTree<Key, Value, KeyOfValue, Compare, Alloc>::rebalance_erase(RBTreeNode<value_type>* node)
	{
		RBTreeNode<value_type>* to_erase = node;
		RBTreeNode<value_type>* to_fillin = nullptr;
		RBTreeNode<value_type>* to_fillin_parent = node->parent;
		if(node->left == nullptr && node->right == nullptr)
		{
			if(node == header->parent)
				header->parent = nullptr;
			else if(node->parent->left == node)
				node->parent->left = nullptr;
			else
				node->parent->right = nullptr;
		}
		else if((node->left == nullptr && node->right != nullptr) || (node->left != nullptr && node->right == nullptr))
		{
			to_fillin = (node->left == nullptr) ? node->right : node->left;
			to_fillin->parent = node->parent;
			if(node == header->parent)
				header->parent = to_fillin;
			else if(node->parent->left == node)
				node->parent->left = to_fillin;
			else
				node->parent->right = to_fillin;
		}
		else
		{
			typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::iterator it = node;
			to_erase = (++it).getNative();
			to_fillin = to_erase->right;
			to_fillin_parent = to_erase->parent;
			node->left->parent = to_erase;
			to_erase->left = node->left;
			if(to_erase != node->right)
			{
				to_erase->parent->left = to_fillin;
				if(to_fillin != nullptr)
					to_fillin->parent = to_erase->parent;
				to_erase->right = node->right;
				node->right->parent = to_erase;
			}
			else
				to_fillin_parent = to_erase;
			to_erase->parent = node->parent;
			if(node == header-->parent)
				header->parent = to_erase;
			else if(node->parent->left == node)
				node->parent->left = to_erase;
			else
				node->parent->right = to_erase;
			swap(to_erase->color, node->color);
			to_erase = node;
		}
		header->left = minimum();
		header->right = maximum();

		if(to_erase->color == rb_tree_black)
		{
			while(to_fillin != header->parent && (to_fillin == nullptr || to_fillin->color != rb_tree_red))
			{
				if(to_fillin_parent->left == to_fillin)
				{
					if(to_fillin_parent->right->color == rb_tree_red)
					{
						to_fillin_parent->color = rb_tree_red;
						to_fillin_parent->right->color = rb_tree_black;
						rotate_left(to_fillin_parent);
					}
					else
					{
						RBTreeNode<value_type>* bls = to_fillin_parent->right->left;
						RBTreeNode<value_type>* brs = to_fillin_parent->right->right;
						if((bls == nullptr || bls->color == rb_tree_black) && (brs == nullptr || brs->color == rb_tree_black))
						{
							to_fillin_parent->right->color = rb_tree_red;
							to_fillin = to_fillin_parent;
							to_fillin_parent = to_fillin_parent->parent;
						}
						else if(bls->color == rb_tree_red && (brs == nullptr || brs->color == rb_tree_black))
						{
							bls->color = rb_tree_black;
							to_fillin_parent->right->color = rb_tree_red;
							rotate_right(to_fillin_parent->right);
						}
						else
						{
							to_fillin_parent->right->color = to_fillin_parent->color;
							to_fillin_parent->color = rb_tree_black;
							brs->color = rb_tree_black;
							rotate_left(to_fillin_parent);
							break;
						}
					}
				}
				else
				{
					if(to_fillin_parent->left->color == rb_tree_red)
					{
						to_fillin_parent->color = rb_tree_red;
						to_fillin_parent->left->color = rb_tree_black;
						rotate_right(to_fillin_parent);
					}
					else
					{
						RBTreeNode<value_type>* bls = to_fillin_parent->right->left;
						RBTreeNode<value_type>* brs = to_fillin_parent->right->right;
						if((bls == nullptr || bls->color == rb_tree_black) && (brs == nullptr || brs->color == rb_tree_black))
						{
							to_fillin_parent->right->color = rb_tree_red;
							to_fillin = to_fillin_parent;
							to_fillin_parent = to_fillin_parent->parent;
						}
						else if(brs->color == rb_tree_red && (bls == nullptr || bls->color == rb_tree_black))
						{
							brs->color = rb_tree_black;
							to_fillin_parent->left->color = rb_tree_red;
							rotate_left(to_fillin_parent->left);
						}
						else
						{
							to_fillin_parent->left->color = to_fillin_parent->color;
							to_fillin_parent->color = rb_tree_black;
							bls->color = rb_tree_black;
							rotate_right(to_fillin_parent);
							break;
						}
					}
				}
			}
			if(to_fillin != nullptr)
				to_fillin->color = rb_tree_black;
		}
		return to_erase;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	void RBTree<Key, Value, KeyOfValue, Compare, Alloc>::clear()
	{
		if(node_count != 0)
		{
			RBTreeNode<value_type>* root = header->parent;
			clear(root);
			header->left = header;
			header->right = header;
			header->parent = nullptr;
			node_count = 0;
		}
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
	RBTree<Key, Value, KeyOfValue, Compare, Alloc>::find(const Key& k)
	{
		RBTreeNode<value_type>* curr = header->parent;
		RBTreeNode<value_type>* last_greater = header;
		while(curr != nullptr)
		{
			if(comp(getKeyOfValue(curr), k))
				curr = curr->right;
			else
			{
				last_greater = curr;
				curr = curr->left;
			}
		}
		iterator res = iterator(last_greater);
		return (res == end() || comp(k, getKeyOfValue(res->getNative()))) ? end() : res;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator
	RBTree<Key, Value, KeyOfValue, Compare, Alloc>::find(const Key& k) const
	{
		RBTreeNode<value_type>* curr = header->parent;
		RBTreeNode<value_type>* last_greater = header;
		while(curr != nullptr)
		{
			if(comp(getKeyOfValue(curr), k))
				curr = curr->right;
			else
			{
				last_greater = curr;
				curr = curr->left;
			}
		}
		const_iterator res = const_iterator(last_greater);
		return (res == end() || comp(k, getKeyOfValue(res->getNative()))) ? end() : res;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
	RBTree<Key, Value, KeyOfValue, Compare, Alloc>::insert(RBTreeNode<value_type>* its_parent, const value_type& v)
	{
		RBTreeNode<value_type>* z = create_node(v);
		if(its_parent == header)
		{
			its_parent->parent = z;
			its_parent->left = z;
			its_parent->right = z;
		}
		else if(comp(KeyOfValue(v), getKeyOfValue(its_parent)))
		{
			its_parent->left = z;
			if(its_parent == leftmost())
				header->left = z;
		}
		else
		{
			its_parent->right = z;
			if(its_parent == rightmost())
				header->right = z;
		}
		z->parent = its_parent;
		z->left = nullptr;
		z->right = nullptr;
		rebalance_insert(z);
		++node_count;
		return iterator(z);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
	RBTree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(const value_type& v)
	{
		RBTreeNode<value_type>* p = header;
		RBTreeNode<value_type>* c = p->parent;
		while(c != nullptr)
		{
			p = c;
			c = comp(KeyOfValue()(v), getKeyOfValue(c)) ? c->left : c->right;
		}
		return insert(p, v);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	void RBTree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(const value_type* vfirst, const value_type* vlast)
	{
		for(; vfirst != vlast; ++vfirst)
			insert_equal(*vfirst);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	void RBTree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(const_iterator vfirst, const_iterator vlast)
	{
		for(; vfirst != vlast; ++vfirst)
			insert_equal(*vfirst);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	pair<typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::iterator, bool>
	RBTree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(const value_type& v)
	{
		RBTreeNode<value_type>* p = header;
		RBTreeNode<value_type>* c = header->parent;
		while(c != nullptr)
		{
			p = c;
			c = comp(KeyOfValue()(v), getKeyOfValue(c)) ? c->left : c->right;
		}
		iterator it = iterator(p);
		if(comp(KeyOfValue()(v), getKeyOfValue(p)))
		{
			if(it == begin())
				return pair<iterator, bool>(insert(p, v), true);
			else
				--it;
		}
		if(comp(KeyOfValue(j.getNative()), KeyOfValue(v)))
			return pair<insert(p, v), true>
		else
			return pair<it, false>;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	void RBTree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(const value_type* vfirst, const value_type* vlast)
	{
		for(; vfirst != vlast; ++vfirst)
			insert_unique(*vfirst);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	void RBTree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(const_iterator vfirst, const_iterator vlast)
	{
		for(; vfirst != vlast; ++vfirst)
			insert_unique(*vfirst);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
	RBTree<Key, Value, KeyOfValue, Compare, Alloc>::lower_bound(const Key& k)
	{
		RBTreeNode<value_type>* p = header;
		RBTreeNode<value_type>* c = header->parent;
		while(c != nullptr)
		{
			if(!comp(getKeyOfValue(c), k))
			{
				p = c;
				c = c->left;
			}
			else
				c = c->right;
		}
		return iterator(p);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator
	RBTree<Key, Value, KeyOfValue, Compare, Alloc>::lower_bound(const Key& k) const
	{
		RBTreeNode<value_type>* p = header;
		RBTreeNode<value_type>* c = header->parent;
		while(c != nullptr)
		{
			if(!comp(getKeyOfValue(c), k))
			{
				p = c;
				c = c->left;
			}
			else
				c = c->right;
		}
		return const_iterator(p);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
	RBTree<Key, Value, KeyOfValue, Compare, Alloc>::upper_bound(const Key& k)
	{
		RBTreeNode<value_type>* p = header;
		RBTreeNode<value_type>* c = header->parent;
		while(c != nullptr)
		{
			if(comp(k, getKeyOfValue(c)))
			{
				p = c;
				c = c->left;
			}
			else
				c = c->right;
		}
		return iterator(p);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator
	RBTree<Key, Value, KeyOfValue, Compare, Alloc>::upper_bound(const Key& k) const
	{
		RBTreeNode<value_type>* p = header;
		RBTreeNode<value_type>* c = header->parent;
		while(c != nullptr)
		{
			if(comp(k, getKeyOfValue(c)))
			{
				p = c;
				c = c->left;
			}
			else
				c = c->right;
		}
		return const_iterator(p);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	pair<typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::iterator, typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::iterator>
	RBTree<Key, Value, KeyOfValue, Compare, Alloc>::equal_range(const Key& k)
	{
		return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	pair<typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::iterator, typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::iterator>
	RBTree<Key, Value, KeyOfValue, Compare, Alloc>::equal_range(const Key&); const
	{
		return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::size_type
	RBTree<Key, Value, KeyOfValue, Compare, Alloc>::count(const Key& k) const
	{
		pair<const_iterator, const_iterator> p = equal_range(k);
		size_type c = 0;
		distance(p.first, p.second, c);
		return c;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	void RBTree<Key, Value, KeyOfValue, Compare, Alloc>::erase(iterator it)
	{
		RBTreeNode<value_type>* erased = rebalance_erase(getNative(it));
		destroy_node(erased);
		--node_count;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	void RBTree<Key, Value, KeyOfValue, Compare, Alloc>::erase(iterator itfirst, iterator itlast)
	{
		if(itfirst == begin() && itlast == end())
			clear();
		else
			while(itfirst != itlast)
				erase(itfirst);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::size_type
	RBTree<Key, Value, KeyOfValue, Compare, Alloc>::erase(const Key& k)
	{
		pair<iterator, iterator> p = equal_range(k);
		size_type c = 0;
		distance(p.first, p.second, c);
		erase(p.first, p.second);
		return c;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	void RBTree<Key, Value, KeyOfValue, Compare, Alloc>::erase(const Key* k1, const Key* k2)
	{
		while(k1 != k2)
			erase(*k1++);
	}
}

#endif