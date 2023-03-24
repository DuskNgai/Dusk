#include <dusk/assert.hpp>
#include <dusk/log.hpp>
#include <dusk/core/window/window.hpp>

DUSK_NAMESPACE_BEGIN

static std::size_t s_glfw_window_count{ 0 };

Window::Window(WindowProps const& props) {
    this->init(props);
}

Window::~Window() {
    this->shut_down();
}

uint32_t Window::get_width() const { return this->m_data.m_props.m_width; }

uint32_t Window::get_height() const { return this->m_data.m_props.m_height; }

void* Window::get_window_raw_ptr() const { return this->m_window; }

void Window::set_event_callback(EventCallbackFunc callback) { this->m_data.m_callback = callback; }

void Window::set_vert_sync(bool enabled) {
    if (enabled) {
        glfwSwapInterval(1);
    }
    else {
        glfwSwapInterval(0);
    }
    this->m_data.m_vert_sync = enabled;
}

bool Window::is_vert_sync() const {
    return this->m_data.m_vert_sync;
}

void Window::on_update() {
    glfwPollEvents();
    this->m_context->swap_buffers();
}

void Window::init(WindowProps const& props) {
    this->m_data.m_props = props;

    DUSK_CORE_INFO(
        "Created a [{:d} x {:d}] window with title \"{:s}\".",
        this->m_data.m_props.m_width, this->m_data.m_props.m_height, this->m_data.m_props.m_title
    );

    if (s_glfw_window_count == 0) {
        DUSK_CORE_ASSERT(glfwInit(), "Failed to initialize GLFW.");
        glfwSetErrorCallback(
            [](int error, char const* description) {
                DUSK_CORE_ERROR("Dusk GLFW Error {:d}: {:s}\n", error, description);
            }
        );
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    this->m_window = glfwCreateWindow(
        static_cast<int>(this->m_data.m_props.m_width),
        static_cast<int>(this->m_data.m_props.m_height),
        this->m_data.m_props.m_title.c_str(), nullptr, nullptr
    );
    ++s_glfw_window_count;

    this->m_context = GraphicsContext::create(this->m_window);
    this->m_context->init();

    this->set_vert_sync(true);

    // Set GLFW callbacks
    glfwSetWindowUserPointer(this->m_window, &this->m_data);
    glfwSetWindowSizeCallback(this->m_window, [](GLFWwindow* window, int width, int height) {
        WindowData* data{ (WindowData*)glfwGetWindowUserPointer(window) };
        data->m_props.m_width = width;
        data->m_props.m_height = height;

        WindowResizeEvent e(width, height);
        data->m_callback(e);
    });

    glfwSetWindowCloseCallback(this->m_window, [](GLFWwindow* window) {
        WindowData* data{ (WindowData*)glfwGetWindowUserPointer(window) };
        WindowCloseEvent e;
        data->m_callback(e);
    });

    glfwSetKeyCallback(this->m_window, [](GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods) {
        WindowData* data{ (WindowData*)glfwGetWindowUserPointer(window) };

        switch (action) {
            case GLFW_PRESS: {
                KeyPressedEvent e(static_cast<KeyCode>(key), false);
                data->m_callback(e);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleasedEvent e(static_cast<KeyCode>(key));
                data->m_callback(e);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressedEvent e(static_cast<KeyCode>(key), true);
                data->m_callback(e);
                break;
            }
        }
    });

    glfwSetCharCallback(this->m_window, [](GLFWwindow* window, unsigned codepoint) {
        WindowData* data{ (WindowData*)glfwGetWindowUserPointer(window) };

        KeyTypedEvent e(static_cast<KeyCode>(codepoint));
        data->m_callback(e);
    });

    glfwSetMouseButtonCallback(this->m_window, [](GLFWwindow* window, int button, int action, [[maybe_unused]] int mods) {
        WindowData* data{ (WindowData*)glfwGetWindowUserPointer(window) };

        switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent e(static_cast<MouseCode>(button));
                data->m_callback(e);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent e(static_cast<MouseCode>(button));
                data->m_callback(e);
                break;
            }
        }
    });

    glfwSetScrollCallback(this->m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
        WindowData* data{ (WindowData*)glfwGetWindowUserPointer(window) };

        MouseScrolledEvent e(static_cast<float>(xoffset), static_cast<float>(yoffset));
        data->m_callback(e);
    });

    glfwSetCursorPosCallback(this->m_window, [](GLFWwindow* window, double xpos, double ypos) {
        WindowData* data{ (WindowData*)glfwGetWindowUserPointer(window) };

        MouseMovedEvent e(
            static_cast<float>(xpos), static_cast<float>(ypos),
            static_cast<float>(data->m_props.m_width), static_cast<float>(data->m_props.m_height)
        );
        data->m_callback(e);
    });
}

void Window::shut_down() {
    glfwDestroyWindow(this->m_window);
    --s_glfw_window_count;

    if (s_glfw_window_count == 0) {
        glfwTerminate();
    }
}

DUSK_NAMESPACE_END
