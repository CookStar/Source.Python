# ../entities/helpers.py

"""Provides helper functions to convert from one type to another."""

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core.cache import CachedProperty


# =============================================================================
# >> FORWARD IMPORTS
# =============================================================================
# Source.Python Imports
#   Entities
from _entities._helpers import baseentity_from_basehandle
from _entities._helpers import baseentity_from_edict
from _entities._helpers import baseentity_from_index
from _entities._helpers import baseentity_from_inthandle
from _entities._helpers import baseentity_from_pointer
from _entities._helpers import basehandle_from_baseentity
from _entities._helpers import basehandle_from_edict
from _entities._helpers import basehandle_from_index
from _entities._helpers import basehandle_from_inthandle
from _entities._helpers import basehandle_from_pointer
from _entities._helpers import edict_from_baseentity
from _entities._helpers import edict_from_basehandle
from _entities._helpers import edict_from_index
from _entities._helpers import edict_from_inthandle
from _entities._helpers import edict_from_pointer
from _entities._helpers import find_output_name
from _entities._helpers import index_from_baseentity
from _entities._helpers import index_from_basehandle
from _entities._helpers import index_from_edict
from _entities._helpers import index_from_inthandle
from _entities._helpers import index_from_pointer
from _entities._helpers import inthandle_from_baseentity
from _entities._helpers import inthandle_from_basehandle
from _entities._helpers import inthandle_from_edict
from _entities._helpers import inthandle_from_index
from _entities._helpers import inthandle_from_pointer
from _entities._helpers import pointer_from_baseentity
from _entities._helpers import pointer_from_basehandle
from _entities._helpers import pointer_from_edict
from _entities._helpers import pointer_from_index
from _entities._helpers import pointer_from_inthandle
#   Memory
from memory.manager import MemberFunction


# =============================================================================
# >> ALL DECLARATION
# =============================================================================
__all__ = ('baseentity_from_basehandle',
           'baseentity_from_edict',
           'baseentity_from_index',
           'baseentity_from_inthandle',
           'baseentity_from_pointer',
           'basehandle_from_baseentity',
           'basehandle_from_edict',
           'basehandle_from_index',
           'basehandle_from_inthandle',
           'basehandle_from_pointer',
           'edict_from_baseentity',
           'edict_from_basehandle',
           'edict_from_index',
           'edict_from_inthandle',
           'edict_from_pointer',
           'find_output_name',
           'index_from_baseentity',
           'index_from_basehandle',
           'index_from_edict',
           'index_from_inthandle',
           'index_from_pointer',
           'inthandle_from_baseentity',
           'inthandle_from_basehandle',
           'inthandle_from_edict',
           'inthandle_from_index',
           'inthandle_from_pointer',
           'pointer_from_baseentity',
           'pointer_from_basehandle',
           'pointer_from_edict',
           'pointer_from_index',
           'pointer_from_inthandle',
           'EntityMemFuncWrapper',
           'wrap_entity_mem_func',
           )


# =============================================================================
# >> CLASSES
# =============================================================================
class EntityMemFuncWrapper(MemberFunction, CachedProperty):
    def __init__(self, wrapper):
        self.__func__ = wrapper
        CachedProperty.__init__(self)

    def __get__(self, wrapped_self, objtype):
        if wrapped_self is None:
            return self.__func__
        func = wrapped_self.__dict__.get(self.name, None)
        if func is not None:
            return func
        self.wrapped_self = wrapped_self
        func = wrapped_self.__getattr__(self.__func__.__name__)
        MemberFunction.__init__(
            self, func._manager, func._type_name, func, func._this
        )
        return self

    def __set__(self, wrapped_self, value):
        wrapped_self.__dict__[self.name] = value

    def __call__(self, *args, **kwargs):
        return super().__call__(
            *self.__func__(self.wrapped_self, *args, **kwargs))

    def call_trampoline(self, *args, **kwargs):
        return super().call_trampoline(
            *self.__func__(self.wrapped_self, *args, **kwargs))

    def skip_hooks(self, *args, **kwargs):
        return super().skip_hooks(
            *self.__func__(self.wrapped_self, *args, **kwargs))


# =============================================================================
# >> FUNCTIONS
# =============================================================================
def wrap_entity_mem_func(wrapper):
    """A decorator to wrap an entity memory function."""
    return EntityMemFuncWrapper(wrapper)
