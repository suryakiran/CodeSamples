import os, sys, re
from ComponentManager import ComponentManager as mgr

class Component(object):
    def __init__(self, **kwargs):
        super(Component, self).__init__()

    def definitions(self):
        pass

    def flags(self):
        pass

    def includes(self):
        pass

    def libs(self):
        pass

    def libdirs(self):
        pass

    def dependencies(self):
        pass
    
