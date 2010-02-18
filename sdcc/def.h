/* def.h --- 
 * 
 * Filename: def.h
 * Description: data type definition
 * Author: bigclean
 * Maintainer: 
 * Created: Sat Nov 21 02:22:51 2009 (-0500)
 * Version: 
 * Last-Updated: Mon Feb  8 22:09:48 2010 (-0500)
 *           By: bigclean
 *     Update #: 7
 * URL: 
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 8-Feb-2010    bigclean  
 *    Last-Updated: Sat Feb  6 15:06:33 2010 (-0500) #5 (bigclean)
 *    define new types to replace old ones(unit_t type to be comsummated)
 * 6-Feb-2010    bigclean  
 *    Last-Updated: Sat Feb  6 14:57:55 2010 (-0500) #3 (bigclean)
 *    1. change doxygen syntax from QT to standard JavaDoc
 *    2. offical use typedef to replace #define
 * 
 */

/* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301, USA.
 */

/* Code: */


/**
 * @file def.h 
 * @brief data type definition
 * @author Jujie Zheng 
 * @date 20010-2-8
 */
#ifndef __DEF_H_
#define __DEF_H_

// \note typedef is much better than #define to define new types
// \note Types names should follow suffix '_t' to indicate type.
// FIXME: doxygen generate somehow fails
// prefered type defintions style
typedef unsigned int uint_t;    /*! 8 bits unsigned int */
typedef unsigned char uchar_t;  /*! 8 bits unsigned char */

#endif

/* def.h ends here */
