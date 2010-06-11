/****************************************************************
 *
 * Copyright (C) 2010 Max Planck Institute for Human Cognitive
 * and Brain Sciences, Leipzig.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Author: Thomas Pröger, proeger@cbs.mpg.de, 2010
 *
 *****************************************************************/

#ifndef IMAGEFORMAT_VISTA_H_
#define IMAGEFORMAT_VISTA_H_

// global includes
#include <viaio/VImage.h>

// local includes
#include <DataStorage/io_interface.h>

namespace isis
{

namespace image_io
{

class ImageFormat_Vista: public FileFormat
{
public:

	std::string name() { return "de.mpg.cbs.isis.vista"; }
	std::string suffixes() {return ".v";}
	int load( data::ChunkList &chunks, const std::string &filename,
			  const std::string &dialect ) throw( std::runtime_error & );
	void write( const data::Image &image, const std::string &filename,
				const std::string &dialect ) throw( std::runtime_error & );

private:

	/**
	 * This function copies all chunk header informations to the appropriate
	 * vista image attribute values.
	 *
	 * @param chunk A reference to chunk that provides the metadata.
	 * @param image The target image. Alle metadata will be copied to the
	 * corresponding header attributes.
	 */
	void copyHeaderToVista(const data::Image& image, VImage& vimage);

	template<typename T> bool copyImageToVista(const data::Image& image, VImage& vimage){
		T min,max;
		image.getMinMax<T>(min,max);
		const util::FixedVector<size_t, 4> csize = image.getChunk( 0, 0 ).sizeToVector();
		const util::FixedVector<size_t, 4> isize = image.sizeToVector();
		LOG_IF(isize[3]>1,Debug,error) << "Vista cannot store 4D-Data in one VImage";

		for ( size_t z = 0; z < isize[2]; z += csize[2] ) {
			for ( size_t y = 0; y < isize[1]; y += csize[1] ) {
				for ( size_t x = 0; x < isize[0]; x += csize[0] ) {
					data::Chunk ch=image.getChunkAs<T>( min,max,x, y, z, 0 );
					ch.getTypePtr<T>().copyToMem(0,csize.product()-1,&VPixel( vimage, z, y, x, T ));
				}
			}
		}
		return true;
	}

	/**
	 * This function copies all metadata from Vista image header attributes to
	 * the corresponding fields in the target Vista image.
	 * @param image The target chunk where all data will be copied to.
	 * @oaram chunk The source image that provides the Vista metadata attributes.
	 */
	void copyHeaderFromVista(const VImage& image, data::Chunk& chunk);

	/**
	 * This function creates a MemChunk with the correct type and adds it to the
	 * end of the Chunk list.
	 */
	template <typename TInput> void addChunk(data::ChunkList &chunks, VImage image);
};

}
}//namespace image_io isis

#endif /* IMAGEFORMAT_VISTA_H_ */
