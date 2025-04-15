#pragma once

#include "camera.hpp"
#include "components/transform.hpp"
#include <optional>
#include <raylib.h>
#include <stack>

namespace Systems {

class CameraManager {
public:
  int CreateCamera(const Camera::CameraConfig &config);
  void SetCameraTarget(int id, EntityID targetID);
  std::vector<Camera::CameraWrapper> GetCameras();
  void Update(float camSensX, float camSensY);
  void Update(float camSens);
  /*void DrawDebug();*/

  void SetActiveCamera(int id);
  Camera3D *GetActiveCamera();

  void PushCamera(int id);
  void PopCamera();

  bool HasFollowTarget(int id);
  bool HasFollowTarget(Camera::CameraWrapper &cam);
  bool CheckBounds(Rectangle r, Vector3 pos);

  Entity *GetFollowTarget(int id);
  Entity *GetFollowTarget(Camera::CameraWrapper &cam);

  Camera::CameraWrapper *GetActiveCameraWrapper();

private:
  std::vector<Camera::CameraWrapper> cameras;
  std::stack<int> cameraStack;
  std::optional<int> activeCameraId;
  std::optional<int> previousCameraId;

  void FixedCamSetup(Camera::CameraWrapper &active,
                     TransformComponent *targetTransform);
  void FixedCamUpdate(Camera::CameraWrapper &active);

  void FollowCamUpdate(Camera::CameraWrapper &cam, Camera::CameraConfig &cfg,
                       Vector2 delta, float camSensX, float camSensY,
                       TransformComponent *transformComponent, float dt);

  void SetCurrentActiveCamera(Camera::CameraWrapper &cam, int id,
                              TransformComponent *targetTransform);
};

} // namespace Systems

extern Systems::CameraManager GlobalCameraManager;
