/*
 * Copyright 2005 - 2009  Zarafa B.V.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License, version 3, 
 * as published by the Free Software Foundation with the following additional 
 * term according to sec. 7:
 *  
 * According to sec. 7 of the GNU Affero General Public License, version
 * 3, the terms of the AGPL are supplemented with the following terms:
 * 
 * "Zarafa" is a registered trademark of Zarafa B.V. The licensing of
 * the Program under the AGPL does not imply a trademark license.
 * Therefore any rights, title and interest in our trademarks remain
 * entirely with us.
 * 
 * However, if you propagate an unmodified version of the Program you are
 * allowed to use the term "Zarafa" to indicate that you distribute the
 * Program. Furthermore you may use our trademarks where it is necessary
 * to indicate the intended purpose of a product or service provided you
 * use it in accordance with honest practices in industrial or commercial
 * matters.  If you want to propagate modified versions of the Program
 * under the name "Zarafa" or "Zarafa Server", you may only do so if you
 * have a written permission by Zarafa B.V. (to acquire a permission
 * please contact Zarafa at trademark@zarafa.com).
 * 
 * The interactive user interface of the software displays an attribution
 * notice containing the term "Zarafa" and/or the logo of Zarafa.
 * Interactive user interfaces of unmodified and modified versions must
 * display Appropriate Legal Notices according to sec. 5 of the GNU
 * Affero General Public License, version 3, when you propagate
 * unmodified or modified versions of the Program. In accordance with
 * sec. 7 b) of the GNU Affero General Public License, version 3, these
 * Appropriate Legal Notices must retain the logo of Zarafa or display
 * the words "Initial Development by Zarafa" if the display of the logo
 * is not reasonably feasible for technical reasons. The use of the logo
 * of Zarafa in Legal Notices is allowed for unmodified and modified
 * versions of the software.
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

// -*- Mode: C++ -*-
#ifndef __PHP_EXT_MAIN_H
#define __PHP_EXT_MAIN_H

/***************************************************************
* Thread safe global variable
***************************************************************/
// ZTS is Zend Thread Safety
// but is isn't defined, as it's seems to be experimental in php4
// and maybe better in php5, but I haven't got the slightest clue yet.
#ifdef ZTS
#include "TSRM.h"
#endif


/***************************************************************
* Variables
***************************************************************/
#include "globals.h"

/**
* Numeric identifier for the resource type
*
*/
static int le_mapi_session; 
static int le_mapi_table;
static int le_mapi_rowset;
static int le_mapi_msgstore;
static int le_mapi_addrbook;
static int le_mapi_mailuser;
static int le_mapi_distlist;
static int le_mapi_abcont;
static int le_mapi_folder;
static int le_mapi_message;
static int le_mapi_attachment;
static int le_mapi_property;
static int le_mapi_modifytable;
static int le_istream;
static int le_freebusy_support;
static int le_freebusy_data;
static int le_freebusy_update;
static int le_freebusy_enumblock;
static int le_mapi_exportchanges;
static int le_mapi_importhierarchychanges;
static int le_mapi_importcontentschanges;

/**
* When adding or changing a entry here, don't forget to 
* add or change the same entry in class.mapi.php 
*/
static char* name_mapi_session = "MAPI Session";
static char* name_mapi_table = "MAPI Table";
static char* name_mapi_rowset = "MAPI Rowset";
static char* name_mapi_msgstore = "MAPI Message Store";
static char* name_mapi_addrbook = "MAPI Addressbook";
static char* name_mapi_mailuser = "MAPI Mail User";
static char* name_mapi_distlist = "MAPI Distribution List";
static char* name_mapi_abcont = "MAPI Addressbook Container";
static char* name_mapi_folder = "MAPI Folder";
static char* name_mapi_message = "MAPI Message";
static char* name_mapi_attachment = "MAPI Attachment";
static char* name_mapi_property = "MAPI Property";
static char* name_mapi_modifytable = "MAPI Exchange Modify Table";
static char* name_istream = "IStream Interface";
static char* name_fb_support = "Freebusy Support Interface";
static char* name_fb_data = "Freebusy Data Interface";
static char* name_fb_update = "Freebusy Update Interface";
static char* name_fb_enumblock = "Freebusy Enumblock Interface";
static char* name_mapi_exportchanges = "ICS Export Changes";
static char* name_mapi_importhierarchychanges = "ICS Import Hierarchy Changes";
static char* name_mapi_importcontentschanges = "ICS Import Contents Changes";

/**
* common used variables
*/

/***************************************************************
* Function definitions
**************************************************************/
/* All the functions that will be exported (available) must be declared */
PHP_MINIT_FUNCTION(mapi);
PHP_MINFO_FUNCTION(mapi);
PHP_MSHUTDOWN_FUNCTION(mapi);
PHP_RINIT_FUNCTION(mapi);
PHP_RSHUTDOWN_FUNCTION(mapi);

ZEND_FUNCTION(mapi_last_hresult);
ZEND_FUNCTION(mapi_prop_type);
ZEND_FUNCTION(mapi_prop_id);
ZEND_FUNCTION(mapi_is_error);
ZEND_FUNCTION(mapi_make_scode);
ZEND_FUNCTION(mapi_prop_tag);

ZEND_FUNCTION(mapi_createoneoff);
ZEND_FUNCTION(mapi_parseoneoff);

ZEND_FUNCTION(mapi_logon);
ZEND_FUNCTION(mapi_logon_zarafa);
ZEND_FUNCTION(mapi_logon_pst);
ZEND_FUNCTION(mapi_getmsgstorestable);
ZEND_FUNCTION(mapi_openmsgstore);
ZEND_FUNCTION(mapi_openmsgstore_exchange);
ZEND_FUNCTION(mapi_openmsgstore_zarafa);
ZEND_FUNCTION(mapi_openmsgstore_zarafa_other);

ZEND_FUNCTION(mapi_openentry);
ZEND_FUNCTION(mapi_openaddressbook);
ZEND_FUNCTION(mapi_ab_openentry);
ZEND_FUNCTION(mapi_ab_resolvename);
ZEND_FUNCTION(mapi_ab_getdefaultdir);

ZEND_FUNCTION(mapi_msgstore_createentryid);
ZEND_FUNCTION(mapi_msgstore_openentry);
ZEND_FUNCTION(mapi_msgstore_getreceivefolder);
ZEND_FUNCTION(mapi_msgstore_entryidfromsourcekey);
ZEND_FUNCTION(mapi_msgstore_openmultistoretable);

ZEND_FUNCTION(mapi_table_queryallrows);
ZEND_FUNCTION(mapi_table_queryrows);
ZEND_FUNCTION(mapi_table_getrowcount);
ZEND_FUNCTION(mapi_table_sort);
ZEND_FUNCTION(mapi_table_restrict);

ZEND_FUNCTION(mapi_folder_gethierarchytable);
ZEND_FUNCTION(mapi_folder_getcontentstable);
ZEND_FUNCTION(mapi_folder_createmessage);
ZEND_FUNCTION(mapi_folder_createfolder);
ZEND_FUNCTION(mapi_folder_deletefolder);
ZEND_FUNCTION(mapi_folder_deletemessages);
ZEND_FUNCTION(mapi_folder_copymessages);
ZEND_FUNCTION(mapi_folder_copyfolder);
ZEND_FUNCTION(mapi_folder_emptyfolder);
ZEND_FUNCTION(mapi_folder_setreadflags);
ZEND_FUNCTION(mapi_folder_getsearchcriteria);
ZEND_FUNCTION(mapi_folder_setsearchcriteria);

ZEND_FUNCTION(mapi_message_getattachmenttable);
ZEND_FUNCTION(mapi_message_getrecipienttable);
ZEND_FUNCTION(mapi_message_openattach);
ZEND_FUNCTION(mapi_message_createattach);
ZEND_FUNCTION(mapi_message_deleteattach);
ZEND_FUNCTION(mapi_message_modifyrecipients);
ZEND_FUNCTION(mapi_message_submitmessage);
ZEND_FUNCTION(mapi_message_setreadflag);

ZEND_FUNCTION(mapi_attach_openbin);
ZEND_FUNCTION(mapi_attach_openobj);

ZEND_FUNCTION(mapi_getnamesfromids);
ZEND_FUNCTION(mapi_getidsfromnames);

ZEND_FUNCTION(mapi_decompressrtf);

ZEND_FUNCTION(mapi_folder_openmodifytable);
ZEND_FUNCTION(mapi_rules_gettable);
ZEND_FUNCTION(mapi_rules_modifytable);

ZEND_FUNCTION(mapi_stream_write);
ZEND_FUNCTION(mapi_stream_read);
ZEND_FUNCTION(mapi_openpropertytostream);
ZEND_FUNCTION(mapi_stream_stat);
ZEND_FUNCTION(mapi_stream_seek);
ZEND_FUNCTION(mapi_stream_commit);
ZEND_FUNCTION(mapi_stream_setsize);
ZEND_FUNCTION(mapi_stream_create);

// generic functions for the function for every object derived from IMAPIProp (message, attachment, etc...)
ZEND_FUNCTION(mapi_getprops);
ZEND_FUNCTION(mapi_setprops);
ZEND_FUNCTION(mapi_copyto);
//ZEND_FUNCTION(mapi_copyprops);
ZEND_FUNCTION(mapi_openproperty);
ZEND_FUNCTION(mapi_deleteprops);
ZEND_FUNCTION(mapi_savechanges);

ZEND_FUNCTION(mapi_zarafa_createstore);

ZEND_FUNCTION(mapi_zarafa_createuser);
ZEND_FUNCTION(mapi_zarafa_deleteuser);
ZEND_FUNCTION(mapi_zarafa_setuser);
ZEND_FUNCTION(mapi_zarafa_getuser_by_id);
ZEND_FUNCTION(mapi_zarafa_getuser_by_name);
ZEND_FUNCTION(mapi_zarafa_getuserlist);

ZEND_FUNCTION(mapi_zarafa_getquota);
ZEND_FUNCTION(mapi_zarafa_setquota);

ZEND_FUNCTION(mapi_zarafa_creategroup);
ZEND_FUNCTION(mapi_zarafa_deletegroup);
ZEND_FUNCTION(mapi_zarafa_setgroup);

ZEND_FUNCTION(mapi_zarafa_addgroupmember);
ZEND_FUNCTION(mapi_zarafa_deletegroupmember);

ZEND_FUNCTION(mapi_zarafa_getgroup_by_id);
ZEND_FUNCTION(mapi_zarafa_getgroup_by_name);
ZEND_FUNCTION(mapi_zarafa_getgrouplist);
ZEND_FUNCTION(mapi_zarafa_getgrouplistofuser);
ZEND_FUNCTION(mapi_zarafa_getuserlistofgroup);

ZEND_FUNCTION(mapi_zarafa_createcompany);
ZEND_FUNCTION(mapi_zarafa_deletecompany);
ZEND_FUNCTION(mapi_zarafa_getcompany_by_id);
ZEND_FUNCTION(mapi_zarafa_getcompany_by_name);
ZEND_FUNCTION(mapi_zarafa_getcompanylist);

ZEND_FUNCTION(mapi_zarafa_add_company_remote_viewlist);
ZEND_FUNCTION(mapi_zarafa_del_company_remote_viewlist);
ZEND_FUNCTION(mapi_zarafa_get_remote_viewlist);
ZEND_FUNCTION(mapi_zarafa_add_user_remote_adminlist);
ZEND_FUNCTION(mapi_zarafa_del_user_remote_adminlist);
ZEND_FUNCTION(mapi_zarafa_get_remote_adminlist);
ZEND_FUNCTION(mapi_zarafa_add_quota_recipient);
ZEND_FUNCTION(mapi_zarafa_del_quota_recipient);
ZEND_FUNCTION(mapi_zarafa_get_quota_recipientlist);

ZEND_FUNCTION(mapi_zarafa_check_license);
ZEND_FUNCTION(mapi_zarafa_getcapabilities);

// permissions functions
ZEND_FUNCTION(mapi_zarafa_getpermissionrules);
ZEND_FUNCTION(mapi_zarafa_setpermissionrules);

//Freebusy support functions
ZEND_FUNCTION(mapi_freebusysupport_open);
ZEND_FUNCTION(mapi_freebusysupport_close);
ZEND_FUNCTION(mapi_freebusysupport_loaddata);
ZEND_FUNCTION(mapi_freebusysupport_loadupdate);

//Freebusy data functions
ZEND_FUNCTION(mapi_freebusydata_enumblocks);
ZEND_FUNCTION(mapi_freebusydata_getpublishrange);
ZEND_FUNCTION(mapi_freebusydata_setrange);

// Freebusy enumblock
ZEND_FUNCTION(mapi_freebusyenumblock_reset);
ZEND_FUNCTION(mapi_freebusyenumblock_next);
ZEND_FUNCTION(mapi_freebusyenumblock_skip);
ZEND_FUNCTION(mapi_freebusyenumblock_restrict);

// freebusy update
ZEND_FUNCTION(mapi_freebusyupdate_publish);
ZEND_FUNCTION(mapi_freebusyupdate_reset);
ZEND_FUNCTION(mapi_freebusyupdate_savechanges);

// Favorite functions
ZEND_FUNCTION(mapi_favorite_add);

// ICS functions
ZEND_FUNCTION(mapi_exportchanges_config);
ZEND_FUNCTION(mapi_exportchanges_synchronize);
ZEND_FUNCTION(mapi_exportchanges_updatestate);
ZEND_FUNCTION(mapi_exportchanges_getchangecount);

ZEND_FUNCTION(mapi_importcontentschanges_config);
ZEND_FUNCTION(mapi_importcontentschanges_updatestate);
ZEND_FUNCTION(mapi_importcontentschanges_importmessagechange);
ZEND_FUNCTION(mapi_importcontentschanges_importmessagedeletion);
ZEND_FUNCTION(mapi_importcontentschanges_importperuserreadstatechange);
ZEND_FUNCTION(mapi_importcontentschanges_importmessagemove);

ZEND_FUNCTION(mapi_importhierarchychanges_config);
ZEND_FUNCTION(mapi_importhierarchychanges_updatestate);
ZEND_FUNCTION(mapi_importhierarchychanges_importfolderchange);
ZEND_FUNCTION(mapi_importhierarchychanges_importfolderdeletion);

ZEND_FUNCTION(mapi_wrap_importcontentschanges);
ZEND_FUNCTION(mapi_wrap_importhierarchychanges);

ZEND_FUNCTION(mapi_inetmapi_imtoinet);

#if SUPPORT_EXCEPTIONS
ZEND_FUNCTION(mapi_enable_exceptions);
#endif

// Destructor functions needed for the PHP resources. 
static void _php_free_mapi_session(zend_rsrc_list_entry *rsrc TSRMLS_DC);
static void _php_free_mapi_rowset(zend_rsrc_list_entry *rsrc TSRMLS_DC);
static void _php_free_mapi_object(zend_rsrc_list_entry *rsrc TSRMLS_DC);
static void _php_free_istream(zend_rsrc_list_entry *rsrc TSRMLS_DC);
static void _php_free_fb_object(zend_rsrc_list_entry *rsrc TSRMLS_DC);

#endif
