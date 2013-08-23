#include "StdAfx.h"
#include "ErrorReporter.h"



ErrorReporter::ErrorReporter(const wchar_t* Message)
    : message(Message)
{
}

ErrorReporter::ErrorReporter(const wchar_t* FileName, size_t LineNumber, const wchar_t* Function,
                             const wchar_t* Command, ErrorCodeType Type, long ErrorCode, const wchar_t* AdditionalMessage)
{
#pragma region formatting message
    wchar_t itowBuffer[12] = {};

    if ( FileName )
    {
        message += FileName;
        if ( LineNumber ) {
            _itow_s( LineNumber, itowBuffer, 10 );

            message += L'(';
            message += itowBuffer;
            message += L')';
        }
        message += L'\n';
    }
    if ( Function )
    {
        message += L"Function \t: ";
        message += Function;
        message += L'\n';
    }
    if ( Command )
    {
        message += L"Command \t: ";
        message += Command;
        message += L'\n';
    }

    switch ( Type )
    {
    case ErrorCodeType::HR:
        if ( ErrorCode )
        {
            _ltow_s( ErrorCode, itowBuffer, 16 );

            message += L"HRESULT \t: ";
            message += _com_error(ErrorCode).ErrorMessage();
            message += L" (0x";
            message += itowBuffer;
            message += L")\n";
        }
        break;
    case ErrorCodeType::Nonzero:
        if ( ErrorCode )
        {
            _ltow_s( ErrorCode, itowBuffer, 10 );

            message += L"ErrorCode \t: ";
            message += itowBuffer;
            message += L'\n';
        }
        break;
    case ErrorCodeType::False:
        message += L"Command has returned false(0)\n";
        break;
    }

    DWORD LastError = GetLastError();
    if ( LastError )
    {
        _ltow_s( LastError, itowBuffer, 10 );

        message += L"GetLastError() \t: ";
        message += _com_error(LastError).ErrorMessage();
        message += L" (";
        message += itowBuffer;
        message += L")\n";
    }

    if ( AdditionalMessage )
    {
        message += AdditionalMessage;
    }

    if ( message.back() != L'\n' )
        message += L'\n';
#pragma endregion
}

void ErrorReporter::Report(ErrorReportType Type)
{
    std::wstring text;
    text += L"\n\n";
    text += L"==============================================================================\n";
    text += message;
    text += L"------------------------------------------------------------------------------\n";

    if ( IsDebuggerPresent() )
    {
        OutputDebugString( text.c_str() );
        DebugBreak();
    }
    else
    {
        AllocConsole();
        AttachConsole( GetCurrentProcessId() );
        FILE* dummy;
        _wfreopen_s(&dummy, L"CON", L"w", stdout);
        _wsetlocale(LC_ALL, L"");
        _putws( text.c_str() );
        _wsystem(L"pause");
        FreeConsole();
    }

    if ( Type == ErrorReportType::Error )
    {
        ExitProcess(EXIT_FAILURE);
    }
}
