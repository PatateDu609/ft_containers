/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:32:16 by gboucett          #+#    #+#             */
/*   Updated: 2021/03/04 17:43:46 by gboucett         ###   ########.fr       */
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

	template <typename T>
	class RBTreeNode;

	template <typename T, typename RawNode>
	class RBTreeIterator;

	template <typename T, typename RawNode>
	class RBTreeReverseIterator;
} // namespace ft

#if defined DEBUG && DEBUG == 1

#include <vector>
#include <algorithm>

template<typename T>
void print_equivalent(std::ostream& os, ft::RBTreeNode<T> *node)
{
	typedef ft::RBTreeNode<T> *Node;

	Node current = node->equivalent();

	while (current)
	{
		os << "\t\"" << current << "\" [label = " << current->data()
			<< ", style = filled, fontcolor = white, fillcolor = blue]\n";

		os << "\t\"" << current << "\" -> \"" << current->father() << "\" [color = turquoise];\n";
		os << "\t\"" << current->father() << "\" -> \"" << current << "\" [color = sienna];\n";
		current = current->equivalent();
	}
}

template<typename T>
void print_dot(std::ostream& os, ft::RBTreeNode<T> *node, ft::RBTreeNode<T> *sentinelStart,
	ft::RBTreeNode<T> *sentinelEnd, std::vector<ft::RBTreeNode<T> *>& data)
{
	bool seen = true;

	if (std::find(data.begin(), data.end(), node) == data.end())
	{
		if (node == sentinelStart || node == sentinelEnd)
			os << "\t\"" << node << "\"[shape = point]\n";
		else
			os << "\t\"" << node << "\" [label = " << node->data() <<
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
			os << "\"" << node << "\"";
		os << " -> \"" << node->father() << "\" [color = turquoise];\n";
	}
	if (node->left())
	{
		os << "\t\"" << node << "\" -> ";
		if (node->left() == sentinelStart || node->left() == sentinelEnd)
			os << '"' << node->left() << '"';
		else
			os << "\"" << node->left() << "\"";
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
		os << "\t\"" << node << "\" -> ";
		if (node->right() == sentinelStart || node->right() == sentinelEnd)
			os << '"' << node->right() << '"';
		else
			os << "\"" << node->right() << "\"";
		os << " [color = sienna];\n";
		print_dot(os, node->right(), sentinelStart, sentinelEnd, data);
	}
}

#endif

template <typename T, typename RawNode>
class ft::RBTreeIterator
{
public:
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;

	typedef T value_type;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef value_type* pointer;
	typedef const value_type *const_pointer;

private:
	typedef RawNode* Node;

public:
	RBTreeIterator() : _ptr(NULL)
	{}

	RBTreeIterator(Node ptr, Node sentinelStart, Node sentinelEnd) :
		_ptr(ptr), _sentinelStart(sentinelStart), _sentinelEnd(sentinelEnd)
	{}

	RBTreeIterator(const RBTreeIterator& other)
	{
		*this = other;
	}

	RBTreeIterator& operator=(const RBTreeIterator& other)
	{
		_ptr = other._ptr;
		_sentinelStart = other._sentinelStart;
		_sentinelEnd = other._sentinelEnd;
		return *this;
	}

	bool operator==(const RBTreeIterator& b) const
	{
		return _ptr == b._ptr;
	}

	bool operator!=(const RBTreeIterator& b) const
	{
		return !(operator==(b));
	}

	reference operator*()
	{
		return _ptr->data();
	}

	const_reference operator*() const
	{
		return _ptr->data();
	}

	pointer operator->()
	{
		return &_ptr->data();
	}

	const_pointer operator->() const
	{
		return &_ptr->data();
	}

	RBTreeIterator& operator++()
	{
		_ptr = RawNode::successor(_ptr, _sentinelStart);
		return *this;
	}

	RBTreeIterator operator++(int)
	{
		RBTreeIterator rbti(*this);
		_ptr = RawNode::successor(_ptr, _sentinelStart);
		return rbti;
	}

	RBTreeIterator& operator--()
	{
		_ptr = RawNode::predecessor(_ptr, _sentinelEnd);
		return *this;
	}

	RBTreeIterator operator--(int)
	{
		RBTreeIterator rbti(*this);
		_ptr = RawNode::predecessor(_ptr, _sentinelEnd);
		return rbti;
	}

private:
	Node _ptr;
	Node _sentinelStart;
	Node _sentinelEnd;
};

template <typename T, typename RawNode>
class ft::RBTreeReverseIterator
{
public:
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;

	typedef T value_type;
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef value_type* pointer;
	typedef const value_type *const_pointer;

private:
	typedef RawNode* Node;

public:
	RBTreeReverseIterator() : _ptr(NULL)
	{}

	RBTreeReverseIterator(Node ptr, Node sentinelStart, Node sentinelEnd) :
		_ptr(ptr), _sentinelStart(sentinelStart), _sentinelEnd(sentinelEnd)
	{}

	RBTreeReverseIterator(const RBTreeReverseIterator& other)
	{
		*this = other;
	}

	RBTreeReverseIterator& operator=(const RBTreeReverseIterator& other)
	{
		_ptr = other._ptr;
		_sentinelStart = other._sentinelStart;
		_sentinelEnd = other._sentinelEnd;
		return *this;
	}

	bool operator==(const RBTreeReverseIterator& b) const
	{
		return _ptr == b._ptr;
	}

	bool operator!=(const RBTreeReverseIterator& b) const
	{
		return !(operator==(b));
	}

	reference operator*()
	{
		return _ptr->data();
	}

	const_reference operator*() const
	{
		return _ptr->data();
	}

	pointer operator->()
	{
		return &_ptr->data();
	}

	const_pointer operator->() const
	{
		return &_ptr->data();
	}

	RBTreeReverseIterator& operator++()
	{
		_ptr = RawNode::predecessor(_ptr, _sentinelEnd);
		return *this;
	}

	RBTreeReverseIterator operator++(int)
	{
		RBTreeReverseIterator rbti(*this);
		_ptr = RawNode::predecessor(_ptr, _sentinelEnd);
		return rbti;
	}

	RBTreeReverseIterator& operator--()
	{
		_ptr = RawNode::successor(_ptr, _sentinelStart);
		return *this;
	}

	RBTreeReverseIterator operator--(int)
	{
		RBTreeReverseIterator rbti(*this);
		_ptr = RawNode::successor(_ptr, _sentinelStart);
		return rbti;
	}

private:
	Node _ptr;
	Node _sentinelStart;
	Node _sentinelEnd;
};

template <typename T>
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
	typedef RBTreeNode<value_type> Self;
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

	SelfPtr equivalent() const
	{
		return _equivalent;
	}

	SelfPtr equivalent_root() const
	{
		return _equivalent_root;
	}

	SelfPtr equivalent_last() const
	{
		return _equivalent_last;
	}

	size_type duplicates() const
	{
		return _nb_equivalent;
	}

	static SelfPtr successor(SelfPtr node, const SelfPtr sentinel)
	{
		if (node->_equivalent_root && node != node->_equivalent_root)
			return node->_parent;
		if (node->_right)
			return min(node->_right, sentinel);
		if (node == node->_parent->_left)
			return node->_parent->_equivalent ? node->_parent->_equivalent_last : node->_parent;
		return node->grand_father()->_equivalent ?
			node->grand_father()->_equivalent_last : node->grand_father();
	}

	static SelfPtr predecessor(SelfPtr node, const SelfPtr sentinel)
	{
		if (node->_equivalent_root && node != node->_equivalent_root)
			return node->_parent;
		if (node->_left)
			return max(node->_left, sentinel);
		else if (node == node->_parent->_right)
			return node->_parent->_equivalent ? node->_parent->_equivalent_last : node->_parent;
		return node->grand_father()->_equivalent ?
			node->grand_father()->_equivalent_last : node->grand_father();
	}

	static SelfPtr min(SelfPtr node, const SelfPtr sentinel)
	{
		SelfPtr current = node;

		while (current->_left && current->_left != sentinel)
			current = current->_left;
		return current->_equivalent ? current->_equivalent_last : current;
	}

	static SelfPtr max(SelfPtr node, const SelfPtr sentinel)
	{
		SelfPtr current = node;

		while (current->_right && current->_right != sentinel)
			current = current->_right;
		return current->_equivalent ? current->_equivalent_last : current;
	}

	void add_equivalent(SelfPtr node)
	{
		SelfPtr old = _equivalent_last;

		node->_equivalent_root = _equivalent_root;
		_equivalent_last = node->_equivalent_last = node;
		_nb_equivalent++;

		if (_equivalent == NULL)
		{
			_equivalent_root = this;
			_equivalent = node;
			node->_parent = this;
			node->_equivalent_root = _equivalent_root;
			return ;
		}
		node->_parent = old;
		old->_equivalent = node;
	}

	void remove_equivalents(SelfPtr oldPlace)
	{
		delete _equivalent;

		_equivalent = oldPlace->_equivalent;
		_equivalent_last = oldPlace->_equivalent_last;
		_equivalent_root = _equivalent ? this : NULL;

		if (_equivalent)
			_equivalent->_parent = this;

		oldPlace->_equivalent = NULL;
	}

#if defined DEBUG && DEBUG == 1

	std::string dumpColor() const
	{
		return _color == BLACK ? "black" : "red";
	}

	void dump() const
	{
		std::cout << "current node : " << this << std::endl;
		std::cout << "left : " << _left << std::endl;
		std::cout << "right : " << _right << std::endl;
		std::cout << "father : " << _parent << std::endl;
		std::cout << "data : " << _data << std::endl;
		std::cout << "equivalent : " << _equivalent << std::endl;
		std::cout << "equivalent root : " << _equivalent_root << std::endl;
		std::cout << "equivalent last : " << _equivalent_last << std::endl;
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
	typedef RBTreeNode<value_type>* Node;
	typedef RBTreeNode<value_type> RawNode;

public:
	typedef RBTreeIterator<value_type, RawNode> iterator;
	typedef RBTreeIterator<const value_type, RawNode> const_iterator;
	typedef RBTreeReverseIterator<value_type, RawNode> reverse_iterator;
	typedef RBTreeReverseIterator<const value_type, RawNode> const_reverse_iterator;

	RBTree() : _root(NULL), _sentinelStart(new RawNode()), _sentinelEnd(new RawNode()), _size(0)
	{
		_root = _sentinelEnd;
		_sentinelEnd->father() = NULL;
	}

	~RBTree()
	{
		clear();
		delete _sentinelEnd;
	}

	iterator begin()
	{
		if (empty())
			return iterator(_root, _sentinelStart, _sentinelEnd);
		return iterator(_sentinelStart->father()->equivalent() ?
			_sentinelStart->father()->equivalent_last() : _sentinelStart->father(),
			_sentinelStart, _sentinelEnd);
	}

	iterator end()
	{
		return iterator(_sentinelEnd, _sentinelStart, _sentinelEnd);
	}

	const_iterator begin() const
	{
		if (empty())
			return const_iterator(_root, _sentinelStart, _sentinelEnd);
		return const_iterator(_sentinelStart->father()->equivalent() ?
			_sentinelStart->father()->equivalent_last() : _sentinelStart->father(),
			_sentinelStart, _sentinelEnd);
	}

	const_iterator end() const
	{
		return const_iterator(_sentinelEnd, _sentinelStart, _sentinelEnd);
	}

	reverse_iterator rbegin()
	{
		if (empty())
			return reverse_iterator(_sentinelStart, _sentinelStart, _sentinelEnd);
		else
			return reverse_iterator(_sentinelEnd->father()->equivalent() ?
				_sentinelEnd->father()->equivalent_last() : _sentinelEnd->father(),
				_sentinelStart, _sentinelEnd);
	}

	reverse_iterator rend()
	{
		return reverse_iterator(_sentinelStart, _sentinelStart, _sentinelEnd);
	}

	const_reverse_iterator rbegin() const
	{
		if (empty())
			return const_reverse_iterator(_sentinelStart, _sentinelStart, _sentinelEnd);
		else
			return const_reverse_iterator(_sentinelEnd->father()->equivalent() ?
				_sentinelEnd->father()->equivalent_last() : _sentinelEnd->father(),
				_sentinelStart, _sentinelEnd);
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(_sentinelStart, _sentinelStart, _sentinelEnd);
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

		_size -= result;
		return result;
	}

	Node search(const_reference val) const
	{
		return __search(_root, val);
	}

	void clear()
	{
		__clear(_root);
		_root = _sentinelEnd;
		_root->father() = NULL;
		_sentinelStart->father() = NULL;
		_size = 0;
	}

	size_type size() const
	{
		return _size;
	}

	bool empty() const
	{
		return size() == 0;
	}

	void printInOrder() const
	{
		const_iterator current = begin();

		std::cout << "Tree :";
		for (; current != end(); current++)
			std::cout << " " << *current;
		std::cout << std::endl;
	}

	void printInReverseOrder() const
	{
		const_reverse_iterator rit = rbegin();

		std::cout << "Tree :";
		for (; rit != rend(); rit++)
			std::cout << " " << *rit;
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
		{
			Node min = RawNode::min(x->right(), _sentinelStart);
			return min->equivalent_root() ? min->equivalent_root() : min;
		}
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
			if (v->left() == _sentinelStart)
			{
				u->left() = _sentinelStart;
				_sentinelStart->father() = u;
			}
			if (v->right() == _sentinelEnd)
			{
				u->right() = _sentinelEnd;
				_sentinelEnd->father() = u;
			}
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

			Node remplacement;
			if (v == parent->left())
				remplacement = parent->left() = v->left();
			else
				remplacement = parent->right() = v->right();

			if (remplacement)
				remplacement->father() = parent;
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
			std::vector<ft::RBTreeNode<T> *> data;
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
