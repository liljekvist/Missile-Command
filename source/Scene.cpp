#include "Scene.hpp"
#include <cstddef>

Scene::Scene() = default; // Notting to init :V

Scene::~Scene() {} // Notting to remove from heap :feelsgoodman:

auto Scene::getSize() const -> size_t
{
    return m_drawables.size();
}

auto Scene::getVec() -> std::vector<std::shared_ptr<SceneObject>>
{
    return m_drawables;
}

auto Scene::AddSceneObject(std::shared_ptr<SceneObject> Obj)
    -> bool // gib me many copies here :D Refrence counting <3
{
    if(Obj != nullptr
       && !std::any_of(begin(), end(), [&Obj](const std::shared_ptr<SceneObject>& elem) {
              return (elem == Obj);
          }))
    {
        this->m_drawables.push_back(Obj);
    }
    else
    {
        return false;
    }
    return true;
}

auto Scene::ReleaseSceneObject(std::shared_ptr<SceneObject> obj) -> bool
{
    bool deleted = false;
    m_drawables.erase(
        std::remove_if(
            begin(),
            end(),
            [&obj, &deleted](const std::shared_ptr<SceneObject>& elem) {
                deleted = true;
                return (elem == obj);
            }),
        end());
    return deleted;
}

auto Scene::GetClosestFirableTower(sf::Vector2f pos) -> std::shared_ptr<Tower>
{
    std::shared_ptr<Tower> c_obj = nullptr; // Clostest
    for(auto& elem : m_drawables)
    {
        if(std::shared_ptr<Tower> ch_obj = std::dynamic_pointer_cast<Tower>(elem);
           ch_obj) // not nullptr. Casted correctly
        {
            if(c_obj != nullptr)
            {
                if(distanceBetween(ch_obj->getPosition(), pos)
                       < distanceBetween(c_obj->getPosition(), pos)
                   && ch_obj->canFireMissile())
                {
                    c_obj = ch_obj;
                }
            }
            else if(ch_obj->canFireMissile())
            {
                c_obj = ch_obj;
            }
        }
    };
    return c_obj;
}
