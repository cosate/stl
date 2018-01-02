#ifndef GRTW_STL_TREE_H
#define GRTW_STL_TREE_H

#include"stl_algorithms.h"
#include"stl_allocator.h"
#include"stl_construct.h"
#include"stl_function.h"
#include"stl_iterator.h"

namespace grtw
{
	using RBTreeColorType = bool;
	const RBTreeColorType rb_tree_red = false;
	const RBTreeColorType rb_tree_black = true;

	template<class T>
	class RBTreeNode
	{
	public:
		T value;
		RBTreeColorType color;
		RBTreeNode* parent;
		RBTreeNode* left;
		RBTreeNode* right;

		RBTreeNode() : value(T()), parent(nullptr), left(nullptr), right(nullptr) {}
		~RBTreeNode() { destroy(&value); }
	};

	template<class T>
	class RBTree_iterator
	{
	public:
		using iterator_category = bidireactional_iterator_tag;
		using difference_type = ptrdiff_t;
		using value_type = T;
		using reference = T&;
		using pointer = T*;

		using Self = RBTree_iterator<T>;

	private:
		RBTreeNode<T>* node;

	public:
		RBTree_iterator() : node(nullptr) {};

		RBTree_iterator(RBTreeNode<T>* x) : node(x) {}

		RBTree_iterator(const RBTree_iterator<T>& x) : node(x.getNative()) {}

		RBTreeNode<T>* getNative() { return node; }

		reference operator*() const { return node->value; }

		pointer operator->() const { return &(operator*()); }

		RBTree_iterator& operator=(const RBTree_iterator<T>& other)
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

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc = allocator<RBTreeNode<T>>>
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

		using iterator = RBTree_iterator<value_type>;
		using const_iterator = RBTree_iterator<const value_type>;
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

		RBTreeNode<value_type>* creater_node(const value_type& v)
		{
			RBTreeNode<value_type>* tmp = Alloc::allocate(1);
			construct(&(tmp->value), v);
			return tmp;
		}

		RBTreeNode<value_type>* clone_node(RBTreeNode<value_type>* other)
		{
			RBTreeNode<value_type>* tmp = creater_node(other->value);
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
		void copy(RBTreeNode<value_type>*);

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

		RBTree(const RBTree<T, Compare, Alloc>& other)
		{
			header = Alloc::allocate(1);
			if(other.node_count == 0)
				empty_initialize();
			else
			{
				header->color = rb_tree_red;
				header->parent = copy(RBTreeNode<value_type>* other.header);
				header->left = minimum();
				header->right = maximum();
			}
			node_count = other.node_count;
		}

		RBTree<T, Compare, Alloc>& operator=(const RBTree<T, Compare, Alloc>&);

		~RBTree() { clear(); }

		iterator begin() { return iterator(leftmost()); }
		iterator end() { return iterator(header); }
		const_iterator begin() const { return iterator(leftmost()); }
		const_iterator end() const { return iterator(header); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		bool empty() const { return node_count == 0; }
		size_type size() const { return node_count; }

		iterator insert_unique(const value_type& v);
		iterator insert_equal(const value_type& v);
		void erase(iterator);
		void erase(iterator, iterator);
		void erase(const Key&);
		void erase(const Key&, const Key&);
		void clear();

		iterator find(const Key&);
		const_iterator find(const Key&) const;
		size_type count(const Key&);
	};

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	void RBTree<Key, Value, KeyOfValue, Compare, Alloc>::rebalance_insert(RBTreeNode<Value>* node)
	{
		RBTreeNode<Value>* root = header->parent;
		node->color = rb_tree_red;
		while(node != root && node->parent->color == rb_tree_red)
		{
			RBTreeNode<Value>* pa = node->parent;
			RBTreeNode<Value>* grandpa = pa->parent;
			if(grandpa->left == pa)
			{
				RBTreeNode<Value>* unc = grandpa->right;
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
				RBTreeNode<Value>* unc = grandpa->left;
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
	void RBTree<Key, Value, KeyOfValue, Compare, Alloc>::rebalance_erase(RBTreeNode<Value>* node)
	{
		RBTreeNode<Value>* to_erase = node;
		if(node->left != nullptr && node->right != nullptr)
		{
			typename RBTree<Key, Value, KeyOfValue, Compare, Alloc>::iterator it = node;
			to_erase = (++it).getNative();
		}
		RBTreeNode<Value>* to_fillin = nullptr;
		if(to_erase->left != nullptr)
			to_fillin = to_erase->left;
		else
			to_fillin = to_erase->right;

		if(to_erase != node)
		{
			node->left->parent = to_erase;
			to_erase->left = node->left;
			if(to_erase != node->right)
			{
				if(to_fillin != nullptr)
					to_fillin->parent = to_erase->parent;
				to_erase->parent->left = to_fillin;
				to_erase->right = node->right;
				node->right->parent = to_erase;
			}
			if(node == header->parent)
				header->parent = to_erase;
			else
			{
				if(node->parent->left == node)
					node->parent->left = to_erase;
				else
					node->parent->right = to_erase;
			}
			to_erase->parent = node->parent;
			to_erase->color = node->color;
		}
		else
		{
			if(to_fillin != nullptr)
				to_fillin->parent = to_erase->parent;

			if(to_erase->parent == header)
				header->parent = to_fillin;
			else
			{
				if(to_erase->parent->left == to_erase)
					to_erase->parent->left = to_fillin;
				else
					to_erase->parent->right = to_fillin;
			}
			if(leftmost() == to_erase)
			{
				if(to_erase->right == nullptr)
					header->left = to_erase->parent;
				else
					header->left = minimum();
			}
			if(rightmost() == to_erase)
			{
				if(to_erase->left == nullptr)
					header->left = to_erase->parent;
				else
					header->left = maximum();
			}
		}
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	void RBTree<Key, Value, KeyOfValue, Compare, Alloc>::clear()
	{
		if(node_count != 0)
		{
			RBTreeNode<Value>* root = header->parent;
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
		RBTreeNode<Value>* curr = header->parent;
		RBTreeNode<Value>* last_greater = header;
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
		RBTreeNode<Value>* curr = header->parent;
		RBTreeNode<Value>* last_greater = header;
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
	RBTree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(const Value& v)
	{

	}
}

#endif