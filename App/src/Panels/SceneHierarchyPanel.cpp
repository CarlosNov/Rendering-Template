#include "AppLayer.h"
#include "Renderer/RendererCommand.h"

#include "Scene/Components.h"

#include <imgui.h>
#include <imgui_internal.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace App
{
	void SceneHierarchyPanel::SetScene(Core::Scene* scene)
	{
		m_Scene = scene;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		if (m_Scene)
		{
			DrawSceneNode();

			if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			{
				m_SelectedNode = -1;
				m_SelectedEntity = {};
				m_Scene->SetActiveEntity({});
			}
				

			// Right-click on blank space
			if (ImGui::BeginPopupContextWindow(0, 1))
			{
				if (ImGui::MenuItem("Create Empty Entity"))
				{

				}
					//m_Scene->CreateEntity("Empty Entity");

				ImGui::EndPopup();
			}
		}

		ImGui::End();

		ImGui::Begin("Properties");

		if (m_SelectedEntity)
		{
			DrawComponents(m_Scene->GetEntityByID(m_SelectedEntity.GetEntityID()));
		}

		ImGui::End();
	}

	static void DrawVec3Gui(const std::string& label, glm::vec3& m_Values, float resetValue = 0.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 100.0f);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			m_Values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &m_Values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			m_Values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &m_Values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			m_Values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &m_Values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);
		ImGui::PopID();
	}

	void SceneHierarchyPanel::DrawSceneNode()
	{
		auto name = "Scene";

		ImGuiTreeNodeFlags flags = ((m_SelectedNode == 0) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
		
		bool opened = ImGui::TreeNodeEx((void*)0, flags, name);

		if (ImGui::IsItemClicked())
		{
			m_SelectedNode = 0;
		}
		if (opened)
		{
			for (auto& entity : m_Scene->GetRegistry())
			{
				DrawEntityNode(entity);
			}
			ImGui::TreePop();
		}
	}

	void SceneHierarchyPanel::DrawEntityNode(Core::Entity& entity)
	{
		auto& tag = entity.GetTagComponent().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectedNode == entity.GetEntityID() + 2) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)(entity.GetEntityID()+2), flags, tag.c_str());

		if (ImGui::IsItemClicked())
		{
			m_SelectedNode = entity.GetEntityID() + 2;
			m_SelectedEntity = entity;
			m_Scene->SetActiveEntity(entity.GetEntityID());
		}

		if (opened)
		{
			ImGui::TreePop();
		}

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;

			ImGui::EndPopup();
		}

		if (entityDeleted)
		{
			/*
			m_Scene->DestroyEntity(entity);
			if (m_SelectedEntity == entity)
				m_SelectedEntity = {};
			*/
		}
	}

	void SceneHierarchyPanel::DrawComponents(Core::Entity& entity)
	{
		if (entity.HasTagComponent())
		{
			auto& tag = entity.GetTagComponent().Tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strncpy_s(buffer, sizeof(buffer), tag.c_str(), sizeof(buffer));
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-1);

		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponent");

		if (ImGui::BeginPopup("AddComponent"))
		{
			DisplayAddComponentEntry<Core::TransformComponent>("Transform");

			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();

		DrawComponent<Core::TransformComponent>("Transform", entity, [](Core::Entity& entity)
		{
			DrawVec3Gui("Position", entity.GetTransformComponent().Translation, 0.0f);
			DrawVec3Gui("Rotation", entity.GetTransformComponent().Rotation, 0.0f);
			DrawVec3Gui("Scale", entity.GetTransformComponent().Scale, 1.0f);
		});
		/*
		ImGui::Spacing();

		ImGui::PushID("Color");
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 100.0f);
		ImGui::Text("Color");
		ImGui::NextColumn();
		ImGui::ColorEdit4("Color", glm::value_ptr(m_ActiveScene.GetActiveEntity().GetColorComponent().Color));
		ImGui::PopID();
		*/
	}

	template<typename T>
	void SceneHierarchyPanel::DisplayAddComponentEntry(const std::string& entryName) {
		if (std::is_same<T,Core::TransformComponent>::value)
		{
			if (ImGui::MenuItem(entryName.c_str()))
			{
				//m_SelectionContext.AddComponent<T>();

				ImGui::CloseCurrentPopup();
			}
		}
	}

	template<typename T, typename F>
	void SceneHierarchyPanel::DrawComponent(const std::string& name, Core::Entity& entity, F Function)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
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
			Function(entity);
			ImGui::TreePop();
		}

		if (removeComponent)
		{

		}
	}
}