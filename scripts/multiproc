import multiprocessing
from multiprocessing import Process, Queue, Lock
from time import sleep
from random import uniform
import os
from numpy import arange

def doCalculation(par):
    #foo = os.popen("ps -ef | grep python")
    alpha = par * 15 * 7
    size  = 25
    steps = 3000
    burn  = 1000
    beta  = 5.0
    q     = 0.0
    cmd  = "./authcpp " + " ".join(map(str,[size, steps, burn, beta, alpha, q]))
    print cmd
    foo = os.popen(cmd)
    res = [line[0:-1] for line in foo]
    return "".join(res)

def feed(queue, parlist):
    for par in parlist:
            queue.put(par)
        
def calc(queueIn, queueOut):
    while True:
        try:
            par = queueIn.get(block = False)
            #print "dealing with ", par, "" 
            res = doCalculation(par)
            queueOut.put((par,res))
        except:
            break

def write(queue, fname):
    fhandle = open(fname, "w")    
    while True:
        try:
            par, res = queue.get(block = False)
            print >>fhandle, par, res
        except:
            break
    fhandle.close()

if __name__ == "__main__":
    nthreads = multiprocessing.cpu_count()
    fname = "foo"
    workerQueue = Queue()
    writerQueue = Queue()
    parlist = arange(0,2,0.1)
    feedProc = Process(target = feed , args = (workerQueue, parlist))
    calcProc = [Process(target = calc , args = (workerQueue, writerQueue)) for i in range(nthreads)]
    writProc = Process(target = write, args = (writerQueue, fname))
    
    feedProc.start()
    feedProc.join ()
    
    for p in calcProc:
        p.start()
    for p in calcProc:
        p.join()

    writProc.start()
    writProc.join ()
