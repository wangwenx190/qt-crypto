#pragma once

#include <QtCore/qglobal.h>

#ifndef QTCRYPTO_API
#  ifdef QTCRYPTO_BUILD_STATIC
#    define QTCRYPTO_API
#  else
#    ifdef QTCRYPTO_BUILD_LIBRARY
#      define QTCRYPTO_API Q_DECL_EXPORT
#    else
#      define QTCRYPTO_API Q_DECL_IMPORT
#    endif
#  endif
#endif