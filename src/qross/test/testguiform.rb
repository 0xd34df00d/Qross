#!/usr/bin/env qross

require 'Qross'

dialog = Qross.createDialog("TestGuiFormDialog")
form = dialog
print "form %s %s" % (form,dir(form))
form.loadUiFile("/home/kde4/koffice/libs/qross/test/testguiform.ui")
form.exec_loop()
