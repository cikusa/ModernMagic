////////////////////////////////////////////////////////////////////////////////
/// @file  fcyException.h
/// @brief fancy库异常定义
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyType.h"

#include <string>

/// @addtogroup fancy库异常
/// @brief 定义fancy库中的异常
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief fcy异常基类
/// @note  所有内部异常从该类派生
////////////////////////////////////////////////////////////////////////////////
class fcyException
{
protected:
	fuInt m_Time;            ///< @brief 记录异常时间戳
	std::string m_ExcpSrc;   ///< @brief 记录异常来源
	std::string m_ExcpDesc;  ///< @brief 记录异常信息
public:
	fuInt GetTime()const;    ///< @brief 获得异常时间
	fcStr GetSrc()const;     ///< @brief 获得异常来源
	fcStr GetDesc()const;    ///< @brief 获得异常信息
public:
	/// @brief     构造函数
	/// @param[in] Src  异常源
	/// @param[in] Desc 异常描述
	fcyException(fcStr Src, fcStr Desc);
	fcyException(const fcyException& Org);
	~fcyException();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fcyWin32异常
/// @note  包装Win32异常
////////////////////////////////////////////////////////////////////////////////
class fcyWin32Exception :
	public fcyException
{
private:
	fuInt m_LastError;          ///< @brief 最后一次错误代码
public:
	fuInt GetErrorCode()const;  ///< @brief 获得最后一次错误
public:
	/// @brief     构造函数
	/// @note      异常会自动在Info字段追加LastError值
	/// @param[in] Src  异常源
	/// @param[in] Info 异常描述
	fcyWin32Exception(fcStr Src, fcStr Info);
	~fcyWin32Exception();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fcyWin32COM异常
/// @note  包装COM异常
////////////////////////////////////////////////////////////////////////////////
class fcyWin32COMException :
	public fcyException
{
private:
	fInt m_HR;              ///< @brief 保存HResult字段
public:
	fInt GetResult()const;  ///< @brief 返回HResult字段
public:
	/// @brief     构造函数
	/// @note      异常会自动在Info字段追加HRESULT值
	/// @param[in] Src  异常源
	/// @param[in] Info 异常描述
	/// @param[in] HRet HResult
	fcyWin32COMException(fcStr Src, fcStr Info, fInt HRet);
	~fcyWin32COMException();
};

/// @}