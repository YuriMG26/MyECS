#pragma once
#include "../../Logger.h"
#include "../Scene.h"

class ParticleScene : public Scene {
 public:
  ParticleScene(unsigned int entity_num);
  ParticleScene(const std::string& sceneName, uint32_t entity_num);

  void update(float delta, Camera2D camera);

 private:
  void InitParticleScene();

  uint32_t m_EntityNum = 0;
};
