/*
 * Copyright 2005 - 2015  Zarafa B.V. and its licensors
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License, version 3,
 * as published by the Free Software Foundation with the following
 * additional terms according to sec. 7:
 * 
 * "Zarafa" is a registered trademark of Zarafa B.V.
 * The licensing of the Program under the AGPL does not imply a trademark 
 * license. Therefore any rights, title and interest in our trademarks 
 * remain entirely with us.
 * 
 * Our trademark policy (see TRADEMARKS.txt) allows you to use our trademarks
 * in connection with Propagation and certain other acts regarding the Program.
 * In any case, if you propagate an unmodified version of the Program you are
 * allowed to use the term "Zarafa" to indicate that you distribute the Program.
 * Furthermore you may use our trademarks where it is necessary to indicate the
 * intended purpose of a product or service provided you use it in accordance
 * with honest business practices. For questions please contact Zarafa at
 * trademark@zarafa.com.
 *
 * The interactive user interface of the software displays an attribution 
 * notice containing the term "Zarafa" and/or the logo of Zarafa. 
 * Interactive user interfaces of unmodified and modified versions must 
 * display Appropriate Legal Notices according to sec. 5 of the GNU Affero 
 * General Public License, version 3, when you propagate unmodified or 
 * modified versions of the Program. In accordance with sec. 7 b) of the GNU 
 * Affero General Public License, version 3, these Appropriate Legal Notices 
 * must retain the logo of Zarafa or display the words "Initial Development 
 * by Zarafa" if the display of the logo is not reasonably feasible for
 * technical reasons.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *  
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef mapi_array_ptr_INCLUDED
#define mapi_array_ptr_INCLUDED

#include "zcdefs.h"
#include <utility>

template<typename _T>
class mapi_array_proxy _final {
public:
	typedef _T		value_type;
	typedef _T**	pointerpointer;

	mapi_array_proxy(pointerpointer lpp) : m_lpp(lpp) {}

	operator pointerpointer() { return m_lpp; }
	operator LPVOID*() { return (LPVOID*)m_lpp; }

private:
	pointerpointer	m_lpp;
};


template <typename _T>
class mapi_array_ptr _final {
public:
	typedef _T						value_type;
	typedef _T*						pointer;
	typedef _T&						reference;
	typedef const _T*				const_pointer;
	typedef const _T&				const_reference;
	typedef mapi_array_proxy<_T>	proxy;

	enum { element_size = sizeof(_T) };

	// Constructors
	mapi_array_ptr() : m_lpObject(NULL) {}
	
	mapi_array_ptr(pointer lpObject) : m_lpObject(lpObject) {}


	// Destructor
	~mapi_array_ptr() {
		if (m_lpObject) {
			MAPIFreeBuffer(m_lpObject);
			m_lpObject = NULL;
		}
	}


	// Assignment
	mapi_array_ptr& operator=(pointer lpObject) {
		if (m_lpObject != lpObject) {
			mapi_array_ptr tmp(lpObject);
			swap(tmp);
		}
		return *this;
	}


	// Dereference
	reference operator*() { return *m_lpObject; }
	const_reference operator*() const { return *m_lpObject; }

	
	// Utility
	void swap(mapi_array_ptr &other) {
		std::swap(m_lpObject, other.m_lpObject);
	}

	operator void*() { return m_lpObject; }
	operator const void*() const { return m_lpObject; }

	proxy operator&() {
		if (m_lpObject) {
			MAPIFreeBuffer(m_lpObject);
			m_lpObject = NULL;
		}

		return proxy(&m_lpObject);
	}

	pointer release() {
		pointer lpTmp = m_lpObject;
		m_lpObject = NULL;
		return lpTmp;
	}

	reference operator[](unsigned i) { return m_lpObject[i]; }
	const_reference operator[](unsigned i) const { return m_lpObject[i]; }

	pointer get() { return m_lpObject; }
	const_pointer get() const { return m_lpObject; }

	void** lppVoid() {
		if (m_lpObject) {
			MAPIFreeBuffer(m_lpObject);
			m_lpObject = NULL;
		}

		return (void**)&m_lpObject;
	}

	bool operator!() const {
		return m_lpObject == NULL;
	}

	unsigned elem_size() const {
		return element_size;
	}
	
private:	// inhibit copying untill refcounting is implemented
	mapi_array_ptr(const mapi_array_ptr &other);
	mapi_array_ptr& operator=(const mapi_array_ptr &other);

private:
	pointer	m_lpObject;
};

#endif // ndef mapi_array_ptr_INCLUDED
