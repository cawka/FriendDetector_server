/* 
 * File:   init.h
 * Author: cawka
 *
 * Created on May 11, 2010, 1:12 AM
 */

#ifndef _INIT_H
#define	_INIT_H

#define OTL_ODBC_UNIX
//#define OTL_ODBC
#define OTL_STL
#include <otlv4.h>

#include <boost/shared_ptr.hpp>
using namespace boost;

extern otl_connect DB;

#endif	/* _INIT_H */

