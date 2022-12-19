#include "Scene.hpp"

Scene::Scene() {} // Notting to init :V

Scene::~Scene() {} // Notting to remove from heap :feelsgoodman:

int Scene::GetSize() const
{
    return drawables.size();
}

std::vector<shared_ptr<SceneObject>> Scene::getVec()
{
    return drawables;
}

bool Scene::AddSceneObject(
    shared_ptr<SceneObject> Obj) // gib me many copies here :D Refrence counting <3
{
    if(Obj != nullptr && !std::any_of(begin(), end(), [&Obj](const shared_ptr<SceneObject> elem) {
           return (elem == Obj);
       }))
        this->drawables.push_back(Obj);
    else
        return false;
    return true;
}

bool Scene::ReleaseSceneObject(shared_ptr<SceneObject> Obj)
{
    bool deleted = false;
    drawables.erase(
        std::remove_if(begin(), end(), [&Obj, &deleted](const shared_ptr<SceneObject> x) {
            deleted = true;
            return (x == Obj);
        }));
    return deleted;
}

shared_ptr<Tower> Scene::GetClosestFirableTower(sf::Vector2f pos)
{
    shared_ptr<Tower> cObj = nullptr; // Clostest
    for(auto& Obj : drawables)
    {
        if(shared_ptr<Tower> chObj = std::dynamic_pointer_cast<Tower>(Obj);
           chObj) // not nullptr. Casted correctly
        {
            if(cObj != nullptr)
            {
                if(distanceBetween(chObj->getPosition(), pos)
                       < distanceBetween(cObj->getPosition(), pos)
                   && chObj->canFireMissile())
                {
                    cObj = chObj;
                }
            }
            else if(chObj->canFireMissile())
                cObj = chObj;
        }
    };
    return cObj;
}
