#pragma once
#include "Model.hpp"
#include "Transform.hpp"
#include "Rigidbody.hpp"

class Object : public Model
{
public:
    //Scene graph
    std::list<std::unique_ptr<Object>> children;
    Object* parent = nullptr;

    //Space information
    Transform transform;
    RigidBody rb;

    // constructor, expects a filepath to a 3D model.
    Object() {};

    Object(std::string const& modelName, bool gamma = false) : Model(modelName)
    {}

    //Add child. Argument input is argument of any constructor that you create.
    //By default you can use the default constructor and don't put argument input.
    template<typename... TArgs>
    void addChild(const TArgs&... args)
    {
        children.emplace_back(std::make_unique<Object>(args...));
        children.back()->parent = this;
    }

    //Update transform if it was changed
    void updateSelfAndChild()
    {
        if (transform.IsDirty())
        {
            forceUpdateSelfAndChild();
            return;
        }

        for (auto&& child : children)
        {
            child->updateSelfAndChild();
        }
    }

    //Force update of transform even if local space don't change
    void forceUpdateSelfAndChild()
    {
        if (parent)
            transform.computeModelMatrix(parent->transform.getModelMatrix());
        else
            transform.computeModelMatrix();

        for (auto&& child : children)
        {
            child->forceUpdateSelfAndChild();
        }
    }
};