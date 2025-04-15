#pragma once

#include <string>
namespace Systems::UI::Message {

void Set(const std::string message);
void Set(const std::string message, float duration);
void Dismiss();
void Update();
void Draw();
bool IsActive();
bool IsWaitingForInput();

} // namespace Systems::UI::Message
