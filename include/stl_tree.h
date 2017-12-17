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

	struct RBTreeNode_base
	{
		RBTreeColorType color;
		RBTreeNode_base* parent;
		RBTreeNode_base* left;
		RBTreeNode_base* right;

		static RBTreeNode_base* minimum(RBTreeNode_base* root)
		{
			while(root->left != nullptr)
				root = root->left;
			return root;
		}

		static RBTreeNode_base* maximum(RBTreeNode_base* root)
		{
			while(root->right != nullptr)
				root = root->right;
			return root;
		}
	};

	template<class T>
	struct RBTreeNode : public RBTreeNode_base
	{
		T value;
	};

	struct RBTree_iterator_base
	{
		using iterator_category = bidireactional_iterator_tag;
		using difference_type = ptrdiff_t;
		RBTreeNode_base* node;

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
				RBTreeNode_base* p = node->parent;
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
				RBTreeNode_base* l = node->left;
				while(l->right != nullptr)
					l = l->right;
				node = l;
			}
			else
			{
				RBTreeNode_base* p = node->parent;
				while(node == p->left)
				{
					node = p;
					p = p->parent;
				}
				node = p;
			}
		}

		bool operator==(const RBTree_iterator_base& other)
		{
			return node == other.node;
		}

		bool operator!=(const RBTree_iterator_base& other)
		{
			return node != other.node;
		}
	};

	template<class T>
	struct RBTree_iterator : public RBTree_iterator_base
	{
		using value_type = T;
		using reference = T&;
		using pointer = T*;
		using Self = RBTree_iterator<T>;

		RBTree_iterator() {};

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
			return ((RBTreeNode<T>*)node)->value;
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

		Self = operator--(int)
		{
			Self tmp = *this;
			decrement();
			return tmp;
		}
	};
}

#endif