#pragma once
#include <exception>

#define ExceptionClass(__ClassName__) \
class __ClassName__ : std::exception \
{ \
	String m_sWhat; \
public: \
	inline __ClassName__(const String& _sWhat = "") : m_sWhat(_sWhat) { } \
	virtual ~__ClassName__() = default; \
	__ClassName__& operator=(const __ClassName__&) = default; \
	virtual inline const char* what() const override { return m_sWhat.c_str(); } \
};
