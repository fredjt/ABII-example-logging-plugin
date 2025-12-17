//
// Created by Trent Tanchin on 7/4/24.
//

#include "header.h"
#include "bits/dlfcn.h"

namespace abii
{
static decltype(opendir)* real_opendir = nullptr;

extern "C" __nonnull((1)) __attribute_malloc__ __attr_dealloc(closedir, 1)
DIR* abii_opendir(const char* name)
{
    OVERRIDE_PREFIX(opendir)
        pre_fmtd_str str = "opendir(__name)";
        abii_args->push_func(new ArgPrinter(str));

        abii_args->push_arg(new ArgPrinter(name, "__name"));

        const auto pi_ret = real_opendir(name);

        abii_args->push_return(new ArgPrinter(pi_ret, "return"));
    OVERRIDE_SUFFIX(opendir, pi_ret)
    return real_opendir(name);
}

static decltype(dlopen)* real_dlopen = nullptr;

extern "C" void* abii_dlopen(const char* file, int mode) __THROWNL
{
    OVERRIDE_PREFIX(dlopen)
        pre_fmtd_str str = "dlopen(__file, __mode)";
    abii_args->push_func(new ArgPrinter(str));

    abii_args->push_arg(new ArgPrinter(file, "__file"));

    auto printer = new ArgPrinter(mode, "__mode");
    printer->set_enum_printer(print_bits_dlfcn_rtld, mode);
    abii_args->push_arg(printer);

    const auto pi_ret = real_dlopen(file, mode);

    abii_args->push_return(new ArgPrinter(pi_ret, "return"));
    OVERRIDE_SUFFIX(dlopen, pi_ret)
    return real_dlopen(file, mode);
}
}
