# ../vtf/constants.py

"""Provides access to engine's vtf interface."""

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
#   VTF
from _vtf._constants import ImageFormat
from _vtf._constants import TEXTUREFLAGS_POINTSAMPLE
from _vtf._constants import TEXTUREFLAGS_TRILINEAR
from _vtf._constants import TEXTUREFLAGS_CLAMPS
from _vtf._constants import TEXTUREFLAGS_CLAMPT
from _vtf._constants import TEXTUREFLAGS_ANISOTROPIC
from _vtf._constants import TEXTUREFLAGS_HINT_DXT5
from _vtf._constants import TEXTUREFLAGS_SRGB
from _vtf._constants import TEXTUREFLAGS_NORMAL
from _vtf._constants import TEXTUREFLAGS_NOMIP
from _vtf._constants import TEXTUREFLAGS_NOLOD
from _vtf._constants import TEXTUREFLAGS_ALL_MIPS
from _vtf._constants import TEXTUREFLAGS_PROCEDURAL
from _vtf._constants import TEXTUREFLAGS_ONEBITALPHA
from _vtf._constants import TEXTUREFLAGS_EIGHTBITALPHA
from _vtf._constants import TEXTUREFLAGS_ENVMAP
from _vtf._constants import TEXTUREFLAGS_RENDERTARGET
from _vtf._constants import TEXTUREFLAGS_DEPTHRENDERTARGET
from _vtf._constants import TEXTUREFLAGS_NODEBUGOVERRIDE
from _vtf._constants import TEXTUREFLAGS_SINGLECOPY
from _vtf._constants import TEXTUREFLAGS_STAGING_MEMORY
from _vtf._constants import TEXTUREFLAGS_IMMEDIATE_CLEANUP
from _vtf._constants import TEXTUREFLAGS_IGNORE_PICMIP
from _vtf._constants import TEXTUREFLAGS_UNUSED_00400000
from _vtf._constants import TEXTUREFLAGS_NODEPTHBUFFER
from _vtf._constants import TEXTUREFLAGS_UNUSED_01000000
from _vtf._constants import TEXTUREFLAGS_CLAMPU
from _vtf._constants import TEXTUREFLAGS_VERTEXTEXTURE
from _vtf._constants import TEXTUREFLAGS_SSBUMP
from _vtf._constants import TEXTUREFLAGS_UNUSED_10000000
from _vtf._constants import TEXTUREFLAGS_BORDER
from _vtf._constants import TEXTUREFLAGS_UNUSED_40000000
from _vtf._constants import TEXTUREFLAGS_UNUSED_80000000


# =============================================================================
# >> ALL DECLARATION
# =============================================================================
__all__ = ('ImageFormat',
           'VTFFlags',
           )


# =============================================================================
# >> ENUMERATORS
# =============================================================================
class VTFFlags(IntFlag):
    """VTF flags wrapper enumerator."""

    POINTSAMPLE = TEXTUREFLAGS_POINTSAMPLE
    TRILINEAR = TEXTUREFLAGS_TRILINEAR
    CLAMPS = TEXTUREFLAGS_CLAMPS
    CLAMPT = TEXTUREFLAGS_CLAMPT
    ANISOTROPIC = TEXTUREFLAGS_ANISOTROPIC
    HINT_DXT5 = TEXTUREFLAGS_HINT_DXT5
    SRGB = TEXTUREFLAGS_SRGB
    NORMAL = TEXTUREFLAGS_NORMAL
    NOMIP = TEXTUREFLAGS_NOMIP
    NOLOD = TEXTUREFLAGS_NOLOD
    ALL_MIPS = TEXTUREFLAGS_ALL_MIPS
    PROCEDURAL = TEXTUREFLAGS_PROCEDURAL
    ONEBITALPHA = TEXTUREFLAGS_ONEBITALPHA
    EIGHTBITALPHA = TEXTUREFLAGS_EIGHTBITALPHA
    ENVMAP = TEXTUREFLAGS_ENVMAP
    RENDERTARGET = TEXTUREFLAGS_RENDERTARGET
    DEPTHRENDERTARGET = TEXTUREFLAGS_DEPTHRENDERTARGET
    NODEBUGOVERRIDE = TEXTUREFLAGS_NODEBUGOVERRIDE
    SINGLECOPY = TEXTUREFLAGS_SINGLECOPY
    STAGING_MEMORY = TEXTUREFLAGS_STAGING_MEMORY
    IMMEDIATE_CLEANUP = TEXTUREFLAGS_IMMEDIATE_CLEANUP
    IGNORE_PICMIP = TEXTUREFLAGS_IGNORE_PICMIP
    UNUSED_00400000 = TEXTUREFLAGS_UNUSED_00400000
    NODEPTHBUFFER = TEXTUREFLAGS_NODEPTHBUFFER
    UNUSED_01000000 = TEXTUREFLAGS_UNUSED_01000000
    CLAMPU = TEXTUREFLAGS_CLAMPU
    VERTEXTEXTURE = TEXTUREFLAGS_VERTEXTEXTURE
    SSBUMP = TEXTUREFLAGS_SSBUMP
    UNUSED_10000000 = TEXTUREFLAGS_UNUSED_10000000
    BORDER = TEXTUREFLAGS_BORDER
    UNUSED_40000000 = TEXTUREFLAGS_UNUSED_40000000
    UNUSED_80000000 = TEXTUREFLAGS_UNUSED_80000000
