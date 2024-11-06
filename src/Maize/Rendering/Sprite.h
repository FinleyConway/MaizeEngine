#pragma once

#include <memory>

#include "Maize/Math/Vec2.h"
#include "Maize/Math/Rect.h"
#include "Maize/Rendering/Mesh.h"

namespace Maize {

	class Sprite
	{
	public:
		Sprite() = default;
		Sprite(const std::shared_ptr<sf::Texture>& texture, const IntRect& rect);
		Sprite(const std::shared_ptr<sf::Texture>& texture, const IntRect& rect, Vec2f pivot);

		/**
		 * Get the mesh of the sprite.
		 * @return The mesh in a from of a vector.
		 */
		const std::vector<sf::Vertex>& GetVertices() const;

		/**
		 * Get the texture used to render the sprite.
		 * @return A weak reference of the texture.
		 */
		const std::weak_ptr<sf::Texture>& GetTexture() const;

		/**
		 * Get where the sprite is located on the texture.
		 * @return A rect pointing to the location.
		 */
		const IntRect& GetTextureRect() const;

		/**
		 * Get local bounds of the sprite.
		 * @return A rect as the bounds of the sprite.
		 */
		const FloatRect& GetBounds() const;

		/**
		 * Where the centre of the sprite is based.
		 * @return A point pointing to the location.
		 */
		Vec2f GetPivot() const;

		/**
		 * Change the texture which is used to render the sprite.
		 * @param texture A reference pointer of the texture.
		 */
		void SetTexture(const std::shared_ptr<sf::Texture>& texture);

		/**
		 * Change where the sprite is pointing to in the texture.
		 * @param rect The new location.
		 */
		void SetTextureRect(const IntRect& rect);

		/**
		 * Change where the centre is based on the pivot
		 * @param pivot A point of the new location.
		 */
		void SetPivot(Vec2f pivot);

	private:
		void UpdateTextureRect(const IntRect& rect);

	private:
		Mesh m_Mesh;
		std::weak_ptr<sf::Texture> m_TextureReference;
		IntRect m_TextureRect;
		Vec2f m_Pivot;
	};

} // Maize
