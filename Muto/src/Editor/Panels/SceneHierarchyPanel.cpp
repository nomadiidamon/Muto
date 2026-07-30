#include "mupch.h"
#include <Utils/PlatformUtils.h>
#include "SceneHierarchyPanel.h"
#include "Scene/Components.h"

#include "imgui.h"
#include "imgui_internal.h"
//#include <imgui/misc/cpp/imgui_stdlib.h>

#include <glm/gtc/type_ptr.hpp>

#include <cstring>


namespace Muto {

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
		m_SelectionContext = {};
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");
		if (m_Context) {

			auto view = m_Context->m_Registry.view<NameComponent>();

			for (auto entity : view) {
				Entity e{ entity, m_Context.get() };
				DrawEntityNode(e);
			}

			if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
				m_SelectionContext = {};

			// Right-click on blank space
			if (ImGui::BeginPopupContextWindow(0, ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight))
			{
				if (ImGui::MenuItem("Create Empty Entity"))
					m_SelectionContext = m_Context->CreateEntity("Empty Entity");

				ImGui::EndPopup();
			}
		}
		ImGui::End();

		ImGui::Begin("Properties");
		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);
		}

		ImGui::End();
	}

	void SceneHierarchyPanel::SetSelectedEntity(Entity entity)
	{
		m_SelectionContext = entity;
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& name = entity.GetComponent<NameComponent>().Name;
		void* nodeID = (void*)(uint64_t)(uint32_t)entity;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
		bool opened = ImGui::TreeNodeEx(nodeID, flags, name.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;

			if (ImGui::MenuItem("Duplicate Entity"))
			{
				Entity newEntity = m_Context->CreateEntity(name);
				// Copy components
				if (entity.HasComponent<NameComponent>()) {
					auto& src = entity.GetComponent<NameComponent>();
					auto& newEntName = newEntity.GetComponent<NameComponent>();
					///TODO: Improve name duplication logic
					if (src.Name.capacity() > 0 && isdigit(src.Name.back()))
					{
						// Increment trailing number
						size_t i = src.Name.size() - 1;
						while (i > 0 && isdigit(src.Name[i - 1]))
							--i;
						std::string baseName = src.Name.substr(0, i);
						std::string numberStr = src.Name.substr(i);
						int number = std::stoi(numberStr);
						newEntName.Name = baseName + std::to_string(number + 1);
					}
					else
						newEntName.Name = src.Name + "1";
				}
				if (entity.HasComponent<SpriteRendererComponent>())
				{
					auto& src = entity.GetComponent<SpriteRendererComponent>();
					newEntity.AddComponent<SpriteRendererComponent>(src);
				}
				if (entity.HasComponent<CameraComponent>())
				{
					auto& cc = entity.GetComponent<CameraComponent>();
					newEntity.AddComponent<CameraComponent>(cc);
				}
				if (entity.HasComponent<NativeScriptComponent>())
				{
					auto& nsc = entity.GetComponent<NativeScriptComponent>();
					newEntity.AddComponent<NativeScriptComponent>(nsc);
				}
				if (entity.HasComponent<TextureAnimationComponent>())
				{
					auto& tac = entity.GetComponent<TextureAnimationComponent>();
					newEntity.AddComponent<TextureAnimationComponent>(tac);
				}
				// Add more components as needed
				m_SelectionContext = newEntity;
			}

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, name.c_str());
			if (opened)
			{
				/// TODO: Draw child entities here in the future
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}

		if (entityDeleted)
		{
			m_Context->DestroyEntity(entity);
			if (m_SelectionContext == entity)
				m_SelectionContext = {};
		}
	}

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		// Compute available width for the three float controls in the right column
		float availableWidth = ImGui::GetContentRegionAvail().x;
		float itemSpacing = ImGui::GetStyle().ItemSpacing.x;
		float totalButtonWidth = buttonSize.x * 3.0f;
		// Account for SameLine() spacings between button+control pairs (conservative estimate)
		float totalSpacing = itemSpacing * 6.0f;
		float itemWidth = (availableWidth - totalButtonWidth - totalSpacing) / 3.0f;
		if (itemWidth <= 0.0f)
			itemWidth = ImGui::CalcItemWidth();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::PushItemWidth(itemWidth);
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::PushItemWidth(itemWidth);
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::PushItemWidth(itemWidth);
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	static void DrawVec2Control(const std::string& label, glm::vec2& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		// Compute available width for the three float controls in the right column
		float availableWidth = ImGui::GetContentRegionAvail().x;
		float itemSpacing = ImGui::GetStyle().ItemSpacing.x;
		float totalButtonWidth = buttonSize.x * 2.0f;
		// Account for SameLine() spacings between button+control pairs (conservative estimate)
		float totalSpacing = itemSpacing * 4.0f;
		float itemWidth = (availableWidth - totalButtonWidth - totalSpacing) / 2.0f;
		if (itemWidth <= 0.0f)
			itemWidth = ImGui::CalcItemWidth();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::PushItemWidth(itemWidth);
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::PushItemWidth(itemWidth);
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	static void SubTextureEdit(Entity entity, const std::string& label, SubTextureComponent& subTexture)
	{
		ImGui::Text(label.c_str());

		auto& subTexRef = subTexture.GetSubTexture();
		if (subTexRef && subTexRef->GetTexture()) {
			auto oldSubRef = subTexRef;
			glm::vec2 oldOffset = subTexture.Offset;
			glm::vec2 oldTiling = subTexture.TilingFactor;

			DrawVec2Control("Offset", subTexture.Offset);
			DrawVec2Control("Scale", subTexture.TilingFactor, 1.0f);

			if (subTexRef->GetTexture())
			{
				auto tex = subTexRef->GetTexture();
				if (tex) {

					auto newSub = SubTexture2D::CreateFromCoords(
						tex, subTexture.Offset,
						glm::vec2(static_cast<float>(tex->GetWidth()) * subTexture.TilingFactor.x,
							static_cast<float>(tex->GetHeight()) * subTexture.TilingFactor.y));
					subTexture.SubTexture = newSub;

					if (entity.HasComponent<TextureAnimationComponent>()) {
						auto& texAnim = entity.GetComponent<TextureAnimationComponent>();
						for (auto& frame : texAnim.SubTextures) {
							// frame == oldSubRef compares Ref<> identity
							if (frame == oldSubRef) {
								frame = newSub;
							}
						}

						if (texAnim.CurrentFrame >= (int)texAnim.SubTextures.size())
							texAnim.CurrentFrame = texAnim.SubTextures.empty() ? 0 : (int)texAnim.SubTextures.size() - 1;
					}
				}
			}
		}
		else {
			ImGui::Text("No texture assigned.");
		}

	}

	static void TextureAnimationEdit(const std::string& label, SubTextureComponent& subTexture, TextureAnimationComponent& texAnim) {
		ImGui::Text(label.c_str());

		auto& subTexRef = subTexture.GetSubTexture();
		if (subTexRef && subTexRef->GetTexture()) {
			glm::vec2 oldOffset = subTexture.Offset;
			glm::vec2 oldTiling = subTexture.TilingFactor;

			DrawVec2Control("Offset", subTexture.Offset);
			DrawVec2Control("Scale", subTexture.TilingFactor, 1.0f);

			if (subTexRef->GetTexture())
			{
				auto tex = subTexRef->GetTexture();
				if (tex) {

					if (ImGui::Button("Add SubTexture to Animation")) {
						bool skip = false;
						for (int i = 0; i < texAnim.SubTextures.size(); i++) {
							if (texAnim.SubTextures[i] == subTexture.GetSubTexture()) {
								MU_CORE_WARN("Sub Texture already stored in array. Skipping addition");
								skip = true;
								break;
							}
						}
						if (!skip) {
							texAnim.SubTextures.push_back(subTexture.GetSubTexture());
						}
					}
					if (ImGui::Button("Override Current Frame")) {
						if (texAnim.SubTextures.size() == 0) {
							MU_CORE_WARN("No frames to override.");
						}
						else {
							if (texAnim.CurrentFrame < 0 || texAnim.CurrentFrame >= (int)texAnim.SubTextures.size())
								texAnim.CurrentFrame = 0;
							texAnim.SubTextures[texAnim.CurrentFrame] = SubTexture2D::CreateFromCoords(tex, subTexture.Offset,
								glm::vec2(static_cast<float>(tex->GetWidth()) * subTexture.TilingFactor.x,
									static_cast<float>(tex->GetHeight()) * subTexture.TilingFactor.y));
						}
					}
					if (ImGui::Button("Remove Current Frame")) {

						if (texAnim.SubTextures.size() <= 1) {
							return;
						}

						int idx = texAnim.CurrentFrame;
						if (idx < 0) idx = 0;
						if (idx >= (int)texAnim.SubTextures.size()) idx = (int)texAnim.SubTextures.size() - 1;

						texAnim.SubTextures.erase(texAnim.SubTextures.begin() + idx);
						MU_CORE_INFO("Animation Frame removed successfully!");

						if (texAnim.SubTextures.empty())
							texAnim.CurrentFrame = 0;
						else if (texAnim.CurrentFrame >= (int)texAnim.SubTextures.size())
							texAnim.CurrentFrame = 0;
					}
				}
			}
		}
		else {
			ImGui::Text("No texture assigned.");
		}
	}

	template<typename T, typename UIFunction>
	static void DrawComponent(const std::string& name, Entity entity, UIFunction uiFunction)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		if (entity.HasComponent<T>())
		{
			auto& component = entity.GetComponent<T>();
			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
			ImGui::PopStyleVar(
			);
			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove component"))
					removeComponent = true;

				ImGui::EndPopup();
			}

			if (open)
			{
				uiFunction(entity, component);
				ImGui::TreePop();
			}

			if (removeComponent)
				entity.RemoveComponent<T>();
		}
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<NameComponent>())
		{
			auto& name = entity.GetComponent<NameComponent>().Name;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strncpy_s(buffer, sizeof(buffer), name.c_str(), sizeof(buffer));
			if (ImGui::InputText("##Name", buffer, sizeof(buffer)))
			{
				name = std::string(buffer);
			}
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-1);

		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent"))
		{
			DisplayAddComponentEntry<CameraComponent>("Camera");
			//DisplayAddComponentEntry<ScriptComponent>("Script");
			DisplayAddComponentEntry<SpriteRendererComponent>("Sprite Renderer");
			DisplayAddComponentEntry<SubTextureComponent>("SubTexture");
			DisplayAddComponentEntry<TextureAnimationComponent>("Texture Animation");
			DisplayAddComponentEntry<ParticleSystemComponent>("Particle System");

			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();

		DrawComponent<TransformComponent>("Transform", entity, [](Entity ent, auto& component)
			{
				DrawVec3Control("Translation", component.Translation);
				glm::vec3 rotation = glm::degrees(component.Rotation);
				DrawVec3Control("Rotation", rotation);
				component.Rotation = glm::radians(rotation);
				DrawVec3Control("Scale", component.Scale, 1.0f);
			});

		DrawComponent<CameraComponent>("Camera", entity, [](Entity ent, auto& component)
			{
				auto& camera = component.Camera;

				ImGui::Checkbox("Primary", &component.Primary);

				const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
				const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];
				if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
				{
					for (int i = 0; i < 2; i++)
					{
						bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
						if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
						{
							currentProjectionTypeString = projectionTypeStrings[i];
							camera.SetProjectionType((SceneCamera::ProjectionType)i);
						}

						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
				{
					float perspectiveVerticalFov = glm::degrees(camera.GetPerspectiveVerticalFOV());
					if (ImGui::DragFloat("Vertical FOV", &perspectiveVerticalFov))
						camera.SetPerspectiveVerticalFOV(glm::radians(perspectiveVerticalFov));

					float perspectiveNear = camera.GetPerspectiveNearClip();
					if (ImGui::DragFloat("Near", &perspectiveNear))
						camera.SetPerspectiveNearClip(perspectiveNear);

					float perspectiveFar = camera.GetPerspectiveFarClip();
					if (ImGui::DragFloat("Far", &perspectiveFar))
						camera.SetPerspectiveFarClip(perspectiveFar);
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
				{
					float orthoSize = camera.GetOrthographicSize();
					if (ImGui::DragFloat("Size", &orthoSize))
						camera.SetOrthographicSize(orthoSize);

					float orthoNear = camera.GetOrthographicNearClip();
					if (ImGui::DragFloat("Near", &orthoNear))
						camera.SetOrthographicNearClip(orthoNear);

					float orthoFar = camera.GetOrthographicFarClip();
					if (ImGui::DragFloat("Far", &orthoFar))
						camera.SetOrthographicFarClip(orthoFar);

					ImGui::Checkbox("Fixed Aspect Ratio", &component.FixedAspectRatio);
				}
			});

		DrawComponent<SpriteRendererComponent>("Sprite Renderer", entity, [](Entity ent, auto& component)
			{
				ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));

				// Separate checkbox for enabling/disabling texture usage
				ImGui::Checkbox("Texture Enabled", &component.TextureEnabled);
				ImGui::SameLine();

				// Display current texture name (if any) and buttons to Set / Change / Clear the texture
				if (component.Texture)
				{
					ImGui::TextUnformatted(component.Texture->GetName().c_str());
					ImGui::SameLine();
					if (ImGui::Button("Change Texture"))
					{
						std::string filePath = FileDialogs::OpenFile("Image Files (*.png;*.jpg;*.jpeg;*.bmp;*.tga)\0*.png;*.jpg;*.jpeg;*.bmp;*.tga\0All Files (*.*)\0*.*\0");
						if (!filePath.empty())
						{
							auto& tex = Texture2D::Create(filePath);
							if (tex)
							{
								component.Texture = tex;
								component.TextureEnabled = true;
								if (ent.HasComponent<SubTextureComponent>()) {
									auto& stc = ent.GetComponent<SubTextureComponent>();
									stc.SetTexture(component.Texture);

									if (ent.HasComponent<TextureAnimationComponent>()) {
										auto& texAnim = ent.GetComponent<TextureAnimationComponent>();
										// Always replace animation frames with a fresh initial frame based on the new texture
										texAnim.SubTextures.clear();
										texAnim.SubTextures.push_back(SubTexture2D::CreateFromCoords(
											component.Texture, stc.Offset,
											glm::vec2(static_cast<float>(tex->GetWidth()) * stc.TilingFactor.x,
												static_cast<float>(tex->GetHeight()) * stc.TilingFactor.y)
										));
										texAnim.CurrentFrame = 0;
										texAnim.TimeAccumulator = 0.0f;
									}
								}
							}
							else
							{
								MU_WARN("Could not load texture {0}", filePath);
							}
						}
					}
					ImGui::SameLine();
					if (ImGui::Button("Clear Texture"))
					{
						component.Texture = nullptr;
						component.TextureEnabled = false;
					}
				}
				else
				{
					ImGui::SameLine();
					if (ImGui::Button("Set Texture"))
					{
						std::string filePath = FileDialogs::OpenFile("Image Files (*.png;*.jpg;*.jpeg;*.bmp;*.tga)\0*.png;*.jpg;*.jpeg;*.bmp;*.tga\0All Files (*.*)\0*.*\0");
						if (!filePath.empty())
						{
							auto tex = Texture2D::Create(filePath);
							if (tex)
							{
								component.Texture = tex;
								component.TextureEnabled = true;
							}
							else
							{
								MU_WARN("Could not load texture {0}", filePath);
							}
						}
					}
				}

				ImGui::DragFloat("Tiling Factor", &component.TilingFactor, 0.1f, 0.0f, 100.0f);

			});

		DrawComponent<SubTextureComponent>("SubTexture", entity, [](Entity ent, auto& component)
			{
				std::string name = (component.SubTexture && component.SubTexture->GetTexture()) ? component.SubTexture->GetTexture()->GetName() : std::string();
				SubTextureEdit(ent, name, component);
			});

		DrawComponent<TextureAnimationComponent>("Texture Animation", entity, [](Entity ent, auto& component)
			{
				ImGui::DragFloat("Frame Time", &component.FrameTime, 0.01f, 0.01f, 10.0f);
				if (component.SubTextures.size() > 0) {
					// Clamp current frame to valid range
					if (component.CurrentFrame < 0) component.CurrentFrame = 0;
					if (component.CurrentFrame >= (int)component.SubTextures.size()) component.CurrentFrame = (int)component.SubTextures.size() - 1;
					ImGui::SliderInt("Frame Count", &component.CurrentFrame, 0, component.SubTextures.size() - 1);
				}
				else
					ImGui::Text("No frames in animation.");

				ImGui::Checkbox("Play Animation", &component.IsLooping);
				auto& stc = ent.GetOrAddComponent<SubTextureComponent>();

				std::string texName = (stc.SubTexture && stc.SubTexture->GetTexture()) ? stc.SubTexture->GetTexture()->GetName() : std::string();
				TextureAnimationEdit(texName, stc, component);
			});

		DrawComponent<ParticleSystemComponent>("Particle System", entity, [](Entity ent, auto& component)
			{
				ParticleSystem& ps = component.ParticleSystem;
				ParticleProps& psp = ps.m_Props;
				ImGui::DragFloat("Lifetime", &psp.Lifetime, 0.1f, 0.0f, 10000.0f);
				ImGui::DragFloat("Lifetime Variation", &psp.LifetimeVariation, 0.1f, 0.0f, 10000.0f);
				ImGui::Separator();

				ImGui::DragFloat("Start Size", &psp.SizeBegin, 0.1f, 0.0f, 10000.0f);
				ImGui::DragFloat("Size Variation", &psp.SizeVariation, 0.1f, 0.0f, 10000.0f);
				ImGui::DragFloat("End Size", &psp.SizeEnd, 0.1f, 0.0f, 10000.0f);
				ImGui::Separator();

				ImGui::ColorEdit4("Start Color", glm::value_ptr(psp.ColorBegin));
				ImGui::ColorEdit4("End Color", glm::value_ptr(psp.ColorEnd));
				ImGui::Separator();

				ImGui::DragFloat2("Velocity", glm::value_ptr(psp.Velocity), 0.1f);
				ImGui::DragFloat2("Velocity Variation", glm::value_ptr(psp.VelocityVariation), 0.1f);
				ImGui::DragFloat3("Position Variation", glm::value_ptr(psp.PositionVariation), 0.1f);
				ImGui::Separator();

				ImGui::DragFloat("Rotation Speed", &psp.Rotation, 0.1f, -360.0f, 360.0f);
				ImGui::DragFloat("Rotation Speed Variation", &psp.RotationVariation, 0.1f, 0.0f, 360.0f);
				ImGui::Separator();

				if (ImGui::Button("Reset System")) {
					ps.ResetSystem();
				}
				ImGui::SameLine();
				if (ImGui::Button("Emit")) {
					ps.Emit(ps.m_Props);
				}
				ImGui::SameLine();
				if (ImGui::Checkbox("Loop", &ps.m_Loop)) {

				}

			});


	}


	template<typename T>
	void SceneHierarchyPanel::DisplayAddComponentEntry(const std::string& entryName) {
		if (!m_SelectionContext.HasComponent<T>())
		{
			if (ImGui::MenuItem(entryName.c_str()))
			{
				m_SelectionContext.AddComponent<T>();
				ImGui::CloseCurrentPopup();
			}
		}
	}

}