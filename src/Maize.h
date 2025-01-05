#pragma once

#include "Maize/Core/Application.h"
#include "Maize/Core/KeyCodes.h"
#include "Maize/Core/Macros/Log.h"
#include "Maize/Core/Macros/Assert.h"

#include "Maize/Math/Math.h"
#include "Maize/Math/Vec2.h"
#include "Maize/Math/Rect.h"

#include "Maize/Rendering/Mesh.h"
#include "Maize/Rendering/Sprite.h"

#include "Maize/Scene/Components/Input.h"
#include "Maize/Scene/Components/Position.h"
#include "Maize/Scene/Components/Rendering/Camera.h"
#include "Maize/Scene/Components/Rendering/SpriteRenderer.h"
#include "Maize/Scene/Components/Rendering/MeshRenderer.h"
#include "Maize/Scene/Components/SceneComponents.h"

#include "Maize/Scene/Scene.h"
#include "Maize/Scene/Entity.h"
#include "Maize/Scene/SystemState.h"

// allow to use imgui within game end :)
#include <imgui-SFML.h>
#include <imgui.h>
