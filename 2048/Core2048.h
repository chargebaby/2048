#pragma once

#include <vector>
#include <algorithm>
#include <assert.h>

#define SAFE_DELETE(ptr) \
	if (ptr) { delete (ptr); (ptr) = NULL; }

struct Digital
{
	int		value_;
	bool	active_;
};

typedef Digital* DigitalPtr;

class Core2048
{
	typedef std::vector<DigitalPtr>	DigPtrVec;
	typedef std::vector<DigPtrVec>	DigPlane;

public:
	Core2048();
	~Core2048();

public:
	void Random();

	void Up();

	void Down();

	void Left();

	void Right();

private:
	bool OperDigs(DigitalPtr &cur, DigitalPtr &pre);

	void MergDigs(DigitalPtr &cur, DigitalPtr &pre);

	void SwapDigs(DigitalPtr &cur, DigitalPtr &pre);

private:
	static void DeleteNodes(DigPtrVec &nodes);

	static void ActiveNodes(DigPtrVec &nodes);

	static void DeleteNode(DigitalPtr &node);

	static void ActiveNode(DigitalPtr &node);

private:
	const int  row_;
	const int  col_;

	DigPlane nodes_;
};

inline void Core2048::DeleteNodes(DigPtrVec &nodes)
{
	for_each(nodes.begin(), nodes.end(), DeleteNode);
}

inline void Core2048::DeleteNode(Digital* &node)
{
	SAFE_DELETE(node)
}

inline void Core2048::ActiveNodes(DigPtrVec &nodes)
{
	for_each(nodes.begin(), nodes.end(), ActiveNode);
}

inline void Core2048::ActiveNode(DigitalPtr &node)
{
	if (node) node->active_ = true;
}
