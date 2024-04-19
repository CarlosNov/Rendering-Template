#include "AppLayer.h"
#include "Renderer/RendererCommand.h"

#include "Scene/Entity.h"
#include "Scene/Components.h"

#include <imgui.h>
#include <imgui_internal.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glm/gtc/type_ptr.hpp> //TODO: Pasar a subclases

namespace App
{
	AppLayer::AppLayer() : Layer("App Layer")
	{

	}

	void AppLayer::OnAttach()
	{
        Core::FramebufferSpecification fbSpec;
        fbSpec.Attachments = { Core::FramebufferTextureFormat::RGBA8,  Core::FramebufferTextureFormat::RED_INTEGER,  Core::FramebufferTextureFormat::Depth };
        fbSpec.Width = 1280;
        fbSpec.Height = 720;

        m_Framebuffer = Core::Framebuffer::Create(fbSpec);

        m_EditorCamera = Core::EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);

        /*
        //Cara 1
        Core::Entity Cara_1 = Core::Entity();
        Core::TransformComponent transformCara_1 = Core::TransformComponent();
        transformCara_1.Translation = { 0.0f, 0.0f, 0.0f };
        Cara_1.SetTransformComponent(transformCara_1);      
        Core::ColorComponent colorCara_1 = Core::ColorComponent();
        colorCara_1.Color = { 1.0f, 0.0f, 0.0f, 1.0f };
        Cara_1.SetColorComponent(colorCara_1);

        m_ActiveScene.AddEntity(Cara_1);

        //Cara 2
        Core::Entity Cara_2 = Core::Entity();
        Core::TransformComponent transformCara_2 = Core::TransformComponent();
        transformCara_2.Translation = { 0.5f, 0.0f, -0.5f };
        transformCara_2.Rotation = { 0.0f, 1.570796f, 0.0f };
        Cara_2.SetTransformComponent(transformCara_2);    
        Core::ColorComponent colorCara_2 = Core::ColorComponent();
        colorCara_2.Color = { 0.0f, 1.0f, 0.0f, 1.0f };
        Cara_2.SetColorComponent(colorCara_2);

        m_ActiveScene.AddEntity(Cara_2);

        //Cara 3
        Core::Entity Cara_3 = Core::Entity();
        Core::TransformComponent transformCara_3 = Core::TransformComponent();
        transformCara_3.Translation = { 0.0f, -0.5f, -0.5f };
        transformCara_3.Rotation = { 1.570796f, 0.0f, 0.0f };
        Cara_3.SetTransformComponent(transformCara_3);
        Core::ColorComponent colorCara_3 = Core::ColorComponent();
        colorCara_3.Color = { 0.0f, 0.0f, 1.0f, 1.0f };
        Cara_3.SetColorComponent(colorCara_3);

        m_ActiveScene.AddEntity(Cara_3);

        //Cara 4
        Core::Entity Cara_4 = Core::Entity();
        Core::TransformComponent transformCara_4 = Core::TransformComponent();
        transformCara_4.Translation = { 0.0f, 0.0f, -1.0f };
        Cara_4.SetTransformComponent(transformCara_4);
        Core::ColorComponent colorCara_4 = Core::ColorComponent();
        colorCara_4.Color = { 1.0f, 0.0f, 0.0f, 1.0f };
        Cara_4.SetColorComponent(colorCara_4);

        m_ActiveScene.AddEntity(Cara_4);

        //Cara 5
        Core::Entity Cara_5 = Core::Entity();
        Core::TransformComponent transformCara_5 = Core::TransformComponent();
        transformCara_5.Translation = { -0.5f, 0.0f, -0.5f };
        transformCara_5.Rotation = { 0.0f, -1.570796f, 0.0f };
        Cara_5.SetTransformComponent(transformCara_5);
        Core::ColorComponent colorCara_5 = Core::ColorComponent();
        colorCara_5.Color = { 0.0f, 1.0f, 0.0f, 1.0f };
        Cara_5.SetColorComponent(colorCara_5);

        m_ActiveScene.AddEntity(Cara_5);

        //Cara 6
        Core::Entity Cara_6 = Core::Entity();
        Core::TransformComponent transformCara_6 = Core::TransformComponent();
        transformCara_6.Translation = { 0.0f, 0.5f, -0.5f };
        transformCara_6.Rotation = { -1.570796f, 0.0f, 0.0f };
        Cara_6.SetTransformComponent(transformCara_6);
        Core::ColorComponent colorCara_6 = Core::ColorComponent();
        colorCara_6.Color = { 0.0f, 0.0f, 1.0f, 1.0f };
        Cara_6.SetColorComponent(colorCara_6);

        m_ActiveScene.AddEntity(Cara_6);
        */
	}

	void AppLayer::OnDetach()
	{

	}

	void AppLayer::OnUpdate()
	{
        if (Core::FramebufferSpecification spec = m_Framebuffer->GetSpecification(); m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
        {
            m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
        }     

        m_Framebuffer->Bind();
        Core::RendererCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.1, 0));
        Core::RendererCommand::Clear();

        m_EditorCamera.OnUpdate();
        m_ActiveScene.Render(m_EditorCamera);

        auto [mx, my] = ImGui::GetMousePos();
        mx -= m_ViewportBounds[0].x;
        my -= m_ViewportBounds[0].y;
        glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
        my = viewportSize.y - my;
        int mouseX = (int)mx;
        int mouseY = (int)my;

        if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
        {
            int pixelData = m_Framebuffer->ReadPixel(1, mouseX, mouseY);
            LOG_INFO(pixelData);
            if (pixelData >= 0 && pixelData <= 100) { m_HoveredEntity.SetEntityID(pixelData); }
            else { m_HoveredEntity.SetEntityID(-1); }
        }

        m_Framebuffer->Unbind();
	}

	void AppLayer::OnImGuiRender()
	{
        static bool m_bool = true;
        bool* p_open = &m_bool;

        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("DockSpace Demo", p_open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                ImGui::MenuItem("Padding", NULL, &opt_padding);
                ImGui::Separator();

                if (ImGui::MenuItem("Flag: NoDockingOverCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingOverCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingOverCentralNode; }
                if (ImGui::MenuItem("Flag: NoDockingSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingSplit; }
                if (ImGui::MenuItem("Flag: NoUndocking", "", (dockspace_flags & ImGuiDockNodeFlags_NoUndocking) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoUndocking; }
                if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
                if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
                if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
                ImGui::Separator();

                if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
                    Core::Application::GetApplication().Close();
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::Begin("Settings");

        DrawVec3Gui("Position", m_ActiveScene.GetActiveEntity().GetTransformComponent().Translation, 0.0f);
        DrawVec3Gui("Rotation", m_ActiveScene.GetActiveEntity().GetTransformComponent().Rotation, 0.0f);
        DrawVec3Gui("Scale", m_ActiveScene.GetActiveEntity().GetTransformComponent().Scale, 1.0f);

        ImGui::Spacing();

        ImGui::PushID("Color");
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, 100.0f);
        ImGui::Text("Color");
        ImGui::NextColumn();
        ImGui::ColorEdit4("Color", glm::value_ptr(m_ActiveScene.GetActiveEntity().GetColorComponent().Color));
        ImGui::PopID();
        
        ImGui::End();

        ImGui::Begin("Viewport");

        auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
        auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
        auto viewportOffset = ImGui::GetWindowPos();
        m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
        m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };
   
        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
        
        uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

        ImGui::End();

        ImGui::End();
	}

	void AppLayer::OnEvent(Core::Event& event)
	{
        m_EditorCamera.OnEvent(event);

        Core::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Core::MouseButtonPressedEvent>(CORE_BIND_EVENT_FN(AppLayer::OnMouseButtonPressed));
	}

    bool AppLayer::OnMouseButtonPressed(Core::MouseButtonPressedEvent& e)
    {
        if (e.GetMouseButton() == Core::Mouse::ButtonLeft)
        {
            if (m_ViewportHovered && m_HoveredEntity.GetEntityID() != -1)
            {
                m_ActiveScene.SetSelectedEntity(m_HoveredEntity.GetEntityID());
            }
        }
        return false;
    }

    void AppLayer::DrawVec3Gui(const std::string& label, glm::vec3& m_Values, float resetValue)
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
}