#include <raylib.h>
#include <string>
#include <systems/ui/message.hpp>

namespace Systems::UI::Message {

static std::string currentMessage;
static float messageTimer = 0.0f;
static bool waitForInput = false;

void Set(const std::string message) {
  currentMessage = message;
  messageTimer = 0.0f;
  waitForInput = true;
}

void Set(const std::string message, float duration) {
  currentMessage = message;
  messageTimer = duration;
  waitForInput = false;
}

void Dismiss() {
  currentMessage.clear();
  messageTimer = 0.0f;
  waitForInput = false;
}

void Update() {
  if (waitForInput && IsKeyPressed(KEY_E)) {
    Dismiss();
  } else
    return;

  if (messageTimer > 0.0f) {
    messageTimer -= GetFrameTime();

    if (messageTimer <= 0.0f)
      Dismiss();
  }
}

void Draw() {
  if (!currentMessage.empty()) {
    int fontSize = 24;
    int marginBottom = 32;
    Font defaultFont = GetFontDefault();

    if (waitForInput)
      currentMessage += "\n[E] to continue";

    int textWidth = MeasureText(currentMessage.c_str(), fontSize);

    int x = (GetScreenWidth() - textWidth) / 2;
    int y = GetScreenHeight() - marginBottom - fontSize;
    DrawText(currentMessage.c_str(), x, y, fontSize, YELLOW);
  }
}

bool IsActive() { return currentMessage.empty(); }

bool IsWaitingForInput() { return waitForInput; }

} // namespace Systems::UI::Message
