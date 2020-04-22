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

//---------------------------------------------------------------------------------
// Includes.
//---------------------------------------------------------------------------------
// Source.Python
#include "utilities/wrap_macros.h"
#include "vtf.h"


//---------------------------------------------------------------------------------
// External variables.
//---------------------------------------------------------------------------------
extern IFileSystem* filesystem;


//---------------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------------
bool IsVTFFile(const char* pFileName, bool bHeaderOnly, int nSkipMipLevels, bool bHeaderFix)
{
	FileHandle_t handle = filesystem->Open(pFileName, "rb");
	if (handle == FILESYSTEM_INVALID_HANDLE)
		BOOST_RAISE_EXCEPTION(PyExc_IOError, "Unable to open file: %s", pFileName)

	int size = filesystem->Size(handle);
	if (bHeaderOnly) {
		int nHeaderSize = VTFFileHeaderSize();
		if (size > nHeaderSize) {
			size = nHeaderSize;
		}
	}

	CUtlBuffer buf;
	buf.EnsureCapacity(size);
	int nBytesRead = filesystem->Read(buf.Base(), size, handle);
	filesystem->Close(handle);
	if (nBytesRead != size)
		BOOST_RAISE_EXCEPTION(PyExc_IOError, "Failed to read file: %s", pFileName)

	buf.SeekPut(CUtlBuffer::SEEK_HEAD, nBytesRead);

	if (bHeaderFix && nBytesRead >= 9) {
		unsigned char* pBuf = static_cast<unsigned char*>(buf.Base());
		unsigned char minor_version = pBuf[8];
		if (minor_version == 5) {
			pBuf[8] = 4;
		}
	}

	IVTFTexture *pTexture = CreateVTFTexture();
	bool bUnserialized = pTexture->Unserialize(buf, bHeaderOnly, nSkipMipLevels);
	DestroyVTFTexture(pTexture);

	return bUnserialized;
}
