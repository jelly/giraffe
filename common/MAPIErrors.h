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

/**
 * MAPIErrors.h
 * Declarations of GetMAPIErrorMessage() and supporting data structures and
 * constants
 */

#include "platform.h"	// for declaration of HRESULT
#include <string>

#ifndef MAPIERRORS_H_INCLUDED
#define MAPIERRORS_H_INCLUDED

#ifndef __M4L_MAPICODE_H_
#ifndef MAPICODE_H
const HRESULT MAPI_E_CALL_FAILED					= 0x80004005;
const HRESULT MAPI_E_NOT_ENOUGH_MEMORY				= 0x8007000E;
const HRESULT MAPI_E_INVALID_PARAMETER				= 0x80070057;
const HRESULT MAPI_E_INTERFACE_NOT_SUPPORTED		= 0x80004002;
const HRESULT MAPI_E_NO_ACCESS						= 0x80070005;
const HRESULT MAPI_E_NO_SUPPORT						= 0x80040102;
const HRESULT MAPI_E_BAD_CHARWIDTH					= 0x80040103;
const HRESULT MAPI_E_STRING_TOO_LONG				= 0x80040105;
const HRESULT MAPI_E_UNKNOWN_FLAGS					= 0x80040106;
const HRESULT MAPI_E_INVALID_ENTRYID				= 0x80040107;
const HRESULT MAPI_E_INVALID_OBJECT					= 0x80040108;
const HRESULT MAPI_E_OBJECT_CHANGED					= 0x80040109;
const HRESULT MAPI_E_OBJECT_DELETED					= 0x8004010A;
const HRESULT MAPI_E_BUSY							= 0x8004010B;
const HRESULT MAPI_E_NOT_ENOUGH_DISK				= 0x8004010D;
const HRESULT MAPI_E_NOT_ENOUGH_RESOURCES			= 0x8004010E;
const HRESULT MAPI_E_NOT_FOUND						= 0x8004010F;
const HRESULT MAPI_E_VERSION						= 0x80040110;
const HRESULT MAPI_E_LOGON_FAILED					= 0x80040111;
const HRESULT MAPI_E_SESSION_LIMIT					= 0x80040112;
const HRESULT MAPI_E_USER_CANCEL					= 0x80040113;
const HRESULT MAPI_E_UNABLE_TO_ABORT				= 0x80040114;
const HRESULT MAPI_E_NETWORK_ERROR					= 0x80040115;
const HRESULT MAPI_E_DISK_ERROR						= 0x80040116;
const HRESULT MAPI_E_TOO_COMPLEX					= 0x80040117;
const HRESULT MAPI_E_BAD_COLUMN						= 0x80040118;
const HRESULT MAPI_E_EXTENDED_ERROR					= 0x80040119;
const HRESULT MAPI_E_COMPUTED						= 0x8004011A;
const HRESULT MAPI_E_CORRUPT_DATA					= 0x8004011B;
const HRESULT MAPI_E_UNCONFIGURED					= 0x8004011C;
const HRESULT MAPI_E_FAILONEPROVIDER				= 0x8004011D;
const HRESULT MAPI_E_UNKNOWN_CPID					= 0x8004011E;
const HRESULT MAPI_E_UNKNOWN_LCID					= 0x8004011F;
const HRESULT MAPI_E_PASSWORD_CHANGE_REQUIRED		= 0x80040120;
const HRESULT MAPI_E_PASSWORD_EXPIRED				= 0x80040121;
const HRESULT MAPI_E_INVALID_WORKSTATION_ACCOUNT	= 0x80040122;
const HRESULT MAPI_E_INVALID_ACCESS_TIME			= 0x80040123;
const HRESULT MAPI_E_ACCOUNT_DISABLED				= 0x80040124;
const HRESULT MAPI_E_END_OF_SESSION					= 0x80040200;
const HRESULT MAPI_E_UNKNOWN_ENTRYID				= 0x80040201;
const HRESULT MAPI_E_MISSING_REQUIRED_COLUMN		= 0x80040202;
const HRESULT MAPI_W_NO_SERVICE						= 0x00040203;
const HRESULT MAPI_E_BAD_VALUE						= 0x80040301;
const HRESULT MAPI_E_INVALID_TYPE					= 0x80040302;
const HRESULT MAPI_E_TYPE_NO_SUPPORT				= 0x80040303;
const HRESULT MAPI_E_UNEXPECTED_TYPE				= 0x80040304;
const HRESULT MAPI_E_TOO_BIG						= 0x80040305;
const HRESULT MAPI_E_DECLINE_COPY					= 0x80040306;
const HRESULT MAPI_E_UNEXPECTED_ID					= 0x80040307;
const HRESULT MAPI_W_ERRORS_RETURNED				= 0x00040380;
const HRESULT MAPI_E_UNABLE_TO_COMPLETE				= 0x80040400;
const HRESULT MAPI_E_TIMEOUT						= 0x80040401;
const HRESULT MAPI_E_TABLE_EMPTY					= 0x80040402;
const HRESULT MAPI_E_TABLE_TOO_BIG					= 0x80040403;
const HRESULT MAPI_E_INVALID_BOOKMARK				= 0x80040405;
const HRESULT MAPI_W_POSITION_CHANGED				= 0x00040481;
const HRESULT MAPI_W_APPROX_COUNT					= 0x00040482;
const HRESULT MAPI_E_WAIT							= 0x80040500;
const HRESULT MAPI_E_CANCEL							= 0x80040501;
const HRESULT MAPI_E_NOT_ME							= 0x80040502;
const HRESULT MAPI_W_CANCEL_MESSAGE					= 0x00040580;
const HRESULT MAPI_E_CORRUPT_STORE					= 0x80040600;
const HRESULT MAPI_E_NOT_IN_QUEUE					= 0x80040601;
const HRESULT MAPI_E_NO_SUPPRESS					= 0x80040602;
const HRESULT MAPI_E_COLLISION						= 0x80040604;
const HRESULT MAPI_E_NOT_INITIALIZED				= 0x80040605;
const HRESULT MAPI_E_NON_STANDARD					= 0x80040606;
const HRESULT MAPI_E_NO_RECIPIENTS					= 0x80040607;
const HRESULT MAPI_E_SUBMITTED						= 0x80040608;
const HRESULT MAPI_E_HAS_FOLDERS					= 0x80040609;
const HRESULT MAPI_E_HAS_MESSAGES					= 0x8004060A;
const HRESULT MAPI_E_FOLDER_CYCLE					= 0x8004060B;
const HRESULT MAPI_W_PARTIAL_COMPLETION				= 0x00040680;
const HRESULT MAPI_E_AMBIGUOUS_RECI					= 0x80040700;

#ifndef ECMAPIEXT_H // mapiext.h
const HRESULT MAPI_E_STORE_FULL						= 0x8004060c;
#endif // !defined ECMAPIEXT_H

#endif // !defined MAPICODE_H
#endif // !defined __M4L_MAPICODE_H_


const char* GetMAPIErrorMessage(HRESULT errorCode);
std::string getMapiCodeString(HRESULT hr, const char* object = "object");

#endif // !defined MAPIERRORS_H_INCLUDED

