#include "Logger.h"

namespace Logger {

void log(const char *format, ...) {
  char buf[128];
  secure_sprintf(buf, 128, LOG_GREEN "[LOG]:" LOG_RESET " %s\n", format);

  va_list args;
  va_start(args, format);
  vprintf(buf, args);
  va_end(args);
}
void error(const char *format, ...) {
  char buf[128];

  secure_sprintf(buf, 128, LOG_RED "[ERROR]:" LOG_RESET " %s\n", format);

  va_list args;
  va_start(args, format);
  vprintf(buf, args);
  va_end(args);
}
void warning(const char *format, ...) {
  char buf[128];
  secure_sprintf(buf, 128, LOG_YELLOW "[WARNING]:" LOG_RESET " %s\n", format);

  va_list args;
  va_start(args, format);
  vprintf(buf, args);
  va_end(args);
}
void memory(const char *format, ...) {
#if 0
  char buf[128];
  secure_sprintf(buf, 128, LOG_CYAN "[MEMORY]:" LOG_RESET " %s\n", format);

  va_list args;
  va_start(args, format);
  vprintf(buf, args);
  va_end(args);
#endif
}
}  // namespace Logger
