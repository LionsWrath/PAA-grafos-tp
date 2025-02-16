# This generator creates a graph with V vertexes and (4*(V-1))/3 edges and has only minimum paths
# More exactly, 2^((V-1)/2) minimum paths with ALWAYS the same weight
# The weight is higher in this version to test overflow

import sys
import argparse
import numpy as np

parser = argparse.ArgumentParser(description="Graph generator - Generate a graph with 2^((V-1)/2) minimum paths with the same value.")
parser.add_argument('v', type=int, help="Number of vertexes")
parser.add_argument('--answer', action="store_true", default=False, help="Print answer instead of Graph")
args = parser.parse_args()

V = args.v
E = int(4*(V - 1)/3)

if (V-1)%3 != 0:
    raise Exception("This graph only accepts a number of Vertexes that respects (V-1)%3 == 0")

if not args.answer:
    print(V, E)

    middle = 1
    while middle != V:
        lower = middle + 1
        upper = middle + 2
        
        print(middle, lower, 1000000)
        print(middle, upper, 1000000)

        middle = middle + 3

        print(lower, middle, 1000000)
        print(upper, middle, 1000000)
else:
    print(E)
    for i in range(E):
        print(i+1, end="", flush=True)

        if i != E-1:
            print(" ", end="", flush=True)
    
    print( )
    print(0)
    print( )
