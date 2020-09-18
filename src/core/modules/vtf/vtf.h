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

#ifndef _VTF_H
#define _VTF_H

//---------------------------------------------------------------------------------
// Includes.
//---------------------------------------------------------------------------------
#include <algorithm>
#include "public/vtf/vtf.h"
#include "public/filesystem.h"
#include "public/tier1/utlbuffer.h"


//---------------------------------------------------------------------------------
// External variables.
//---------------------------------------------------------------------------------
extern IFileSystem* filesystem;


//---------------------------------------------------------------------------------
// Functions.
//---------------------------------------------------------------------------------
bool IsVTFFile(const char* pFileName, bool bHeaderOnly = false, int nSkipMipLevels = 0, bool bHeaderFix = true);


//-----------------------------------------------------------------------------
// IVTFTextureExt extension class.
//-----------------------------------------------------------------------------
class IVTFTextureExt
{
public:
	static boost::shared_ptr<IVTFTexture> __init__()
	{
		return boost::shared_ptr<IVTFTexture>(CreateVTFTexture(), &DestroyVTFTexture);
	}

	static boost::shared_ptr<IVTFTexture> __init__2(int nWidth, int nHeight, int nDepth, ImageFormat fmt, int nFlags, int iFrameCount, int nForceMipCount = -1)
	{
		boost::shared_ptr<IVTFTexture> pTexture(CreateVTFTexture(), &DestroyVTFTexture);
		if (!pTexture->Init(nWidth, nHeight, nDepth, fmt, nFlags, iFrameCount, nForceMipCount))
			BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Failed to initialize texture.")
		return pTexture;
	}

	static boost::shared_ptr<IVTFTexture> Open(const char* pFileName, bool bHeaderOnly = false, int nSkipMipLevels = 0, bool bHeaderFix = true)
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

		boost::shared_ptr<IVTFTexture> pTexture(CreateVTFTexture(), &DestroyVTFTexture);
		if (!pTexture->Unserialize(buf, bHeaderOnly, nSkipMipLevels))
			BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Failed to unserialize texture: %s", pFileName)

		return pTexture;
	}

	static void Save(IVTFTexture* pTexture, const char* pFileName)
	{
		FileHandle_t handle = filesystem->Open(pFileName, "wb");
		if (handle == FILESYSTEM_INVALID_HANDLE)
			BOOST_RAISE_EXCEPTION(PyExc_IOError, "Failed to open file: %s", pFileName)

		CUtlBuffer buf;
		if (!pTexture->Serialize(buf))
			BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Failed to serialize texture: %s", pFileName)

		filesystem->Write(buf.Base(), buf.TellPut(), handle);
		filesystem->Close(handle);
	}

	static bool Unserialize(IVTFTexture* pTexture, PyObject* data, bool bHeaderOnly = false, int nSkipMipLevels = 0, bool bHeaderFix = true)
	{
		char* pData = nullptr;
		int size = 0;

		if (PyBytes_Check(data)) {
			pData = PyBytes_AS_STRING(data);
			size = PyBytes_GET_SIZE(data);
		}
		else if (PyByteArray_Check(data)) {
			pData = PyByteArray_AS_STRING(data);
			size = PyByteArray_GET_SIZE(data);
		}
		else {
			BOOST_RAISE_EXCEPTION(PyExc_TypeError, "a bytes-like object is required, not '%s'", data->ob_type->tp_name)
		}

		CUtlBuffer buf(pData, size, CUtlBuffer::READ_ONLY);

		if (bHeaderFix && size >= 9) {
			unsigned char* pBuf = static_cast<unsigned char*>(buf.Base());
			unsigned char minor_version = pBuf[8];
			if (minor_version == 5) {
				pBuf[8] = 4;
			}
		}

		return pTexture->Unserialize(buf, bHeaderOnly, nSkipMipLevels);
	}

	static PyObject* Serialize(IVTFTexture* pTexture)
	{
		CUtlBuffer buf;
		bool bSerialize = pTexture->Serialize(buf);

		if (bSerialize) {
			PyObject* data = nullptr;
			data = PyBytes_FromStringAndSize(static_cast<char*>(buf.Base()), buf.TellPut());
			if (!data)
				BOOST_RAISE_EXCEPTION(PyExc_RuntimeError, "Failed to generate bytes object.")
			return data;
		}
		else {
			Py_RETURN_NONE;
		}
	}

	static int ComputeMipLevelDimensionsExt(IVTFTexture* pTexture, int iMipLevel, int base_value)
	{
		int mip_count = pTexture->MipCount();
		if (iMipLevel >= mip_count)
			BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Texture has no mipmap: miplevel '%d', mipcount '%d'", iMipLevel, mip_count)
		return (std::max)(1, base_value >> iMipLevel);
	}

	static int ComputeMipWidth(IVTFTexture* pTexture, int iMipLevel)
	{
		int width = pTexture->Width();
		return IVTFTextureExt::ComputeMipLevelDimensionsExt(pTexture, iMipLevel, width);
	}

	static int ComputeMipHeight(IVTFTexture* pTexture, int iMipLevel)
	{
		int height = pTexture->Height();
		return IVTFTextureExt::ComputeMipLevelDimensionsExt(pTexture, iMipLevel, height);
	}

	static int ComputeMipDepth(IVTFTexture* pTexture, int iMipLevel)
	{
		int depth = pTexture->Depth();
		return IVTFTextureExt::ComputeMipLevelDimensionsExt(pTexture, iMipLevel, depth);
	}

	static int ImageDataSizeExt(IVTFTexture* pTexture, unsigned char* pImageData)
	{
		unsigned char* pBaseImageData = pTexture->ImageData();
		if (pBaseImageData && pImageData) {
			int iMemorySize = pTexture->ComputeTotalSize();
			int offset = pImageData - pBaseImageData;
			iMemorySize -= offset;

			return (std::max)(0, iMemorySize);
		}
		else {
			BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Texture has no image data.")
		}
	}

	static int ImageDataSize(IVTFTexture* pTexture)
	{
		unsigned char* pImageData = pTexture->ImageData();
		return IVTFTextureExt::ImageDataSizeExt(pTexture, pImageData);
	}

	static int ImageDataSize(IVTFTexture* pTexture, int iFrame, int iFace, int iMipLevel)
	{
		unsigned char* pImageData = pTexture->ImageData(iFrame, iFace, iMipLevel);
		return IVTFTextureExt::ImageDataSizeExt(pTexture, pImageData);
	}

	static int ImageDataSize(IVTFTexture* pTexture, int iFrame, int iFace, int iMipLevel, int x, int y, int z = 0)
	{
		unsigned char* pImageData = pTexture->ImageData(iFrame, iFace, iMipLevel, x, y, z);
		return IVTFTextureExt::ImageDataSizeExt(pTexture, pImageData);
	}

	static PyObject* GetImageDataExt(IVTFTexture* pTexture, unsigned char* pImageData)
	{
		unsigned char* pBaseImageData = pTexture->ImageData();
		if (pBaseImageData && pImageData) {
			int iMemorySize = pTexture->ComputeTotalSize();
			int offset = pImageData - pBaseImageData;
			iMemorySize -= offset;
			if (iMemorySize < 0)
				BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Image data offset exceeds maximum length: offset '%d', max '%d'", offset, iMemorySize+offset)

			PyObject* data = nullptr;
			data = PyBytes_FromStringAndSize(reinterpret_cast<char*>(pBaseImageData+offset), iMemorySize);
			if (!data)
				BOOST_RAISE_EXCEPTION(PyExc_RuntimeError, "Failed to generate bytes object.")

			return data;
		}
		else {
			BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Texture has no image data.")
		}
	}

	static PyObject* GetImageData(IVTFTexture* pTexture)
	{
		unsigned char* pImageData = pTexture->ImageData();
		return IVTFTextureExt::GetImageDataExt(pTexture, pImageData);
	}

	static PyObject* GetImageData(IVTFTexture* pTexture, int iFrame, int iFace, int iMipLevel)
	{
		unsigned char* pImageData = pTexture->ImageData(iFrame, iFace, iMipLevel);
		return IVTFTextureExt::GetImageDataExt(pTexture, pImageData);
	}

	static PyObject* GetImageData(IVTFTexture* pTexture, int iFrame, int iFace, int iMipLevel, int x, int y, int z = 0)
	{
		unsigned char* pImageData = pTexture->ImageData(iFrame, iFace, iMipLevel, x, y, z);
		return IVTFTextureExt::GetImageDataExt(pTexture, pImageData);
	}

	static void SetImageDataExt(IVTFTexture* pTexture, PyObject* data, unsigned char* pImageData)
	{
		unsigned char* pBaseImageData = pTexture->ImageData();
		if (pBaseImageData && pImageData) {
			char* pData = nullptr;
			int size = 0;

			if (PyBytes_Check(data)) {
				pData = PyBytes_AS_STRING(data);
				size = PyBytes_GET_SIZE(data);
			}
			else if (PyByteArray_Check(data)) {
				pData = PyByteArray_AS_STRING(data);
				size = PyByteArray_GET_SIZE(data);
			}
			else {
				BOOST_RAISE_EXCEPTION(PyExc_TypeError, "a bytes-like object is required, not '%s'", data->ob_type->tp_name)
			}

			int iMemorySize = pTexture->ComputeTotalSize();
			int offset = pImageData - pBaseImageData;
			iMemorySize -= offset;
			if (iMemorySize < 0)
				BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Image data offset exceeds maximum length: offset '%d', max '%d'", offset, iMemorySize+offset)
			if (size > iMemorySize)
				BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Image data exceeds maximum length: data '%d', max '%d'", size, iMemorySize)

			memcpy(pBaseImageData+offset, pData, size);
		}
		else {
			BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Texture has no image data.")
		}
	}

	static void SetImageData(IVTFTexture* pTexture, PyObject* data)
	{
		unsigned char* pImageData = pTexture->ImageData();
		IVTFTextureExt::SetImageDataExt(pTexture, data, pImageData);
	}

	static void SetImageData(IVTFTexture* pTexture, PyObject* data, int iFrame, int iFace, int iMipLevel)
	{
		
		unsigned char* pImageData = pTexture->ImageData(iFrame, iFace, iMipLevel);
		IVTFTextureExt::SetImageDataExt(pTexture, data, pImageData);
	}

	static void SetImageData(IVTFTexture* pTexture, PyObject* data, int iFrame, int iFace, int iMipLevel, int x, int y, int z = 0)
	{
		unsigned char* pImageData = pTexture->ImageData(iFrame, iFace, iMipLevel, x, y, z);
		IVTFTextureExt::SetImageDataExt(pTexture, data, pImageData);
	}

	static int LowResImageDataSize(IVTFTexture* pTexture)
	{
		unsigned char* pLowResImageData = pTexture->LowResImageData();
		if (pLowResImageData) {
			int StartLocation;
			int SizeInBytes;
			pTexture->LowResFileInfo(&StartLocation, &SizeInBytes);

			return SizeInBytes;
		}
		else {
			BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Texture has no low res image data.")
		}
	}

	static PyObject* GetLowResImageData(IVTFTexture* pTexture)
	{
		unsigned char* pLowResImageData = pTexture->LowResImageData();
		if (pLowResImageData) {
			int StartLocation;
			int SizeInBytes;
			pTexture->LowResFileInfo(&StartLocation, &SizeInBytes);

			PyObject* data = nullptr;
			data = PyBytes_FromStringAndSize(reinterpret_cast<char*>(pLowResImageData), SizeInBytes);
			if (!data)
				BOOST_RAISE_EXCEPTION(PyExc_RuntimeError, "Failed to generate bytes object.")

			return data;
		}
		else {
			BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Texture has no low res image data.")
		}
	}

	static void SetLowResImageData(IVTFTexture* pTexture, PyObject* data)
	{
		unsigned char* pLowResImageData = pTexture->LowResImageData();
		if (pLowResImageData) {
			char* pData = nullptr;
			int size = 0;

			if (PyBytes_Check(data)) {
				pData = PyBytes_AS_STRING(data);
				size = PyBytes_GET_SIZE(data);
			}
			else if (PyByteArray_Check(data)) {
				pData = PyByteArray_AS_STRING(data);
				size = PyByteArray_GET_SIZE(data);
			}
			else {
				BOOST_RAISE_EXCEPTION(PyExc_TypeError, "a bytes-like object is required, not '%s'", data->ob_type->tp_name)
			}

			int StartLocation;
			int SizeInBytes;
			pTexture->LowResFileInfo(&StartLocation, &SizeInBytes);
			if (size > SizeInBytes)
				BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Image data exceeds maximum length: data '%d', max '%d'", size, SizeInBytes)

			memcpy(pLowResImageData, pData, size);
		}
		else {
			BOOST_RAISE_EXCEPTION(PyExc_ValueError, "Texture has no low res image data.")
		}
	}
};


#endif // _VTF_H
