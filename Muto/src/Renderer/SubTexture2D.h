#pragma once
/// @file SubTexture2D.h
/// @author Damon S. Green II
/// @brief Defines the SubTexture2D class, which represents a sub-region of a 2D texture, useful for sprite sheets.
/// @note The SubTexture2D class allows for easy creation of sub-textures from a larger texture, and provides access to the underlying texture and its texture coordinates.

#include <glm/glm.hpp>
#include "Texture.h"


namespace Muto {

	/// @class SubTexture2D
	/// @brief Represents a sub-region of a 2D texture, useful for sprite sheets.
	class SubTexture2D 
	{
	public:
		/// @brief Constructs a SubTexture2D from the given texture and texture coordinates.
		///
		/// @param texture The texture from which the sub-texture is derived.
		/// @param min The minimum texture coordinates (bottom-left).
		/// @param max The maximum texture coordinates (top-right).
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);

		/// @brief Returns the underlying texture of the sub-texture.
		const Ref<Texture2D> GetTexture() { return m_Texture; }
		/// @brief Returns the texture coordinates of the sub-texture.
		glm::vec2* GetTexCoords() { return m_TexCoords; }

		/// @brief Creates a SubTexture2D from a grid of cells within the given texture.
		///
		/// @param texture The texture from which the sub-texture is derived.
		/// @param coords The coordinates of the cell in the grid.
		/// @param cellSize The size of each cell in the grid.
		/// @param spriteSize The size of the sprite in cells (default is 1x1).
		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = {1, 1});
	private:
		/// @brief The underlying texture of the sub-texture.
		Ref<Texture2D> m_Texture;
		/// @brief The texture coordinates of the sub-texture.
		glm::vec2 m_TexCoords[4];
	};

}