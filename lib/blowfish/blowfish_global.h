#ifndef BLOWFISH_GLOBAL_H
#define BLOWFISH_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BLOWFISH_LIBRARY)
#  define BLOWFISHSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BLOWFISHSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BLOWFISH_GLOBAL_H
