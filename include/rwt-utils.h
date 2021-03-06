/* +---------------------------------------------------------------------------+
   |                       Recursive World Toolkit                             |
   |                                                                           |
   |   Copyright (C) 2011-2015  Jose Luis Blanco Claraco                       |
   |                                                                           |
   |      RWT is free software: you can redistribute it and/or modify          |
   |     it under the terms of the GNU General Public License as published by  |
   |     the Free Software Foundation, either version 3 of the License, or     |
   |     (at your option) any later version.                                   |
   |                                                                           |
   |    RWT is distributed in the hope that it will be useful,                 |
   |     but WITHOUT ANY WARRANTY; without even the implied warranty of        |
   |     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         |
   |     GNU General Public License for more details.                          |
   |                                                                           |
   |     You should have received a copy of the GNU General Public License     |
   |     along with  RWT.  If not, see <http://www.gnu.org/licenses/>.         |
   |                                                                           |
   +---------------------------------------------------------------------------+ */

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>


// Useful macros ---------------------
#if defined(__BORLANDC__)
#   define _CURRENT_FUNC_       __FUNC__
#else
#   define _CURRENT_FUNC_       __FUNCTION__
#endif

#define RWTASSERT(_F) \
    { \
        if (!(_F)) \
        { \
            std::stringstream s; \
            s << _CURRENT_FUNC_ << ":" << __LINE__ << ": Assert failed: " << #_F; \
            throw std::runtime_error(s.str()); \
        } \
    } \

#ifdef _DEBUG
#   define RWTASSERT_DEBUG(_F) RWTASSERT(_F)
#else
#   define RWTASSERT_DEBUG(_F)
#endif

/** Usage: RWT_MESSAGE << "blah" << x << endl;
  */
#define RWT_MESSAGE std::cout << "[" << _CURRENT_FUNC_ << "] "

// Define a decl. modifier for printf-like format checks at compile time:
#ifdef __GNUC__
#	define RWT_printf_format_check(_FMT_,_VARARGS_)  __attribute__ ((__format__ (__printf__, _FMT_,_VARARGS_)))
#else
#	define RWT_printf_format_check(_FMT_,_VARARGS_)
#endif

namespace rwt
{
	/** Returns the numeric representation of a string, or raises an exception if it's not a valid number */
	double str2num(const std::string &s);

}

