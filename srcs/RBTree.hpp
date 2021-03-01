/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teyber <teyber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:32:16 by gboucett          #+#    #+#             */
/*   Updated: 2021/03/01 20:34:50 by teyber           ###   ########.fr       */
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
void print_equivalent(std::ostream& os, ft::RBTreeNode<T, Compare> *node)
{
	typedef ft::RBTreeNode<T, Compare> *Node;

	Node current = node->equivalent();

	while (current)
	{
		os << "\t" << (long)current << " [label = " << current->data()
			<< ", style = filled, fontcolor = white, fillcolor = blue]\n";

		os << "\t" << (long)current << " -> " << (long)current->father() << " [color = turquoise];\n";
		os << "\t" << (long)current->father() << " -> " << (long)current << " [color = sienna];\n";
		current = current->equivalent();
	}
}

template<typename T, typename Compare>
void print_dot(std::ostream& os, ft::RBTreeNode<T, Compare> *node, ft::RBTreeNode<T, Compare> *sentinelStart,
	ft::RBTreeNode<T, Compare> *sentinelEnd, std::vector<ft::RBTreeNode<T, Compare> *>& data)
{
	bool seen = true;

	if (std::find(data.begin(), data.end(), node) == data.end())
	{
		if (node == sentinelStart || node == sentinelEnd)
			os << "\t\"" << node << "\"[shape = point]\n";
		else
			os << "\t" << (long)node << " [label = " << node->data() <<
				", style = filled, fontcolor = white, fillcolor = " << node->dumpColor() << "]\n";
		seen = false;
		data.push_back(node);
	}
	if (node->father())
	{
		os << "\t";
		if (node == sentinelStart || node == sentinelEnd)
			os << '"' << node << '"';
		else
			os << (long)node;
		os << " -> " << (long)node->father() << " [color = turquoise];\n";
	}
	if (node->left())
	{
		os << "\t" << (long)node << " -> ";
		if (node->left() == sentinelStart || node->left() == sentinelEnd)
			os << '"' << node->left() << '"';
		else
			os << (long)node->left();
		os << " [color = sienna];\n";
		print_dot(os, node->left(), sentinelStart, sentinelEnd, data);
	}

	if (!seen)
	{
		os << "\n";
		print_equivalent(os, node);
		os << "\n";
	}

	if (node->right())
	{
		os << "\t" << (long)node << " -> ";
		if (node->right() == sentinelStart || node->right() == sentinelEnd)
			os << '"' << node->right() << '"';
		else
			os << (long)node->right();
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
	typedef size_t size_type;

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
	RBTreeNode() :
		_parent(NULL), _left(NULL), _right(NULL), _color(BLACK),
		_equivalent(NULL), _equivalent_root(NULL), _equivalent_last(NULL), _nb_equivalent(0)
	{}

	RBTreeNode(SelfPtr parent, SelfPtr left, value_type data, SelfPtr right, Color color = BLACK) :
		_parent(parent), _left(left), _data(data), _right(right), _color(color),
		_equivalent(NULL), _equivalent_root(NULL), _equivalent_last(NULL), _nb_equivalent(0)
	{}

	RBTreeNode(const_reference data) :
		_parent(NULL), _left(NULL), _data(data), _right(NULL), _color(BLACK),
		_equivalent(NULL), _equivalent_root(NULL), _equivalent_last(NULL), _nb_equivalent(0)
	{}

	RBTreeNode(const Self& other)
	{
		*this = other;
	}

	~RBTreeNode()
	{
		_data.~value_type();
		delete _equivalent;
	}

	RBTreeNode& operator=(const Self& other)
	{
		_parent = other._parent;
		_left = other._left;
		_data = other._data;
		_right = other._right;
		_color = other._color;
		_equivalent = other._equivalent;
		_equivalent_root = other._equivalent_root;
		_equivalent_last = other._equivalent_last;
		_nb_equivalent = other._nb_equivalent;
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

	static Color color(SelfPtr n)
	{
		if (n)
			return n->color();
		return BLACK;
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

	SelfPtr equivalent() const
	{
		return _equivalent;
	}

	size_type duplicates() const
	{
		return _nb_equivalent;
	}

	void add_equivalent(SelfPtr node)
	{
		SelfPtr old = _equivalent_last;

		node->_equivalent_root = _equivalent_root;
		_equivalent_last = node->_equivalent_last = node;
		_nb_equivalent++;

		if (_equivalent == NULL)
		{
			_equivalent = node;
			node->_parent = this;
			return ;
		}
		node->_parent = old;
		old->_equivalent = node;
	}

	void remove_equivalents(SelfPtr oldPlace)
	{
		delete _equivalent;

		_equivalent = oldPlace->_equivalent;
		if (_equivalent)
			_equivalent->_parent = this;
		_equivalent_root = this;
		_equivalent_last = oldPlace->_equivalent_last;
		_nb_equivalent = oldPlace->_nb_equivalent;

		oldPlace->_equivalent = NULL;
		oldPlace->_equivalent_root = NULL;
		oldPlace->_equivalent_last = NULL;
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

	SelfPtr _equivalent;
	SelfPtr _equivalent_root;
	SelfPtr _equivalent_last;
	size_type _nb_equivalent;

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
		bool dup = false;

		if (_root == _sentinelEnd || _root == NULL)
			_root = __insert(_root, node, dup);
		else
			__insert(_root, node, dup);

		if (!dup)
		{
			node->recolor();
			__fix_insertion(node);
		}

		_size++;
	}

	size_type erase(const_reference val)
	{
		if (_root == _sentinelEnd)
			return (0);

		Node v = __search(_root, val);

		if (!v)
			return (0);

		size_type result = v->duplicates() + 1;
		__erase(v);

		_size--;
		return result;
	}

	Node search(const_reference val) const
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

	Node __search(Node node, const_reference val) const
	{
		if (node == NULL || node == _sentinelStart || node == _sentinelEnd || node->data() == val)
			return node == _sentinelEnd || node == _sentinelStart ? NULL : node;
		if (comp(node->data(), val))
			return __search(node->right(), val);
		return __search(node->left(), val);
	}

	Node __insert(Node node, Node newNode, bool& dup)
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
			{
				dup = true;
				x->add_equivalent(newNode);
				return node;
			}
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
					__insert_left_left_rotation(node);
				else if (rel_grand_father && !rel_father)
					__insert_left_right_rotation(node);
				else if (!rel_grand_father && !rel_father)
					__insert_right_right_rotation(node);
				else
					__insert_right_left_rotation(node);
				node = node->father();
			}
		}

		_root->color() = RawNode::BLACK;
	}

	void __insert_left_left_rotation(Node node)
	{
		Node gf = node->grand_father();
		Node f = node->father();

		gf->rotate(RawNode::RIGHT, _root);

		typename RawNode::Color tmp = gf->color();
		gf->color() = f->color();
		f->color() = tmp;
	}

	void __insert_left_right_rotation(Node node)
	{
		node->father()->rotate(RawNode::LEFT, _root);
		__insert_left_left_rotation(node);
	}

	void __insert_right_right_rotation(Node node)
	{
		Node gf = node->grand_father();
		Node f = node->father();

		gf->rotate(RawNode::LEFT, _root);

		typename RawNode::Color tmp = gf->color();
		gf->color() = f->color();
		f->color() = tmp;
	}

	void __insert_right_left_rotation(Node node)
	{
		node->father()->rotate(RawNode::RIGHT, _root);
		__insert_right_right_rotation(node);
	}

	Node __BST_erase(Node x)
	{
		if (x->left() && x->right()
			&& x->left() != _sentinelStart
			&& x->right() != _sentinelEnd) // If node is internal node
			return x->right()->min(_sentinelStart);
		if (x->left() && x->left() != _sentinelStart) // If node has only left child
			return x->left();
		return x->right() == _sentinelEnd ? NULL : x->right(); // Other cases (only right child and no child at all)
	}

	void __erase(Node v)
	{
		Node u = __BST_erase(v);

		bool uvBlack = (RawNode::color(u) == RawNode::BLACK && v->color() == RawNode::BLACK); // Check if double black

		if (u == NULL) // v is a leaf
		{
			__erase_leaf(v, uvBlack);
			return ;
		}
		if (!v->left() || v->left() == _sentinelStart
			|| !v->right() || v->right() == _sentinelEnd) // v have only a single child
		{
			__erase_single_child(v, u, uvBlack);
			return ;
		}

		// v is internal node, therefore swap u and v and recurse
		swap(u->data(), v->data());
		v->remove_equivalents(u);
		__erase(u);
	}

	void __erase_single_child(Node v, Node u, bool uvBlack)
	{
		Node parent = v->father();

		if (v == _root)
		{
			_root->data() = u->data();
			_root->left() = _sentinelStart;
			_root->right() = _sentinelEnd;
			_root->father() = NULL;
			delete u;
		}
		else
		{
			if (v == parent->left())
				parent->left() = u;
			else
				parent->right() = u;
			delete v;
			u->father() = parent;
			if (uvBlack)
				__fix_erase(v);
			else
				u->color() = RawNode::BLACK;
		}
	}

	void __erase_leaf(Node v, bool uvBlack)
	{
		Node parent = v->father();

		if (v == _root)
			_root = _sentinelEnd;
		else
		{
			if (uvBlack)
				__fix_erase(v);
			else if (v->sibling())
				v->sibling()->color() = RawNode::RED;

			if (v == parent->left())
				parent->left() = NULL;
			else
				parent->right() = NULL;
		}
		delete v;
	}

	void __fix_erase(Node x)
	{
		if (x == _root)
			return ;

		Node sibling = x->sibling(), parent = x->father();

		if (!sibling)
			__fix_erase(parent);
		else
		{
			if (sibling->color() == RawNode::RED)
			{
				parent->color() = RawNode::RED;
				sibling->recolor();
				parent->rotate(sibling == parent->left() ? RawNode::RIGHT : RawNode::LEFT, _root);
				__fix_erase(x);
			}
			else
			{
				if (RawNode::color(sibling->right()) == RawNode::RED ||
					RawNode::color(sibling->left()) == RawNode::RED)
					__fix_erase_has_one_red(sibling, parent);
				else
				{
					sibling->recolor();
					if (parent->color() == RawNode::BLACK)
						__fix_erase(parent);
					else
						parent->recolor();
				}
			}
		}
	}

	void __fix_erase_has_one_red(Node sibling, Node parent)
	{
		if (sibling->left() != NULL && sibling->left() != _sentinelStart &&
			sibling->left()->color() == RawNode::RED)
		{
			if (sibling == parent->left())
			{
				sibling->left()->color() = sibling->color();
				sibling->color() = parent->color();
				parent->rotate(RawNode::RIGHT, _root);
			}
			else
			{
				sibling->left()->color() = parent->color();
				sibling->rotate(RawNode::RIGHT, _root);
				parent->rotate(RawNode::LEFT, _root);
			}
		}
		else
		{
			if (sibling == parent->left())
			{
				sibling->right()->color() = parent->color();
				sibling->rotate(RawNode::LEFT, _root);
				parent->rotate(RawNode::RIGHT, _root);
			}
			else
			{
				sibling->right()->color() = sibling->color();
				sibling->color() = parent->color();
				parent->rotate(RawNode::LEFT, _root);
			}
		}
		parent->color() = RawNode::BLACK;
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
