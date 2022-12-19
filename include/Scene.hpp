#pragma once
#include <memory>
using std::shared_ptr, std::make_shared, std::unique_ptr, std::make_unique;
#include <vector>

#include "SceneObject.hpp"

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

    inline std::vector<shared_ptr<SceneObject>>::iterator begin() // Thanks for the Module 3 code :D
    {
        return drawables.begin();
    }
    inline std::vector<shared_ptr<SceneObject>>::iterator end()
    {
        return drawables.end();
    }
};
