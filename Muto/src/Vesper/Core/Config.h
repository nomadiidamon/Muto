#pragma once
/// @file Config.h
/// @author Damon S. Green II
/// @brief Configuration macros for the Vesper engine and editor.
/// @todo: Implement Default Graphics API


/// Editor Configurations
#ifdef VZ_EDITOR_USE_DEFAULT_SCENE 
#define VZ_EDITOR_DEFAULT_SCENE "../../Resources/Scenes/TriColored3DCubeAndSpriteAnims.vesper"
#endif

#define VZ_DEFAULT_TEXTURE Texture2D::Create("../../Resources/Textures/Checkerboard.png")

