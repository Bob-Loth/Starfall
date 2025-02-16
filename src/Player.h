#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> //for value_ptr

#include "Component.h"
#include "Renderer.h"
#include "LunaBodyRenderer.h"
#include "GameObject.h"
#include "EulerTransform.h"
#include "PlayerMovement.h"
#include "PlayerTransform.h"
#include "HeadRenderer.h"
#include "imgui/imgui.h"

#include <vector>
#include <memory>
#include <string>

using glm::vec3;
using glm::mat4;
using glm::normalize;

class Player
{
private:
	Player(vec3 pos);
	vec3 pos = vec3(0);
	float playerYOffset = -1.5f;	// target move pos
	float currentFloatOffset = 0;
	float idleTime = 0.0f;
	const float idleHeight = .4f;
	float currentRotationChange = 0.0f;
	float currentZRotation = 0.0f;
	float currentXRotation = 0.0f;
	float radius = 1.8f;
	void AnimatePlayerModel(float frameTime);
	void SetManualRotations();
	void SetAutomaticRotations(float frameTime);
	shared_ptr<Transform> trans = NULL;
	shared_ptr<EulerTransform> pTransform;
	shared_ptr<PlayerTransform> headTrans;
	shared_ptr<PlayerTransform> arm1Trans;
	shared_ptr<PlayerTransform> arm2Trans;
	shared_ptr<HeadRenderer> headRenderer;
	void UpdatePlayerAnimations(float frameTime);
	void UpdateArmAnimations(float frameTime, int thrust, int rTurn, int lTurn);
	void UpdateHeadAnimations(float frameTime, int headTurn);
	void SetBaseRotation(float frameTime, int thrust);
	void SetHoverAnimation(float frameTime, int thrust);
	vec3 rightArmEulerOffset = vec3(0, 0, 0);
	vec3 leftArmEulerOffset = vec3(0, 0, 0);
	vec3 headEulerOffset = vec3(0, 0, 0);


	// animation constants (keyframes)
	vec3 rightArmBoostForward = vec3(-39, 0, -11);
	vec3 leftArmBoostForward = vec3(-39, 0, 11);
	vec3 rightArmTurnOut = vec3(0, 0, 20);
	vec3 leftArmTurnOut = vec3(0, 0, -20);
	vec3 rightArmBoostBackward = vec3(39, 0, -11);
	vec3 leftArmBoostBackward = vec3(39, 0, 11);
	vec3 rightArmIdle = vec3(0, 33, -9);
	vec3 leftArmIdle = vec3(0, -33, 9);

	vec3 headTurnRight = vec3(0, 22, 0);
	vec3 headTurnLeft = vec3(0, -22, 0);

	quat rBoostForwards, lBoostForwards,
		rArmTurnOut, lArmTurnOut,
		rBoostBackwards, lBoostBackwards,
		rArmIdle, lArmIdle,
		hTurnRight, hTurnLeft;
	quat rRot = glm::identity<quat>();
	quat lRot = glm::identity<quat>();
	quat hRot = glm::identity<quat>();
public:
	const std::string pName = "player";
	const std::string pArm1Name = "arm1";
	const std::string pArm2Name = "arm2";
	const std::string pHeadName = "head";
	shared_ptr<PlayerMovement> movement = NULL;
	void Update(float frameTime, ComponentManager* compMan);
	void SetInput(int index, bool val);
	vec3 GetForward();
	vec3 GetVelocity();
	float GetCurrentSpeed() { return movement->GetSpeed(); }
	float GetCurrentSpeedAsPct() { return movement->GetSpeed() / 35; }
	float GetMaxSpeed() { return movement->GetMaxSpeed(); }
	void Init(ComponentManager* compMan, shared_ptr<EulerTransform> pTrans,
		shared_ptr<PlayerTransform> head, shared_ptr<PlayerTransform> arm1,
		shared_ptr<PlayerTransform> arm2, shared_ptr<HeadRenderer> headr);
	const vec3 GetPosition() { return pTransform->GetPos(); }
	quat GetRotation() { return pTransform->GetRot(); }
  // Is GetRadius Needed?
	float GetRadius() { return radius; }
	static Player& GetInstance(vec3 pos) {
		static Player instance(pos);
		return instance;
	}
};