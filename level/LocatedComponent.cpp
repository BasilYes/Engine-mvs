#include "LocatedComponent.h"
#include "debug.h"
LocatedComponent::LocatedComponent(LocatedObject* object, Transform relativeTransform, LocatedObject* parent, LocatedComponent* right, LocatedComponent* child)
	:m_object{ object }, m_relativeTransform{ relativeTransform }, m_parent{ parent }, m_right{ right }, m_child{ child }
{
	ASSERT(object && parent, "Located component mast have owned obj and parent")
}
void LocatedComponent::refreshTreeTransform(const mat3& parentRotate, const Transform& parentTransform)
{
	LocatedComponent* node = this;
	while (node)
	{
		node->m_object->setRotation(node->getRelativeRotation() + parentTransform.rotation);
		node->m_object->setScale(node->getRelativeScale() * parentTransform.scale);
		node->m_object->setLocation(parentRotate * node->getRelativeLocation() * parentTransform.scale + parentTransform.location);
		if (node->m_child)
		{
			mat3 mat;
			initRotateTransform(mat, node->m_object->getRotation());
			node->m_child->refreshTreeTransform(mat, node->m_object->getTransform());
		}
		node = node->m_right;
	}
}
void LocatedComponent::refreshNodeTransform()
{
	mat3 mat;
	initRotateTransform(mat, m_parent->getRotation());
	m_object->setRotation(getRelativeRotation() + m_parent->getRotation());
	m_object->setScale(getRelativeScale() * m_parent->getScale());
	m_object->setLocation(mat * getRelativeLocation() * m_parent->getScale() + m_parent->getLocation());
	if (m_child)
	{
		initRotateTransform(mat, m_object->getRotation());
		m_child->refreshTreeTransform(mat, m_object->getTransform());
	}
}
LocatedComponent::~LocatedComponent()
{
	delete m_right;
	delete m_child;
	delete m_object;
}

void LocatedComponent::setRelativeScale(const vec3 scale)
{
	m_relativeTransform.scale = scale;
	refreshNodeTransform();
}

void LocatedComponent::setRelativeLocation(const vec3 location)
{
	m_relativeTransform.location = location;
	refreshNodeTransform();
}

void LocatedComponent::setRelativeRotation(const vec3 rotation)
{
	m_relativeTransform.rotation = rotation;
	refreshNodeTransform();
}

void LocatedComponent::setRelativeTransform(const Transform transform)
{
	m_relativeTransform = transform;
	refreshNodeTransform();
}