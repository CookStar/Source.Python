/**
* =============================================================================
* Source Python
* Copyright (C) 2012-2016 Source Python Development Team.  All rights reserved.
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
#include "export_main.h"
#include "vtf.h"


//-----------------------------------------------------------------------------
// Forward declarations.
//-----------------------------------------------------------------------------
static void export_functions(scope);
static void export_vtf_texture(scope);


//-----------------------------------------------------------------------------
// Declare the _vtf module.
//-----------------------------------------------------------------------------
DECLARE_SP_MODULE(_vtf)
{
	export_functions(_vtf);
	export_vtf_texture(_vtf);
}


//-----------------------------------------------------------------------------
// Exports functions.
//-----------------------------------------------------------------------------
void export_functions(scope _vtf)
{
	def(
		"is_vtf_file",
		&IsVTFFile,
		(arg("file_path"), arg("header_only")=false, arg("skip_mip_levels")=0, arg("header_fix")=true)
	);

	def(
		"header_size",
		&VTFFileHeaderSize,
		(arg("major_version")=-1, arg("minor_version")=-1)
	);
}


//-----------------------------------------------------------------------------
// Exports IVTFTexture.
//-----------------------------------------------------------------------------
BOOST_PYTHON_FUNCTION_OVERLOADS(image_data_size_overload, IVTFTextureExt::ImageDataSize, 6, 7)
BOOST_PYTHON_FUNCTION_OVERLOADS(get_image_data_overload, IVTFTextureExt::GetImageData, 6, 7)
BOOST_PYTHON_FUNCTION_OVERLOADS(set_image_data_overload, IVTFTextureExt::SetImageData, 7, 8)

void export_vtf_texture(scope _vtf)
{
	class_<IVTFTexture, boost::shared_ptr<IVTFTexture>, boost::noncopyable>("VTFTexture", no_init)
		.def("__init__",
			make_constructor(
				&IVTFTextureExt::__init__,
				default_call_policies()
			)
		)
		.def("__init__",
			make_constructor(
				&IVTFTextureExt::__init__2,
				default_call_policies(),
				(arg("width"), arg("height"), arg("depth"), arg("image_format"), arg("flags"), arg("frame_count"), arg("force_mip_count")=-1)
			),
			"Initializes the texture and allocates space for the bits.\n"
			"In most cases, you shouldn't force the mip count."
		)

		.def(
			"init",
			&IVTFTexture::Init,
			(arg("width"), arg("height"), arg("depth"), arg("image_format"), arg("flags"), arg("frame_count"), arg("force_mip_count")=-1),
			"Initializes the texture and allocates space for the bits.\n"
			"In most cases, you shouldn't force the mip count."
		)

		.add_property(
			"bump_scale",
			&IVTFTexture::BumpScale,
			&IVTFTexture::SetBumpScale
		)

		.add_property(
			"reflectivity",
			make_function(
				&IVTFTexture::Reflectivity,
				reference_existing_object_policy()
			),
			&IVTFTexture::SetReflectivity,
			"NOTE: reflectivity[0] = blue, [1] = greem, [2] = red."
		)

		.def(
			"init_low_res_image",
			&IVTFTexture::InitLowResImage,
			(arg("width"), arg("height"), arg("image_format")),
			"Methods to initialize the low-res image."
		)

		.def(
			"unserialize",
			&IVTFTextureExt::Unserialize,
			(arg("texture"), arg("header_only")=false, arg("skip_mip_levels")=0, arg("header_fix")=true),
			"When unserializing, we can skip a certain number of mip levels, and we also can just load everything but the image data.\n"
			"NOTE: If you skip mip levels, the height + width of the texture will change to reflect the size of the largest read in mip level."
		)
		.def(
			"serialize",
			&IVTFTextureExt::Serialize
		)

		.def(
			"file_size",
			&IVTFTexture::FileSize,
			(arg("mip_skip_count")=0)
		)

		.add_property(
			"width",
			&IVTFTexture::Width
		)
		.add_property(
			"height",
			&IVTFTexture::Height
		)
		.add_property(
			"depth",
			&IVTFTexture::Depth
		)
		.add_property(
			"mip_count",
			&IVTFTexture::MipCount
		)

		.def(
			"row_size_in_bytes",
			&IVTFTexture::RowSizeInBytes,
			(arg("mip_level")=0),
			"returns the size of one row of a particular mip level."
		)

		.def(
			"face_size_in_bytes",
			&IVTFTexture::FaceSizeInBytes,
			(arg("mip_level")=0),
			"returns the size of one face of a particular mip level."
		)

		.add_property(
			"format",
			&IVTFTexture::Format
		)
		.add_property(
			"face_count",
			&IVTFTexture::FaceCount
		)
		.add_property(
			"frame_count",
			&IVTFTexture::FrameCount
		)
		.add_property(
			"flags",
			&IVTFTexture::Flags
		)

		.add_property(
			"low_res_width",
			&IVTFTexture::LowResWidth
		)
		.add_property(
			"low_res_height",
			&IVTFTexture::LowResHeight
		)
		.add_property(
			"low_res_format",
			&IVTFTexture::LowResFormat
		)

		.def("is_cube_map",
			&IVTFTexture::IsCubeMap
		)
		.def("is_normal_map",
			&IVTFTexture::IsNormalMap
		)
		.def("is_volume_texture",
			&IVTFTexture::IsVolumeTexture
		)

		.def("compute_mip_width",
			&IVTFTextureExt::ComputeMipWidth,
			arg("mip_level"),
			"Computes the width of a particular mip level."
		)
		.def("compute_mip_height",
			&IVTFTextureExt::ComputeMipHeight,
			arg("mip_level"),
			"Computes the height of a particular mip level."
		)
		.def("compute_mip_depth",
			&IVTFTextureExt::ComputeMipDepth,
			arg("mip_level"),
			"Computes the depth of a particular mip level."
		)

		.def("compute_mip_size",
			&IVTFTexture::ComputeMipSize,
			arg("mip_level"),
			"Computes the size (in bytes) of a single mipmap of a single face of a single frame."
		)
		.def("compute_face_size",
			&IVTFTexture::ComputeFaceSize,
			(arg("starting_mip_level")=0),
			"Computes the size (in bytes) of a single face of a single frame.\n"
			"All mip levels starting at the specified mip level are included."
		)
		.def("compute_total_size",
			&IVTFTexture::ComputeTotalSize,
			"Computes the total size (in bytes) of all faces, all frames."
		)

		.def("image_data_size",
			GET_FUNCTION(int, IVTFTextureExt::ImageDataSize, IVTFTexture*),
			"Returns the image data size."
		)
		.def("image_data_size",
			GET_FUNCTION(int, IVTFTextureExt::ImageDataSize, IVTFTexture*, int, int, int),
			(arg("frame"), arg("face"), arg("mip_level")),
			"Returns the image data size associated with a particular frame, face, and mip level."
		)
		.def("image_data_size",
			GET_FUNCTION(int, IVTFTextureExt::ImageDataSize, IVTFTexture*, int, int, int, int, int, int),
			image_data_size_overload(
				(arg("frame"), arg("face"), arg("mip_level"), arg("x"), arg("y"), arg("z")=0),
				"Returns the image data size associated with a particular frame, face, mip level, and offset."
			)
		)

		.def("get_image_data",
			GET_FUNCTION(PyObject*, IVTFTextureExt::GetImageData, IVTFTexture*),
			"Returns the image data."
		)
		.def("get_image_data",
			GET_FUNCTION(PyObject*, IVTFTextureExt::GetImageData, IVTFTexture*, int, int, int),
			(arg("frame"), arg("face"), arg("mip_level")),
			"Returns the image data associated with a particular frame, face, and mip level."
		)
		.def("get_image_data",
			GET_FUNCTION(PyObject*, IVTFTextureExt::GetImageData, IVTFTexture*, int, int, int, int, int, int),
			get_image_data_overload(
				(arg("frame"), arg("face"), arg("mip_level"), arg("x"), arg("y"), arg("z")=0),
				"Returns the image data associated with a particular frame, face, mip level, and offset."
			)
		)

		.def("set_image_data",
			GET_FUNCTION(void, IVTFTextureExt::SetImageData, IVTFTexture*, PyObject*),
			arg("image_data"),
			"Sets the image data."
		)
		.def("set_image_data",
			GET_FUNCTION(void, IVTFTextureExt::SetImageData, IVTFTexture*, PyObject*, int, int, int),
			(arg("image_data"), arg("frame"), arg("face"), arg("mip_level")),
			"Sets the image data associated with a particular frame, face, and mip level."
		)
		.def("set_image_data",
			GET_FUNCTION(void, IVTFTextureExt::SetImageData, IVTFTexture*, PyObject*, int, int, int, int, int, int),
			set_image_data_overload(
				(arg("image_data"), arg("frame"), arg("face"), arg("mip_level"), arg("x"), arg("y"), arg("z")=0),
				"Sets the image data associated with a particular frame, face, mip level, and offset."
			)
		)

		.def("low_res_image_data_size",
			&IVTFTextureExt::LowResImageDataSize,
			"Returns the low-res image data size."
		)
		.def("get_low_res_image_data",
			&IVTFTextureExt::GetLowResImageData,
			"Returns the low-res image data."
		)
		.def("set_low_res_image_data",
			&IVTFTextureExt::SetLowResImageData,
			arg("low_res_image_data"),
			"Sets the low-res image data size."
		)

		//DXT is broken.
		.def(
			"convert_image_format",
			&IVTFTexture::ConvertImageFormat,
			(arg("image_format"), arg("normal_to_DUDV")),
			"Converts the textures image format.\n"
			"Use ImageFormat.DEFAULT if you want to be able to use various tool functions."
		)

		.def("fix_cubemap_face_orientation",
			&IVTFTexture::FixCubemapFaceOrientation,
			"Fixes the cubemap faces orientation from our standard to the standard the material system needs."
		)

		.def("generate_mipmaps",
			&IVTFTexture::GenerateMipmaps,
			"Generates mipmaps from the base mip levels."
		)

		.def("put_one_over_mip_level_in_alpha",
			&IVTFTexture::PutOneOverMipLevelInAlpha,
			"Put 1/miplevel (1..n) into alpha."
		)

		.def("compute_reflectivity",
			&IVTFTexture::ComputeReflectivity,
			"Computes the reflectivity."
		)

		.def("compute_alpha_flags",
			&IVTFTexture::ComputeAlphaFlags,
			"Computes the alpha flags."
		)

		.def("construct_low_res_image",
			&IVTFTexture::ConstructLowResImage,
			"Generate the low-res image bits."
		)

		.def("set_alpha_test_threshholds",
			&IVTFTexture::SetAlphaTestThreshholds,
			(arg("base"), arg("high_freq")),
			"Sets threshhold values for alphatest mipmapping."
		)

		.def("save",
			&IVTFTextureExt::Save,
			arg("file_path")
		)

		.def("open", &IVTFTextureExt::Open,
			(arg("file_path"), arg("header_only")=false, arg("skip_mip_levels")=0, arg("header_fix")=true)
		).staticmethod("open")
	;
}
