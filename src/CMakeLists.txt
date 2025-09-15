add_executable(
	touhou_postech
	"main.cpp"
	"game.cpp"
	"player.cpp"
	"enemy.cpp"
	"object.cpp"
	"shape.cpp"
	"bullet.cpp"
	"boundingbox.cpp"
)

target_link_libraries(touhou_postech
	GLUT glew OpenGL::GL glm
)