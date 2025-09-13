#include "player.hpp"

Player::Player::Player()
    : Object::Object(
        // Center at origin
        std::array<float, 3>{0.0f, -0.5f, 0.0f}, 
        Shape::Shape<float, 3, Shape::RGBColor>(    
            // subshapes: vector of subshapes, each subshape is a vector of vertices
            std::vector<std::vector<std::array<float, 3>>>{
                {
                    {0.0f, 0.05f, 0.0f},
                    {-0.1f, -0.05f, 0.0f},
                    {0.1f, -0.05f, 0.0f}
                }
            },
            // colors: vector of color sets, each set is a vector of colors for the subshape
            std::vector<std::vector<Shape::RGBColor>>{
                {
                    {1.0f, 1.0f, 0.0f},
                    {0.0f, 1.0f, 1.0f},
                    {1.0f, 0.0f, 1.0f}
                }
            },
            // drawMethod: vector of draw methods for each subshape
            std::vector<unsigned int>{ GL_TRIANGLES }
        )
    ),
    playerHealth(5)
{
    // Initialize other player state variables here if needed
}