%module libcommon

%{
    #include <platform.h>
    #include <mapi.h>
    #include <mapidefs.h>
    #include <mapicode.h>
    #include <mapiutil.h>

    #include "HtmlToTextParser.h"
    #include "rtfutil.h"
    #include "favoritesutil.h"
    #include "Util.h"
	#include "ECLogger.h"
%}

%include "wchar.i"
%include <windows.i>
%include "cstring.i"
%include "cwstring.i"
%include "std_string.i"

class CHtmlToTextParser {
    public:
        bool Parse(wchar_t *in);
        std::wstring& GetText();
        
        %extend {
            wchar_t *__str__() {
                return (wchar_t*)$self->GetText().c_str();
            }

            wchar_t *GetData() {
                return (wchar_t*)$self->GetText().c_str();
            }
        }

};

/////////////////////////////////
// HRESULT
/////////////////////////////////
%include "exception.i"
%typemap(out) HRESULT (char ex[64])
{
  if(FAILED($1)) {
    snprintf(ex,sizeof(ex),"failed with HRESULT 0x%08X", $1);
	SWIG_exception(SWIG_RuntimeError, ex);
  }
}

/////////////////////////////////
// std::string&
/////////////////////////////////
%typemap(in,numinputs=0) std::string &OUTPUT	(std::string s)
{
	$1 = &s;
}
%typemap(argout,fragment="SWIG_FromCharPtr") (std::string &OUTPUT)
{
	%append_output(SWIG_FromCharPtr($1->c_str()));
	if(PyErr_Occurred())
		goto fail;
}

%typemap(in,numinputs=0) std::wstring &OUTPUT	(std::wstring s)
{
	$1 = &s;
}
%typemap(argout,fragment="SWIG_FromWCharPtr") (std::wstring &OUTPUT)
{
	%append_output(SWIG_FromWCharPtr($1->c_str()));
	if(PyErr_Occurred())
		goto fail;
}


// some common/rtfutil.h functions
HRESULT HrExtractHTMLFromRTF(std::string lpStrRTFIn, std::string &OUTPUT, ULONG ulCodepage);
HRESULT HrExtractHTMLFromTextRTF(std::string lpStrRTFIn, std::string &OUTPUT, ULONG ulCodepage);
HRESULT HrExtractHTMLFromRealRTF(std::string lpStrRTFIn, std::string &OUTPUT, ULONG ulCodepage);
HRESULT HrExtractBODYFromTextRTF(std::string lpStrRTFIn, std::wstring &OUTPUT);

// functions from common/Util.h
class Util {
public:
    static ULONG GetBestBody(IMAPIProp *lpPropObj, ULONG ulFlags);
};

