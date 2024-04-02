#pragma once
#include "../../Logger.h"
#include "../Scene.h"

class ParticleScene : public Scene {
 public:
  ParticleScene();
  ParticleScene(const std::string& sceneName);

  void update(float delta, Camera2D camera);

 private:
};
