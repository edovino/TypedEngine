#include "Application.h"

#include "Rendering/RenderAPI.h"
#include "Rendering/RenderCommand.h"

#include "glm/glm.hpp"

extern "C" {
  #include "Scripting/TElua.h"
}

Application* app;
Window* window;
Camera* camera;

static void callback_keyPressed(Key key, Modifier mod) { app->onKeyPressed(key, mod); }
static void callback_keyReleased(Key key, Modifier mod) { app->onKeyReleased (key, mod); }
static void callback_mouseScrolled(float offsetx, float offsety) { app->onMouseScrolled(offsetx, offsety); }
static void callback_windowRefreshed() {  app->onWindowRefreshed(); }

static std::string getName() {
  std::string name = "TypedEngine : ";
#ifdef TE_DEBUG
  name += "Debug";
#else
  name += "Release";
#endif
  return name;
}

int main() {
  window = RenderAPI::createWindow({ 680, 480 }, getName().c_str());

  window->callback_keyPressed(callback_keyPressed);
  window->callback_keyReleased(callback_keyReleased);
  window->callback_mouseScrolled(callback_mouseScrolled);
  window->callback_windowRefreshed(callback_windowRefreshed);

  camera = new Camera(window);
  RenderCommand::init(camera);

  init_lua();

  app = createApplication();
  app->window = window;
  app->camera = camera;

  app->begin();

  float previous = window->getTime();    //YUCK! @CleanUp: Make custom deltaTime function, don't want glfw in the main file
  
  while (window->isRunning()) {
    float time = window->getTime();
    float deltaTime = time - previous;

    run_lua(deltaTime, time);
    app->tick(deltaTime, time);

    RenderCommand::clear({ 0.9f, 0.9f, 0.9f, 1.0f });
    RenderCommand::run();

    window->swapBuffers();
    
    previous = time;
  }

  close_lua();
  RenderCommand::end();

  delete app;
  return 0;
}
