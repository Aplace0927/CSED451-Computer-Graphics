add_executable(
	touhou_postech
	"BBong/collider3d.cpp"
	"BBong/collisionmanager.cpp"
	"BBong/component.cpp"
	"BBong/gameobject.cpp"
 	"BBong/graphicsmanager.cpp"
	"BBong/input.cpp"
	"BBong/mesh2d.cpp"
	"BBong/mesh3d.cpp"
	"BBong/objfileloader.cpp"
	"BBong/physicsmanager.cpp"
 	"BBong/renderer2d.cpp"
	"BBong/renderer3d.cpp"
	"BBong/transform.cpp"
	"enemy.cpp"
	"enemypatterns.cpp"
	"game.cpp"
	"healthbar.cpp"
	"main.cpp"
	"player.cpp"
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