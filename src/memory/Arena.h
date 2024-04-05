#pragma once

class ArenaAllocator {
 public:
  ArenaAllocator();
  ~ArenaAllocator();

 private:
  void* m_Memory = nullptr;
};
