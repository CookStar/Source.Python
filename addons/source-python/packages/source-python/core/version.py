# ../core/version.py

"""Provides the Source.Python version."""

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Cvars
from cvars.public import PublicConVar


# =============================================================================
# >> ALL DECLARATION
# =============================================================================
__all__ = ('VERSION',
           )


# =============================================================================
# >> CONSTANTS
# =============================================================================
VERSION = 'unversioned'


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
_sp_version = PublicConVar(
    'sp_version', VERSION, description='Source.Python version')