from math import sqrt

def exp(p):
    return 1/p

def stddev(p):
    return sqrt((1-p) / (p**2))

p=0.00022
print(f"Numero di volte atteso per venire ricoverato da non vaccinato: {exp(p):.02f}, stddev: {stddev(p):.02f}")