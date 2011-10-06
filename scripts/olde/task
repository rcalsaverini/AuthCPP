import multiprocessing
from multiprocessing import Process, Queue
from time import sleep, time
from random import uniform
import os
from numpy import arange

def doCalculation(par):
    u,q   = par
    size  = 10
    steps = 150
    burn  = 0
    beta  = 5.0
    alpha = size * (size - 1.0)/2.0 * u
    cmd  = "./authcpp " + " ".join(map(str,[size, steps, burn, beta, alpha, q]))
    foo = os.popen(cmd)
    res = [line[0:-1] for line in foo]
    return "".join(res)


if __name__ == "__main__":
    for i in xrange(15):
        #for j in xrange(35):
            #u = float(i)/35.0 * 0.8  + 0.2
            u = 0.6
            q = float(i)/15.0 * 0.5  
            par = (u,q)
            foo = doCalculation(par)
            print "%5.2f %5.2f %s"%(u, q, foo)
            
            
