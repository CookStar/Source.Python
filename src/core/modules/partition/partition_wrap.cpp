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

//---------------------------------------------------------------------------------
// Includes.
//---------------------------------------------------------------------------------
// Source.Python
#include "export_main.h"
#include "modules/memory/memory_tools.h"
#include "partition.h"


//---------------------------------------------------------------------------------
// External variables.
//---------------------------------------------------------------------------------
extern ISpatialPartition* partition;


//---------------------------------------------------------------------------------
// Forward declarations.
//---------------------------------------------------------------------------------
void export_spatial_partition(scope);
void export_partition_enumerator(scope);
void export_partition_masks(scope);
void export_iteration_retval(scope);


//---------------------------------------------------------------------------------
// Declare the _partition module.
//---------------------------------------------------------------------------------
DECLARE_SP_MODULE(_partition)
{
	export_spatial_partition(_partition);
	export_partition_enumerator(_partition);
	export_partition_masks(_partition);
	export_iteration_retval(_partition);
}


//---------------------------------------------------------------------------------
// Exports ISpatialPartition.
//---------------------------------------------------------------------------------
void export_spatial_partition(scope _partition)
{
	class_<ISpatialPartition, boost::noncopyable>("_SpatialPartition", no_init)
		.def("enumerate_elements_in_box",
			&ISpatialPartition::EnumerateElementsInBox,
			"Enumerates over all elements within a box.",
			args("listMask", "mins", "maxs", "coarseTest", "enumerator")
		)

		.def("enumerate_elements_in_sphere",
			&ISpatialPartition::EnumerateElementsInSphere,
			"Enumerates over all elements within a sphere.",
			args("listMask", "origin", "radius", "coarseTest", "enumerator")
		)

		.def("enumerate_elements_along_ray",
			&ISpatialPartition::EnumerateElementsAlongRay,
			"Enumerates over all elements along a ray.",
			args("listMask", "ray", "coarseTest", "enumerator")
		)

		.def("enumerate_elements_at_point",
			&ISpatialPartition::EnumerateElementsAtPoint,
			"Enumerates over all elements at a specific point.",
			args("listMask", "point", "coarseTest", "enumerator")
		)

		ADD_MEM_TOOLS(ISpatialPartition)
	;

	_partition.attr("spatial_partition") = object(ptr(partition));
}


//-----------------------------------------------------------------------------
// Exports IPartitionEnumerator
//-----------------------------------------------------------------------------
void export_partition_enumerator(scope _partition)
{
	class_<IPartitionEnumeratorWrap, boost::noncopyable>("PartitionEnumerator")
		.def("enum_element",
			pure_virtual(&IPartitionEnumeratorWrap::EnumElement),
			"Gets called with each handle."
		)

		ADD_MEM_TOOLS_WRAPPER(IPartitionEnumeratorWrap, IPartitionEnumerator)
	;
}


//-----------------------------------------------------------------------------
// Exports partition masks
//-----------------------------------------------------------------------------
void export_partition_masks(scope _partition)
{
	_partition.attr("PARTITION_ENGINE_SOLID_EDICTS") = static_cast<unsigned int>(PARTITION_ENGINE_SOLID_EDICTS);
	_partition.attr("PARTITION_ENGINE_TRIGGER_EDICTS") = static_cast<unsigned int>(PARTITION_ENGINE_TRIGGER_EDICTS);
	_partition.attr("PARTITION_ENGINE_NON_STATIC_EDICTS") = static_cast<unsigned int>(PARTITION_ENGINE_NON_STATIC_EDICTS);
	_partition.attr("PARTITION_ENGINE_STATIC_PROPS") = static_cast<unsigned int>(PARTITION_ENGINE_STATIC_PROPS);
}


//-----------------------------------------------------------------------------
// Exports IterationRetval_t
//-----------------------------------------------------------------------------
void export_iteration_retval(scope _partition)
{
	enum_<IterationRetval_t>("IterationRetval")
		.value("CONTINUE", ITERATION_CONTINUE)
		.value("STOP", ITERATION_STOP)
	;
}

