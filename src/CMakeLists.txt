add_executable(
	touhou_postech
	"main.cpp"
	"game.cpp"
	"player.cpp"
	"enemy.cpp"
	"BBong/physicsmanager.cpp"
 	"BBong/graphicsmanager.cpp"
	"enemypatterns.cpp"
	"healthbar.cpp"
	"BBong/transform.cpp"
	"BBong/component.cpp"
	"BBong/input.cpp"
	"BBong/gameobject.cpp"
 	"BBong/renderer2d.cpp"
	"BBong/objfileloader.cpp"
	"BBong/mesh3d.cpp"
	"BBong/renderer3d.cpp"
	"BBong/mesh2d.cpp"
	"utility.cpp" 
	)
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
target_compile_definitions(
	touhou_postech PRIVATE ASSETS_DIRECTORY="${RUNTIME_ASSET_DIRECTORY}/"
)
target_compile_definitions(touhou_postech PRIVATE GLM_ENABLE_EXPERIMENTAL)

if (DEFINED BOUNDING_BOX_DEBUG)
	target_compile_definitions(touhou_postech PRIVATE BOUNDING_BOX_DEBUG)
endif()