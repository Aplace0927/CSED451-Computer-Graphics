add_executable(
	hello_opengl
	"hello_opengl.cpp"
)

target_link_libraries(hello_opengl
	GLUT glew OpenGL::GL glm
)