#include "Renderer/Renderer.h"
#include "Renderer/UniformBuffer.h"

#include <glad/glad.h> //TODO: Eliminar y crear uniform buffer

namespace Core
{
	struct RendererData
	{
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<Shader> m_Shader;

		struct CameraData
		{
			glm::mat4 ViewProjection;
		};
		CameraData CameraBuffer;
		UniformBuffer* CameraUniformBuffer;
	};

	static RendererData s_RendererData;

	void Renderer::Init()
	{
		s_RendererData.CameraUniformBuffer = UniformBuffer::Create(sizeof(RendererData::CameraData), 0);

		//Vertex Array
		s_RendererData.m_VertexArray.reset(VertexArray::Create());

		//Vertex Buffer
		float vertices[4 * 7] =
		{
			-0.75f, -0.75f, 0.0f, 0.2f, 1.0f, 0.5f, 1.0f,
			 0.75f, -0.75f, 0.0f, 1.0f, 0.5f, 0.2f, 1.0f,
			 0.75f,  0.75f, 0.0f, 0.5f, 0.2f, 1.0f, 1.0f,
			-0.75f,  0.75f, 0.0f, 0.5f, 0.2f, 1.0f, 1.0f
		};

		s_RendererData.m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		//Vertex Layout
		BufferLayout layout = {
			{ ShaderDataType::vecFloat3, "a_Position", false },
			{ ShaderDataType::vecFloat4, "a_Color", false }
		};

		s_RendererData.m_VertexBuffer->SetLayout(layout);
		s_RendererData.m_VertexArray->AddVertexBuffer(s_RendererData.m_VertexBuffer);

		//Index Buffer
		unsigned int indices[6]{ 0, 1, 2, 2, 3, 0 };

		s_RendererData.m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		s_RendererData.m_VertexArray->SetIndexBuffer(s_RendererData.m_IndexBuffer);

		std::string vertexSrc = R"(
			#version 450
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			layout(std140, binding = 0) uniform Camera
			{
				mat4 u_ViewProjection;
			};

			out vec4 v_Color;			

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
				v_Color = a_Color;
			}
		)";

		std::string fragmentSrc = R"(
			#version 450
			
			layout(location = 0) out vec4 color;

			in vec4 v_Color;		

			void main()
			{
				color = v_Color;
			}
		)";

		s_RendererData.m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	void Renderer::Shutdown()
	{

	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{

	}

	void Renderer::BeginScene(const EditorCamera& camera)
	{
		s_RendererData.CameraBuffer.ViewProjection = camera.GetViewProjection();
		s_RendererData.CameraUniformBuffer->SetData(&s_RendererData.CameraBuffer, sizeof(RendererData::CameraData));
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit()
	{
		s_RendererData.m_Shader->Bind();
		s_RendererData.m_VertexArray->Bind();
		RendererCommand::DrawIndexed(s_RendererData.m_VertexArray);
	}
}
