import random
import math


def UCTSEARCH(budget,root):
	for iter in range(budget):
		if iter%10000==9999:
			logger.info("simulation: %d"%iter)
			logger.info(root)
		front=TREEPOLICY(root)
		reward=DEFAULTPOLICY(front.state)
		BACKUP(front,reward)
	return BESTCHILD(root,0)

def TREEPOLICY(node):
	while node.state.terminal()==False:
		if node.fully_expanded()==False:	
			return EXPAND(node)
		else:
			node=BESTCHILD(node,SCALAR)
	return node