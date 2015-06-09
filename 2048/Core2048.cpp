#include "Core2048.h"


Core2048::Core2048()
	: row_(4), col_(4), nodes_(row_, DigPtrVec(col_, NULL))
{}


Core2048::~Core2048()
{
	for_each(nodes_.begin(), nodes_.end(), DeleteNodes);
}

void Core2048::Random()
{
	while (true)
	{
		size_t r = rand() % (col_ * row_);
		size_t i = r / col_;
		size_t j = r % col_;

		if (nodes_[i][j] == NULL)
		{
			DigitalPtr &ptr = nodes_[i][j];

			ptr = new Digital();
			ptr->active_ = true;
			ptr->value_ = (rand() % 4 == 1) ? 4 : 2;
			break;
		}
	}
}

void Core2048::Up()
{
	for (int i = 0; i < col_; ++i)
	{
		for (int j = 1; j < row_; ++j)
		{
			for (int k = j - 1; k >= 0; --k)
			{
				if (OperDigs(nodes_[k + 1][i], nodes_[k][i])) break;
			}
		}
	}

	for_each(nodes_.begin(), nodes_.end(), ActiveNodes);
}

void Core2048::Down()
{
	for (int i = 0; i < col_; ++i)
	{
		for (int j = row_ - 2; j >= 0; --j)
		{
			for (int k = j + 1; k < row_; ++k)
			{
				if (OperDigs(nodes_[k - 1][i], nodes_[k][i])) break;
			}
		}
	}

	for_each(nodes_.begin(), nodes_.end(), ActiveNodes);
}

void Core2048::Left()
{
	for (int i = 0; i < row_; ++i)
	{
		for (int j = 1; j < col_; ++j)
		{
			for (int k = j - 1; k >= 0; --k)
			{
				if (OperDigs(nodes_[i][k + 1], nodes_[i][k])) break;
			}
		}
	}

	for_each(nodes_.begin(), nodes_.end(), ActiveNodes);
}

void Core2048::Right()
{
	for (int i = 0; i < row_; ++i)
	{
		for (int j = col_ - 2; j >= 0; --j)
		{
			for (int k = j + 1; k < col_; ++k)
			{
				if (OperDigs(nodes_[i][k - 1], nodes_[i][k])) break;
			}
		}
	}

	for_each(nodes_.begin(), nodes_.end(), ActiveNodes);
}

bool Core2048::OperDigs(DigitalPtr &cur, DigitalPtr &pre)
{
	if (cur == NULL) 
		return false;

	if (pre)
	{
		MergDigs(cur, pre);
		return true;
	}

	SwapDigs(cur, pre);
	return false;
}

void Core2048::MergDigs(DigitalPtr &cur, DigitalPtr &pre)
{
	assert(pre != NULL);

	if (cur->value_ == pre->value_ && pre->active_ == true)
	{
		pre->value_ *= 2;
		pre->active_ = false;
		DeleteNode(cur);
	}
}

void Core2048::SwapDigs(DigitalPtr &cur, DigitalPtr &pre)
{
	assert(pre == NULL);

	pre = new Digital;

	pre->value_  = cur->value_;
	pre->active_ = cur->active_;

	DeleteNode(cur);
}