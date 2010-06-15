/*  This file is part of the KDE project
    Copyright (C) 2007 David Faure <faure@kde.org>
    Copyright (C) 2007 Sebastian Sauer <mail@dipe.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef QROSS_EXPORT_H
#define QROSS_EXPORT_H

#ifndef QROSS_EXPORT
# if defined(qross_EXPORTS)
   /* We are building this library */
#  define QROSS_EXPORT Q_DECL_EXPORT
# else
   /* We are using this library */
#  define QROSS_EXPORT Q_DECL_IMPORT
# endif
#endif

#ifndef QROSSCORE_EXPORT
# if defined(qrosscore_EXPORTS)
   /* We are building this library */
#  define QROSSCORE_EXPORT Q_DECL_EXPORT
# else
   /* We are using this library */
#  define QROSSCORE_EXPORT Q_DECL_IMPORT
# endif
#endif

#ifndef QROSSUI_EXPORT
# if defined(qrossui_EXPORTS)
   /* We are building this library */
#  define QROSSUI_EXPORT Q_DECL_EXPORT
# else
   /* We are using this library */
#  define QROSSUI_EXPORT Q_DECL_IMPORT
# endif
#endif

# ifndef QROSS_EXPORT_DEPRECATED
#  define QROSS_EXPORT_DEPRECATED Q_DECL_DEPRECATED QROSS_EXPORT
# endif
# ifndef QROSSCORE_EXPORT_DEPRECATED
#  define QROSSCORE_EXPORT_DEPRECATED Q_DECL_DEPRECATED QROSSCORE_EXPORT
# endif

#endif
