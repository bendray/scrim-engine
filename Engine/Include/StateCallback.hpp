#pragma once

#include <types.hpp>

namespace Scrim
{
    class StateCallback
    {
    private:
        StateCallbackFunc m_func;
        IState*   m_pState;
        String    m_guid;
    public:
        StateCallback(StateCallbackFunc func, IState* pState, String guid) :
                m_func(func),
                m_pState(pState),
                m_guid(std::move(guid)){}
        StateCallback(const StateCallback& other) = default;
        StateCallback& operator=(StateCallback&& other) = default;
        inline bool operator==(const StateCallback& rhs){
            return (m_guid == rhs.m_guid); }
        const IState* GetInstance() { return m_pState; }
        const String& GetGUID() { return m_guid; } 
        template <typename ... TArgs>
        auto operator ()(TArgs&&... args)
                -> decltype(m_func(std::forward<TArgs>(args)...))
        {
            return m_func(std::forward<TArgs>(args)...);
        }
    };
}
