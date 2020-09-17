# ../partition.py

"""Provides access to the spatial partition interfaces."""

# =============================================================================
# >> IMPORTS
# =============================================================================
# Python Imports
#   Enum
from enum import IntFlag


# =============================================================================
# >> FORWARD IMPORTS
# =============================================================================
# Source.Python Imports
#   Engines
from _partition import spatial_partition
from _partition import IterationRetval
from _partition import PartitionEnumerator
from _partition import PARTITION_ENGINE_SOLID_EDICTS
from _partition import PARTITION_ENGINE_TRIGGER_EDICTS
from _partition import PARTITION_ENGINE_NON_STATIC_EDICTS
from _partition import PARTITION_ENGINE_STATIC_PROPS


# =============================================================================
# >> ALL DECLARATION
# =============================================================================
__all__ = ('spatial_partition',
           'IterationRetval',
           'PartitionEnumerator',
           'PartitionMasks',
           )


# =============================================================================
# >> ENUMERATORS
# =============================================================================
class PartitionMasks(IntFlag):
    """Partition masks wrapper enumerator."""

    SOLID_EDICTS = PARTITION_ENGINE_SOLID_EDICTS
    TRIGGER_EDICTS = PARTITION_ENGINE_TRIGGER_EDICTS
    NON_STATIC_EDICTS = PARTITION_ENGINE_NON_STATIC_EDICTS
    STATIC_PROPS = PARTITION_ENGINE_STATIC_PROPS

