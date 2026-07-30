#include <Muto.h>
#include <App/EntryPoint.h>

#include "imgui/imgui.h"

#include "RenderAPI/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public Muto::Layer {
public:
  ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f) {
    /// Traingle Setup
    /// @todo Abstract triangle rendering into Renderer2D (Similar to QuadVertex
    /// struct) (will use this shape for boids)
    {
      m_TriangleVertexArray = Muto::VertexArray::Create();

      float triangleVertices[3 * 7] = {
          -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f, 0.5f, -0.5f, 0.0f, 0.2f,
          0.3f,  0.8f,  1.0f, 0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f,  1.0f,
      };

      Muto::Ref<Muto::VertexBuffer> vertexBuffer;
      vertexBuffer = (Muto::VertexBuffer::Create(triangleVertices,
                                                 sizeof(triangleVertices)));
      Muto::BufferLayout layout = {{Muto::ShaderDataType::Float3, "a_Position"},
                                   {Muto::ShaderDataType::Float4, "a_Color"}

      };
      vertexBuffer->SetLayout(layout);
      m_TriangleVertexArray->AddVertexBuffer(vertexBuffer);
      uint32_t indices[3] = {0, 1, 2};
      Muto::Ref<Muto::IndexBuffer> indexBuffer;
      indexBuffer = (Muto::IndexBuffer::Create(indices, sizeof(indices) /
                                                            sizeof(uint32_t)));
      m_TriangleVertexArray->SetIndexBuffer(indexBuffer);

      std::string triangleVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
			)";

      std::string triangleFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
			)";

      m_Shader = Muto::Shader::Create("VertexPosColor", triangleVertexSrc,
                                      triangleFragmentSrc);
    }

    m_SquareVA = Muto::VertexArray::Create();
    float squareVertices[5 * 4] = {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, -0.5f,
                                   0.0f,  1.0f,  0.0f, 0.5f, 0.5f, 0.0f, 1.0f,
                                   1.0f,  -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};

    Muto::Ref<Muto::VertexBuffer> squareVB;
    squareVB =
        (Muto::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({{Muto::ShaderDataType::Float3, "a_Position"},
                         {Muto::ShaderDataType::Float2, "a_TexCoord"}});
    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
    Muto::Ref<Muto::IndexBuffer> squareIB;
    squareIB = (Muto::IndexBuffer::Create(squareIndices, sizeof(squareIndices) /
                                                             sizeof(uint32_t)));
    m_SquareVA->SetIndexBuffer(squareIB);

    std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

    std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

    m_FlatColorShader = (Muto::Shader::Create("FlatColor", blueShaderVertexSrc,
                                              flatColorShaderFragmentSrc));
  }

  void OnUpdate(Muto::Timestep ts) override {
    // Update
    m_CameraController.OnUpdate(ts);

    // Render
    Muto::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Muto::RenderCommand::Clear();

    Muto::Renderer::BeginScene(m_CameraController.GetCamera());
    // Squares
    static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
    std::dynamic_pointer_cast<Muto::OpenGLShader>(m_FlatColorShader)->Bind();
    std::dynamic_pointer_cast<Muto::OpenGLShader>(m_FlatColorShader)
        ->UploadUniformFloat3("u_Color", m_SquareColor);
    for (int y = 0; y < 20; y++) {
      for (int x = 0; x < 20; x++) {
        glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
        Muto::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
      }
    }
    // Triangle
    Muto::Renderer::Submit(m_Shader, m_TriangleVertexArray);
    Muto::Renderer::EndScene();
  }

  void OnImGuiRender() override {}

  void OnEvent(Muto::Event &e) override { m_CameraController.OnEvent(e); }

private:
  Muto::Ref<Muto::Shader> m_Shader;
  Muto::Ref<Muto::VertexArray> m_TriangleVertexArray;
  Muto::Ref<Muto::Shader> m_FlatColorShader;
  Muto::Ref<Muto::VertexArray> m_SquareVA;
  Muto::OrthographicCameraController m_CameraController;
  glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};

class SandboxApp : public Muto::Application {
public:
  SandboxApp() {

    PushLayer(new Sandbox2D());
    // PushLayer(new ExampleLayer());
  }
  ~SandboxApp() {}
};

Muto::Application *Muto::CreateApplication() { return new SandboxApp(); }