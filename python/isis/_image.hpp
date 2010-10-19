/*
 * _image.hpp
 *
 *  Created on: Oct 19, 2010
 *      Author: tuerke
 */

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include "DataStorage/image.hpp"

namespace isis
{
namespace python
{
class _Image : public isis::data::Image, boost::python::wrapper<isis::data::Image>
{
public:
	_Image ( PyObject *p) : self( p ) {}
	_Image ( PyObject *p, const isis::data::Image &base ) : isis::data::Image( base ), self( p ) {}

	size_t voxel( const int &first, const int &second, const int &third, const int &fourth )
	{
		switch( this->typeID()) {
		case data::TypePtr<int8_t>::staticID:
			return isis::data::Image::voxel<int8_t>( first, second, third, fourth );
			break;
		case data::TypePtr<u_int8_t>::staticID:
			return isis::data::Image::voxel<u_int8_t>( first, second, third, fourth );
			break;
		case data::TypePtr<int16_t>::staticID:
			return isis::data::Image::voxel<int16_t>( first, second, third, fourth );
			break;
		case data::TypePtr<u_int16_t>::staticID:
			return isis::data::Image::voxel<u_int16_t>( first, second, third, fourth );
			break;
		case data::TypePtr<int32_t>::staticID:
			return isis::data::Image::voxel<int32_t>( first, second, third, fourth );
			break;
		case data::TypePtr<u_int32_t>::staticID:
			return isis::data::Image::voxel<u_int32_t>( first, second, third, fourth );
			break;
		case data::TypePtr<float>::staticID:
			return isis::data::Image::voxel<float>( first, second, third, fourth );
			break;
		case data::TypePtr<double>::staticID:
			return isis::data::Image::voxel<double>( first, second, third, fourth );
			break;
		default:
			return 0;
		}
	}
	bool setVoxel( const int &first, const int &second, const int &third, const int &fourth, const float &value )
	{
		switch( this->typeID()) {
		case data::TypePtr<int8_t>::staticID:
			isis::data::Image::voxel<int8_t>(first, second, third, fourth) = value;
			return true;
			break;
		case data::TypePtr<u_int8_t>::staticID:
			isis::data::Image::voxel<u_int8_t>(first, second, third, fourth) = value;
			return true;
			break;
		case data::TypePtr<int16_t>::staticID:
			isis::data::Image::voxel<int16_t>(first, second, third, fourth) = value;
			return true;
			break;
		case data::TypePtr<u_int16_t>::staticID:
			isis::data::Image::voxel<u_int16_t>(first, second, third, fourth) = value;
			return true;
			break;
		case data::TypePtr<int32_t>::staticID:
			isis::data::Image::voxel<int32_t>(first, second, third, fourth) = value;
			return true;
			break;
		case data::TypePtr<u_int32_t>::staticID:
			isis::data::Image::voxel<u_int32_t>(first, second, third, fourth) = value;
			return true;
			break;
		case data::TypePtr<float>::staticID:
			isis::data::Image::voxel<float>(first, second, third, fourth) = value;
			return true;
			break;
		case data::TypePtr<double>::staticID:
			isis::data::Image::voxel<double>(first, second, third, fourth) = value;
			return true;
			break;
		default:
			return false;

		}

	}



private:
	PyObject *self;

};



class _ImageList : public std::list<isis::data::Image>
{


};

}}

#endif /* IMAGE_HPP_ */
