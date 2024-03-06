#include "CorePCHeader.h"
#include "Core/Application.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Core
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(CORE_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		//Vertex Array
		m_VertexArray.reset(VertexArray::Create());

		//Vertex Buffer
		float vertices[4 * 7] =
		{
			-0.75f, -0.75f, 0.0f, 0.2f, 1.0f, 0.5f, 1.0f,
			 0.75f, -0.75f, 0.0f, 1.0f, 0.5f, 0.2f, 1.0f,
			 0.75f,  0.75f, 0.0f, 0.5f, 0.2f, 1.0f, 1.0f,
			-0.75f,  0.75f, 0.0f, 0.5f, 0.2f, 1.0f, 1.0f
		};
		
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		//Vertex Layout
		BufferLayout layout = {
			{ ShaderDataType::vecFloat3, "a_Position", false },
			{ ShaderDataType::vecFloat4, "a_Color", false }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		//Index Buffer
		unsigned int indices[6] { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec4 v_Color;			

			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
				v_Color = a_Color;
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec4 v_Color;		

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1, 0.1, 0.1, 0);
			glClear(GL_COLOR_BUFFER_BIT);

			//Shader
			m_Shader->Bind();

			//Print
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			//Run Loop
			for (auto layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (auto layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(CORE_BIND_EVENT_FN(Application::OnWindowClose));

		CORE_LOG_INFO("{0}", event.ToString());

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(event);
			if (event.IsHandled()) { break; }
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
}