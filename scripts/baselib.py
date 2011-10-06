import os
from time import time
from numpy import arange, sqrt, mean, array
from numpy.random import uniform, normal
import multiprocessing
from multiprocessing import Process, Queue, Lock, Value
from Queue import Empty


def showList(x):
    return " ".join(map(str,x))

class runSystem:
    def __init__(self, pardict):
        self.size   = pardict["size"]
        self.steps  = pardict["steps"]
        self.burn   = pardict["burn"]
        self.anneal = pardict["anneal"]
        self.beta   = pardict["beta"]
        self.alpha  = pardict["alpha"]
        self.q      = pardict["q"]
        self.lone   = pardict["lone"]

    def parlist(self):
        return [self.size, self.steps, self.burn, self.anneal, self.beta, self.alpha, self.q, self.lone]
        
    def doCalculation(self):
        cmd  = "../authcpp " + " ".join(map(str,self.parlist()))
        foo = os.popen(cmd)
        output = "".join([line[0:-1] for line in foo])
        res = output.split()
        return map(float,res)



class Batch:
    def __init__(self, descript, fixval, varval):
        self.descript = descript
        self.fixval   = fixval
        self.varval   = varval[0]
        self.varrange = (varval[1], varval[2], varval[3])
        self.batch    = {}

    def iterfix(self):
        return self.fixval.iteritems()

    def cabecalho(self,fh):
        print >>fh, "# ", self.descript
        for k,v in self.iterfix():
            print >>fh, "# %s: %s"%(k, v)
        print >>fh, "# %s: %s .. %s, %s"%(self.varval, self.varrange[0], self.varrange[1], self.varrange[2])

    def createBatch(self):
        var = {}
        varvals = arange(self.varrange[0], self.varrange[1], self.varrange[2])
        self.batch = {}
        for v in varvals:
                base = self.fixval.copy()
                base[self.varval] = v
                self.batch[v] = base
                #return self.batch
    def iterBatch():
        return self.batch.iteritems()
                
    def runBatch(self, fname):
        fh  = open(fname, "w")
        self.createBatch()
        self.cabecalho(fh)
        for (v,pars) in self.iterBatch():
            job = runSystem(pars)
            res = job.doCalculation()
            print >>fh, v, showList(res)
        fh.close()


class parallelBatch:
    def __init__(self, descript, fixval, varval):
        self.descript = descript
        self.fixval   = fixval
        self.varval   = varval[0]
        self.varrange = (varval[1], varval[2], varval[3])
        self.batch    = Queue()
        self.output   = Queue()
        self.nthreads = multiprocessing.cpu_count()
        self.count    = Value('i', 0)
        self.time     = Value('d', time())

    def iterfix(self):
        return self.fixval.iteritems()

    def cabecalho(self, fh):
        print >>fh, "# ", self.descript
        for k,v in self.iterfix():
            print >>fh, "# %s: %s"%(k, v)
        print >>fh, "# %s: %s .. %s, %s"%(self.varval, self.varrange[0], self.varrange[1], self.varrange[2])

    def createBatch(self):
        var = {}
        varvals = arange(self.varrange[0], self.varrange[1], self.varrange[2])
        for v in varvals:
                base = self.fixval.copy()
                base[self.varval] = v
                self.batch.put((v, base))
                self.count.value = self.count.value + 1
                
    def runAll(self):
        while True:
            try:
                v,pars = self.batch.get(block = False)
                job = runSystem(pars)
                t1 = time()
                print "%s-th run init, %s = %s, time: %s" %(self.count.value, self.varval, v, t1 - self.time.value)
                res = job.doCalculation()
                self.count.value = self.count.value - 1
                print "%s-th run complete, %s = %s, time: %s , %s" %(self.count.value, self.varval, v, time() - t1, time() - self.time.value)
                self.output.put((v,res))
            except Empty:
                print "END"
                break

    def go(self):
        procs = [Process(target = self.runAll, args = ()) for i in xrange(self.nthreads)]
        for p in procs:
            p.start()
        for p in procs:
            p.join()

    def report(self, fname):
        fh = open(fname, 'w')
        self.cabecalho(fh)
        out = []
        while True:
            try:
                v, res = self.output.get(block=False)
                out.append((v,res))
            except Empty:
                break
        for (v,res) in sorted(out):
            print >>fh, v, showList(res)
            
