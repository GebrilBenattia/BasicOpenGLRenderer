#pragma once
#include "Matrix4.hpp"

class Transform
{
public:
    //Local space information
    Vector3 pos = { 0.0f, 0.0f, 0.0f };
    Vector3 eulerRot = { 0.0f, 0.0f, 0.0f }; //In degrees
    Vector3 scale = { 1.0f, 1.0f, 1.0f };

    //Global space information concatenate in matrix
    Matrix4 modelMatrix = Matrix4::Identity();

    //Dirty flag
    bool isDirty = true;

protected:
    Matrix4 getLocalModelMatrix()
    {
        // translation * rotation * scale (also know as TRS matrix)
        return Matrix4::TRS(pos, eulerRot, scale);
    }
public:

    void computeModelMatrix()
    {
        modelMatrix = getLocalModelMatrix();
        isDirty = false;
    }

    void computeModelMatrix(const Matrix4& parentGlobalModelMatrix)
    {
        modelMatrix = Matrix4::MultiplyBy(parentGlobalModelMatrix, getLocalModelMatrix());
        isDirty = false;
    }

    void setLocalPosition(const Vector3& newPosition)
    {
        pos = newPosition;
        isDirty = true;
    }

    const Vector3& getLocalPosition()
    {
        return pos;
    }

    const Matrix4& getModelMatrix()
    {
        return modelMatrix;
    }

    bool IsDirty()
    {
        return isDirty;
    }
};