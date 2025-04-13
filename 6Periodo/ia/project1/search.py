# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util
from game import Directions
from typing import List

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()

def generic_search(problem: SearchProblem, insertFunction) -> List[Directions]:
    # Fronteira começa com o estado inicial e caminho até a solução começa vazio
    fringe = [(problem.getStartState(), [], 0)]
    
    # Guarda nós já visitados para não os explorar novamente
    visited = []
    
    # Enquanto a fronteira não é vazia, explora ela
    while len(fringe) > 0:
        node, path, cost = fringe.pop(0)
        
        # Caso nó não tenha sido explorado ainda
        if node not in visited:
            visited.append(node)
            
            # Se é um estado final, retorna o caminho até eke
            if problem.isGoalState(node):
                return path
            
            # Insere na fronteira com a função passada como parâmetro
            fringe = insertFunction(node, fringe, path, cost)


def heuristic_search(problem: SearchProblem, insertFunction, heuristic) -> List[Directions]:
    # Fronteira começa com o estado inicial e caminho até a solução começa vazio
    fringe = [(problem.getStartState(), [], 0, heuristic(problem.getStartState(), problem))]
    
    # Dicionario mantem o nó visitado e o menor custo até chegar aquele nó
    visited = {}
    
    # Enquanto a fronteira não é vazia, explora ela
    while len(fringe) > 0:
        node, path, cost, _ = fringe.pop(0)
        
        # Visita nó novamente apenas caso o custo para chegar enle for menor que o anteriormente registrado
        if node not in visited or visited[node] > cost:
            visited.update({node: cost})
            
            # Se é um estado final, retorna o caminho até eke
            if problem.isGoalState(node):
                return path
            
            # Insere na fronteira com a função passada como parâmetro
            fringe = insertFunction(node, fringe, path, cost)

def tinyMazeSearch(problem: SearchProblem) -> List[Directions]:
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def depthFirstSearch(problem: SearchProblem) -> List[Directions]:
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    """
    def insertBeginning(node, fringe: list, path, _) -> List:
        # Cria cópia da fronteira
        new_fringe = fringe.copy()
        
        # Para cada sucessor, os insere no começo da fila
        for s, dir, cost in problem.getSuccessors(node):
            new_fringe.insert(0, (s, path + [dir], cost))
        
        # Retorna nova fronteira com nó inserido no início
        return new_fringe
    
    return generic_search(problem, insertBeginning)
    util.raiseNotDefined()

def breadthFirstSearch(problem: SearchProblem) -> List[Directions]:
    """Search the shallowest nodes in the search tree first."""
    
    def insertEnd(node, fringe: list, path, _) -> List:
        # Cria cópia da fronteira
        new_fringe = fringe.copy()
        
        # Para cada sucessor, os insere no final da fila
        for s, dir, cost in problem.getSuccessors(node):
            new_fringe.append((s, path + [dir], cost))
        
        # Retorna nova fronteira com nó no final da fila
        return new_fringe
    
    return generic_search(problem, insertEnd)
    util.raiseNotDefined()

def uniformCostSearch(problem: SearchProblem) -> List[Directions]:
    """Search the node of least total cost first."""
    
    def insertAscOrder(node, fringe: list, path, costToNode) -> List:
        # Cria cópia da fronteira
        new_fringe = fringe.copy()
        
        # Para cada sucessor, os insere ordenado na fila
        for s, dir, cost in problem.getSuccessors(node):
            new_cost = costToNode+cost
            if len(new_fringe) == 0:
                new_fringe.append((s, path + [dir], new_cost))
            else:
                pos = 0
                # Acha posicao de insercao
                while pos < len(new_fringe):
                    if new_cost >= new_fringe[pos][2]:
                        pos += 1
                    else:
                        break
                # Insere na posição encontrada
                new_fringe.insert(pos, (s, path + [dir], new_cost))
                        
        # Retorna nova fronteira
        return new_fringe
    
    # Chama busca genérica com inserção ordenada
    return generic_search(problem, insertAscOrder)
    util.raiseNotDefined()

def nullHeuristic(state, problem=None) -> float:
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem: SearchProblem, heuristic=nullHeuristic) -> List[Directions]:
    """Search the node that has the lowest combined cost and heuristic first."""
    def insertHeuristicOrder(node, fringe: list, path, costToNode) -> List:
        new_fringe = fringe.copy()
        
        # Para cada sucessor, os insere ordenado na fila
        for s, dir, cost in problem.getSuccessors(node):
            new_cost = costToNode+cost
            
            # Ordena pelo custo até o nó + custo da heurística
            f = new_cost + heuristic(s, problem)
            
            # Caso seja o primeiro
            if len(new_fringe) == 0:
                new_fringe.append((s, path + [dir], new_cost, heuristic(s, problem)))
            else:
                pos = 0
                # Acha posicao de insercao comparando o f atual com o do nó inserido na fila
                while pos < len(new_fringe):
                    f_node = new_fringe[pos][2] + new_fringe[pos][3]
                    if f >= f_node:
                        pos += 1
                    else:
                        break
                # Insere na posição encontrada
                new_fringe.insert(pos, (s, path + [dir], new_cost, heuristic(s, problem)))
        return new_fringe
    
    # Chama busca heurística com inserção ordenada heurística
    return heuristic_search(problem, insertHeuristicOrder, heuristic)
    util.raiseNotDefined()

# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
