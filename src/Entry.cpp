#include "ecs/ECSGame.h"
#include "oop/game/OOPGame.h"

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
#if 0
  OOPGame *app = new OOPGame(argc, argv, "Game sandbox", 1280, 720, true);
  app->run();
  delete app;
#endif

#if 1
  ECSGame *app = new ECSGame(argc, argv, 1280, 720, "ECS Game", false);
  app->run();
  delete app;
#endif
}
