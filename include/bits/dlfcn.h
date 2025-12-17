//
// Created by Trent Tanchin on 12/11/25.
//

#ifndef EXAMPLE_LOGGER_DLFCN_H
#define EXAMPLE_LOGGER_DLFCN_H

#include <abii/libabii.h>

namespace abii
{
const defines_map bits_dlfcn_rtld = {
    {RTLD_LOCAL, "RTLD_LOCAL"},
    {RTLD_LAZY, "RTLD_LAZY"},
    {RTLD_NOW, "RTLD_NOW"},
    {RTLD_NOLOAD, "RTLD_NOLOAD"},
    {RTLD_DEEPBIND, "RTLD_DEEPBIND"},
    {RTLD_GLOBAL, "RTLD_GLOBAL"},
    {RTLD_NODELETE, "RTLD_NODELETE"}
};

template<typename T>
std::string print_bits_dlfcn_rtld(const T v)
{
    return print_or_enum_entries(v, bits_dlfcn_rtld);
}
}

#endif //EXAMPLE_LOGGER_DLFCN_H
