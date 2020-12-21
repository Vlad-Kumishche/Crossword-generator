#ifndef SOLVER_H
#define SOLVER_H

#include "../Structures/Slot.h"
class Solver
{
public:
	virtual ~Solver() {};
	virtual void Solve(const Grid& grid, Library* lib, SolvingMode mode) = 0;
private:
	//Library used by the solver
	Library* lib_;
	bool is_solved_;
	SolvingMode mode_;
};

#endif