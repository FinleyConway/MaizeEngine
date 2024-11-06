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

		const std::vector<sf::Vertex>& GetVertices() const;
		const std::weak_ptr<sf::Texture>& GetTexture() const;
		const IntRect& GetTextureRect() const;
		const FloatRect& GetBounds() const;
		Vec2f GetPivot() const;

		void SetTexture(const std::shared_ptr<sf::Texture>& texture);
		void SetTextureRect(const IntRect& rect);
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
