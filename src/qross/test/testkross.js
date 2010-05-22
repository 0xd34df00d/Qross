#!/usr/bin/env qross

var qross = Qross
var kjsaction = qross.action("MyKjsScript")

kjsaction.setInterpreter("python")
kjsaction.setCode("print \"Hello world from Python\"")

println("-----------------------> trigger");
kjsaction.trigger()
