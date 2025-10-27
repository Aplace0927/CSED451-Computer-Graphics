add_executable(
	touhou_postech
	"main.cpp"
	"game.cpp"
	"player.cpp"
	"enemy.cpp"
	"physicsmanager.cpp"
 	"graphicsmanager.cpp"
	"enemypatterns.cpp"
	"healthbar.cpp"
	"transform.cpp"
	"component.cpp"
 "input.cpp")
if (UNIX AND NOT APPLE)
	target_link_libraries(touhou_postech
		GLUT glew OpenGL::GL glm glu
	)
else()
	target_link_libraries(touhou_postech
		GLUT glew OpenGL::GL glm
	)
endif()

# Allow experimental GLM extensions used in the project
target_compile_definitions(touhou_postech PRIVATE GLM_ENABLE_EXPERIMENTAL)

if (DEFINED BOUNDING_BOX_DEBUG)
	target_compile_definitions(touhou_postech PRIVATE BOUNDING_BOX_DEBUG)
endif()