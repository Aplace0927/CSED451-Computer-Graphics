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
	"singleton.cpp"
	"physicsmanager.cpp"
 	"graphicsmanager.cpp"
	"objectpool.cpp"
	"enemypatterns.cpp"
)

target_link_libraries(touhou_postech
	GLUT glew OpenGL::GL glm
)

if (DEFINED BOUNDING_BOX_DEBUG)
	target_compile_definitions(touhou_postech PRIVATE BOUNDING_BOX_DEBUG)
endif()