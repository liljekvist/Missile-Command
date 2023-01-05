#pragma once
#include <memory>
#include <vector>

#include "SceneObject.hpp"
#include "Tower.hpp"
#include "VectorMath.hpp"

// Definition of why make class when teacher make good class 4 u :D

class Scene
{
    std::vector<std::shared_ptr<SceneObject>> m_drawables;

  public:
    Scene();
    ~Scene();
    Scene(const Scene& other) = delete; // No copys thanks >:(
    auto operator=(const Scene& other) -> Scene& = delete;
    Scene(Scene&& other) = delete; // No move thanks >:(
    auto operator=(Scene&& other) -> Scene& = delete;

    [[nodiscard]] auto getSize() const -> size_t;

    auto getVec() -> std::vector<std::shared_ptr<SceneObject>>;

    
    
    auto AddSceneObject(std::shared_ptr<SceneObject> Obj) -> bool;
    auto ReleaseSceneObject(std::shared_ptr<SceneObject> Obj) -> bool;
    auto GetClosestFirableTower(sf::Vector2f pos) -> std::shared_ptr<Tower>;

    inline auto begin()
        -> std::vector<std::shared_ptr<SceneObject>>::iterator // Thanks for the Module 3 code :D
    {
        return m_drawables.begin();
    }
    inline auto end() -> std::vector<std::shared_ptr<SceneObject>>::iterator
    {
        return m_drawables.end();
    }

    template<typename T>
    auto getClosestSceneObjectOfType(sf::Vector2f pos) -> std::shared_ptr<T>
    {
        std::shared_ptr<T> c_obj = nullptr; // Clostest
        for(auto& obj : m_drawables)
        {
            if(std::shared_ptr<T> ch_obj = std::dynamic_pointer_cast<T>(obj);
               ch_obj) // not nullptr. Casted correctly
            {
                if(c_obj == nullptr
                   || distanceBetween(ch_obj->getPosition(), pos)
                          < distanceBetween(c_obj->getPosition(), pos))
                {
                    c_obj = ch_obj;
                }
            }
        };
        return c_obj;
    }

    template<typename T>
    auto getAllOfType() -> std::vector<std::shared_ptr<T>>
    {
        std::vector<std::shared_ptr<T>> v_type;
        // Clostest
        for(auto& obj : m_drawables)
        {
            if(std::shared_ptr<T> ch_obj = std::dynamic_pointer_cast<T>(obj);
               ch_obj) // not nullptr. Casted correctly
            {
                v_type.push_back(ch_obj);
            }
        };
        return v_type;
    }
};
