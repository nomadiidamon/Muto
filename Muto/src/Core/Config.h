#pragma once
/// @file Config.h
/// @author Damon S. Green II
/// @brief Configuration macros for the Muto engine and editor.
/// @todo: Implement Default Graphics API


/// Editor Configurations
#ifdef MU_EDITOR_USE_DEFAULT_SCENE 
#define MU_EDITOR_DEFAULT_SCENE "../../Resources/Scenes/TriColored3DCubeAndSpriteAnims.vesper"
#endif

#define MU_DEFAULT_TEXTURE Texture2D::Create("../../Resources/Textures/Checkerboard.png")

