#ifndef PATTERN_SOLVER_H
#define PATTERN_SOLVER_H
#include "Solver.h"

class PatternSolver : public Solver
{
public:
	PatternSolver() {}

	void Solve(const Grid& grid, Library* lib, SolvingMode mode);

private:
	void Loop(Grid grid, int depth);

	void CommitSlot(Grid& grid, const Slot& slot, int depth);
	//Library used by the solver
	Library* lib_;
	bool is_solved_;
	SolvingMode mode_;
};

#endif