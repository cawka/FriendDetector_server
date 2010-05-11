/* 
 * File:   init.h
 * Author: cawka
 *
 * Created on May 11, 2010, 1:12 AM
 */

#ifndef _INIT_H
#define	_INIT_H

#include <sqlite3.h>
#include <libsqlitewrapped.h>

#include <boost/shared_ptr.hpp>
using namespace boost;

extern shared_ptr<Database> DB;

#endif	/* _INIT_H */

