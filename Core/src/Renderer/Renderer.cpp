#include "Renderer/Renderer.h"
#include "Renderer/UniformBuffer.h"

#include <glad/glad.h>

namespace Core
{
	struct RectVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		int EntityID;
	};

	struct CircleVertex
	{
		glm::vec3 Position;
		glm::vec3 LocalPosition;
		glm::vec4 Color;
		int EntityID;
	};

	struct RendererData
	{
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;

		std::shared_ptr<VertexArray> RectVertexArray;
		std::shared_ptr<VertexBuffer> RectVertexBuffer;
		std::shared_ptr<Shader> RectShader;

		std::shared_ptr<VertexArray> CircleVertexArray;
		std::shared_ptr<VertexBuffer> CircleVertexBuffer;
		std::shared_ptr<Shader> CircleShader;

		uint32_t RectIndexCount = 0;
		RectVertex* RectVertexBufferInitial = nullptr;
		RectVertex* RectVertexBufferPtr = nullptr;

		uint32_t CircleIndexCount = 0;
		CircleVertex* CircleVertexBufferInitial = nullptr;
		CircleVertex* CircleVertexBufferPtr = nullptr;

		glm::vec4 VertexPositions[4];

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
		RendererCommand::Init();

		//Vertex Array
		s_RendererData.RectVertexArray = VertexArray::Create();

		//Vertex Buffer
		s_RendererData.RectVertexBuffer = VertexBuffer::Create(s_RendererData.MaxVertices * sizeof(RectVertex));

		//Vertex Layout
		s_RendererData.RectVertexBuffer->SetLayout({
			{ ShaderDataType::vecFloat3, "a_Position", false },
			{ ShaderDataType::vecFloat4, "a_Color", false },
			{ ShaderDataType::vecInt, "a_EntityID", false}
		});

		s_RendererData.RectVertexArray->AddVertexBuffer(s_RendererData.RectVertexBuffer);

		//Initialice VertexBuffer
		s_RendererData.RectVertexBufferInitial = new RectVertex[s_RendererData.MaxVertices];
		
		//Index Buffer
		uint32_t* rectIndices = new uint32_t[s_RendererData.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_RendererData.MaxIndices; i += 6)
		{
			rectIndices[i + 0] = offset + 0;
			rectIndices[i + 1] = offset + 1;
			rectIndices[i + 2] = offset + 2;

			rectIndices[i + 3] = offset + 2;
			rectIndices[i + 4] = offset + 3;
			rectIndices[i + 5] = offset + 0;

			offset += 4;
		}

		s_RendererData.RectVertexArray->SetIndexBuffer(IndexBuffer::Create(rectIndices, s_RendererData.MaxIndices));
		delete[] rectIndices;

		std::string RectVertexSrc = R"(
			#version 450 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			layout(location = 2) in int a_EntityID;

			layout(std140, binding = 0) uniform Camera
			{
				mat4 u_ViewProjection;
			};

			struct VertexOutput
			{
				vec4 Color;
			};

			layout (location = 0) out VertexOutput Output;
			layout (location = 1) out flat int v_EntityID;


			void main()
			{
				Output.Color = a_Color;
				v_EntityID = a_EntityID;

				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string RectFragmentSrc = R"(
			#version 450 core

			layout(location = 0) out vec4 o_Color;
			layout(location = 1) out int o_EntityID;

			struct VertexOutput
			{
				vec4 Color;
			};

			layout (location = 0) in VertexOutput Input;
			layout (location = 1) in flat int v_EntityID;

			void main()
			{
				vec4 texColor = Input.Color;

				if (texColor.a == 0.0)
					discard;

				o_Color = texColor;
				o_EntityID = v_EntityID;
			}
		)";

		std::string circleVertexSrc = R"(
			#version 450 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			layout(location = 2) in vec3 a_LocalPosition;

			layout(std140, binding = 0) uniform Camera
			{
				mat4 u_ViewProjection;
			};

			struct VertexOutput
			{
				vec3 LocalPosition;
				vec4 Color;
			};

			layout (location = 0) out VertexOutput Output;

			void main()
			{
				Output.LocalPosition = a_LocalPosition;
				Output.Color = a_Color;

				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string circleFragmentSrc = R"(
			#version 450 core

			layout(location = 0) out vec4 o_Color;

			struct VertexOutput
			{
				vec3 LocalPosition;
				vec4 Color;
			};

			layout (location = 0) in VertexOutput Input;

			void main()
			{
				float fade = 0.01;
				float thickness = 1.0;

				// Calculate distance and fill circle with white
				float distance = 1.0 - length(Input.LocalPosition);
				float circle = smoothstep(0.0, fade, distance);
				circle *= smoothstep(thickness + fade, thickness, distance);

				if (circle == 0.0)
					discard;

				// Set output color
				o_Color = Input.Color;
				o_Color.a *= circle;
			}
		)";

		//s_RendererData.m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
		s_RendererData.RectShader.reset(new Shader(RectVertexSrc, RectFragmentSrc));

		s_RendererData.VertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_RendererData.VertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		s_RendererData.VertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		s_RendererData.VertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		s_RendererData.CameraUniformBuffer = UniformBuffer::Create(sizeof(RendererData::CameraData), 0);
	}

	void Renderer::Shutdown()
	{
		delete[] s_RendererData.RectVertexBufferInitial;
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{

	}

	void Renderer::BeginScene(const EditorCamera& camera)
	{
		s_RendererData.CameraBuffer.ViewProjection = camera.GetViewProjection();
		s_RendererData.CameraUniformBuffer->SetData(&s_RendererData.CameraBuffer, sizeof(RendererData::CameraData));

		StartBatch();
	}

	void Renderer::EndScene()
	{
		Flush();
	}

	void Renderer::StartBatch()
	{
		s_RendererData.RectIndexCount = 0;
		s_RendererData.RectVertexBufferPtr = s_RendererData.RectVertexBufferInitial;

		s_RendererData.CircleIndexCount = 0;
		s_RendererData.CircleVertexBufferPtr = s_RendererData.CircleVertexBufferInitial;
	}

	void Renderer::Flush()
	{
		if (s_RendererData.RectIndexCount)
		{
			uint32_t vertexSize = (uint32_t) ((uint8_t*) s_RendererData.RectVertexBufferPtr - (uint8_t*) s_RendererData.RectVertexBufferInitial);
			s_RendererData.RectVertexBuffer->SetData(s_RendererData.RectVertexBufferInitial, vertexSize);

			s_RendererData.RectShader->Bind();
			s_RendererData.RectVertexArray->Bind();
			RendererCommand::DrawIndexed(s_RendererData.RectVertexArray);
		}
	}

	void Renderer::DrawRect(const glm::vec2& position, const glm::vec3& size, const glm::vec4& color)
	{
		DrawRect({ position.x, position.y, 0.0f}, size, color);
	}

	void Renderer::DrawRect(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), size);

		DrawRect(transform, color);
	}

	void Renderer::DrawRect(const glm::mat4& transform, const glm::vec4& color, uint32_t entityID)
	{
		if (s_RendererData.RectIndexCount >= RendererData::MaxIndices)
		{
			Flush();
			StartBatch();
		}

		for(uint32_t i = 0; i < 4; i++)
		{
			s_RendererData.RectVertexBufferPtr->Position = transform * s_RendererData.VertexPositions[i];
			s_RendererData.RectVertexBufferPtr->Color = color;
			s_RendererData.RectVertexBufferPtr->EntityID = entityID;
			s_RendererData.RectVertexBufferPtr++;
		}
		s_RendererData.RectIndexCount += 6;
	}
}
