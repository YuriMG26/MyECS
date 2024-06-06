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

#define OOP 1

int main(int argc, char *argv[]) {
#if OOP
  OOPGame *app = new OOPGame(argc, argv, "Game sandbox", 1280, 720, true);
  app->run();
  delete app;
#else
  ECSGame *app = new ECSGame(argc, argv, "ECS Game", 1280, 720, false);
  app->run();
  delete app;
#endif
}
