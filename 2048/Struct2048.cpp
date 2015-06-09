#include "Struct2048.hpp"


Struct2048::Struct2048()
	: row_(4), col_(4), nodes_(row_ * col_, NULL) 
{
	CreatePlaneRef();
}

Struct2048::Struct2048(int rows, int cols)
	: row_(rows), col_(cols), nodes_(row_ * cols, NULL)
{
	CreatePlaneRef();
}

Struct2048::~Struct2048()
{
	for_each(nodes_.begin(), nodes_.end(), DelNode);
}


void Struct2048::Random()
{
	while (true)
	{
		size_t r = rand() % nodes_.size();

		if (nodes_[r] == NULL)
		{
			nodes_[r] = new Digital();
			nodes_[r]->active_ = true;
			nodes_[r]->value_ = (rand() % 4 == 1) ? 4 : 2;
			break;
		}
	}
}

void Struct2048::CreateRowRef()
{
	DigRef dig_ref;

	for (size_t i = 0; i < nodes_.size(); ++i)
		PushBackRef(dig_ref, rows_ref_, i, row_);
}

void Struct2048::CreateColRef()
{
	DigRef dig_ref;

	for (int i = 0; i < col_; ++i)
		for (size_t j = i; j < nodes_.size(); j += col_)
			PushBackRef(dig_ref, cols_ref_, j, col_);
}

void Struct2048::PushBackRef(DigRef& dig_ref, DigRefVec& ref_vec,
				const int index, const int direction)
{
	dig_ref.push_back(nodes_.begin() + index);

	if (dig_ref.size() % direction == 0)
	{
		ref_vec.push_back(dig_ref);
		dig_ref.clear();
	}
}

void Struct2048::Merge(DigRef &list, bool reverse)
{
	reverse
		? ForEachCmp(++list.rbegin(), list.rend(), list.rbegin())
		: ForEachCmp(++list.begin(),  list.end(),  list.begin());

	for_each(list.begin(), list.end(), ActiveNode);
}

void Struct2048::MergeBatch(DigRefVec &ref_vec, bool reverse)
{
	for (size_t i = 0; i < ref_vec.size(); ++i)
	{
		Merge(ref_vec[i], reverse);
	}
}

void Struct2048::CreatePlaneRef()
{
	CreateRowRef();
	CreateColRef();
}

void Struct2048::DoMerge(DigPtrVecIter cur, DigPtrVecIter pre)
{
	if ((*cur)->value_ == (*pre)->value_ && (*pre)->active_ == true)
	{
		(*pre)->value_ *= 2;
		(*pre)->active_ = false;
		DelNode(*cur);
	}
}

void Struct2048::SwapDig(DigPtrVecIter cur, DigPtrVecIter pre)
{
	DEREFONE(pre) = new Digital;

	DEREFONE(pre)->value_  = DEREFONE(cur)->value_;
	DEREFONE(pre)->active_ = DEREFONE(cur)->active_;

	DelNode(*cur);
}

void DoMerge(Digital* cur, Digital* pre)
{
	assert(cur != NULL && pre != NULL);

	if (cur->value_ == pre->value_ && pre->active_ == true)
	{
		pre->value_ *= 2;
		pre->active_ = false;
		DelNode(cur);
	}
}

// void print(const Struct2048 &s)
// {
// 	for (size_t i = 0; i < s.nodes_.size(); ++i)
// 	{
// 		if (s.nodes_[i] == NULL)
// 			printf("\t");
// 		else
// 			printf("%d \t", s.nodes_[i]->value_);
// 
// 		if ((i + 1) % s.col_ == 0)
// 			printf("\n");
// 	}
// 
// 	printf("\n--------------------------------------\n");
//}