# This generator creates a graph with V vertexes and 5*((V-1)/4) edges and has only minimum paths
# More exactly, 2^((V-1)/2) minimum paths with ALWAYS the same weight and multiple bridges

import sys
import argparse
import numpy as np

parser = argparse.ArgumentParser(description="Graph generator - Generate a graph with 2^((V-1)/2) minimum paths with the same value.")
parser.add_argument('v', type=int, help="Number of vertexes")
parser.add_argument('--answer', action="store_true", default=False, help="Print answer instead of Graph")
args = parser.parse_args()

V = args.v
E = int(5*(V - 1)/4)

if (V-1)%4 != 0:
    raise Exception("This graph only accepts a number of Vertexes that respects (V-1)%4 == 0")

if not args.answer:
    print(V, E)

    middle = 1
    while middle != V:
        lower = middle + 1
        upper = middle + 2
        
        print(middle, lower, 1)
        print(middle, upper, 1)

        middle = middle + 3

        print(lower, middle, 1)
        print(upper, middle, 1)
        print(middle, middle+1, 1)

        middle = middle + 1
else:
    I = list(filter(lambda x: (x+1)%5 == 0, range(E)))
    print(E)
    for i in range(E):
        print(i+1, end="", flush=True)

        if i != E-1:
            print(" ", end="", flush=True)

    print( )
    print(len(I))
    for i in I:
        print(i+1, end="", flush=True)

        if i != I[len(I)-1]:
            print(" ", end="", flush=True)
    print( )


