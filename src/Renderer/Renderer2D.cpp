#include <Dusk/Renderer/Renderer2D.hpp>
#include <Dusk/Renderer/RenderCommand.hpp>
#include <Dusk/Utils/Utils.hpp>
#include <Dusk/Log.hpp>

DUSK_NAMESPACE_BEGIN

std::unique_ptr<Renderer2D::Renderer2DData> Renderer2D::Renderer2D::s_data = std::make_unique<Renderer2D::Renderer2DData>();

void Renderer2D::Init() {
    Renderer2D::s_data->quad_vertex_array = VertexArray::Create();

    // A square/quad that can be reused.
    {
        // Actual cpu vertex buffer.
        Renderer2D::s_data->quad_vertex_buffer_cpu.reserve(__detail::RENDERER2D_VERTICES_BUFFER_SIZE);
        // Dynamic vertex buffer.
        Renderer2D::s_data->quad_vertex_buffer = VertexBuffer::Create(__detail::RENDERER2D_VERTICES_BUFFER_SIZE * sizeof(Renderer2D::QuadVertex));
        Renderer2D::s_data->quad_vertex_buffer->SetLayout(BufferLayout({
            { ShaderDataType::Vec3,    "a_Position"},
            { ShaderDataType::Vec4,       "a_Color"},
            { ShaderDataType::Vec2,    "a_TexCoord"},
            {ShaderDataType::Float,    "a_TexIndex"},
            {ShaderDataType::Float, "a_TilingScale"}
        }));
        Renderer2D::s_data->quad_vertex_array->AddVertexBuffer(Renderer2D::s_data->quad_vertex_buffer);

        // Actual cpu index buffer.
        Renderer2D::s_data->quad_index_buffer_cpu.reserve(__detail::RENDERER2D_INDICES_BUFFER_SIZE);
        //! Every quad should follow this indexing format.
        {
            // 3------2
            // |      |
            // |      |
            // 0------1
            uint32_t offset = 0;
            for (uint32_t i = 0; i < __detail::RENDERER2D_QUADS_BUFFER_SIZE; ++i) {
                Renderer2D::s_data->quad_index_buffer_cpu.push_back(offset + 0);
                Renderer2D::s_data->quad_index_buffer_cpu.push_back(offset + 1);
                Renderer2D::s_data->quad_index_buffer_cpu.push_back(offset + 2);

                Renderer2D::s_data->quad_index_buffer_cpu.push_back(offset + 0);
                Renderer2D::s_data->quad_index_buffer_cpu.push_back(offset + 2);
                Renderer2D::s_data->quad_index_buffer_cpu.push_back(offset + 3);

                offset += 4;
            }
        }
        // Index buffer.
        auto square_index_buffer = IndexBuffer::Create(__detail::RENDERER2D_INDICES_BUFFER_SIZE, Renderer2D::s_data->quad_index_buffer_cpu.data());
        Renderer2D::s_data->quad_vertex_array->SetIndexBuffer(square_index_buffer);
    }
    // Read shader file.
    {
        Renderer2D::s_data->texture_shader = Shader::Create(
            ReadTextFile(GetFilePath("assets/shaders/BatchTextureVertexShader.glsl")),
            ReadTextFile(GetFilePath("assets/shaders/BatchTextureFragmentShader.glsl"))
        );
        Renderer2D::s_data->texture_shader->Bind();
        auto sampler = IntegerSequenceToArray(std::make_integer_sequence<int, __detail::RENDERER2D_TEXTURE_SLOTS_SIZE>{});
        Renderer2D::s_data->texture_shader->SetIntArray("u_Textures", sampler.data(), __detail::RENDERER2D_TEXTURE_SLOTS_SIZE);
    }
    // Texture
    {
        // Assign space for actual cpu texture slots.
        Renderer2D::s_data->texture_slots_cpu.reserve(__detail::RENDERER2D_TEXTURE_SLOTS_SIZE);
        // Only a small white texture is enough.
        Renderer2D::s_data->white_texture = Texture2D::Create(1, 1);
        // ABGR, reverse of RGBA, little endian.
        uint32_t white_texture_data{0xffffffff};
        Renderer2D::s_data->white_texture->SetData(&white_texture_data);
        // Texture slot 0 is reserved for white texture.
        Renderer2D::s_data->texture_slots_cpu.push_back(Renderer2D::s_data->white_texture);
    }
}

void Renderer2D::Shutdown() {
    // Free all.
    Renderer2D::s_data.reset();
}

void Renderer2D::BeginScene(Camera* camera) {
    // Camera settings.
    auto vp = camera->GetProjectionMatrix() * camera->GetViewMatrix();
    Renderer2D::s_data->texture_shader->Bind();
    Renderer2D::s_data->texture_shader->SetMat4("u_ViewProjection", vp);

    Renderer2D::StartBatch();
}

void Renderer2D::EndScene() {
    Renderer2D::Flush();
}

void Renderer2D::Flush() {
    // Bind all the textures.
    for (std::size_t i = 0; i < Renderer2D::s_data->texture_slots_cpu.size(); ++i) {
        Renderer2D::s_data->texture_slots_cpu[i]->Bind(i);
    }

    // Upload cpu data to gpu.
    Renderer2D::s_data->quad_vertex_buffer->SetData(
        static_cast<uint32_t>(Renderer2D::s_data->quad_vertex_buffer_cpu.size()) * sizeof(Renderer2D::QuadVertex),
        reinterpret_cast<float*>(Renderer2D::s_data->quad_vertex_buffer_cpu.data())
    );
    // Specify the index.
    RenderCommand::DrawElements(
        Renderer2D::s_data->quad_vertex_array.get(),
        static_cast<uint32_t>(Renderer2D::s_data->quad_vertex_buffer_cpu.size() / 4 * 6)
    );
}

void Renderer2D::StartBatch() {
    // Clear the cpu vertex buffer. Prepare for the next batch.
    Renderer2D::s_data->quad_vertex_buffer_cpu.clear();
    Renderer2D::s_data->texture_slots_cpu.erase(
        Renderer2D::s_data->texture_slots_cpu.begin() + 1,
        Renderer2D::s_data->texture_slots_cpu.end()
    );
}

void Renderer2D::NextBatch() {
    Renderer2D::Flush();
    Renderer2D::StartBatch();
}

void Renderer2D::DrawQuad(glm::vec2 const& position, glm::vec2 const& size, glm::vec4 const& color) {
    // Dispatch to the 3D version of the function.
    Renderer2D::DrawQuad(glm::vec3(position, 0.0f), size, color);
}

void Renderer2D::DrawQuad(glm::vec3 const& position, glm::vec2 const& size, glm::vec4 const& color) {
    // First scaling, then rotation, then translation.
    glm::mat4 model = glm::translate(glm::mat4{1.0f}, position) * glm::rotate(glm::mat4{1.0f}, 0.0f, {0.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), {size, 1.0f});
    // Dispatch to the matrix version of the function.
    Renderer2D::DrawQuad(model, color);
}

void Renderer2D::DrawQuad(glm::vec2 const& position, glm::vec2 const& size, std::shared_ptr<Texture> const& texture, float tiling_scale, glm::vec4 const& tint_color) {
    // Dispatch to the 3D version of the function.
    Renderer2D::DrawQuad(glm::vec3(position, 0.0f), size, texture, tiling_scale, tint_color);
}

void Renderer2D::DrawQuad(glm::vec3 const& position, glm::vec2 const& size, std::shared_ptr<Texture> const& texture, float tiling_scale, glm::vec4 const& tint_color) {
    // First scaling, then rotation, then translation.
    glm::mat4 model = glm::translate(glm::mat4{1.0f}, position) * glm::rotate(glm::mat4{1.0f}, 0.0f, {0.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), {size, 1.0f});
    // Dispatch to the matrix version of the function.
    Renderer2D::DrawQuad(model, texture, tiling_scale, tint_color);
}

void Renderer2D::DrawRotatedQuad(glm::vec2 const& position, glm::vec2 const& size, float radians, glm::vec4 const& color) {
    // Dispatch to the 3D version of the function.
    Renderer2D::DrawRotatedQuad(glm::vec3(position, 0.0f), size, radians, color);
}

void Renderer2D::DrawRotatedQuad(glm::vec3 const& position, glm::vec2 const& size, float radians, glm::vec4 const& color) {
    // First scaling, then rotation, then translation.
    glm::mat4 model = glm::translate(glm::mat4{1.0f}, position) * glm::rotate(glm::mat4{1.0f}, radians, {0.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), {size, 1.0f});
    // Dispatch to the matrix version of the function.
    Renderer2D::DrawQuad(model, color);
}

void Renderer2D::DrawRotatedQuad(glm::vec2 const& position, glm::vec2 const& size, float radians, std::shared_ptr<Texture> const& texture, float tiling_scale, glm::vec4 const& tint_color) {
    // Dispatch to the 3D version of the function.
    Renderer2D::DrawRotatedQuad(glm::vec3(position, 0.0f), size, radians, texture, tiling_scale, tint_color);
}

void Renderer2D::DrawRotatedQuad(glm::vec3 const& position, glm::vec2 const& size, float radians, std::shared_ptr<Texture> const& texture, float tiling_scale, glm::vec4 const& tint_color) {
    // First scaling, then rotation, then translation.
    glm::mat4 model = glm::translate(glm::mat4{1.0f}, position) * glm::rotate(glm::mat4{1.0f}, radians, {0.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), {size, 1.0f});
    // Dispatch to the matrix version of the function.
    Renderer2D::DrawQuad(model, texture, tiling_scale, tint_color);
}

void Renderer2D::DrawQuad(glm::mat4 const& model, glm::vec4 const& color) {
    if (Renderer2D::s_data->quad_vertex_buffer_cpu.size() >= __detail::RENDERER2D_VERTICES_BUFFER_SIZE) {
        Renderer2D::NextBatch();
    }

    // clang-format off
    // Fill the quad vertex buffer.
    for (uint32_t i = 0; i < __detail::RENDERER2D_QUADS_VERTICES_COUNT; ++i) {
        Renderer2D::s_data->quad_vertex_buffer_cpu.push_back({
            model * __detail::RENDERER2D_VERTICES[i], color, __detail::RENDERER2D_UVS[i], __detail::RENDERER2D_TEXTURE_INDEX, __detail::RENDERER2D_TILING_SCALE
        });
    }
    // clang-format on

    //! BUG
    // Set uniform variables in shader.
    Renderer2D::s_data->texture_shader->Bind();
    Renderer2D::s_data->texture_shader->SetVec4("u_Color", __detail::RENDERER2D_TINT_COLOR);
}

void Renderer2D::DrawQuad(glm::mat4 const& model, std::shared_ptr<Texture> const& texture, float tiling_scale, glm::vec4 const& tint_color) {
    if (Renderer2D::s_data->quad_vertex_buffer_cpu.size() >= __detail::RENDERER2D_VERTICES_BUFFER_SIZE) {
        Renderer2D::NextBatch();
    }

    float texture_index{0.0f};
    // Check if we had submit the texture before;
    for (std::size_t i = 1; i < Renderer2D::s_data->texture_slots_cpu.size(); ++i) {
        if (Renderer2D::s_data->texture_slots_cpu[i]->GetTextureID() == texture->GetTextureID()) {
            texture_index = static_cast<float>(i);
            break;
        }
    }
    // If not, submit it.
    if (texture_index == 0.0f) {
        if (Renderer2D::s_data->texture_slots_cpu.size() >= __detail::RENDERER2D_TEXTURE_SLOTS_SIZE) {
            Renderer2D::NextBatch();
        }
        texture_index = static_cast<float>(Renderer2D::s_data->texture_slots_cpu.size());
        Renderer2D::s_data->texture_slots_cpu.push_back(texture);
    }

    // clang-format off
    // Fill the quad vertex buffer.
    for (uint32_t i = 0; i < __detail::RENDERER2D_QUADS_VERTICES_COUNT; ++i) {
        Renderer2D::s_data->quad_vertex_buffer_cpu.push_back({
            model * __detail::RENDERER2D_VERTICES[i], __detail::RENDERER2D_COLOR, __detail::RENDERER2D_UVS[i], texture_index, tiling_scale
        });
    }
    // clang-format on

    //! BUG
    // Set uniform variables in shader.
    Renderer2D::s_data->texture_shader->Bind();
    Renderer2D::s_data->texture_shader->SetVec4("u_Color", tint_color);
}

DUSK_NAMESPACE_END
