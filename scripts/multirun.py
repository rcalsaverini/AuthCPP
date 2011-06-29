# for k in xrange(20):
#     fhandle = open("./res/conv/test"+str(k), "w") 
#     foo = popen("./test")
#     for line in foo:
#         print >>fhandle, line[0:-1]

import os
import multiprocessing
from multiprocessing import Process, Queue
from Queue import Empty
from numpy.random import uniform
from numpy import mean, arange


def runnit(a):
    idrun, size, steps, burn, beta, alpha, q = a
    fname = "./res/conv/test" + idrun
    print "handling ", fname
    fhandle = open(fname, "w")
    args = " ".join(map(str,[size,steps,burn,beta,alpha,q]))
    foo = os.popen("./test " + args)
    for line in foo:
        print >>fhandle, line[0:-1]    

def runFoo(queue):
    while True:
        try:
            a = queue.get(block = False)
            runnit(a)
        except Empty:
            print "The End, my friend"
            break
        
if __name__ == "__main__":
    nthreads = multiprocessing.cpu_count()
    N = 20
    workQueue = Queue()
    names = [(str(x), 15,1000, 0, 2.0, 1.0, x) for x in arange(0,1,0.1) ]
    for proc in names:
        workQueue.put(proc)

    processes = [Process(target = runFoo, args=(workQueue,)) for i in range(nthreads)]
    for p in processes:
        p.start()
    for p in processes:
        p.join()
