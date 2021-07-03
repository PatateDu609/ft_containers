/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:32:16 by gboucett          #+#    #+#             */
/*   Updated: 2021/03/14 11:16:27 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "algorithm.hpp"
#include "MapUtils.hpp"

#include <limits>
#include <memory>
#include <cstddef>

namespace ft
{
	template <typename T, typename Compare, typename Alloc>
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
#include <iostream>
#include <fstream>
#include <string>

template <typename T>
void print_equivalent(std::ostream &os, ft::RBTreeNode<T> *node)
{
	typedef ft::RBTreeNode<T> *Node;

	Node current = node->equivalent();

	while (current)
	{
		os << "\t\"" << current << "\" [label = \"" << current->data() << " (" << current << ")\""
		   << ", style = filled, fontcolor = white, fillcolor = blue]\n";

		os << "\t\"" << current << "\" -> \"" << current->father() << "\" [color = turquoise];\n";
		os << "\t\"" << current->father() << "\" -> \"" << current << "\" [color = sienna];\n";
		current = current->equivalent();
	}
}

template <typename T>
void print_dot(std::ostream &os, ft::RBTreeNode<T> *node, ft::RBTreeNode<T> *sentinelStart,
			   ft::RBTreeNode<T> *sentinelEnd, std::vector<ft::RBTreeNode<T> *> &data)
{
	bool seen = true;

	if (std::find(data.begin(), data.end(), node) == data.end())
	{
		if (node == sentinelStart || node == sentinelEnd)
			os << "\t\"" << node << "\"[shape = point]\n";
		else
			os << "\t\"" << node << "\" [label = \"" << node->data() << " (" << node << ")\""
			   << ", style = filled, fontcolor = white, fillcolor = " << node->dumpColor() << "]\n";
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

template <typename T, typename Compare, typename Alloc>
void dumpRBT(const ft::RBTree<T, Compare, Alloc> &rbt, const std::string &name = "rbt.dot")
{
	std::ofstream ofs(name.c_str());

	std::cout << "\n\nSentinels :\n";
	std::cout << "\t- start : " << rbt.getSentinelStart() << std::endl;
	std::cout << "\t- end : " << rbt.getSentinelEnd() << std::endl;

	ofs << rbt;

	ofs.close();
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
	typedef value_type *pointer;
	typedef const value_type *const_pointer;

private:
	typedef RawNode *Node;

public:
	RBTreeIterator() : _ptr(NULL)
	{
	}

	RBTreeIterator(Node ptr, Node sentinelStart, Node sentinelEnd) : _ptr(ptr), _sentinelStart(sentinelStart), _sentinelEnd(sentinelEnd)
	{
	}

	RBTreeIterator(const RBTreeIterator &other)
	{
		*this = other;
	}

	RBTreeIterator &operator=(const RBTreeIterator &other)
	{
		_ptr = other._ptr;
		_sentinelStart = other._sentinelStart;
		_sentinelEnd = other._sentinelEnd;
		return *this;
	}

	bool operator==(const RBTreeIterator &b) const
	{
		return _ptr == b._ptr;
	}

	bool operator!=(const RBTreeIterator &b) const
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
		return _ptr->data_address();
	}

	const_pointer operator->() const
	{
		return &_ptr->data();
	}

	RBTreeIterator &operator++()
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

	RBTreeIterator &operator--()
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

	Node ptr() const
	{
		return _ptr;
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
	typedef value_type *pointer;
	typedef const value_type *const_pointer;

private:
	typedef RawNode *Node;

public:
	RBTreeReverseIterator() : _ptr(NULL)
	{
	}

	RBTreeReverseIterator(Node ptr, Node sentinelStart, Node sentinelEnd) : _ptr(ptr), _sentinelStart(sentinelStart), _sentinelEnd(sentinelEnd)
	{
	}

	RBTreeReverseIterator(const RBTreeReverseIterator &other)
	{
		*this = other;
	}

	RBTreeReverseIterator &operator=(const RBTreeReverseIterator &other)
	{
		_ptr = other._ptr;
		_sentinelStart = other._sentinelStart;
		_sentinelEnd = other._sentinelEnd;
		return *this;
	}

	bool operator==(const RBTreeReverseIterator &b) const
	{
		return _ptr == b._ptr;
	}

	bool operator!=(const RBTreeReverseIterator &b) const
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

	RBTreeReverseIterator &operator++()
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

	RBTreeReverseIterator &operator--()
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

#if DEBUG && DEBUG == 1

	friend std::ostream &operator<<(std::ostream &os, const RBTreeReverseIterator &rit)
	{
		rit._ptr->dump(os);
		return os;
	}

#endif

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
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef value_type *pointer;
	typedef const value_type *const_pointer;
	typedef size_t size_type;

	enum RotateType
	{
		LEFT,
		RIGHT
	};

	enum Color
	{
		BLACK = false,
		RED = true
	};

private:
	typedef RBTreeNode<value_type> Self;
	typedef Self *SelfPtr;

public:
	RBTreeNode() : _parent(NULL), _left(NULL), _right(NULL), _color(BLACK)
	{
	}

	RBTreeNode(SelfPtr parent, SelfPtr left, value_type data, SelfPtr right, Color color = BLACK) : _parent(parent), _left(left), _data(data), _right(right), _color(color)
	{
	}

	RBTreeNode(const_reference data) : _parent(NULL), _left(NULL), _data(data), _right(NULL), _color(BLACK)
	{
	}

	RBTreeNode(const Self &other)
	{
		*this = other;
	}

	~RBTreeNode()
	{
		_data.~value_type();
	}

	RBTreeNode &operator=(const Self &other)
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

	Color &color()
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

	pointer data_address()
	{
		return &_data;
	}

	const_pointer data_address() const
	{
		return &_data;
	}

	SelfPtr &left()
	{
		return _left;
	}

	SelfPtr &right()
	{
		return _right;
	}

	SelfPtr sibling()
	{
		if (father())
			return this == father()->left() ? father()->right() : father()->left();
		return NULL;
	}

	SelfPtr &father()
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

	void rotate(RotateType type, SelfPtr &root)
	{
		if (type == RIGHT)
			rightRotate(root);
		else if (type == LEFT)
			leftRotate(root);
	}

	static SelfPtr successor(SelfPtr node, const SelfPtr sentinel)
	{
		if (node->_right && node->_right != sentinel)
			return min(node->_right, sentinel);
		if (node == node->_parent->_left)
			return node->_parent;
		return node->_parent->_parent;
	}

	static SelfPtr predecessor(SelfPtr node, const SelfPtr sentinel)
	{
		if (node->_left)
			return Self::max(node->_left, sentinel);
		if (node == node->_parent->_right)
			return node->_parent;
		return node->grand_father();
	}

	static SelfPtr min(SelfPtr node, const SelfPtr sentinel)
	{
		SelfPtr current = node;

		while (current->_left && current->_left != sentinel)
			current = current->_left;
		return current;
	}

	static SelfPtr max(SelfPtr node, const SelfPtr sentinel)
	{
		SelfPtr current = node;

		while (current->_right && current->_right != sentinel)
			current = current->_right;
		return current;
	}

#if defined DEBUG && DEBUG == 1

	std::string dumpColor() const
	{
		return _color == BLACK ? "black" : "red";
	}

	void dump(std::ostream &os = std::cout) const
	{
		os << "current node : " << this << std::endl;
		os << "left : " << _left << std::endl;
		os << "right : " << _right << std::endl;
		os << "father : " << _parent << std::endl;
		os << "data : " << _data << std::endl;
	}

#endif

private:
	SelfPtr _parent;
	SelfPtr _left;
	value_type _data;
	SelfPtr _right;
	Color _color;

	void rightRotate(SelfPtr &root)
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

	void leftRotate(SelfPtr &root)
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

template <typename T, typename Compare, typename Alloc>
class ft::RBTree
{
public:
	typedef T value_type;
	typedef Compare value_compare;
	typedef Alloc allocator_type;

	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;

	typedef typename allocator_type::size_type size_type;
	typedef typename allocator_type::difference_type difference_type;

private:
	typedef RBTreeNode<value_type> Node;

public:
	typedef RBTreeIterator<value_type, Node> iterator;
	typedef RBTreeIterator<const value_type, Node> const_iterator;
	typedef RBTreeReverseIterator<value_type, Node> reverse_iterator;
	typedef RBTreeReverseIterator<const value_type, Node> const_reverse_iterator;

	RBTree(const value_compare &comp, const allocator_type &alloc) : _comp(comp), allocator(alloc)
	{
		init(comp);
	}

	RBTree(const RBTree &other) : _comp(other._comp)
	{
		allocator = other.allocator;
		init(other._comp);
		*this = other;
	}

	template <typename InputIterator>
	RBTree(InputIterator first, InputIterator last, const value_compare &comp, const allocator_type &alloc) : _comp(comp), allocator(alloc)
	{
		init(comp);
		insert(first, last);
	}

	~RBTree()
	{
		clear();
		destroyNode(_sentinelStart);
		destroyNode(_sentinelEnd);
	}

	RBTree &operator=(const RBTree &other)
	{
		clear();
		insert(other.begin(), other.end());
		return *this;
	}

	iterator begin()
	{
		if (empty())
			return iterator(_root, _sentinelStart, _sentinelEnd);
		return iterator(_sentinelStart->father(), _sentinelStart, _sentinelEnd);
	}

	iterator end()
	{
		return iterator(_sentinelEnd, _sentinelStart, _sentinelEnd);
	}

	const_iterator begin() const
	{
		if (empty())
			return const_iterator(_root, _sentinelStart, _sentinelEnd);
		return const_iterator(_sentinelStart->father(), _sentinelStart, _sentinelEnd);
	}

	const_iterator end() const
	{
		return const_iterator(_sentinelEnd, _sentinelStart, _sentinelEnd);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(empty() ? _sentinelStart : _sentinelEnd->father(),
								_sentinelStart, _sentinelEnd);
	}

	reverse_iterator rend()
	{
		return reverse_iterator(_sentinelStart, _sentinelStart, _sentinelEnd);
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(empty() ? _sentinelStart : _sentinelEnd->father(),
									  _sentinelStart, _sentinelEnd);
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(_sentinelStart, _sentinelStart, _sentinelEnd);
	}

	iterator insert(const_reference val)
	{
		Node *node = newNode(val);

		if (_root == _sentinelEnd || _root == NULL)
		{
			_root = __insert(_root, node);
			return iterator(_root, _sentinelStart, _sentinelEnd);
		}

		node->recolor();
		__insert(_root, node);
		//if ()
		//return iterator(find);
		_size++;

		if (!node->grand_father())
			return iterator(node, _sentinelStart, _sentinelEnd);

		__fix_insertion(node);

		return iterator(node, _sentinelStart, _sentinelEnd);
	}

	template <typename InputIterator>
	void insert(InputIterator first, InputIterator last)
	{
		for (; first != last; first++)
			(void)insert(*first);
	}

	iterator insert(iterator hint, const_reference val)
	{
		(void)hint;
		return insert(val);
	}

	size_type erase(const_reference val)
	{
		if (_root == _sentinelEnd)
			return 0;

		Node *v = __find(_root, val);

		if (!v)
			return 0;

		__erase(v);

		_size--;
		if (empty())
			clear();
		return 1;
	}

	void erase(iterator it)
	{
		Node *node = it.ptr();

		__erase(node);
		_size--;
	}

	void erase(iterator first, iterator last)
	{
		if (first == begin() && last == end())
		{
			clear();
			return;
		}
		Node *tmp;

		while (first != last)
		{
			tmp = first.ptr();
			_size--;
			tmp = __erase(tmp);
			first = iterator(tmp, _sentinelStart, _sentinelEnd);
		}
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

	size_type max_size() const
	{
		return allocator_node.max_size();
	}

	bool empty() const
	{
		return size() == 0;
	}

	void swap(RBTree &other)
	{
		RBTree tmp = other;
		other = *this;
		*this = tmp;
	}

	iterator find(const_reference val)
	{
		Node *result = __find(_root, val);
		return iterator(result ? result : _sentinelEnd, _sentinelStart, _sentinelEnd);
	}

	const_iterator find(const_reference val) const
	{
		Node *result = __find(_root, val);
		return const_iterator(result ? result : _sentinelEnd, _sentinelStart, _sentinelEnd);
	}

	size_type count(const_reference val) const
	{
		Node *result = __find(_root, val);
		return result ? 1 : 0;
	}

	iterator lower_bound(const_reference k)
	{
		iterator result = begin();

		for (; result != end() && _comp(*result, k); result++)
			;
		return result;
	}

	const_iterator lower_bound(const_reference k) const
	{
		const_iterator result = begin();

		for (; result != end() && _comp(*result, k); result++)
			;
		return result;
	}

	iterator upper_bound(const_reference k)
	{
		iterator result = lower_bound(k);

		while (*result == k)
			result++;
		return result;
	}

	const_iterator upper_bound(const_reference k) const
	{
		const_iterator result = lower_bound(k);

		while (*result == k)
			result++;
		return result;
	}

	ft::pair<iterator, iterator> equal_range(const_reference k)
	{
		return ft::make_pair(lower_bound(k), upper_bound(k));
	}

	ft::pair<const_iterator, const_iterator> equal_range(const_reference k) const
	{
		return ft::make_pair(lower_bound(k), upper_bound(k));
	}

	allocator_type get_allocator() const
	{
		return allocator;
	}

#if defined DEBUG && DEBUG == 1

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
		{
			std::cout << " " << *rit;
		}
		std::cout << std::endl;
	}

	const Node *getSentinelStart() const
	{
		return _sentinelStart;
	}

	const Node *getSentinelEnd() const
	{
		return _sentinelEnd;
	}

#endif

private:
	Node *_root;
	Node *_sentinelStart;
	Node *_sentinelEnd;
	size_type _size;
	value_compare _comp;

	allocator_type allocator;
	typename allocator_type::template rebind<Node>::other allocator_node;

	Node *newNode(const_reference val = value_type())
	{
		Node *node = allocator_node.allocate(1);
		allocator_node.construct(node, Node());
		allocator.construct(node->data_address(), val);

		return node;
	}

	void destroyNode(Node *node)
	{
		allocator.destroy(node->data_address());
		allocator_node.destroy(node);
		allocator_node.deallocate(node, 1);
	}

	void init(const value_compare &comp)
	{
		_comp = comp;
		_sentinelStart = newNode();
		_sentinelEnd = newNode();
		_size = 0;
		_root = _sentinelEnd;
	}

	Node *__find(Node *node, const_reference val) const
	{
		bool isEq = false;

		if (node && !_comp(val, node->data()) && !_comp(node->data(), val))
			isEq = true;

		if (node == NULL || node == _sentinelStart || node == _sentinelEnd || isEq)
			return node == _sentinelEnd || node == _sentinelStart ? NULL : node;
		if (_comp(node->data(), val))
			return __find(node->right(), val);
		return __find(node->left(), val);
	}

	Node *__insert(Node *node, Node *newNode)
	{
		Node *target = NULL, *x = node;

		while (x != NULL && x != _sentinelStart && x != _sentinelEnd)
		{
			// Don't insert anything if duplicates
			target = x;
			if (_comp(newNode->data(), x->data()))
				x = x->left();
			else if (_comp(x->data(), newNode->data()))
				x = x->right();
			else
				return NULL;
		}

		if (!target)
		{
			target = newNode;
			target->left() = _sentinelStart;
			target->right() = _sentinelEnd;
			_sentinelStart->father() = target;
			_sentinelEnd->father() = target;
		}
		else if (_comp(newNode->data(), target->data()))
		{
			if (x == _sentinelStart)
			{
				_sentinelStart->father() = newNode;
				newNode->left() = _sentinelStart;
			}
			target->left() = newNode;
		}
		else if (_comp(target->data(), newNode->data()))
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

	void __fix_insertion(Node *node)
	{
		while (node->father()->color() == Node::RED)
		{
			Node *father = node->father();
			Node *grand_father = node->grand_father();
			Node *uncle = node->uncle();

			if (father == grand_father->right())
			{
				if (uncle && uncle->color() == Node::RED)
				{
					uncle->color() = father->color() = Node::BLACK;
					grand_father->color() = Node::RED;
					node = grand_father;
				}
				else
				{
					if (node == father->left())
					{
						node = father;
						node->rotate(Node::RIGHT, _root);
						father = node->father();
						grand_father = node->grand_father();
					}
					father->color() = Node::BLACK;
					grand_father->color() = Node::RED;
					grand_father->rotate(Node::LEFT, _root);
				}
			}
			else
			{
				if (uncle && uncle->color() == Node::RED)
				{
					uncle->color() = father->color() = Node::RED;
					grand_father->color() = Node::RED;
					node = grand_father;
				}
				else
				{
					if (node == father->right())
					{
						node = father;
						node->rotate(Node::LEFT, _root);
						father = node->father();
						grand_father = node->grand_father();
					}
					father->color() = Node::BLACK;
					grand_father->color() = Node::RED;
					grand_father->rotate(Node::RIGHT, _root);
				}
			}

			if (node == _root)
				break;
		}

		_root->color() = Node::BLACK;
	}

	void __insert_left_left_rotation(Node *node)
	{
		Node *gf = node->grand_father();
		Node *f = node->father();

		gf->rotate(Node::RIGHT, _root);

		typename Node::Color tmp = gf->color();
		gf->color() = f->color();
		f->color() = tmp;
	}

	void __insert_left_right_rotation(Node *node)
	{
		node->father()->rotate(Node::LEFT, _root);
		__insert_left_left_rotation(node);
	}

	void __insert_right_right_rotation(Node *node)
	{
		Node *gf = node->grand_father();
		Node *f = node->father();

		gf->rotate(Node::LEFT, _root);

		typename Node::Color tmp = gf->color();
		gf->color() = f->color();
		f->color() = tmp;
	}

	void __insert_right_left_rotation(Node *node)
	{
		node->father()->rotate(Node::RIGHT, _root);
		__insert_right_right_rotation(node);
	}

	Node *__BST_erase(Node *x) // Return the target erase
	{
		if (x->left() && x->right() && x->left() != _sentinelStart && x->right() != _sentinelEnd) // If node is internal node
			return Node::min(x->right(), _sentinelStart);
		if (x->left() && x->left() != _sentinelStart) // If node has only left child
			return x->left();
		return x->right() == _sentinelEnd ? NULL : x->right(); // Other cases (only right child and no child at all)
	}

	Node *__erase(Node *v)
	{
		Node *u = __BST_erase(v);
		Node *suc = Node::successor(v, _sentinelStart);

		bool uvBlack = (Node::color(u) == Node::BLACK && v->color() == Node::BLACK); // Check if double black

		if (u == NULL) // v is a leaf
		{
			__erase_leaf(v, uvBlack);
			return suc;
		}
		if (!v->left() || v->left() == _sentinelStart || !v->right() || v->right() == _sentinelEnd) // v have only a single child
		{
			__erase_single_child(v, u, uvBlack);
			return u;
		}

		// v is internal node, so swap u and v and recurse
		ft::swap(u->data(), v->data());
		return __erase(u);
	}

	void __erase_single_child(Node *v, Node *u, bool uvBlack)
	{
		Node *parent = v->father();

		if (v == _root)
		{
			_root->data() = u->data();
			_root->left() = _sentinelStart;
			_root->right() = _sentinelEnd;
			_root->father() = NULL;
			destroyNode(u);
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
			destroyNode(v);
			u->father() = parent;
			if (uvBlack)
				__fix_erase(v);
			else
				u->color() = Node::BLACK;
		}
	}

	void __erase_leaf(Node *v, bool uvBlack)
	{
		Node *parent = v->father();

		if (v == _root)
			_root = _sentinelEnd;
		else
		{
			if (uvBlack)
				__fix_erase(v);
			else if (v->sibling())
				v->sibling()->color() = Node::RED;

			Node *remplacement; // Reconnects node child (it may be NULL or a sentinel)
			if (v == parent->left())
				remplacement = parent->left() = v->left();
			else
				remplacement = parent->right() = v->right();

			if (remplacement)
				remplacement->father() = parent;
		}
		destroyNode(v);
	}

	void __fix_erase(Node *x)
	{
		if (x == _root)
			return;

		Node *sibling = x->sibling(), *parent = x->father();

		if (!sibling)
			__fix_erase(parent);
		else
		{
			if (sibling->color() == Node::RED)
			{
				parent->color() = Node::RED;
				sibling->recolor();
				parent->rotate(sibling == parent->left() ? Node::RIGHT : Node::LEFT, _root);
				__fix_erase(x);
			}
			else
			{
				if (Node::color(sibling->right()) == Node::RED ||
					Node::color(sibling->left()) == Node::RED)
					__fix_erase_has_one_red(sibling, parent);
				else
				{
					sibling->recolor();
					if (parent->color() == Node::BLACK)
						__fix_erase(parent);
					else
						parent->recolor();
				}
			}
		}
	}

	void __fix_erase_has_one_red(Node *sibling, Node *parent)
	{
		if (sibling->left() != NULL && sibling->left() != _sentinelStart &&
			sibling->left()->color() == Node::RED)
		{
			if (sibling == parent->left())
			{
				sibling->left()->color() = sibling->color();
				sibling->color() = parent->color();
				parent->rotate(Node::RIGHT, _root);
			}
			else
			{
				sibling->left()->color() = parent->color();
				sibling->rotate(Node::RIGHT, _root);
				parent->rotate(Node::LEFT, _root);
			}
		}
		else
		{
			if (sibling == parent->left())
			{
				sibling->right()->color() = parent->color();
				sibling->rotate(Node::LEFT, _root);
				parent->rotate(Node::RIGHT, _root);
			}
			else
			{
				sibling->right()->color() = sibling->color();
				sibling->color() = parent->color();
				parent->rotate(Node::LEFT, _root);
			}
		}
		parent->color() = Node::BLACK;
	}

	void __clear(Node *node)
	{
		if (!node || node == _sentinelEnd || node == _sentinelStart)
			return;
		if (node->left() && node->left() != _sentinelStart)
			__clear(node->left());
		if (node->right() && node->right() != _sentinelEnd)
			__clear(node->right());
		destroyNode(node);
	}

#if defined DEBUG && DEBUG == 1

	friend std::ostream &operator<<(std::ostream &os, const ft::RBTree<T, Compare, Alloc> &rbt)
	{
		using std::endl;

		typename ft::RBTree<T, Compare, Alloc>::Node *root = rbt._root;

		os << "digraph Tree {" << endl;
		if (!root)
			os << std::endl;
		else if (!root->left() && !root->right())
		{
			os << "\t\"" << root->data() << "\" [shape = point]\n";
			os << "\t\"" << root->data() << "\";" << endl;
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

#endif
