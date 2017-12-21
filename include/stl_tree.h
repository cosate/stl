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
	private:
		T value;
		RBTreeColorType color;
		RBTreeNode* parent;
		RBTreeNode* left;
		RBTreeNode* right;

	public:
		RBTreeNode() : value(T()), parent(nullptr), left(nullptr), right(nullptr) {}
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

		RBTree_iterator(RBTreeNode<T>* x)
		{
			node = x;
		}

		RBTree_iterator(const RBTree_iterator<T>& x)
		{
			node = x.node;
		}

		reference operator*() const
		{
			return node->value;
		}

		pointer operator->() const
		{
			return &(operator*());
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

		bool operator==(const RBTree_iterator& other)
		{
			return node == other.node;
		}

		bool operator!=(const RBTree_iterator& other)
		{
			return node != other.node;
		}

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
				RBTreeNode* p = node->parent;
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
				RBTreeNode* l = node->left;
				while(l->right != nullptr)
					l = l->right;
				node = l;
			}
			else
			{
				RBTreeNode* p = node->parent;
				while(node == p->left)
				{
					node = p;
					p = p->parent;
				}
				node = p;
			}
		}
	};

	template<class Key, class Value class KeyOfValue, class Compare, class Alloc = allocator<T>>
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

		using iterator = RBTree_iterator<Value>;
		using const_iterator = RBTree_iterator<const Value>;
		using reverse_iterator = reverse_iterator<iterator>;
		using const_reverse_iterator = reverse_iterator<const_iterator>;

	private:
		RBTreeNode<Value>* header;
		size_type node_count;
		Compare comp;

	private:
		void empty_initialize()
		{

		}

	public:
		RBTree()
		{
			header = Alloc::allocator(1);
			empty_initialize();
		}
		RBTree(const Compare& c)
	}
}

#endif