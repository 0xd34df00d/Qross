#!/usr/bin/env qross

"""
  This Python script demonstrates how Qross could be used from
  within python scripts.
"""

print "__name__ = %s" % __name__
#print "__main__ = %s %s" % (__main__,dir(__main__))

#import TestObject1, TestObject2
#self.object1 = TestObject1
#self.object2 = TestObject2

import Qross
#print dir(Qross)
kjsaction = Qross.action("MyKjsScript")
#print dir(kjsaction)
kjsaction.setInterpreter("javascript")
kjsaction.setCode( "println(\"Hello world from Kjs\");" )
print "-----------------------> trigger"
kjsaction.trigger()
