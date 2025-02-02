/**
 * @file thexception.h
 * String exception class.
 */
  
/* Copyright (C) 2000 Stacho Mudrak
 * 
 * $Date: $
 * $RCSfile: $
 * $Revision: $
 *
 * -------------------------------------------------------------------- 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 * --------------------------------------------------------------------
 */

#pragma once

#include <stdexcept>
#include <fmt/core.h>

/**
 * Therion exception class.
 */
class thexception : public std::runtime_error {
public:
    explicit thexception(const std::string& msg)
    : std::runtime_error(msg)
    {}
};


#if __cplusplus >= 202002L
template <typename... Args>
[[noreturn]] void ththrow(fmt::format_string<Args...> format, Args&& ...args)
{
    throw thexception(fmt::format(format, std::forward<Args>(args)...));
}

template <typename... Args>
[[noreturn]] void threthrow(fmt::format_string<Args...> format, Args&& ...args)
{
    try
    {
        throw;
    }
    catch(const std::exception& e)
    {
        throw thexception(fmt::format("{} -- {}", fmt::format(format, std::forward<Args>(args)...), e.what()));
    }
}
#else
template <typename FormatStr, typename... Args>
[[noreturn]] void ththrow(const FormatStr& format, Args&& ...args)
{
    throw thexception(fmt::format(format, std::forward<Args>(args)...));
}

template <typename FormatStr, typename... Args>
[[noreturn]] void threthrow(const FormatStr& format, Args&& ...args)
{
    try
    {
        throw;
    }
    catch(const std::exception& e)
    {
        throw thexception(fmt::format("{} -- {}", fmt::format(format, std::forward<Args>(args)...), e.what()));
    }
}
#endif
