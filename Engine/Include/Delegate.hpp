#pragma once

#include <functional>
#include <type_traits>
#include <list>

//event declarations
#define EVENT(NAME)  typedef Event<> NAME;
#define EVENT0(NAME) typedef Event<> NAME; //same as previous
#define EVENT1(NAME, P1) typedef Event<P1> NAME;
#define EVENT2(NAME, P1, P2) typedef Event<P1, P2> NAME;
#define EVENT3(NAME, P1, P2, P3) typedef Event<P1, P2, P3> NAME;
#define EVENT4(NAME, P1, P2, P3, P4) typedef Event<P1, P2, P3, P4> NAME;
#define EVENT5(NAME, P1, P2, P3, P4, P5) typedef Event<P1, P2, P3, P4, P5> NAME;

template<int> struct IntegerConstant {};
template<int ...> struct IntSequence {};
template<int N, int ... Args> struct MakeIntSequence
    : MakeIntSequence<N-1, N-1, Args...> {};
template<int ... Args> struct MakeIntSequence<0, Args...>
    : IntSequence<Args...> {};
template<int N> struct std::is_placeholder<IntegerConstant<N>>
    : std::integral_constant<int, N+1> {};
template<class... Args, int... Is>
std::function<void(Args...)> DelegateBind(void(*pFunc)(Args...), IntSequence<Is...>)
{
    return std::bind(pFunc, IntegerConstant<Is>{}...);
}
template<class... Args>
std::function<void(Args...)> NewDelegate(void(*pFunc)(Args...))
{
    return DelegateBind(pFunc, MakeIntSequence< sizeof...(Args) >{});
}
template<class T, class... Args, int... Is>
std::function<void(Args...)> DelegateBind(void(T::*p)(Args...), T* base, IntSequence<Is...>)
{
    return std::bind(p, base, IntegerConstant<Is>{}...);
}
template<class T, class ... Args>
std::function<void(Args...)> NewDelegate(T* base, void(T::*pFunc)(Args...))
{
    return DelegateBind(pFunc, base, MakeIntSequence< sizeof...(Args) >{});
}

namespace Scrim
{
    template<class ... Args>
    class Event
    {
    public:
        typedef std::function<void(Args...)> Delegate;
        typedef std::list<Delegate> DelegateList;

        DelegateList delegates;

        void Clear()
        {
            delegates.clear();
        }

        void AddDelegate(Delegate delegate)
        {
            delegates.push_back(delegate);
        }

        void Invoke(Args... args)
        {
             for(auto& delegate : delegates)
             {
                 delegate(args...);
             }
        }

        Event& operator =(Delegate delegate)
        {
             Clear();
             AddDelegate(delegate);
             return *this;
        }
        Event& operator +=(Delegate delegate)
        {
             AddDelegate(delegate);
             return *this;
        }
    };
}
