#include "Logger.h"

namespace Logger {

void log(const char *format, ...) {
  char buf[128];
  sprintf_s(buf, 128, LOG_GREEN "[LOG]:" LOG_RESET " %s\n", format);

  va_list args;
  va_start(args, buf);
  vprintf(buf, args);
  va_end(args);
}
void error(const char *format) {
  printf(LOG_RED "[ERROR]:" LOG_RESET " %s\n", format);
}
void warning(const char *format) {
  printf(LOG_YELLOW "[WARNING]:" LOG_RESET " %s\n", format);
}
void memory(const char *format, ...) {
  char buf[128];
  sprintf_s(buf, 128, LOG_CYAN "[MEMORY]:" LOG_RESET " %s\n", format);

  va_list args;
  va_start(args, buf);
  vprintf(buf, args);
  va_end(args);
}
}  // namespace Logger