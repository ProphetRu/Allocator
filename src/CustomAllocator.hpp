#pragma once

template <typename T, std::size_t N>
class CustomAllocator
{
public:
    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = const T*;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;

    template <typename U>
    struct rebind
	{
        using other = CustomAllocator<U, N>;
    };

    CustomAllocator() noexcept = default;

    template <typename U>
    CustomAllocator(const CustomAllocator<U, N>&) noexcept {}

    T* allocate(std::size_t n)
	{
        if (n > N) 
        {
            throw std::bad_alloc();
        }
        if (n == 0) 
        {
            return nullptr;
        }

        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) noexcept
	{
        ::operator delete(p, n * sizeof(T));
    }

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args)
	{
        ::new (static_cast<void*>(p)) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* p) noexcept
	{
        p->~U();
    }

    std::size_t max_size() const noexcept
	{
        return N;
    }
};
