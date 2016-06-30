# -*- coding: utf-8 -*-
from abc import ABCMeta, abstractmethod
from sage.modules.free_module_element import vector


class ReplSpaceElement(object):
    __metaclass__ = ABCMeta

    @property
    def vector(self):
        return self._v

    def __repr__(self):
        return repr(self.vector)

    def __init__(self, v):
        self._v = vector((a for a in v))

    def __add__(self, other):
        if other == 0:
            return self
        elif isinstance(other, self.__class__):
            return self.__class__(self.vector + other.vector)
        else:
            raise NotImplementedError

    def __neg__(self):
        return self.__class__(-self.vector)

    def __radd__(self, other):
        return self.__add__(other)

    def __mul__(self, other):
        if other in self.vector.base_ring():
            return self.__class__(self.vector * other)
        else:
            raise ValueError

    def __rmul__(self, other):
        return self * other

    def __sub__(self, other):
        return self + (-other)

    @abstractmethod
    def parent(self):
        pass

    @abstractmethod
    def left_action(self, g):
        r'''
        :param g: an element of GL_n
        :returns g \dot self
        :rtype ReplSpaceElement
        '''
        pass
