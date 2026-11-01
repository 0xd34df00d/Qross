/**********************************************************************
 * Qross - scripting bridge for Qt applications.
 * SPDX-License-Identifier: LGPL-2.0-or-later
 **********************************************************************/

#pragma once

// Ruby's stdbool shim includes <cstdbool>, which C++17 deprecated.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcpp"
#include <ruby.h>
#include <ruby/encoding.h>
#pragma GCC diagnostic pop

// Onigmo's shorthand would rename QMetaType::UChar.
#undef UChar
