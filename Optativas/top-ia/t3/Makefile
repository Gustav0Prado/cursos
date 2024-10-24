all: solver dimacs

solver: solver.py
	cp solver.py ./solver
	chmod +x ./solver

dimacs: dimacs.py
	cp dimacs.py ./dimacs
	chmod +x ./dimacs

clean:
	rm -rf ./__pycache__ ./dimacs ./solver