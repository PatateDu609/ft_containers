/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 14:54:28 by gboucett          #+#    #+#             */
/*   Updated: 2021/07/04 15:37:08 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <memory>
#include <cstdlib>

#if defined DEBUG && DEBUG == 1
#define __DEBUG

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#endif

#include "algorithm.hpp"

namespace ft
{
	enum RBTreeColor
	{
		BLACK,
		RED
	};

	template <typename T>
	struct RBTreeNode;

	template <typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T> >
	class RBTree;
}

template <typename T>
struct ft::RBTreeNode
{
	typedef T value_type;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef value_type *pointer;
	typedef const value_type *const_pointer;
	typedef RBTreeNode<T> Node;

	Node *parent;
	Node *left;
	value_type data;
	Node *right;
	RBTreeColor color;

	RBTreeNode() : parent(NULL), left(NULL), data(), right(NULL)
	{
	}

	pointer data_addr()
	{
		return &data;
	}

	const_pointer data_addr() const
	{
		return &data;
	}

#ifdef __DEBUG

	std::string dump(bool link)
	{
		std::ostringstream oss;

		if (!link)
		{
			oss << "\"" << this << "\" [shape=point]\n";
			return oss.str();
		}

		std::string color = (this->color == BLACK ? "black" : "red");
		std::string style = (color == "black" ? ", color=white" : "");

		oss << "\"" << this << "\" [label=<";
		oss << "<table border='0' cellborder='1' cellspacing='0'>";
		oss << "<tr>";
		oss << "<td port='left' width='21px'></td>";
		oss << "<td port='middle' bgcolor='" << color
			<< "'><font color='white'>" << data << "</font></td>";
		oss << "<td port='right' width='21px'></td>";
		oss << "</tr>";
		oss << "</table>";
		oss << ">]\n";

		if (left)
			oss << "\t\"" << this << "\":left -- \"" << left << "\":middle\n";
		if (right)
			oss << "\t\"" << this << "\":right -- \"" << right << "\":middle\n";

		return oss.str();
	}

#endif

	static Node *min(Node *n, Node *sentinel)
	{
		while (n->left != sentinel && n->left)
			n = n->left;
		return n;
	}

	static const Node *min(const Node *n, const Node *sentinel)
	{
		while (n->left != sentinel && n->left)
			n = n->left;
		return n;
	}

	static Node *max(Node *n, Node *sentinel)
	{
		while (n->right != sentinel && n->right)
			n = n->right;
		return n;
	}

	static const Node *max(const Node *n, const Node *sentinel)
	{
		while (n->right != sentinel && n->right)
			n = n->right;
		return n;
	}

	static void left_rotate(Node *x)
	{
		if (!x || !x->right)
			return;

		Node *y = x->right;

		x->right = y->left;
		if (y->left)
			y->left->parent = x;

		y->parent = x->parent;
		if (x->parent && x == x->parent->left)
			x->parent->left = y;
		else if (x->parent && x == x->parent->right)
			x->parent->right = y;

		y->left = x;
		x->parent = y;
	}

	static void right_rotate(Node *x)
	{
		if (!x || !x->left)
			return;

		Node *y = x->left;

		x->left = y->right;
		if (y->right)
			y->right->parent = x;

		y->parent = x->parent;
		if (x->parent && x == x->parent->left)
			x->parent->left = y;
		else if (x->parent && x == x->parent->right)
			x->parent->right = y;

		y->right = x;
		x->parent = y;
	}
};

template <typename T, typename Compare, typename Alloc>
class ft::RBTree
{
public:
	typedef T value_type;
	typedef Compare compare_type;
	typedef Alloc allocator_type;

	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef value_type *pointer;
	typedef const value_type *const_pointer;

	typedef std::ptrdiff_t difference_type;
	typedef std::size_t size_type;

private:
	typedef RBTreeNode<value_type> Node;

public:
	RBTree(const compare_type &comp = compare_type(), const allocator_type &alloc = allocator_type()) : root(NULL), _size(0), sentinelStart(NULL), sentinelEnd(NULL), _comp(comp), _alloc(alloc)
	{
		__init_tree();
	}

	~RBTree()
	{
		__clear();
		destroy_node(sentinelEnd);
		destroy_node(sentinelStart);
	}

	bool empty() const
	{
		return _size == 0;
	}

	size_type size() const
	{
		return _size;
	}

	size_type max_size() const
	{
		return allocator_node.max_size();
	}

	void insert(const_reference val)
	{
		Node *node = create_node(val);

		if (empty())
		{
			__insert_empty(node);
			return;
		}

		if (!__insert_bst(node))
		{
			destroy_node(node);
			return;
		}

		if (node->parent && node->parent->parent)
			__rebalance_tree(node);
	}

	void clear()
	{
		__clear();
	}

	allocator_type get_allocator() const
	{
		return _alloc;
	}

#ifdef __DEBUG

	void dump(const std::string &filename)
	{
		std::ofstream ofs(filename.c_str());

		if (!ofs.is_open())
			return;

		ofs << "graph g {\n";
		ofs << "\tnode [shape=plaintext, fontcolor=white, height=.1];\n\n";
		ofs << "\t" << sentinelStart->dump(false);
		ofs << "\t" << sentinelEnd->dump(false);
		dumpTree(ofs, root);
		ofs << "}";

		ofs.close();
	}

	void dumpTree(std::ofstream &ofs, Node *node)
	{
		ofs << "\t" << node->dump(true);

		if (node->left && node->left != sentinelStart)
			dumpTree(ofs, node->left);
		if (node->right && node->right != sentinelEnd)
			dumpTree(ofs, node->right);
	}

#endif

private:
	Node *root;
	size_type _size;
	Node *sentinelStart;
	Node *sentinelEnd;
	compare_type _comp;
	allocator_type _alloc;

	typename allocator_type::template rebind<Node>::other allocator_node;

	void __init_tree()
	{
		sentinelEnd = create_node();
		sentinelStart = create_node();
		sentinelEnd->color = sentinelStart->color = BLACK;
		root = sentinelEnd;
	}

	Node *create_node(const_reference val = value_type())
	{
		Node *node = allocator_node.allocate(1);
		allocator_node.construct(node, Node());

		_alloc.construct(node->data_addr(), val);

		node->color = RED;
		return node;
	}

	void destroy_node(Node *node)
	{
		_alloc.destroy(node->data_addr());
		allocator_node.destroy(node);
		allocator_node.deallocate(node, 1);
	}

	Node *__find(const_reference val, Node **leaf = NULL)
	{
		Node *node = root;

		while (node && node != sentinelEnd && node != sentinelStart)
		{
			if (leaf)
				*leaf = node;
			if (_comp(val, node->data))
				node = node->left;
			else if (_comp(node->data, val))
				node = node->right;
			else
				return node;
		}
		return NULL;
	}

	void __clear()
	{
		__clear_helper(root);
		_size = 0;
		root = sentinelEnd;
	}

	void __clear_helper(Node *node)
	{
		if (!node || node == sentinelStart || node == sentinelEnd)
			return;
		__clear_helper(node->left);
		__clear_helper(node->right);
		destroy_node(node);
	}

	void __left_rotate(Node *x)
	{
		Node::left_rotate(x);

		if (!x->parent->parent)
			root = x->parent;
	}

	void __right_rotate(Node *x)
	{
		Node::right_rotate(x);

		if (!x->parent->parent)
			root = x->parent;
	}

	void __insert_empty(Node *node)
	{
		root = node;
		root->left = sentinelStart;
		root->right = sentinelEnd;
		sentinelStart->parent = sentinelEnd->parent = root;
		_size++;

		root->color = BLACK;
	}

	bool __insert_bst(Node *node)
	{
		Node *target;

		if (__find(node->data, &target)) // No duplicates
			return false;

		node->parent = target;
		if (_comp(node->data, target->data))
		{
			if (target->left)
				target->left->parent = node;
			node->left = target->left; // target->left can either be NULL or sentinelStart
			target->left = node;
		}
		else
		{
			if (target->right)
				target->right->parent = node;
			node->right = target->right; // same as the left case, but with sentinelEnd...
			target->right = node;
		}
		_size++;
		return true; // If it is not a duplicate, insertion will go well
	}

	void __rebalance_tree(Node *node)
	{
		while (node != root && node->parent->color == RED)
		{
			Node *parent = node->parent;
			Node *grand_parent = node->parent->parent;
			Node *uncle;

			if (parent == grand_parent->left)
			{
				uncle = grand_parent->right;
				if (uncle && uncle->color == RED)
				{
					uncle->color = parent->color = BLACK;
					grand_parent->color = RED;
					node = grand_parent;
				}
				else
				{
					if (node == parent->right)
					{
						node = parent;
						__left_rotate(node);
					}
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					__right_rotate(node->parent->parent);
				}
			}
			else
			{
				uncle = grand_parent->left;
				if (uncle && uncle->color == RED)
				{
					uncle->color = parent->color = BLACK;
					grand_parent->color = RED;
					node = grand_parent;
				}
				else
				{
					if (node == parent->left)
					{
						node = parent;
						__right_rotate(node);
					}
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					__left_rotate(node->parent->parent);
				}
			}
		}

		root->color = BLACK;
	}
};

#endif
