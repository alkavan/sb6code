
#include <sb6.h>

GLuint create_shader_program(void)
{
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint program;

    static const GLchar * vertex_shader_source[] = {
            "#version 430 core \n"
            "void main(void) { \n"
            "const vec4 vertices[3] = vec4[3]("
            "vec4(0.25, -0.25, 0.5, 1.0),"
            "vec4(-0.25, -0.25, 0.5, 1.0),"
            "vec4(0.25, 0.25, 0.5, 1.0)); \n"
            "gl_Position = vertices[gl_VertexID];\n"
            "} \n"
    };

    static const GLchar * fragment_shader_source[] = {
            "#version 430 core \n"
            "out vec4 color; \n"
            "void main(void) { \n"
            "color = vec4(0.0, 0.8, 1.0, 1.0); \n"
            "} \n"
    };



    // Create and compile vertex shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    // Create and compile fragment shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    // Create program, attach shaders to it, and link it
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

class c2_1_app : public sb6::application
{
private:
    GLuint rendering_program;
    GLuint vertex_array_object;
public:
    void init()
    {
        static const char title[] = "c2_1_app";

        sb6::application::init();

        memcpy(info.title, title, sizeof(title));
    }

    void startup()
    {
        rendering_program = create_shader_program();
        glGenVertexArrays(1, &vertex_array_object);
        glBindVertexArray(vertex_array_object);
    }

    void render(double currentTime)
    {

        GLfloat color[] = { 0.0f, 0.2f, 0.0f, 1.0f }; // Green
        glClearBufferfv(GL_COLOR, 0, color);

        glUseProgram(rendering_program);

        //glPointSize(40.0f);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void shutdown()
    {
        glDeleteVertexArrays(1, &vertex_array_object);
        glDeleteProgram(rendering_program);
        glDeleteVertexArrays(1, &vertex_array_object);
    }
};

DECLARE_MAIN(c2_1_app)

