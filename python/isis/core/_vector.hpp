#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include "CoreUtils/vector.hpp"

using namespace isis::util;

namespace isis
{
namespace python
{


// helper class vector
template<class T>
class _Vector4 : public vector4<T>, boost::python::wrapper< vector4<T> >
{
public:
	_Vector4 () : boost::python::wrapper< vector4<T> >() {}
	_Vector4( PyObject *p ) :  self( p ), boost::python::wrapper< vector4<T> >()  {}

	_Vector4( PyObject *p, const T &first, const T &second, const T &third, const T &fourth )
		: vector4<T>( first, second, third, fourth ),  self( p ) {}

	_Vector4( PyObject *p, const vector4<T> &v )
		: vector4<T>( v ), self( p ) {}


	void setItem( size_t elem, const T &value ) {
		if( elem <= 3 && elem >= 0 ) {
			this->operator []( elem ) = value;
		} else {
			LOG( Runtime, error ) << "Index out of range!";
		}
	}

	T getItem( size_t elem ) {
		if( elem <= 3 && elem >= 0 ) {
			return this->operator []( elem );
		} else {
			LOG( Runtime, error ) << "Index out of range!";
		}
	}



private:
	PyObject *self;

};

}
}
#endif

