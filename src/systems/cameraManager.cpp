#include "components/transform.hpp"
#include "core/entityManager.hpp"
#include "systems/camera.hpp"
#include <cmath>
#include <optional>
#include <raylib.h>
#include <raymath.h>
#include <systems/cameraManager.hpp>
#include <utils/camera.hpp>

namespace Systems {

int CameraManager::CreateCamera(const Camera::CameraConfig &config) {
  cameras.push_back(Camera::CameraWrapper{});
  int id = static_cast<int>(cameras.size()) - 1;
  auto &cam = cameras.back();
  cam.config = config;
  cam.active = false;

  auto target = GlobalEntityManager.GetEntity(config.followTargetID);

  cam.cam.position =
      cam.config.behavior == Camera::CameraBehavior::Follow
          ? Vector3Add(target && target->HasComponent<TransformComponent>()
                           ? target->GetComponent<TransformComponent>().position
                           : (Vector3){0},
                       config.offset)
          : config.offset;

  cam.cam.up = (Vector3){0, 1, 0};
  cam.cam.fovy = config.zoom;
  cam.cam.projection = CAMERA_PERSPECTIVE;

  return id;
}
void CameraManager::SetCameraTarget(int id, EntityID targetID) {
  if (id >= 0 && id < cameras.size()) {
    cameras[id].config.followTargetID = targetID;
  }
}

void CameraManager::SetActiveCamera(int id) {
  if (id >= 0 && id < cameras.size()) {
    previousCameraId = activeCameraId;
    activeCameraId = id;
  }
}

Camera::CameraWrapper *CameraManager::GetActiveCameraWrapper() {
  if (activeCameraId && *activeCameraId < cameras.size()) {
    return &cameras.at(*activeCameraId);
  }

  return nullptr;
}

Camera3D *CameraManager::GetActiveCamera() {
  if (activeCameraId && *activeCameraId < cameras.size()) {
    return &cameras.at(*activeCameraId).cam;
  }

  return nullptr;
}

void CameraManager::PushCamera(int id) {
  if (activeCameraId)
    cameraStack.push(*activeCameraId);

  SetActiveCamera(id);
}

void CameraManager::PopCamera() {
  if (!cameraStack.empty()) {
    cameraStack.pop();

    if (!cameraStack.empty()) {
      SetActiveCamera(cameraStack.top());
    } else {
      activeCameraId = std::nullopt;
    }
  }
}

Entity *CameraManager::GetFollowTarget(Camera::CameraWrapper &cam) {
  return GlobalEntityManager.GetEntity(cam.config.followTargetID);
}

Entity *CameraManager::GetFollowTarget(int id) {
  return GetFollowTarget(cameras.at(id));
}

bool CameraManager::HasFollowTarget(Camera::CameraWrapper &cam) {
  auto target = GlobalEntityManager.GetEntity(cam.config.followTargetID);

  return target;
}

std::vector<Camera::CameraWrapper> CameraManager::GetCameras() {
  return cameras;
}

bool CameraManager::HasFollowTarget(int id) {
  auto cam = GetCameras().at(id);

  return HasFollowTarget(cam);
}

bool CameraManager::CheckBounds(Rectangle r, Vector3 pos) {
  return pos.x >= r.x && pos.x <= (r.x + r.width) && pos.z >= r.y &&
         pos.z <= (r.y + r.height);
}

void CameraManager::SetCurrentActiveCamera(
    Camera::CameraWrapper &cam, int id, TransformComponent *targetTransform) {
  if (HasFollowTarget(cam) &&
      CheckBounds(cam.config.boundsXZ, targetTransform->position)) {
    if (activeCameraId == -1 ||
        cam.config.priority > cameras.at(*activeCameraId).config.priority) {
      previousCameraId = activeCameraId;
      SetActiveCamera(id);
    }
  }
}

void CameraManager::FixedCamSetup(Camera::CameraWrapper &active,
                                  TransformComponent *targetTransform) {
  if (active.config.behavior == Camera::CameraBehavior::Fixed &&
      GetFollowTarget(active) &&
      !CheckBounds(active.config.boundsXZ, targetTransform->position)) {
    if (previousCameraId && *previousCameraId >= 0) {
      SetActiveCamera(*previousCameraId);
      previousCameraId = -1;
    }
  }
}

void CameraManager::FollowCamUpdate(Camera::CameraWrapper &cam,
                                    Camera::CameraConfig &cfg, Vector2 delta,
                                    float camSensX, float camSensY,
                                    TransformComponent *transformComponent,
                                    float dt) {
  float distance = Vector3Length(cfg.offset);

  cam.yaw -= delta.x * camSensX;
  cam.pitch -= delta.y * camSensY;
  cam.pitch = Clamp(cam.pitch, -1.5f, 1.5f);

  Vector3 offset = {cosf(cam.pitch) * sinf(cam.yaw), sinf(cam.pitch),
                    cosf(cam.pitch) * cosf(cam.yaw)};

  offset = Vector3Scale(offset, distance);
  Vector3 desiredPos = Vector3Add(transformComponent->position, offset);

  cam.cam.position =
      Vector3Lerp(cam.cam.position, desiredPos, cfg.followLerp * dt);

  cam.cam.target = Vector3Lerp(cam.cam.target, transformComponent->position,
                               cfg.followLerp * dt);
}

void CameraManager::Update(float camSensX, float camSensY) {
  Vector3 playerPos = {0};

  size_t count = cameras.size();

  for (size_t i = 0; i < count; i++) {
    if (i == activeCameraId)
      continue;

    auto &cam = cameras.at(i);
    auto targetTransform =
        GetFollowTarget(cam)->TryGetComponent<TransformComponent>();

    SetCurrentActiveCamera(cam, i, targetTransform);

    if (!activeCameraId || *activeCameraId < 0 || *activeCameraId >= count)
      return;

    if (*activeCameraId < 0)
      continue;

    Camera::CameraWrapper &active = cameras.at(*activeCameraId);

    FixedCamSetup(active, targetTransform);
  }

  auto &cam = cameras.at(*activeCameraId);
  Vector2 delta = GetMouseDelta();
  auto target = GetFollowTarget(cam);

  if (!target)
    return;

  auto transformComponent = target->TryGetComponent<TransformComponent>();

  if (!transformComponent)
    return;

  float dt = GetFrameTime();

  if (cfg.behavior == Camera::CameraBehavior::Follow) {
  }

  else if (cfg.behavior == Camera::CameraBehavior::Fixed) {
    Vector3 dir =
        Vector3Subtract(transformComponent->position, cam.cam.position);
    dir = Vector3Normalize(dir);

    Vector3 baseTarget = transformComponent->position;
    Vector3 rotatedTarget = {baseTarget.x + dir.x * cfg.rotationIntensity,
                             baseTarget.y,
                             baseTarget.z + dir.z * cfg.rotationIntensity};

    float t = Clamp(cfg.followLerp * dt, 0.0f, 1.0f);
    float easedT = EaseInOut(t);

    cam.cam.target = Vector3Lerp(cam.cam.target, rotatedTarget, easedT);
    ;
  }

  cam.cam.fovy = cfg.zoom;
}

void CameraManager::Update(float camSens) { Update(camSens, camSens); }

} // namespace Systems

Systems::CameraManager GlobalCameraManager;
