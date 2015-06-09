#include "Plane2048.h"

namespace gcore
{
	Plane2048::Plane2048() 
		: row_(4), col_(4), plane_(row_, NodeList(col_, nullptr))
	{ }

	Plane2048::~Plane2048()
	{
		for_each(plane_.begin(), plane_.end(), DelNodes);
	}

	void Plane2048::ActiveNodes(NodeList &list)
	{
		for_each(list.begin(), list.end(), ActiveNode);
	}

	void Plane2048::MergeRow(const int index, bool reverse)
	{
		assert(index >= 0 && index < row_);

		Merge(plane_[index], reverse);
	}

	void Plane2048::MergeCol(const int index, bool reverse)
	{
		assert(index >= 0 && index < col_);

		NodeList list;
		NodeList::iterator iter, iter2;

		for (int i = 0; i < row_; ++i)
		{
			iter = plane_[i].begin();
			advance(iter, index);
			list.push_back(*iter);
		}

		Merge(list, reverse);

		for (int i = 0; i < row_; ++i)
		{
			iter  = plane_[i].begin();
			iter2 = list.begin();
			advance(iter,  index);
			advance(iter2, i);
			std::iter_swap(iter, iter2);
		}
	}

	void Plane2048::Merge(NodeList &list, bool reverse)
	{
		reverse 
			? for_each_move(++list.rbegin(), list.rend(), list.rbegin())
			: for_each_move(++list.begin(), list.end(), list.begin());

		ActiveNodes(list);
	}

	void DoMerge(N2048Ptr &ptr_old, N2048Ptr &ptr_new)
	{
		if (ptr_new->value_ == ptr_old->value_ && ptr_new->active_ == true)
		{
			ptr_new->value_ *= 2;
			ptr_new->active_ = false;
			DelNode(ptr_old);
		}
	}

}
