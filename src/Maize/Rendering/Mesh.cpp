#include "Maize/Rendering/Mesh.h"

#include <limits>

namespace Maize {

	void Mesh::AddVertices(std::span<sf::Vertex> mesh)
	{
		m_Mesh.reserve(mesh.size());
		m_Mesh.assign(mesh.begin(), mesh.end()); // copy mesh
		m_Bounds = GetMeshBounds(); // generate rectangular bounds
	}

	void Mesh::AddVertices(std::span<sf::Vertex> mesh, const FloatRect& bounds)
	{
		m_Mesh.reserve(mesh.size());
		m_Mesh.assign(mesh.begin(), mesh.end()); // copy mesh
		m_Bounds = bounds; // assign pre-defined bounds
	}

	const std::vector<sf::Vertex>& Mesh::GetVertices() const
	{
		return m_Mesh;
	}

	size_t Mesh::GetVertexCount() const
	{
		return m_Mesh.size();
	}

	const FloatRect& Mesh::GetBounds() const
	{
		return m_Bounds;
	}

	void Mesh::Clear()
	{
		m_Mesh.clear();
		m_Bounds = FloatRect();
	}

	FloatRect Mesh::GetMeshBounds()
	{
		auto minX = std::numeric_limits<float>::max();
		auto minY = std::numeric_limits<float>::max();
		auto maxX = std::numeric_limits<float>::min();
		auto maxY = std::numeric_limits<float>::min();

		for (const auto& vertex : m_Mesh)
		{
			minX = std::min(minX, vertex.position.x);
			minY = std::min(minY, vertex.position.y);
			maxX = std::max(maxX, vertex.position.x);
			maxY = std::max(maxY, vertex.position.y);
		}

		return FloatRect(minX, minY, maxX, maxY);
	}

} // Maize