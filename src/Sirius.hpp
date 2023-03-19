
#pragma once

// This header file is intended for use by client
//  applications only.

#include "Core/Application.hpp"
#include "Core/Logger/Logger.hpp"

#include "Core/Layer.hpp"
#include "UI/ImGuiLayer.hpp"
#include "UI/Scene.hpp"

#include "Core/Timestep.hpp"

#include "Core/Input/Input.hpp"
#include "Core/Input/KeyCodes.h"
#include "Core/Input/MouseButtonCodes.h"

#include "Math/Math.hpp"

// -------------- Renderer ---------------- //
#include "Renderer/Utils/Buffer.hpp"
#include "Renderer/Utils/VertexArray.hpp"
#include "Renderer/Utils/Shader.hpp"
#include "Renderer/Utils/Texture.hpp"
#include "Renderer/Utils/Color.hpp"
#include "Renderer/Utils/Material.hpp"

#include "Renderer/Objects/Light.hpp"
#include "Renderer/Objects/Model.hpp"
#include "Renderer/Objects/PrefabMeshes.hpp"
#include "Renderer/Objects/Skybox.hpp"

#include "Renderer/Objects/Camera.hpp"
#include "Renderer/Objects/CameraController.hpp"

#include "Renderer/RenderCommand.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Renderer2D.hpp"
#include "Renderer/Renderer3D.hpp"
// ---------------------------------------- //
