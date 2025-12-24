//
// Created by Trent Tanchin on 12/11/25.
//

#ifndef EXAMPLE_LOGGER_DLFCN_H
#define EXAMPLE_LOGGER_DLFCN_H

#include <abii/libabii.h>

namespace abii
{
const defines_map bits_dlfcn_rtld = {
    {0, "RTLD_LOCAL"},
    {0x00001, "RTLD_LAZY"},
    {0x00002, "RTLD_NOW"},
    {0x00004, "RTLD_NOLOAD"},
    {0x00008, "RTLD_DEEPBIND"},
    {0x00100, "RTLD_GLOBAL"},
    {0x01000, "RTLD_NODELETE"}
};

template <typename T>
std::string print_bits_dlfcn_rtld(const T v)
{
    return print_or_enum_entries(v, bits_dlfcn_rtld);
}
}

#endif //EXAMPLE_LOGGER_DLFCN_H
