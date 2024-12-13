#ifndef DEFINE_H
#define DEFINE_H

#include "version.h"

#define APP_NAME "ChessGames"

#if defined(INTERN_BUILD)
#undef APP_VERSION_STR
#define APP_VERSION_STR             std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR) + "." + std::to_string(VERSION_PATCH) + "." + std::to_string(VERSION_BUILD)
#undef APP_VERSION_QSTR
#define APP_VERSION_QSTR            QString::number(VERSION_MAJOR) + "." + QString::number(VERSION_MINOR) + "." + QString::number(VERSION_PATCH) + "." + QString::number(VERSION_BUILD)
#else
#undef APP_VERSION_STR
#define APP_VERSION_STR             std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR) + "." + std::to_string(VERSION_PATCH)
#undef APP_VERSION_QSTR
#define APP_VERSION_QSTR            QString::number(VERSION_MAJOR) + "." + QString::number(VERSION_MINOR) + "." + QString::number(VERSION_PATCH)
#endif

#if defined(WITH_DEBUG_MSG)
#define DEBUG(...)                  qDebug() << __VA_ARGS__
#else
#define DEBUG(...)                  // Do nothing
#endif

#define NONE_FLAGS                  (0)
#define ENABLE_FLAGS(Flags, Mask)   ((Flags) |= (Mask))
#define DISABLE_FLAGS(Flags, Mask)  ((Flags) &= ~(Mask))
#define CHECK_FLAGS(Flags, Mask)    ((Flags) & (Mask))

#endif // DEFINE_H
