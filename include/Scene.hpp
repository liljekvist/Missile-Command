#pragma once
#include <memory>
using std::shared_ptr, std::make_shared, std::unique_ptr, std::make_unique;
#include <vector>

#include "SceneObject.hpp"
#include "Tower.hpp"
#include "VectorMath.hpp"

// Definition of why make class when teacher make good class 4 u :D

class Scene
{
    std::vector<shared_ptr<SceneObject>> drawables;

  public:
    Scene();
    ~Scene();
    Scene(const Scene& other) = delete; // No copys thanks >:(
    Scene& operator=(const Scene& other) = delete;

    int GetSize() const;

    std::vector<shared_ptr<SceneObject>> getVec();

    bool AddSceneObject(shared_ptr<SceneObject> Obj);
    bool ReleaseSceneObject(shared_ptr<SceneObject> Obj);
    shared_ptr<Tower> GetClosestFirableTower(sf::Vector2f pos);

    inline std::vector<shared_ptr<SceneObject>>::iterator begin() // Thanks for the Module 3 code :D
    {
        return drawables.begin();
    }
    inline std::vector<shared_ptr<SceneObject>>::iterator end()
    {
        return drawables.end();
    }

    template<typename T>
    shared_ptr<T> GetClosestSceneObjectOfType(sf::Vector2f pos)
    {
        shared_ptr<T> cObj = nullptr; // Clostest
        for(auto& Obj : drawables)
        {
            if(shared_ptr<T> chObj = std::dynamic_pointer_cast<T>(Obj);
               chObj) // not nullptr. Casted correctly
            {
                if(cObj == nullptr)
                    cObj = chObj;
                else if(
                    distanceBetween(chObj->getPosition(), pos)
                    < distanceBetween(cObj->getPosition(), pos))
                {
                    cObj = chObj;
                }
            }
        };
        return cObj;
    }

    template<typename T>
    std::vector<std::shared_ptr<T>> GetAllOfType()
    {
        std::vector<std::shared_ptr<T>> vType;
        // Clostest
        for(auto& Obj : drawables)
        {
            if(shared_ptr<T> chObj = std::dynamic_pointer_cast<T>(Obj);
               chObj) // not nullptr. Casted correctly
            {
                vType.push_back(chObj);
            }
        };
        return vType;
    }
};
