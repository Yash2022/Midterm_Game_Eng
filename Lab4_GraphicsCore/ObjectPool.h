//Ramanooj
#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

#include <vector>
#include <memory>

template <typename T>
class ObjectPool
{
public:
    ObjectPool() {}
    ~ObjectPool()
    {
        for (auto& obj : m_pool)
        {
            delete obj;
        }
        m_pool.clear();
    }

    T* GetResource()
    {
        if (!m_pool.empty())
        {
            T* obj = m_pool.back();
            m_pool.pop_back();
            return obj;
        }
        else
        {
            T* obj = new T();
            return obj;
        }
    }

    void ReturnResource(T* obj)
    {
        m_pool.push_back(obj);
    }

    void Clear()
    {
        for (auto& obj : m_pool)
        {
            delete obj;
        }
        m_pool.clear();
    }

private:
    std::vector<T*> m_pool;
};

#endif // OBJECTPOOL_H
