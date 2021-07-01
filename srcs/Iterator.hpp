#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>

namespace ft
{
	template <typename It>
	struct IteratorTraits
	{
		typedef typename It::iterator_category iterator_category;
		typedef typename It::value_type value_type;
		typedef typename It::difference_type difference_type;
		typedef typename It::pointer pointer;
		typedef typename It::reference reference;
	};

	template <typename Tp>
	struct IteratorTraits<Tp *>
	{
		typedef std::random_access_iterator_tag iterator_category;
		typedef Tp value_type;
		typedef std::ptrdiff_t difference_type;
		typedef Tp *pointer;
		typedef Tp &reference;
	};

	template <typename Tp>
	struct IteratorTraits<const Tp *>
	{
		typedef std::random_access_iterator_tag iterator_category;
		typedef Tp value_type;
		typedef std::ptrdiff_t difference_type;
		typedef const Tp *pointer;
		typedef const Tp &reference;
	};

	template <typename Cat, typename T, typename Dist = std::ptrdiff_t, typename Ptr = T *, typename Ref = T &>
	struct Iterator
	{
		typedef Cat iterator_category;
		typedef T value_type;
		typedef Dist difference_type;
		typedef Ptr pointer;
		typedef Ref reference;
	};

	template <typename It>
	class ReverseIterator;
}

template <typename It>
class ft::ReverseIterator : public ft::Iterator<
								typename ft::IteratorTraits<It>::iterator_category,
								typename ft::IteratorTraits<It>::value_type,
								typename ft::IteratorTraits<It>::difference_type,
								typename ft::IteratorTraits<It>::pointer,
								typename ft::IteratorTraits<It>::reference>
{
private:
	typedef IteratorTraits<It> traits;

public:
	typedef typename traits::value_type value_type;
	typedef typename traits::difference_type difference_type;
	typedef typename traits::pointer pointer;
	typedef typename traits::reference reference;

	ReverseIterator() : current()
	{
	}

	ReverseIterator(const ReverseIterator &rev) : current(rev.current)
	{
	}

	ReverseIterator(const It &it) : current(it)
	{
	}

	ReverseIterator &operator=(const ReverseIterator &rev)
	{
		current = rev.current;
		return *this;
	}

	~ReverseIterator()
	{
	}

	bool operator==(const ReverseIterator &rev)
	{
		return current == rev.current;
	}

	bool operator<(const ReverseIterator &rev)
	{
		return rev.current < current;
	}

	bool operator>(const ReverseIterator &rev)
	{
		return rev < *this;
	}

	bool operator<=(const ReverseIterator &rev)
	{
		return !(*this > rev);
	}

	bool operator>=(const ReverseIterator &rev)
	{
		return !(*this < rev);
	}

	bool operator!=(const ReverseIterator &rev)
	{
		return !(*this == rev);
	}

	const reference operator*() const
	{
		It tmp = current;
		return *--tmp;
	}

	const reference operator->() const
	{
		It tmp = current;
		return *--tmp;
	}

	reference operator*()
	{
		It tmp = current;
		return *--tmp;
	}

	reference operator->()
	{
		It tmp = current;
		return *--tmp;
	}

	ReverseIterator &operator++()
	{
		--current;
		return current;
	}

	ReverseIterator operator++(int)
	{
		ReverseIterator tmp = *this;
		--current;
		return tmp;
	}

	ReverseIterator &operator--()
	{
		++current;
		return *this;
	}

	ReverseIterator operator--(int)
	{
		ReverseIterator tmp = *this;
		++current;
		return tmp;
	}

	ReverseIterator operator+(difference_type n) const
	{
		return ReverseIterator(current - n);
	}

	ReverseIterator &operator+=(difference_type n)
	{
		current -= n;
		return *this;
	}

	ReverseIterator operator-(difference_type n) const
	{
		return ReverseIterator(current + n);
	}

	ReverseIterator &operator-=(difference_type n)
	{
		current += n;
		return *this;
	}

	reference operator[](difference_type n) const
	{
		return *(*this + n);
	}

private:
	It current;
};

#endif
