/**
* =============================================================================
* Source Python
* Copyright (C) 2012-2015 Source Python Development Team.  All rights reserved.
* =============================================================================
*
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License, version 3.0, as published by the
* Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
* details.
*
* You should have received a copy of the GNU General Public License along with
* this program.  If not, see <http://www.gnu.org/licenses/>.
*
* As a special exception, the Source Python Team gives you permission
* to link the code of this program (as well as its derivative works) to
* "Half-Life 2," the "Source Engine," and any Game MODs that run on software
* by the Valve Corporation.  You must obey the GNU General Public License in
* all respects for all other code used.  Additionally, the Source.Python
* Development Team grants this exception to all derivative works.
*/

//-----------------------------------------------------------------------------
// Includes.
//-----------------------------------------------------------------------------
#include <type_traits>
#include "export_main.h"
#include "vtf.h"


//-----------------------------------------------------------------------------
// Forward declarations.
//-----------------------------------------------------------------------------
static void export_image_format(scope);
static void export_vtf_flags(scope);


//-----------------------------------------------------------------------------
// Declare the _vtf._constants module.
//-----------------------------------------------------------------------------
DECLARE_SP_SUBMODULE(_vtf, _constants)
{
	export_image_format(_constants);
	export_vtf_flags(_constants);
}


//-----------------------------------------------------------------------------
// Exports ImageFormat.
//-----------------------------------------------------------------------------
void export_image_format(scope _constants)
{
	enum_<ImageFormat>("ImageFormat")
		.value("DEFAULT", IMAGE_FORMAT_DEFAULT)
		.value("UNKNOWN", IMAGE_FORMAT_UNKNOWN)
		.value("RGBA8888", IMAGE_FORMAT_RGBA8888)
		.value("ABGR8888", IMAGE_FORMAT_ABGR8888)
		.value("RGB888", IMAGE_FORMAT_RGB888)
		.value("BGR888", IMAGE_FORMAT_BGR888)
		.value("RGB565", IMAGE_FORMAT_RGB565)
		.value("I8", IMAGE_FORMAT_I8)
		.value("IA88", IMAGE_FORMAT_IA88)
		.value("P8", IMAGE_FORMAT_P8)
		.value("A8", IMAGE_FORMAT_A8)
		.value("RGB888_BLUESCREEN", IMAGE_FORMAT_RGB888_BLUESCREEN)
		.value("BGR888_BLUESCREEN", IMAGE_FORMAT_BGR888_BLUESCREEN)
		.value("ARGB8888", IMAGE_FORMAT_ARGB8888)
		.value("BGRA8888", IMAGE_FORMAT_BGRA8888)
		.value("DXT1", IMAGE_FORMAT_DXT1)
		.value("DXT3", IMAGE_FORMAT_DXT3)
		.value("DXT5", IMAGE_FORMAT_DXT5)
		.value("BGRX8888", IMAGE_FORMAT_BGRX8888)
		.value("BGR565", IMAGE_FORMAT_BGR565)
		.value("BGRX5551", IMAGE_FORMAT_BGRX5551)
		.value("BGRA4444", IMAGE_FORMAT_BGRA4444)
		.value("DXT1_ONEBITALPHA", IMAGE_FORMAT_DXT1_ONEBITALPHA)
		.value("BGRA5551", IMAGE_FORMAT_BGRA5551)
		.value("UV88", IMAGE_FORMAT_UV88)
		.value("UVWQ8888", IMAGE_FORMAT_UVWQ8888)
		.value("RGBA16161616F", IMAGE_FORMAT_RGBA16161616F)
		.value("RGBA16161616", IMAGE_FORMAT_RGBA16161616)
		.value("UVLX8888", IMAGE_FORMAT_UVLX8888)
		.value("R32F", IMAGE_FORMAT_R32F)
		.value("RGB323232F", IMAGE_FORMAT_RGB323232F)
		.value("RGBA32323232F", IMAGE_FORMAT_RGBA32323232F)
		.value("RG1616F", IMAGE_FORMAT_RG1616F)
		.value("RG3232F", IMAGE_FORMAT_RG3232F)
		.value("RGBX8888", IMAGE_FORMAT_RGBX8888)
		.value("NULL", IMAGE_FORMAT_NULL)
		.value("ATI2N", IMAGE_FORMAT_ATI2N)
		.value("ATI1N", IMAGE_FORMAT_ATI1N)
		.value("RGBA1010102", IMAGE_FORMAT_RGBA1010102)
		.value("BGRA1010102", IMAGE_FORMAT_BGRA1010102)
		.value("R16F", IMAGE_FORMAT_R16F)
		.value("D16", IMAGE_FORMAT_D16)
		.value("D15S1", IMAGE_FORMAT_D15S1)
		.value("D32", IMAGE_FORMAT_D32)
		.value("D24S8", IMAGE_FORMAT_D24S8)
		.value("LINEAR_D24S8", IMAGE_FORMAT_LINEAR_D24S8)
		.value("D24X8", IMAGE_FORMAT_D24X8)
		.value("D24X4S4", IMAGE_FORMAT_D24X4S4)
		.value("D24FS8", IMAGE_FORMAT_D24FS8)
		.value("D16_SHADOW", IMAGE_FORMAT_D16_SHADOW)
		.value("D24X8_SHADOW", IMAGE_FORMAT_D24X8_SHADOW)
		.value("LINEAR_BGRX8888", IMAGE_FORMAT_LINEAR_BGRX8888)
		.value("LINEAR_RGBA8888", IMAGE_FORMAT_LINEAR_RGBA8888)
		.value("LINEAR_ABGR8888", IMAGE_FORMAT_LINEAR_ABGR8888)
		.value("LINEAR_ARGB8888", IMAGE_FORMAT_LINEAR_ARGB8888)
		.value("LINEAR_BGRA8888", IMAGE_FORMAT_LINEAR_BGRA8888)
		.value("LINEAR_RGB888", IMAGE_FORMAT_LINEAR_RGB888)
		.value("LINEAR_BGR888", IMAGE_FORMAT_LINEAR_BGR888)
		.value("LINEAR_BGRX5551", IMAGE_FORMAT_LINEAR_BGRX5551)
		.value("LINEAR_I8", IMAGE_FORMAT_LINEAR_I8)
		.value("LINEAR_RGBA16161616", IMAGE_FORMAT_LINEAR_RGBA16161616)
		.value("LE_BGRX8888", IMAGE_FORMAT_LE_BGRX8888)
		.value("LE_BGRA8888", IMAGE_FORMAT_LE_BGRA8888)
		.value("NUM_IMAGE_FORMATS", NUM_IMAGE_FORMATS)
	;
}


//-----------------------------------------------------------------------------
// Exports VTFFlags.
//-----------------------------------------------------------------------------
void export_vtf_flags(scope _constants)
{
	_constants.attr("TEXTUREFLAGS_POINTSAMPLE") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_POINTSAMPLE);
	_constants.attr("TEXTUREFLAGS_TRILINEAR") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_TRILINEAR);
	_constants.attr("TEXTUREFLAGS_CLAMPS") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_CLAMPS);
	_constants.attr("TEXTUREFLAGS_CLAMPT") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_CLAMPT);
	_constants.attr("TEXTUREFLAGS_ANISOTROPIC") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_ANISOTROPIC);
	_constants.attr("TEXTUREFLAGS_HINT_DXT5") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_HINT_DXT5);
	_constants.attr("TEXTUREFLAGS_SRGB") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_SRGB);
	_constants.attr("TEXTUREFLAGS_NORMAL") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_NORMAL);
	_constants.attr("TEXTUREFLAGS_NOMIP") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_NOMIP);
	_constants.attr("TEXTUREFLAGS_NOLOD") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_NOLOD);
	_constants.attr("TEXTUREFLAGS_ALL_MIPS") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_ALL_MIPS);
	_constants.attr("TEXTUREFLAGS_PROCEDURAL") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_PROCEDURAL);
	_constants.attr("TEXTUREFLAGS_ONEBITALPHA") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_ONEBITALPHA);
	_constants.attr("TEXTUREFLAGS_EIGHTBITALPHA") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_EIGHTBITALPHA);
	_constants.attr("TEXTUREFLAGS_ENVMAP") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_ENVMAP);
	_constants.attr("TEXTUREFLAGS_RENDERTARGET") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_RENDERTARGET);
	_constants.attr("TEXTUREFLAGS_DEPTHRENDERTARGET") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_DEPTHRENDERTARGET);
	_constants.attr("TEXTUREFLAGS_NODEBUGOVERRIDE") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_NODEBUGOVERRIDE);
	_constants.attr("TEXTUREFLAGS_SINGLECOPY") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_SINGLECOPY);
	_constants.attr("TEXTUREFLAGS_STAGING_MEMORY") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_STAGING_MEMORY);
	_constants.attr("TEXTUREFLAGS_IMMEDIATE_CLEANUP") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_IMMEDIATE_CLEANUP);
	_constants.attr("TEXTUREFLAGS_IGNORE_PICMIP") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_IGNORE_PICMIP);
	_constants.attr("TEXTUREFLAGS_UNUSED_00400000") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_UNUSED_00400000);
	_constants.attr("TEXTUREFLAGS_NODEPTHBUFFER") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_NODEPTHBUFFER);
	_constants.attr("TEXTUREFLAGS_UNUSED_01000000") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_UNUSED_01000000);
	_constants.attr("TEXTUREFLAGS_CLAMPU") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_CLAMPU);
	_constants.attr("TEXTUREFLAGS_VERTEXTEXTURE") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_VERTEXTEXTURE);
	_constants.attr("TEXTUREFLAGS_SSBUMP") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_SSBUMP);
	_constants.attr("TEXTUREFLAGS_UNUSED_10000000") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_UNUSED_10000000);
	_constants.attr("TEXTUREFLAGS_BORDER") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_BORDER);
	_constants.attr("TEXTUREFLAGS_UNUSED_40000000") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_UNUSED_40000000);
	_constants.attr("TEXTUREFLAGS_UNUSED_80000000") = static_cast<unsigned int>(CompiledVtfFlags::TEXTUREFLAGS_UNUSED_80000000);
}
