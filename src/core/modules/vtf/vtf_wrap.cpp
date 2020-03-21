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
//static void export_image_format(scope);
//static void export_vtf_flags(scope);


//-----------------------------------------------------------------------------
// Declare the _vtf module.
//-----------------------------------------------------------------------------
DECLARE_SP_MODULE(_vtf)
{
	export_functions(_vtf);
	export_vtf_texture(_vtf);
	//export_image_format(_vtf);
	//export_vtf_flags(_vtf);
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
			)
		)

		.def(
			"init",
			&IVTFTexture::Init,
			(arg("width"), arg("height"), arg("depth"), arg("image_format"), arg("flags"), arg("frame_count"), arg("force_mip_count")=-1)
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
			&IVTFTexture::SetReflectivity
		)

		.def(
			"init_low_res_image",
			&IVTFTexture::InitLowResImage,
			(arg("width"), arg("height"), arg("image_format"))
		)

		.def(
			"unserialize",
			&IVTFTextureExt::Unserialize,
			(arg("texture"), arg("header_only")=false, arg("skip_mip_levels")=0, arg("header_fix")=true)
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
			(arg("mip_level")=0)
		)

		.def(
			"face_size_in_bytes",
			&IVTFTexture::FaceSizeInBytes,
			(arg("mip_level")=0)
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

		.def("compute_mip_size",
			&IVTFTexture::ComputeMipSize
		)
		.def("compute_face_size",
			&IVTFTexture::ComputeFaceSize,
			(arg("starting_mip_level")=0)
		)
		.def("compute_total_size",
			&IVTFTexture::ComputeTotalSize
		)

		.def("image_data_size",
			GET_FUNCTION(int, IVTFTextureExt::ImageDataSize, IVTFTexture*)
		)
		.def("image_data_size",
			GET_FUNCTION(int, IVTFTextureExt::ImageDataSize, IVTFTexture*, int, int, int),
			(arg("frame"), arg("face"), arg("mip_level"))
		)
		.def("image_data_size",
			GET_FUNCTION(int, IVTFTextureExt::ImageDataSize, IVTFTexture*, int, int, int, int, int, int),
			image_data_size_overload(
				(arg("frame"), arg("face"), arg("mip_level"), arg("x"), arg("y"), arg("z")=0)
			)
		)

		.def("get_image_data",
			GET_FUNCTION(PyObject*, IVTFTextureExt::GetImageData, IVTFTexture*)
		)
		.def("get_image_data",
			GET_FUNCTION(PyObject*, IVTFTextureExt::GetImageData, IVTFTexture*, int, int, int),
			(arg("frame"), arg("face"), arg("mip_level"))
		)
		.def("get_image_data",
			GET_FUNCTION(PyObject*, IVTFTextureExt::GetImageData, IVTFTexture*, int, int, int, int, int, int),
			get_image_data_overload(
				(arg("frame"), arg("face"), arg("mip_level"), arg("x"), arg("y"), arg("z")=0)
			)
		)

		.def("set_image_data",
			GET_FUNCTION(void, IVTFTextureExt::SetImageData, IVTFTexture*, PyObject*),
			arg("image_data")
		)
		.def("set_image_data",
			GET_FUNCTION(void, IVTFTextureExt::SetImageData, IVTFTexture*, PyObject*, int, int, int),
			(arg("image_data"), arg("frame"), arg("face"), arg("mip_level"))
		)
		.def("set_image_data",
			GET_FUNCTION(void, IVTFTextureExt::SetImageData, IVTFTexture*, PyObject*, int, int, int, int, int, int),
			set_image_data_overload(
				(arg("image_data"), arg("frame"), arg("face"), arg("mip_level"), arg("x"), arg("y"), arg("z")=0)
			)
		)

		.def("low_res_image_data_size",
			&IVTFTextureExt::LowResImageDataSize
		)
		.def("get_low_res_image_data",
			&IVTFTextureExt::GetLowResImageData
		)
		.def("set_low_res_image_data",
			&IVTFTextureExt::SetLowResImageData,
			arg("low_res_image_data")
		)

		.def(
			"convert_image_format",
			&IVTFTexture::ConvertImageFormat,
			(arg("image_format"), arg("normal_to_DUDV"))
		)

		.def("fix_cubemap_face_orientation",
			&IVTFTexture::FixCubemapFaceOrientation
		)

		.def("generate_mipmaps",
			&IVTFTexture::GenerateMipmaps
		)

		.def("put_one_over_mip_level_in_alpha",
			&IVTFTexture::PutOneOverMipLevelInAlpha
		)

		.def("compute_reflectivity",
			&IVTFTexture::ComputeReflectivity
		)

		.def("compute_alpha_flags",
			&IVTFTexture::ComputeAlphaFlags
		)

		.def("construct_low_res_image",
			&IVTFTexture::ConstructLowResImage
		)

		.def("set_alpha_test_threshholds",
			&IVTFTexture::SetAlphaTestThreshholds,
			(arg("base"), arg("high_freq"))
		)

		.def("save",
			&IVTFTextureExt::Save
		)

		.def("open", &IVTFTextureExt::Open,
			(arg("file_path"), arg("header_only")=false, arg("skip_mip_levels")=0, arg("header_fix")=true)
		).staticmethod("open")
	;
}
