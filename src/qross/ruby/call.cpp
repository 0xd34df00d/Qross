/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#include "call.h"

using namespace Qross;

namespace
{
    struct Call
    {
        VALUE receiver;
        ID method;
        long argc;
        const VALUE* argv;
    };

    VALUE invoke(VALUE argument)
    {
        const auto* const call = reinterpret_cast<const Call*>(argument);
        return rb_funcallv(call->receiver, call->method, int(call->argc), call->argv);
    }
}

Result Qross::runProtected(VALUE (*function)(VALUE), VALUE argument)
{
    int state = 0;
    const VALUE result = rb_protect(function, argument, &state);
    if (state == 0)
        return result;

    VALUE error = rb_errinfo();
    rb_set_errinfo(Qnil);
    if (NIL_P(error))
        error = rb_exc_new_cstr(rb_eRuntimeError, "Ruby left the call without an exception");
    return std::unexpected(error);
}

Result Qross::callProtected(VALUE receiver, ID method, long argc, const VALUE* argv)
{
    const Call call { receiver, method, argc, argv };
    return runProtected(invoke, reinterpret_cast<VALUE>(&call));
}
