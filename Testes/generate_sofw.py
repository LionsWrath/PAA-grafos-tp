# This generator creates a graph with a unique path with V-1 edges.
# This one is a super test of overflow and memory (if using something recursive)

import sys
import argparse
import numpy as np

parser = argparse.ArgumentParser(description="Graph generator - Generate a graph with 2^((V-1)/2) minimum paths with the same value.")
parser.add_argument('v', type=int, help="Number of vertexes")
parser.add_argument('--answer', action="store_true", default=False, help="Print answer instead of Graph")
args = parser.parse_args()

V = args.v
E = V-1

if not args.answer:
    print(V, E)

    middle = 1
    while middle != V:
        print(middle, middle+1, 1000000)

        middle = middle + 1
else:
    print(E)
    for i in range(E):
        print(i+1, end="", flush=True)

        if i != E-1:
            print(" ", end="", flush=True)
    
    print( )
    print(E)
    for i in range(E):
        print(i+1, end="", flush=True)

        if i != E-1:
            print(" ", end="", flush=True)
 
    print( )
