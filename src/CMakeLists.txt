add_executable(
	touhou_postech
	"main.cpp"
	"game.cpp"
	"player.cpp"
	"object.cpp"
	"shape.cpp"
	"boundingbox.cpp"
	"singleton.cpp"
	"physicsmanager.cpp"
 "graphicsmanager.cpp")

target_link_libraries(touhou_postech
	GLUT glew OpenGL::GL glm
)