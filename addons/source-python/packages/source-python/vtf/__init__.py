# ../vtf/__init__.py

"""Provides access to engine's vtf interface."""

# =============================================================================
# >> FORWARD IMPORTS
# =============================================================================
# Source.Python Imports
#   VTF
from _vtf import is_vtf_file
from _vtf import header_size
from _vtf import VTFTexture


# =============================================================================
# >> ALL DECLARATION
# =============================================================================
__all__ = ('is_vtf_file',
           'header_size',
           'VTFTexture',
           )
