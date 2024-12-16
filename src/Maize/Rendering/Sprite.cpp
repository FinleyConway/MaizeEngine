#include "Maize/Rendering/Sprite.h"

namespace Maize
{
    Sprite::Sprite(const std::shared_ptr<sf::Texture>& texture, const IntRect& rect) : m_TextureReference(texture),
        m_TextureRect(rect)
    {
        UpdateTextureRect(rect);
    }

    Sprite::Sprite(const std::shared_ptr<sf::Texture>& texture, const IntRect& rect,
                   Vec2f pivot) : m_TextureReference(texture), m_TextureRect(rect), m_Pivot(pivot)
    {
        UpdateTextureRect(rect);
    }

    const std::vector<sf::Vertex>& Sprite::GetVertices() const
    {
        return m_Mesh.GetVertices();
    }

    const std::weak_ptr<sf::Texture>& Sprite::GetTexture() const
    {
        return m_TextureReference;
    }

    const IntRect& Sprite::GetTextureRect() const
    {
        return m_TextureRect;
    }

    const FloatRect& Sprite::GetBounds() const
    {
        return m_Mesh.GetBounds();
    }

    Vec2f Sprite::GetPivot() const
    {
        return m_Pivot;
    }

    void Sprite::SetTexture(const std::shared_ptr<sf::Texture>& texture)
    {
        m_TextureReference = texture;
    }

    void Sprite::SetTextureRect(const IntRect& rect)
    {
        m_TextureRect = rect;
        UpdateTextureRect(rect);
    }

    void Sprite::SetPivot(Vec2f pivot)
    {
        m_Pivot = pivot;
    }

    void Sprite::UpdateTextureRect(const IntRect& rect)
    {
        // construct the new sprite mesh
        const auto bounds = FloatRect(rect);
        std::array<sf::Vertex, 6> vertices;

        vertices[0].position = sf::Vector2f(0, 0);
        vertices[1].position = sf::Vector2f(0, bounds.height);
        vertices[2].position = sf::Vector2f(bounds.width, 0);
        vertices[3].position = sf::Vector2f(0, bounds.height);
        vertices[4].position = sf::Vector2f(bounds.width, bounds.height);
        vertices[5].position = sf::Vector2f(bounds.width, 0);

        const float left = bounds.x;
        const float right = left + bounds.width;
        const float top = bounds.y;
        const float bottom = top + bounds.height;

        vertices[0].texCoords = sf::Vector2f(left, top);
        vertices[1].texCoords = sf::Vector2f(left, bottom);
        vertices[2].texCoords = sf::Vector2f(right, top);
        vertices[3].texCoords = sf::Vector2f(left, bottom);
        vertices[4].texCoords = sf::Vector2f(right, bottom);
        vertices[5].texCoords = sf::Vector2f(right, top);

        // construct mesh and its bounds
        m_Mesh.AddVertices(vertices, bounds);
    }
} // Maize
