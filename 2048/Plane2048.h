#ifndef _3D_GAME_2048_PLANE_H_
#define _3D_GAME_2048_PLANE_H_

#pragma once

#include <list>
#include <vector>
#include <algorithm>
#include <utility>
#include <assert.h>

#define SAFE_DELETE(ptr) \
	if (ptr) { delete (ptr); (ptr) = nullptr; }

namespace gcore
{
	typedef struct _N2048
	{
		int		value_;
		bool	active_;
	}N2048, *N2048Ptr;

	class Plane2048
	{
		friend void DoMerge(N2048Ptr &ptr_old, N2048Ptr &ptr_new);

	public:
		typedef std::list<N2048Ptr>			NodeList;
		typedef std::vector<NodeList>		Plane;

	public:
		Plane2048();
		~Plane2048();

	public:
		void Random();

		void ActiveNodes(NodeList &list);

		void MergeRow(const int index, bool reverse);

		void MergeCol(const int index, bool reverse);

		void Merge(NodeList &list, bool reverse);

	private:
		int		row_;
		int		col_;
		Plane	plane_;
	};

	inline void DelNode(N2048Ptr &ptr)
	{
		SAFE_DELETE(ptr)
	}

	inline void ActiveNode(N2048Ptr &ptr)
	{
		if (ptr)
			ptr->active_ = true;
	}

	inline void DelNodes(Plane2048::NodeList& nodes)
	{
		for_each(nodes.begin(), nodes.end(), DelNode);
	}

	template<class InputIterator>
	void compare_node(InputIterator current, InputIterator key)
	{
		assert(current != key);

		if (*current == NULL)
			return;

		InputIterator pre = current;

		do
		{
			--pre;

			if (*pre)
			{
				DoMerge(*current, *pre);
				break;
			}
			else
			{
				std::iter_swap(current, pre);
				current = pre;
			}
		} while (pre != key);
	}

	template<class InputIterator>
	void for_each_move(InputIterator first, InputIterator last, InputIterator key)
	{
		while (first != last) 
		{
			compare_node(first, key);
			++first;
		}
	}
}
#endif
