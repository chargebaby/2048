#ifndef _3D_GAME_2048_STRUCT_H_
#define _3D_GAME_2048_STRUCT_H_

#pragma once

#include <assert.h>
#include <algorithm>
#include <functional>
#include <vector>
#include <list>

#define SAFE_DELETE(ptr) \
	if (ptr) { delete (ptr); (ptr) = NULL; }

#define DEREFONE(ptr) (*(ptr))

#define DEREFTWO(ptr) (**(ptr))

struct Digital
{
	int		value_;
	bool	active_;
};

class Struct2048
{
// 	friend void print(const Struct2048 &s);

	typedef std::vector<Digital*>		DigPtrVec;
	typedef DigPtrVec::iterator			DigPtrVecIter;

	typedef std::list<DigPtrVecIter>	DigRef;
	typedef std::vector<DigRef>			DigRefVec;


public:
	Struct2048();
	Struct2048(int rows, int cols);
	~Struct2048();

public:
	void Random();

	void Up();

	void Down();

	void Left();

	void Right();

private:
	void CreatePlaneRef();

	void UpOrDown(bool down);

	void LeftOrRight(bool right);

	void CreateRowRef();

	void CreateColRef();

	void PushBackRef(DigRef& dig_ref, DigRefVec& ref_vec,
				const int index, const int direction);

private:
	static void Merge(DigRef &list, bool reverse);

	static void MergeBatch(DigRefVec &ref_vec, bool reverse);

	static void ActiveNode(DigPtrVecIter iter);

	template<class InputIterator>
	static void ForEachCmp(InputIterator first, InputIterator last, InputIterator key);

	template<class InputIterator>
	static void CompareIter(InputIterator cur, InputIterator key);

	static void DoMerge(DigPtrVecIter cur, DigPtrVecIter pre);

	static void SwapDig(DigPtrVecIter cur, DigPtrVecIter pre);

private:
	const int  row_;
	const int  col_;

	DigPtrVec nodes_;
	DigRefVec rows_ref_;
	DigRefVec cols_ref_;
};

template<class InputIterator>
void Struct2048::ForEachCmp(InputIterator first, InputIterator last, InputIterator key)
{
	while (first != last)
	{
		CompareIter(first, key);
		++first;
	}
}

template<class InputIterator>
void Struct2048::CompareIter(InputIterator cur, InputIterator key)
{
	if (DEREFTWO(cur) == NULL)
		return;

	InputIterator pre, curt;
	pre = curt = cur;

	do
	{
		if (DEREFTWO(--pre))
		{
			DoMerge(DEREFONE(curt), DEREFONE(pre));
			break;
		}
		else
		{
			SwapDig(DEREFONE(curt), DEREFONE(pre));
			curt = pre;
		}
	} while (pre != key);
}

inline void DelNode(Digital* &ptr)
{
	SAFE_DELETE(ptr)
}

inline void Struct2048::ActiveNode(DigPtrVecIter ptr)
{
	if (*ptr)
		(*ptr)->active_ = true;
}

inline void Struct2048::Up()
{
	UpOrDown(false);
}

inline void Struct2048::Down()
{
	UpOrDown(true);
}

inline void Struct2048::UpOrDown(bool down)
{
	MergeBatch(cols_ref_, down);
}

inline void Struct2048::Left()
{
	LeftOrRight(false);
}

inline void Struct2048::Right()
{
	LeftOrRight(true);
}

inline void Struct2048::LeftOrRight(bool right)
{
	MergeBatch(rows_ref_, right);
}
#endif