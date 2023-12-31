#include "oop/OOPGame.h"

// Tracking memory allocations
void *operator new(size_t size) {
  Logger::memory("allocating %zu bytes", size);
  return malloc(size);
}

void operator delete(void *memory, size_t size) {
  Logger::memory("deallocating %zu bytes", size);
  free(memory);
}

int main(int argc, char *argv[]) {
  OOPGame *app =
      new OOPGame(argc, argv, "Game sandbox", 800, 600, true);
  app->run();
  delete app;
}