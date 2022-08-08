#include "RInstance.h"
#include "RCamera.h"
#include "RObject.h"
#include "level/LevelInstance.h"
#include "level/Level.h"

RInstance::RInstance(LevelInstance* ownInstance)
    :m_ownInstance{ownInstance}
{
}

RInstance::~RInstance()
{
    if (m_selfRef)
        LincedList<const RInstance>::remove(m_selfRef);
}

void RInstance::addRObject(RObject* mesh)
{
    m_drawList.pushFront(mesh);
    mesh->RObject::m_selfRef = m_drawList.getFirst();
}

void RInstance::draw(RCamera* camera) const
{
    camera->updateViewMatrix(camera->getLocation() - m_ownInstance->getOffset(), camera->getRotation());
    LincedListItem<const RObject>* item = m_drawList.getFirst();
    while (item)
    {
        item->getContent()->draw(camera);
        item = item->getNext();
    }
}
