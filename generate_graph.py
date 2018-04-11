import numpy as np

V = 100000
E = 0

lw = 1
hw = 1000001

for u in range(V):
    adj = np.random.randint(0, 2, V)
    for idx,val in enumerate(adj):
        if val:
            E = E + 1
            print(u, idx, np.random.randint(lw, hw))

print(V, E)
