/* ES40 emulator.
 * Copyright (C) 2007-2008 by the ES40 Emulator Project
 *
 * WWW    : http://www.es40.org
 * E-mail : camiel@es40.org
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 * 
 * Although this is not required, the author would appreciate being notified of, 
 * and receiving any modifications you may make to the source code that might serve
 * the general public.
 *
 * Parts of this file based upon the Poco C++ Libraries, which is Copyright (C) 
 * 2004-2006, Applied Informatics Software Engineering GmbH. and Contributors.
 */

/**
 * $Id$
 *
 * X-1.1        Camiel Vanderhoeven                             31-MAY-2008
 *      Initial version for ES40 emulator.
 **/

//
// ErrorHandler.h
//
// $Id$
//
// Library: Foundation
// Package: Threading
// Module:  ErrorHandler
//
// Definition of the ErrorHandler class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Foundation_ErrorHandler_INCLUDED
#define Foundation_ErrorHandler_INCLUDED


#include "Foundation.h"
#include "Exception.h"
#include "Mutex.h"

class CErrorHandler
	/// This is the base class for thread error handlers.
	///
	/// An unhandled exception that causes a thread to terminate is usually
	/// silently ignored, since the class library cannot do anything meaningful
	/// about it.
	/// 
	/// The Thread class provides the possibility to register a
	/// global ErrorHandler that is invoked whenever a thread has
	/// been terminated by an unhandled exception.
	/// The ErrorHandler must be derived from this class and can
	/// provide implementations of all three handleException() overloads.
	///
	/// The ErrorHandler is always invoked within the context of
	/// the offending thread.
{
public:
	CErrorHandler();
		/// Creates the ErrorHandler.

	virtual ~CErrorHandler();
		/// Destroys the ErrorHandler.

	virtual void exception(const CException& exc);
		/// Called when a Poco::Exception (or a subclass)
		/// caused the thread to terminate.
		///
		/// This method should not throw any exception - it would
		/// be silently ignored.
		///
		/// The default implementation just breaks into the debugger.
		
	virtual void exception(const std::exception& exc);
		/// Called when a std::exception (or a subclass)
		/// caused the thread to terminate.		
		///
		/// This method should not throw any exception - it would
		/// be silently ignored.
		///
		/// The default implementation just breaks into the debugger.

	virtual void exception();
		/// Called when an exception that is neither a
		/// Poco::Exception nor a std::exception caused
		/// the thread to terminate.
		///
		/// This method should not throw any exception - it would
		/// be silently ignored.
		///
		/// The default implementation just breaks into the debugger.
		
	static void handle(const CException& exc);
		/// Invokes the currently registered ErrorHandler.
		
	static void handle(const std::exception& exc);
		/// Invokes the currently registered ErrorHandler.
	
	static void handle();
		/// Invokes the currently registered ErrorHandler.
	
	static CErrorHandler* set(CErrorHandler* pHandler);
		/// Registers the given handler as the current error handler.
		///
		/// Returns the previously registered handler.

	static CErrorHandler* get();
		/// Returns a pointer to the currently registered
		/// ErrorHandler.

protected:	
	static CErrorHandler* defaultHandler();
		/// Returns the default ErrorHandler.	
		
private:
	static CErrorHandler* _pHandler;
	static CFastMutex     _mutex;
};


//
// inlines
//
inline CErrorHandler* CErrorHandler::get()
{
	return _pHandler;
}


#endif // Foundation_ErrorHandler_INCLUDED
