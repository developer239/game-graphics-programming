#pragma once

#include "core/AssetStore.h"
#include "core/IStrategy.h"
#include "core/Window.h"
#include "gui/Controls.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "logger/Logger.h"
#include "rendering/Painter.h"
#include "rendering/WavefrontLoader.h"
#include "Textures.h"

class LoopStrategy : public Core::IStrategy {
 public:
  Light light;
  Camera camera;
  Painter painter = Painter(800, 600);
  WavefrontLoader wavefrontLoader;
  Mesh mesh;
  // TODO: use smart pointer
  const uint32_t* redbrickTexture = (uint32_t*)REDBRICK_TEXTURE;
  Controls debug;

  bool shouldRotate = false;
  bool shouldCull = false;

  void Init(Core::Window& window, Core::Renderer& renderer) override {
    // wavefrontLoader.LoadObjFile("assets/models/f22.obj", mesh);
    mesh = Mesh::CreateCube();
  }

  void HandleEvent(SDL_Event& event) override {}

  void OnUpdate(
      Core::Window& window, Core::Renderer& renderer, double deltaTime
  ) override {
    if (shouldRotate) {
      mesh.rotate();
    }

    painter.colorBuffer.ClearColorBuffer();
    painter.BackgroundGrid();
    painter.Mesh(mesh, shouldCull, camera, light, redbrickTexture);
  }

  void OnRender(Core::Window& window, Core::Renderer& renderer) override {
    painter.colorBuffer.RenderColorBuffer(renderer);
    debug.Render(shouldRotate, shouldCull, mesh);
  }
};
