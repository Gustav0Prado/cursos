# multiAgents.py
# --------------
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


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent
from pacman import GameState

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState: GameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState: GameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        newFood = successorGameState.getFood()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        dead_ghosts = 0
        total_score = 0
        
        """ 
        Tabela de pontuação do Pacman original
        Pac-Dot = 10 Pts
        1st Ghost = 200 Pts
        2nd Ghost = 400 Pts
        3rd Ghost = 800 Pts
        4th Ghost = 1600 Pts
        """
        
        # Se proximo estado for vitoria, score eh maximo
        if successorGameState.isWin():
            return 9999
        
        # Se for derrota, score eh minimo
        if successorGameState.isLose():
            return -9999
        
        foodDist = [util.manhattanDistance(newPos, food) for food in newFood.asList()]
        minFoodDist = min(foodDist)
        total_score += 10 / minFoodDist
        
        # Para cada fantasma, caso esteja próximo (distancia < 2) o Pacman vai:
        ## Se o timer de fantasma assustado for > 0, tenta ir atrás dos fantasmas para melhorar a pontuação seguindo a tabela de pontuação
        ## Se o timer for zero, retorna um score mínimo
        for i in range(len(successorGameState.getGhostPositions())):
            if util.manhattanDistance(successorGameState.getPacmanPosition(), successorGameState.getGhostPositions()[i]) < 2:
                if newScaredTimes[i] != 0:
                    total_score += 200 * (2 ** dead_ghosts)
                    dead_ghosts += 1
                else:
                    return -9999
        
        return successorGameState.getScore() + total_score

def scoreEvaluationFunction(currentGameState: GameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState: GameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        def max_value(gameState, currAgent, currDepth):
            if gameState.isWin() or gameState.isLose() or currDepth == self.depth:
                return self.evaluationFunction(gameState)
            
            v = float("-inf")
            actions = gameState.getLegalActions(currAgent)
            for a in actions:
                v = max(v, min_value(gameState.generateSuccessor(currAgent, a), currAgent+1, currDepth))
            return v
        
        def min_value(gameState, currAgent, currDepth):
            if gameState.isWin() or gameState.isLose() or currDepth == self.depth:
                return self.evaluationFunction(gameState)
            
            v = float("inf")
            actions = gameState.getLegalActions(currAgent)
            for a in actions:
                # Caso seja o ultimo fantasma, chama o pacman e aumenta a profundidade
                if currAgent == gameState.getNumAgents() - 1:
                    v = min(v, max_value(gameState.generateSuccessor(currAgent, a), 0, currDepth+1))
                # Caso contrario, chama para o proximo fantasma
                else:
                    v = min(v, min_value(gameState.generateSuccessor(currAgent, a), currAgent+1, currDepth))
            return v
        
        # Movimento inicial do Pacman
        v = float("-inf")
        actions = gameState.getLegalActions(0)
        maxAction = ''
        for a in actions:
            new_v = max(v, min_value(gameState.generateSuccessor(0, a), 1, 0))
            if new_v > v:
                v = new_v
                maxAction = a
        return maxAction
        
        util.raiseNotDefined()

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState: GameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        def max_value(gameState, currAgent, currDepth, alpha, beta):
            if gameState.isWin() or gameState.isLose() or currDepth == self.depth:
                return self.evaluationFunction(gameState)
            
            v = float("-inf")
            actions = gameState.getLegalActions(currAgent)
            for a in actions:
                v = max(v, min_value(gameState.generateSuccessor(currAgent, a), currAgent+1, currDepth, alpha, beta))
                if v > beta: return v
                alpha = max(alpha, v)
            return v
        
        def min_value(gameState, currAgent, currDepth, alpha, beta):
            if gameState.isWin() or gameState.isLose() or currDepth == self.depth:
                return self.evaluationFunction(gameState)
            
            v = float("inf")
            actions = gameState.getLegalActions(currAgent)
            for a in actions:
                # Caso seja o ultimo fantasma, chama o pacman e aumenta a profundidade
                if currAgent == gameState.getNumAgents() - 1:
                    v = min(v, max_value(gameState.generateSuccessor(currAgent, a), 0, currDepth+1, alpha, beta))
                # Caso contrario, chama para o proximo fantasma
                else:
                    v = min(v, min_value(gameState.generateSuccessor(currAgent, a), currAgent+1, currDepth, alpha, beta))
                if v < alpha: return v
                beta = min(beta, v)
            return v
        
        # Movimento inicial do Pacman
        v = float("-inf")
        alpha = float("-inf")
        beta = float("inf")
        actions = gameState.getLegalActions(0)
        maxAction = ''
        for a in actions:
            new_v = max(v, min_value(gameState.generateSuccessor(0, a), 1, 0, alpha, beta))
            if new_v > v:
                v = new_v
                maxAction = a
            if v > beta: return maxAction
            alpha = max(alpha, v)
        return maxAction
        util.raiseNotDefined()

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState: GameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        def max_value(gameState, currAgent, currDepth):
            if gameState.isWin() or gameState.isLose() or currDepth == self.depth:
                return self.evaluationFunction(gameState)
            
            v = float("-inf")
            actions = gameState.getLegalActions(currAgent)
            for a in actions:
                v = max(v, exp_value(gameState.generateSuccessor(currAgent, a), currAgent+1, currDepth))
            return v
        
        def exp_value(gameState, currAgent, currDepth):
            if gameState.isWin() or gameState.isLose() or currDepth == self.depth:
                return self.evaluationFunction(gameState)
            
            v = 0
            actions = gameState.getLegalActions(currAgent)
            for a in actions:
                p = 1/len(actions)
                # Caso seja o ultimo fantasma, chama o pacman e aumenta a profundidade
                if currAgent == gameState.getNumAgents() - 1:
                    v += p * max_value(gameState.generateSuccessor(currAgent, a), 0, currDepth+1)
                # Caso contrario, chama para o proximo fantasma
                else:
                    v += p * exp_value(gameState.generateSuccessor(currAgent, a), currAgent+1, currDepth)
            return v
        
        # Movimento inicial do Pacman
        v = float("-inf")
        actions = gameState.getLegalActions(0)
        maxAction = ''
        for a in actions:
            new_v = max(v, exp_value(gameState.generateSuccessor(0, a), 1, 0))
            if new_v > v:
                v = new_v
                maxAction = a
        return maxAction
        util.raiseNotDefined()

def betterEvaluationFunction(currentGameState: GameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
    """
    # Score inicial
    score = 5 * currentGameState.getScore()

    # Posicoes e listas
    newPos   = currentGameState.getPacmanPosition()
    food     = currentGameState.getFood().asList()
    ghostStates = currentGameState.getGhostStates()
    capsules = currentGameState.getCapsules()

    # Bonus e penalidades
    winBonus    =  1e6
    losePenalty = -1e6
    foodPenalty = -50
    capsulePenalty = -10

    # Caso mais basico, do proximo estado ser vitoria ou derrota
    if currentGameState.isWin():
        score += winBonus
    elif currentGameState.isLose():
        score += losePenalty

    # Para cada fantasma
    for g in ghostStates:
        dist = util.manhattanDistance(g.getPosition(), newPos)
        if dist == 1:
            score += losePenalty
        if g.scaredTimer > 0:
            score += pow(max(8 - dist, 0), 2)
        else:
            score -= pow(max(7 - dist, 0), 2)

    # Para cada comida
    maxFood = 0
    for f in food:
        dist = 1.0 / util.manhattanDistance(f, newPos)
        if dist > maxFood:
            maxFood = dist
    score += maxFood

    # Para cada capsula
    maxCapsules = 0
    for c in capsules:
        dist = 50 / util.manhattanDistance(c, newPos)
        if dist > maxCapsules:
            maxCapsules = dist
    score += maxCapsules

    return score
    util.raiseNotDefined()

# Abbreviation
better = betterEvaluationFunction
