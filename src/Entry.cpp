#include "Game.h"

// Tracking memory allocations
void *operator new(size_t size) {
  Logger::memory("allocating %zu bytes\n", size);
  return malloc(size);
}

void operator delete(void *memory, size_t size) {
  Logger::memory("deallocating %zu bytes\n", size);
  free(memory);
}

int main(int argc, char *argv[]) {
  Game *app = new Game(argc, argv, "Game sandbox", 1280, 720, false, 1000);
  app->run();
  delete app;
}