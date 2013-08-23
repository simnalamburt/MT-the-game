// TODO : 함수 형태로 바꾸기

#pragma once
#include <string>

enum class ErrorCodeType { HR, Nonzero, False, Custom };
enum class ErrorReportType { Error, Warning };
class ErrorReporter
{
private:
    std::wstring message;

public:
    explicit ErrorReporter(_In_ const wchar_t*);

    ErrorReporter(_In_opt_ const wchar_t* FileName, _In_opt_ size_t LineNumber, _In_opt_ const wchar_t* Function,
        _In_opt_ const wchar_t* Command, _In_ ErrorCodeType Type, _In_opt_ long ErrorCode, _In_opt_ const wchar_t* AdditionalMessage);

    void Report(ErrorReportType);

private:
    ErrorReporter(const ErrorReporter&);
    ErrorReporter& operator=(const ErrorReporter&);
};

#pragma region ErrorReporter macro definitions
// macro body
#define _ERROR_REPORTER(x, msg, error_code_type, report_type) \
do \
{ \
    long __error_code = (long)(x); \
    if ( (error_code_type == ErrorCodeType::HR && FAILED(__error_code)) || \
        (error_code_type == ErrorCodeType::Nonzero && __error_code) || \
        (error_code_type == ErrorCodeType::False && !__error_code) || \
        (error_code_type == ErrorCodeType::Custom) ) \
    { \
        ErrorReporter( __FILEW__, __LINE__, __FUNCTIONW__, L#x, \
            error_code_type, __error_code, msg ).Report(report_type); \
    } \
} while ( false )

#define HR_ERROR_MSG(x, msg) 				_ERROR_REPORTER(x, msg, ErrorCodeType::HR, 		ErrorReportType::Error)
#define HR_WARNING_MSG(x, msg) 			_ERROR_REPORTER(x, msg, ErrorCodeType::HR, 		ErrorReportType::Warning)
#define NONZERO_ERROR_MSG(x, msg) 		_ERROR_REPORTER(x, msg, ErrorCodeType::Nonzero, ErrorReportType::Error)
#define NONZERO_WARNING_MSG(x, msg) 	_ERROR_REPORTER(x, msg, ErrorCodeType::Nonzero, ErrorReportType::Warning)
#define FALSE_ERROR_MSG(x, msg) 				_ERROR_REPORTER(x, msg, ErrorCodeType::False, 		ErrorReportType::Error)
#define FALSE_WARNING_MSG(x, msg) 			_ERROR_REPORTER(x, msg, ErrorCodeType::False, 		ErrorReportType::Warning)

#define ERROR_MSG(msg)							_ERROR_REPORTER(0, msg, ErrorCodeType::Custom,	ErrorReportType::Error)
#define WARNING_MSG(msg)						_ERROR_REPORTER(0, msg, ErrorCodeType::Custom,	ErrorReportType::Warning)

#define HR_ERROR(x) 								HR_ERROR_MSG(x, nullptr)
#define HR_WARNING(x) 							HR_WARNING_MSG(x, nullptr)
#define NONZERO_ERROR(x) 						NONZERO_ERROR_MSG(x, nullptr)
#define NONZERO_WARNING(x) 				NONZERO_WARNING_MSG(x, nullptr)
#define FALSE_ERROR(x) 							FALSE_ERROR_MSG(x, nullptr)
#define FALSE_WARNING(x) 						FALSE_WARNING_MSG(x, nullptr)
#pragma endregion