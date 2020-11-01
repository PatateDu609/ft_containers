/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:27:06 by gboucett          #+#    #+#             */
/*   Updated: 2020/11/01 18:01:16 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
#define TREE_HPP

#include "algorithm.hpp"
#include <cstddef>
#include <utility>
#include <string>
#include <iostream>
#include <typeinfo>

namespace ft
{
	enum ColorNode
	{
		RED,
		BLACK
	};
	template <typename Key, typename T, class value_compare>
	class RBTree;
	template <typename Key, typename T, class Node>
	class RBTreeIterator;
	// template <typename Key, typename T, class Node>
	// class RBTreeReverseIterator;
	template <typename Key, typename T>
	struct RBTreeNode
	{
		RBTreeNode *parent;
		RBTreeNode *left;
		RBTreeNode *right;
		ColorNode color;
		std::pair<Key, T> *data;
	};
}

template <typename Key, typename T, class Node>
class ft::RBTreeIterator
{
public:

private:
	Node *node;
};

template <typename Key, typename T, class value_compare>
class ft::RBTree
{
public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef std::pair<const key_type, mapped_type> value_type;
	typedef RBTreeNode<const key_type, mapped_type> Node;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef value_type *pointer;
	typedef const value_type *const_pointer;
	typedef size_t size_type;

	RBTree(const value_compare& comp) : _size(0), _root(NULL), _null(initNode()), _comp(comp)
	{
		_root = _null;
	}

	RBTree(const RBTree& other)
	{
		*this = other;
	}

	RBTree &operator=(const RBTree& other)
	{
		_null = initNode();
		_size = 0;
		_root = _null;
		_comp = other._comp;
		if (other._size)
		{
			const Node *node = other.minimum();
			while (node != NULL)
			{
				insert(value_type(node->data->first, node->data->second));
				node = other.successor(node);
			}
		}
		return *this;
	}

	~RBTree()
	{
		__clear__(_root);
		delete _null->data;
		delete _null;
	}

	Node* insert(const_reference val)
	{
		Node *node = initNode(val);
		node->color = RED;

		insertBST(node);
		_size++;

		if (node == _root)
		{
			node->color = BLACK;
			return (node);
		}
		if (node->parent->parent == NULL || node->parent->parent == _null)
			return (node);
		fixInsert(node);
		return (node);
	}

	void erase(const key_type val)
	{
		Node *node = __search__(_root, val);

		if (node == _null)
			return ;
		_size--;
		deleteHandler(node);
		delete node->data;
		delete node;
		_null->parent = NULL;
	}

	size_type size() const
	{
		return _size;
	}

	size_type max_size() const
	{
		return (std::numeric_limits<size_type>::max() / sizeof(Node));
	}

	pointer search(const key_type& key)
	{
		Node *res = __search__(_root, key);
		if (res != _null)
			return res->data;
		return NULL;
	}

	const_pointer search(const key_type& key) const
	{
		const Node *res = __search__(_root, key);
		if (res != _null)
			return res->data;
		return NULL;
	}

	Node *maximum(Node *node = NULL)
	{
		if (!node)
			node = _root;
		Node *res;
		while (node != _null)
		{
			res = node;
			node = node->right;
		}
		return res;
	}

	const Node *maximum(Node *node = NULL) const
	{
		if (!node)
			node = _root;
		Node *res;
		while (node != _null)
		{
			res = node;
			node = node->right;
		}
		return res;
	}

	Node *minimum(Node *node = NULL)
	{
		if (!node)
			node = _root;
		Node *res = NULL;
		while (node != _null)
		{
			res = node;
			node = node->left;
		}
		return res;
	}

	const Node *minimum(Node *node = NULL) const
	{
		if (!node)
			node = _root;
		Node *res;
		while (node != _null)
		{
			res = node;
			node = node->left;
		}
		return res;
	}

	Node *successor(Node *node)
	{
		Node *p = node->parent;

		if (node == maximum())
			return (NULL);
		if (node->right != _null)
			return (minimum(node->right));
		else if (node == p->left)
			return (p);
		else
			return (p->parent);
	}

	const Node *successor(const Node *node) const
	{
		Node *p = node->parent;

		if (node == maximum())
			return (NULL);
		if (node->right != _null)
			return (minimum(node->right));
		else if (node == p->left)
			return (p);
		else
			return (p->parent);
	}

	Node *predecessor(Node *node)
	{
		Node *p = node->parent;

		if (node == minimum())
			return (NULL);
		if (node->left != _null)
			return (maximum(node->left));
		else if (node == p->right)
			return (p);
		else
			return (p->parent);
	}

	const Node *predecessor(const Node *node) const
	{
		Node *p = node->parent;

		if (node == minimum())
			return (NULL);
		if (node->left != _null)
			return (maximum(node->left));
		else if (node == p->right)
			return (p);
		else
			return (p->parent);
	}

	void print() const
	{
		__print__(_root, "", true);
	}

	void clear()
	{
		__clear__(_root);
		_root = NULL;
		_size = 0;
	}

private:
	Node *initNode(value_type val = value_type())
	{
		Node *node = new Node;

		node->data = new value_type(val);
		node->color = BLACK;
		node->parent = NULL;
		node->right = _null;
		node->left = _null;
		return node;
	}

	void insertBST(Node *node)
	{
		Node *root = _root;
		Node *y = NULL;

		while (root != _null)
		{
			y = root;
			root = _comp(node->data, root->data) ? root->left : root->right;
		}

		node->parent = y;
		if (!y)
			_root = node;
		else if (_comp(node->data, y->data))
			y->left = node;
		else
			y->right = node;
	}

	void deleteHandler(Node *z)
	{
		Node *y = z, *x;
		ColorNode y_original_color = y->color;

		if (z->left == _null)
		{
			x = z->right;
			transplantNode(z, z->right);
		}
		else if (z->right == _null)
		{
			x = z->left;
			transplantNode(z, z->left);
		}
		else
		{
			y = successor(z);
			y_original_color = y->color;
			x = y->right;

			if (y->parent == z)
				x->parent = y;
			else
			{
				transplantNode(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transplantNode(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		if (y_original_color == BLACK)
			fixDelete(x);
	}

	void transplantNode(Node *u, Node *v)
	{
		if (u->parent == NULL || u->parent == _null)
			_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}

	void fixInsert(Node *node)
	{
		Node *u;
		while (node->parent->color == RED)
		{
			u = (node->parent == node->parent->parent->right) ?
				node->parent->parent->left : node->parent->parent->right;
			if (u && u->color == RED) // case where p and u are RED
			{
				node->parent->color = (u->color = BLACK);
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else if (node->parent == node->parent->parent->right)
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					rightRotate(node);
				}
				node->parent->parent->color = RED;
				node->parent->color = BLACK;
				leftRotate(node->parent->parent);
			}
			else if (node->parent == node->parent->parent->left)
			{
				if (node == node->parent->right)
				{
					node = node->parent;
					leftRotate(node);
				}
				node->parent->parent->color = RED;
				node->parent->color = BLACK;
				rightRotate(node->parent->parent);
			}
			if (node == _root)
				break;
		}
		_root->color = BLACK;
	}

	void fixDelete(Node *x)
	{
		Node *w;

		while (x != _root && x->color == BLACK)
		{
			if (x == x->parent->left)
			{
				w = x->parent->right;
				if (w->color == RED)
				{
					w->color = BLACK;
					x->parent->color = RED;
					leftRotate(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == BLACK && w->right->color == BLACK)
				{
					w->color = RED;
					x = x->parent;
				}
				else
				{
					if (w->right->color == BLACK)
					{
						w->left->color = BLACK;
						w->color = RED;
						rightRotate(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					leftRotate(x->parent);
					x = _root;
				}
			}
			else
			{
				w = x->parent->left;
				if (w->color == RED)
				{
					w->color = BLACK;
					x->parent->color = RED;
					rightRotate(x->parent);
					w = x->parent->left;
				}
				if (w->right->color == BLACK && w->left->color == BLACK)
				{
					w->color = RED;
					x = x->parent;
				}
				else
				{
					if (w->left->color == BLACK)
					{
						w->right->color = BLACK;
						w->color = RED;
						leftRotate(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					rightRotate(x->parent);
					x = _root;
				}
			}
		}
	}

	Node *__search__(Node *node, const key_type& key)
	{
		while (node != _null)
		{
			if (key == node->data->first)
				return node;
			if (_comp(key, node->data))
				node = node->left;
			else
				node = node->right;
		}

		return node;
	}

	const Node *__search__(Node *node, const key_type& key) const
	{
		while (node != _null)
		{
			if (key == node->data)
				return node;
			if (_comp(key, node->data))
				node = node->left;
			else
				node = node->right;
		}

		return node;
	}

	void __clear__(Node *node)
	{
		if (node == _null)
			return ;
		delete node->data;
		__clear__(node->left);
		__clear__(node->right);
		delete node;
	}

	void leftRotate(Node *node)
	{
		Node *tmp = node->right;

		node->right = tmp->left;
		if (tmp->left != _null)
			tmp->left->parent = node;
		tmp->parent = node->parent;
		if (!node->parent)
			_root = tmp;
		else if (node == node->parent->left)
			node->parent->left = tmp;
		else
			node->parent->right = tmp;
		tmp->left = node;
		node->parent = tmp;
	}

	void rightRotate(Node *node)
	{
		Node *tmp = node->left;

		node->left = tmp->right;
		if (tmp->right != _null)
			tmp->right->parent = node;
		tmp->parent = node->parent;
		if (!node->parent)
			_root = tmp;
		else if (node == node->parent->right)
			node->parent->right = tmp;
		else
			node->parent->left = tmp;
		tmp->right = node;
		node->parent = tmp;
	}

	Node *getSibling(Node *node)
	{
		if (node == _root)
			return _null;
		if (node == node->parent->left)
			return node->parent->right;
		else
			return node->parent->left;
	}

	void __print__(Node *root, std::string indent, bool last) const
	{
		if (root != _null)
		{
			std::cout << indent;
			if (root->parent == NULL)
			{
				std::cout << "root-----";
				indent += "         ";
			}
			else if (last)
			{
				std::cout << "R-----";
				indent += "     ";
			}
			else
			{
				std::cout << "L-----";
				indent += "|    ";
			}

			std::string color = root->color == BLACK ? "BLACK" : "RED";
			std::cout << "key : " << root->data->first << ", value : " << root->data->second << "(" << color << ")" << std::endl;
			__print__(root->left, indent, false);
			__print__(root->right, indent, true);
		}
	}

	size_type _size;
	Node *_root;
	Node *_null;
	value_compare _comp;
};

#endif
