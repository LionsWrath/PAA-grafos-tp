# This generator creates a graph with V vertexes and (V^2 - V)/2 edges and has only minimum paths
# More exactly, |V|! minimum paths with ALWAYS the same weight

import sys
import argparse
import numpy as np
from math import floor

parser = argparse.ArgumentParser(description="Graph generator - Generate a graph with |V|! minimum paths with the same value.")
parser.add_argument('v', type=int, help="Number of vertexes")
parser.add_argument('--answer', action="store_true", default=False, help="Print answer instead of Graph")
args = parser.parse_args()

V = args.v
E = floor((V**2 - V)/2) 

if not args.answer:
    ones = np.ones(V)
    val = []
    for i in range(V):
        val = val + [int(sum(ones[:i]))]

    print(V, E)
    for i in range(V):
        for idx,w in enumerate(val[1:V-i]):
            print(i+1, idx + i + 2, w)
else:
    print(E)
    for i in range(E):
        print(i+1, end="", flush=True)

        if i != E-1:
            print(" ", end="", flush=True)
    
    print( )
    print(0)
    print( )
