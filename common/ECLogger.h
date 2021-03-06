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

// -*- Mode: c++ -*-
#ifndef ECLOGGER_H
#define ECLOGGER_H

#include "zcdefs.h"
#include <list>
#include <pthread.h>
#include <csignal>
#include <cstdarg>
#include <cstdio>
#include <string>

#include "ECConfig.h"

#ifndef __LIKE_PRINTF
#define __LIKE_PRINTF(_fmt, _va)
#endif

static const unsigned int EC_LOGLEVEL_NONE       = 0;
static const unsigned int EC_LOGLEVEL_FATAL	 = 1;
static const unsigned int EC_LOGLEVEL_ERROR	 = 2;
static const unsigned int EC_LOGLEVEL_WARNING    = 3;
static const unsigned int EC_LOGLEVEL_NOTICE	 = 4;
static const unsigned int EC_LOGLEVEL_INFO	 = 5;
static const unsigned int EC_LOGLEVEL_DEBUG	 = 6;
static const unsigned int EC_LOGLEVEL_ALWAYS     = 0xf;

static const unsigned int EC_LOGLEVEL_MASK	 = 0xF;

// Zarafa-server extended log options
static const unsigned int EC_LOGLEVEL_SQL	   = 0x00010000;
static const unsigned int EC_LOGLEVEL_PLUGIN	   = 0x00020000;
static const unsigned int EC_LOGLEVEL_CACHE	   = 0x00040000;
static const unsigned int EC_LOGLEVEL_USERCACHE    = 0x00080000;
static const unsigned int EC_LOGLEVEL_SOAP         = 0x00100000;
static const unsigned int EC_LOGLEVEL_ICS          = 0x00200000;
static const unsigned int EC_LOGLEVEL_SEARCH       = 0x00400000;

static const unsigned int EC_LOGLEVEL_EXTENDED_MASK = 0xFFFF0000;

#define _LOG_BUFSIZE		10240
#define _LOG_TSSIZE			64

#define LOG_DEBUG(_plog,_msg,...) if ((_plog)->Log(EC_LOGLEVEL_DEBUG)) (_plog)->Log(EC_LOGLEVEL_DEBUG, _msg, ##__VA_ARGS__)
#define LOG_AUDIT(_plog,_msg,...) if ((_plog)) (_plog)->Log(EC_LOGLEVEL_FATAL, _msg, ##__VA_ARGS__)

#ifdef UNICODE
#define TSTRING_PRINTF "%ls"
#else
#define TSTRING_PRINTF "%s"
#endif

#define SIZE_T_PRINTF    "%lu"
#define SSIZE_T_PRINTF   "%l"
#define PTRDIFF_T_PRINTF "%l"


/**
 * Prefixes in log message in different process models.
 *
 * LP_NONE: No prefix in log message (default)
 * LP_TID:  Add thread id as prefix
 * LP_PID:  Add linux process id as prefix
 */
enum logprefix { LP_NONE, LP_TID, LP_PID };

/**
 * ECLogger object logs messages to a specific
 * destination. Destinations are created in derived classes.
 */
class ECLogger {
	private:
		unsigned m_ulRef;

	protected:
		/**
		 * Returns string with timestamp in current locale.
		 */
		std::string MakeTimestamp();

		unsigned int max_loglevel;
		locale_t timelocale;
		locale_t datalocale;
		logprefix prefix;

	protected:
		/**
		 * Constructor of ECLogger. Implementations should open the log they're writing to.
		 *
		 * @param[in]	max_ll	Max loglevel allowed to enter in the log. Messages with higher loglevel will be skipped.
		 */
		ECLogger(int max_ll);
		/**
		 * Destructor of ECLogger. Implementations should close the log they're writing to.
		 */
		virtual ~ECLogger();

	public:
		/**
		 * Query if a message would be logged under this loglevel
		 *
		 * @param[in]	loglevel	Loglevel you want to know if it enters the log.
		 * @return		bool
		 * @retval	true	Logging with 'loglevel' will enter log
		 * @retval	false	Logging with 'loglevel' will be dropped
		 */
		virtual bool Log(unsigned int loglevel);

		/**
		 * Set new loglevel for log object
		 *
		 * @param[in]	max_ll	The new maximum loglevel
		 */
		void SetLoglevel(unsigned int max_ll);
		/**
		 * Set new prefix for log
		 *
		 * @param[in]	lp	New logprefix LP_TID or LP_PID. Disable prefix with LP_NONE.
		 */
		void SetLogprefix(logprefix lp);
		/**
		 * Adds reference to this object
		 */
		unsigned AddRef();
		/**
		 * Removes a reference from this object, and deletes it if all
		 * references are removed.
		 */
		unsigned Release();
		/**
		 * Like the CRT snprintf, but uses the datalocale used by the current
		 * ECLogger instance.
		 */
		int snprintf(char *str, size_t size, const char *format, ...) __LIKE_PRINTF(4, 5);
		/**
		 * Used for log rotation. Implementations should prepare to log in a new log.
		 *
		 * @param[in]	lp	New logprefix LP_TID or LP_PID. Disable prefix with LP_NONE.
		 */
		virtual void Reset() = 0;
		/**
		 * Used to get a direct file descriptor of the log file. Returns
		 * -1 if not available.
		 *
		 * @return	int		The file descriptor of the logfile being written to.
		 */
		virtual int GetFileDescriptor();
		/**
		 * Log a message on a specified loglevel using std::string
		 *
		 * @param	loglevel	Loglevel to log message under
		 * @param	message		std::string logmessage. Expected charset is current locale.
		 */
		virtual void Log(unsigned int loglevel, const std::string &message) = 0;
		/**
		 * Log a message on a specified loglevel using char* format
		 *
		 * @param	loglevel	Loglevel to log message under
		 * @param	format		formatted string for the parameter list
		 */
		virtual void Log(unsigned int loglevel, const char *format, ...) __LIKE_PRINTF(3, 4) = 0;
		/**
		 * Log a message on a specified loglevel using char* format
		 *
		 * @param	loglevel	Loglevel to log message under
		 * @param	format		formatted string for the parameter list
		 * @param	va			va_list converted from ... parameters
		 */
		virtual void LogVA(unsigned int loglevel, const char *format, va_list& va) = 0;
};


/**
 * Dummy null logger, drops every log message.
 */
class ECLogger_Null _final : public ECLogger {
	public:
		ECLogger_Null();
		~ECLogger_Null();

		virtual void Reset(void) _override;
		virtual void Log(unsigned int loglevel, const std::string &message) _override;
		virtual void Log(unsigned int loglevel, const char *format, ...) _override __LIKE_PRINTF(3, 4);
		virtual void LogVA(unsigned int loglevel, const char *format, va_list &va) _override;
};

/**
 * File logger. Use "-" for stderr logging. Output is in system locale set in LC_CTYPE.
 */
class ECLogger_File _final : public ECLogger {
	private:
		typedef void* handle_type;
		typedef handle_type(*open_func)(const char*, const char*);
		typedef int(*close_func)(handle_type);
		typedef int(*printf_func)(handle_type, const char*, ...);
		typedef int(*fileno_func)(handle_type);
		typedef int(*flush_func)(handle_type);

		handle_type log;
		pthread_rwlock_t handle_lock;

		char *logname;
		bool timestamp;

		char *buffer;
		size_t buffer_size;

		open_func fnOpen;
		close_func fnClose;
		printf_func fnPrintf;
		fileno_func fnFileno;
		const char *szMode;

		pthread_rwlock_t dupfilter_lock;
		int prevcount;
		std::string prevmsg;
		unsigned int prevloglevel;
		bool DupFilter(const unsigned int loglevel, const std::string &message);
		std::string DoPrefix();

	public:
		ECLogger_File(const unsigned int max_ll, const bool add_timestamp, const char *const filename, const bool compress, const size_t buffer_size);
		~ECLogger_File();

		std::string EmitLevel(const unsigned int loglevel);

		virtual void Reset(void) _override;
		virtual void Log(unsigned int loglevel, const std::string &message) _override;
		virtual void Log(unsigned int loglevel, const char *format, ...) _override __LIKE_PRINTF(3, 4);
		virtual void LogVA(unsigned int loglevel, const char *format, va_list &va) _override;

		int GetFileDescriptor(void) _override;
		bool IsStdErr();
};

/**
 * Linux syslog logger. Output is whatever syslog does, probably LC_CTYPE.
 */
class ECLogger_Syslog _final : public ECLogger {
	private:
		char *m_ident;
		int levelmap[16];	/* converts to syslog levels */

	public:
		ECLogger_Syslog(unsigned int max_ll, const char *ident, int facility);
		~ECLogger_Syslog();

		virtual void Reset(void) _override;
		virtual void Log(unsigned int loglevel, const std::string &message) _override;
		virtual void Log(unsigned int loglevel, const char *format, ...) _override __LIKE_PRINTF(3, 4);
		virtual void LogVA(unsigned int loglevel, const char *format, va_list &va) _override;
};


/**
 * Pipe Logger, only used by forked model processes. Redirects every
 * log message to an ECLogger_File object. This ECLogger_Pipe object
 * can be created by StartLoggerProcess function.
 */
class ECLogger_Pipe _final : public ECLogger {
	private:
		int m_fd;
		pid_t m_childpid;

	public:
		ECLogger_Pipe(int fd, pid_t childpid, int loglevel);
		~ECLogger_Pipe();

		virtual void Reset(void) _override;
		virtual void Log(unsigned int loglevel, const std::string &message) _override;
		virtual void Log(unsigned int loglevel, const char *format, ...) _override __LIKE_PRINTF(3, 4);
		virtual void LogVA(unsigned int loglevel, const char *format, va_list &va) _override;

		int GetFileDescriptor(void) _override;
		void Disown();
};

ECLogger* StartLoggerProcess(ECConfig *lpConfig, ECLogger *lpFileLogger);

/**
 * This class can be used if log messages need to go to
 * multiple destinations. It basically distributes
 * the messages to one or more attached ECLogger objects.
 *
 * Each attached logger can have its own loglevel.
 */
class ECLogger_Tee _final : public ECLogger {
	private:
		typedef std::list<ECLogger*> LoggerList;
		LoggerList m_loggers;

	public:
		ECLogger_Tee();
		~ECLogger_Tee();

		virtual void Reset(void) _override;
		virtual bool Log(unsigned int loglevel) _override;
		virtual void Log(unsigned int loglevel, const std::string &message) _override;
		virtual void Log(unsigned int loglevel, const char *format, ...) _override __LIKE_PRINTF(3, 4);
		virtual void LogVA(unsigned int loglevel, const char *format, va_list &va) _override;

		void AddLogger(ECLogger *lpLogger);
};

ECLogger* CreateLogger(ECConfig *config, const char *argv0, const char *lpszServiceName, bool bAudit = false);
int DeleteLogger(ECLogger *lpLogger);
void LogConfigErrors(ECConfig *lpConfig, ECLogger *lpLogger);

#endif

void generic_sigsegv_handler(ECLogger *lpLogger, const char *const app_name, const char *const version_string, const int signr);
