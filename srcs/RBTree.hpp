/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teyber <teyber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:32:16 by gboucett          #+#    #+#             */
/*   Updated: 2021/02/23 20:40:38 by teyber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "algorithm.hpp"

#include <limits>
#include <cstddef>

namespace ft
{
	template <typename T, typename Compare>
	class RBTree;

	template <typename T, typename Compare>
	class RBTreeNode;
} // namespace ft

#if defined DEBUG && DEBUG == 1

#include <vector>
#include <algorithm>

template<typename T, typename Compare>
void print_dot(std::ostream& os, ft::RBTreeNode<T, Compare> *node, ft::RBTreeNode<T, Compare> *sentinelStart,
	ft::RBTreeNode<T, Compare> *sentinelEnd, std::vector<ft::RBTreeNode<T, Compare> *>& data)
{
	if (std::find(data.begin(), data.end(), node) == data.end())
	{
		if (node == sentinelStart || node == sentinelEnd)
			os << "\t\"" << node << "\"[shape = point]\n";
		else
			os << "\t" << node->data() <<
				" [style = filled, fontcolor = white, fillcolor = " << node->dumpColor() << "]\n";
		data.push_back(node);
	}
	if (node->father())
	{
		os << "\t";
		if (node == sentinelStart || node == sentinelEnd)
			os << '"' << node << '"';
		else
			os << node->data();
		os << " -> " << node->father()->data() << " [color = turquoise];\n";
	}
	if (node->left())
	{
		os << "\t" << node->data() << " -> ";
		if (node->left() == sentinelStart || node->left() == sentinelEnd)
			os << '"' << node->left() << '"';
		else
			os << node->left()->data();
		os << " [color = sienna];\n";
		print_dot(os, node->left(), sentinelStart, sentinelEnd, data);
	}
	if (node->right())
	{
		os << "\t" << node->data() << " -> ";
		if (node->right() == sentinelStart || node->right() == sentinelEnd)
			os << '"' << node->right() << '"';
		else
			os << node->right()->data();
		os << " [color = sienna];\n";
		print_dot(os, node->right(), sentinelStart, sentinelEnd, data);
	}
}

#endif

template <typename T, typename Compare>
class ft::RBTreeNode
{
public:
	typedef T value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	enum RotateType
	{
		LEFT,
		RIGHT
	};

	enum Color {
		BLACK = false,
		RED = true
	};

private:
	typedef RBTreeNode<value_type, Compare> Self;
	typedef Self* SelfPtr;

public:
	RBTreeNode() : _parent(NULL), _left(NULL), _right(NULL), _color(BLACK)
	{}

	RBTreeNode(SelfPtr parent, SelfPtr left, value_type data, SelfPtr right, Color color = BLACK) : _parent(parent), _left(left), _data(data), _right(right), _color(color)
	{}

	RBTreeNode(const_reference data) : _parent(NULL), _left(NULL), _data(data), _right(NULL), _color(BLACK)
	{}

	RBTreeNode(const Self& other)
	{
		*this = other;
	}

	~RBTreeNode()
	{
		_data.~value_type();
	}

	RBTreeNode& operator=(const Self& other)
	{
		_parent = other._parent;
		_left = other._left;
		_data = other._data;
		_right = other._right;
		_color = other._color;
		return *this;
	}

	void recolor()
	{
		_color = _color == BLACK ? RED : BLACK;
	}

	Color& color()
	{
		return _color;
	}

	reference data()
	{
		return _data;
	}

	const_reference data() const
	{
		return _data;
	}

	SelfPtr& left()
	{
		return _left;
	}

	SelfPtr& right()
	{
		return _right;
	}

	SelfPtr sibling()
	{
		if (father())
			return this == father()->left() ? father()->right() : father()->left();
		return NULL;
	}

	SelfPtr& father()
	{
		return _parent;
	}

	SelfPtr father() const
	{
		return _parent;
	}

	SelfPtr grand_father() const
	{
		if (father())
			return father()->father();
		return NULL;
	}

	SelfPtr uncle() const
	{
		if (grand_father())
			return father()->sibling();
		return NULL;
	}

	void rotate(RotateType type, SelfPtr& root)
	{
		if (type == RIGHT)
			rightRotate(root);
		else if (type == LEFT)
			leftRotate(root);
	}

	SelfPtr successor(SelfPtr sentinel)
	{
		if (_right)
			return _right->__min(sentinel);
		else if (this == _parent->_left)
			return _parent;
		return grand_father();
	}

	SelfPtr predecessor(SelfPtr sentinel)
	{
		if (_left)
			return _left->__max(sentinel);
		else if (this == _parent->_right)
			return _parent;
		return grand_father();
	}

	SelfPtr min(SelfPtr sentinel)
	{
		return __min(sentinel);
	}

	SelfPtr max(SelfPtr sentinel)
	{
		return __max(sentinel);
	}

#if defined DEBUG && DEBUG == 1

	std::string dumpColor() const
	{
		return _color == BLACK ? "black" : "red";
	}

#endif

private:
	SelfPtr _parent;
	SelfPtr _left;
	value_type _data;
	SelfPtr _right;
	Color _color;

	void rightRotate(SelfPtr& root)
	{
		SelfPtr pt_left = _left;
		_left = pt_left->_right;

		if (_left)
			_left->_parent = this;

		pt_left->_parent = _parent;

		if (!_parent)
			root = pt_left;
		else if (this == _parent->_left)
			_parent->_left = pt_left;
		else
			_parent->_right = pt_left;

		pt_left->_right = this;
		_parent = pt_left;
	}

	void leftRotate(SelfPtr& root)
	{
		SelfPtr pt_right = _right;
		_right = pt_right->_left;

		if (_right)
			_right->_parent = this;

		pt_right->_parent = _parent;
		if (!_parent)
			root = pt_right;
		else if (this == _parent->_left)
			_parent->_left = pt_right;
		else
			_parent->_right = pt_right;

		pt_right->_left = this;
		_parent = pt_right;
	}

	SelfPtr __min(SelfPtr sentinel)
	{
		SelfPtr current = this;

		while (current->_left && current->_left != sentinel)
			current = current->_left;
		return current;
	}

	SelfPtr __max(SelfPtr sentinel)
	{
		SelfPtr current = this;

		while (current && current->_right && current->_right != sentinel)
			current = current->_right;
		return current;
	}
};

template <typename T, typename Compare>
class ft::RBTree
{
public:
	typedef T value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef size_t size_type;

private:
	typedef RBTreeNode<value_type, Compare>* Node;
	typedef RBTreeNode<value_type, Compare> RawNode;

public:
	RBTree() : _root(NULL), _sentinelStart(new RawNode()), _sentinelEnd(new RawNode()), _size(0)
	{
		_root = _sentinelEnd;
		_sentinelEnd->father() = _root;

	}

	~RBTree()
	{
		clear();
		delete _sentinelEnd;
	}

	void insert(const_reference val)
	{
		Node node = new RawNode(val);

		if (_root == _sentinelEnd || _root == NULL)
			_root = __insert(_root, node);
		else
			__insert(_root, node);

		node->recolor();
		__fix_insertion(node);

		_size++;
	}

	Node search(const_reference val)
	{
		return __search(_root, val);
	}

	void clear()
	{
		__clear(_root);
		_size = 0;
	}

	size_type size() const
	{
		return _size;
	}

	void printInOrder() const
	{
		Node current = _root->min(_sentinelStart);

		std::cout << "Tree :";
		while (current != _sentinelEnd)
		{
			std::cout << " " << current->data();
			current = current->successor(_sentinelStart);
		}
		std::cout << std::endl;
	}

	void printInReverseOrder() const
	{
		Node current = _root->max(_sentinelEnd);

		std::cout << "Tree :";
		while (current != _sentinelStart)
		{
			std::cout << " " << current->data();
			current = current->predecessor(_sentinelEnd);
		}
		std::cout << std::endl;
	}

private:
	Node _root;
	Node _sentinelStart;
	Node _sentinelEnd;
	size_type _size;
	Compare comp;

	Node __search(Node node, const_reference val)
	{
		if (node == NULL || node == _sentinelStart || node == _sentinelEnd || node->data() == val)
			return node;
		if (comp(node->data(), val))
			return __search(node->right(), val);
		return __search(node->left(), val);
	}

	Node __insert(Node node, Node newNode)
	{
		Node target = NULL, x = node;

		while (x != NULL && x != _sentinelStart && x != _sentinelEnd)
		{
			target = x;
			if (comp(newNode->data(), x->data()))
				x = x->left();
			else if (comp(x->data(), newNode->data()))
				x = x->right();
			else
				return (node);
		}

		if (!target)
		{
			target = newNode;
			target->left() = _sentinelStart;
			target->right() = _sentinelEnd;
			_sentinelStart->father() = target;
			_sentinelEnd->father() = target;
		}
		else if (comp(newNode->data(), target->data()))
		{
			if (x == _sentinelStart)
			{
				_sentinelStart->father() = newNode;
				newNode->left() = _sentinelStart;
			}
			target->left() = newNode;
		}
		else if (comp(target->data(), newNode->data()))
		{
			if (x == _sentinelEnd)
			{
				_sentinelEnd->father() = newNode;
				newNode->right() = _sentinelEnd;
			}
			target->right() = newNode;
		}

		if (target != newNode)
			newNode->father() = target;

		return target;
	}

	void __fix_insertion(Node node)
	{
		while (node && node != _root && node->color() == RawNode::RED
			&& node->father()->color() == RawNode::RED)
		{
			if (node->uncle() && node->uncle()->color() == RawNode::RED)
			{
				node->father()->recolor();
				node->uncle()->recolor();
				node->grand_father()->recolor();

				node = node->grand_father();
			}
			else
			{
				bool rel_grand_father = node->grand_father()->left() == node->father();
				bool rel_father = node->father()->left() == node;

				if (rel_grand_father && rel_father)
					__left_left_rotation(node);
				else if (rel_grand_father && !rel_father)
					__left_right_rotation(node);
				else if (!rel_grand_father && !rel_father)
					__right_right_rotation(node);
				else
					__right_left_rotation(node);
				node = node->father();
			}
		}

		_root->color() = RawNode::BLACK;
	}

	void __left_left_rotation(Node node)
	{
		Node gf = node->grand_father();
		Node f = node->father();

		gf->rotate(RawNode::RIGHT, _root);

		typename RawNode::Color tmp = gf->color();
		gf->color() = f->color();
		f->color() = tmp;
	}

	void __left_right_rotation(Node node)
	{
		node->father()->rotate(RawNode::LEFT, _root);
		__left_left_rotation(node);
	}

	void __right_right_rotation(Node node)
	{
		Node gf = node->grand_father();
		Node f = node->father();

		gf->rotate(RawNode::LEFT, _root);

		typename RawNode::Color tmp = gf->color();
		gf->color() = f->color();
		f->color() = tmp;
	}

	void __right_left_rotation(Node node)
	{
		node->father()->rotate(RawNode::RIGHT, _root);
		__right_right_rotation(node);
	}

	void __clear(Node node)
	{
		if (!node || node == _sentinelEnd)
			return ;
		if (node->left() && node->left() != _sentinelEnd)
			__clear(node->left());
		if (node->right() && node->right() != _sentinelEnd)
			__clear(node->right());
		delete node;
	}

#if defined DEBUG && DEBUG == 1

	friend std::ostream& operator<<(std::ostream& os, const ft::RBTree<T, Compare>& rbt)
	{
		using std::endl;

		typename ft::RBTree<T, Compare>::Node root = rbt._root;

		os << "digraph Tree {" << endl;
		if (!root)
			os << std::endl;
		else if (!root->left() && !root->right())
		{
			os << "\t" << root->data() << " [shape = point]\n";
			os << "\t" << root->data() << ";" << endl;
		}
		else
		{
			std::vector<ft::RBTreeNode<T, Compare> *> data;
			print_dot(os, root, rbt._sentinelStart, rbt._sentinelEnd, data);
		}

		os << "}" << endl;

		return os;
	}

#endif
};

#if defined DEBUG && DEBUG == 1

#include <fstream>
#include <string>

template <typename T, typename Compare>
void dumpRBT(const ft::RBTree<T, Compare>& rbt, const std::string& name = "rbt.dot")
{
	std::ofstream ofs(name.c_str());

	ofs << rbt;

	ofs.close();
}

#endif

#endif
