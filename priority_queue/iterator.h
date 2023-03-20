#pragma once

template<class Iterator, class Ref, class Ptr>
class ReverseIterator
{
public:
	typedef ReverseIterator<Iterator, Ref, Ptr> Self;

	ReverseIterator(Iterator it)
		:_it(it)
	{}

	Ref operator*()
	{
		Iterator tmp = _it;
		return *(--tmp);
	}

	Ptr operator->()
	{
		return &(operator*());
	}

	Self& operator++()
	{
		--_it;
		return *this;
	}

	Self& operator--()
	{
		++_it;
		return *this;
	}

	bool operator!=(const Self& s)const
	{
		return _it != s._it;
	}


private:
	Iterator _it;
};