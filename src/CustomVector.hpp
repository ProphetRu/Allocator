#pragma once

#include <memory>

template<typename T, typename Allocator = std::allocator<T>>
class CustomVector
{
public:
    using value_type      = T;
    using allocator_type  = Allocator;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = typename std::allocator_traits<allocator_type>::pointer;
    using const_pointer   = typename std::allocator_traits<allocator_type>::const_pointer;
    using iterator        = pointer;
    using const_iterator  = const_pointer;

    CustomVector() noexcept :
		m_Size(0),
		m_Capacity(0),
		m_Data(nullptr)
    {
    }

    explicit CustomVector(size_type count, const value_type& value = value_type()) :
		m_Size(count),
		m_Capacity(count),
		m_Data(m_Allocator.allocate(count))
    {
        std::uninitialized_fill_n(m_Data, count, value);
    }

    ~CustomVector() noexcept
	{
        clear();
        m_Allocator.deallocate(m_Data, m_Capacity);
    }

    void push_back(const value_type& value)
	{
        if (m_Size == m_Capacity) 
        {
            reserve(m_Capacity == 0 ? 1 : m_Capacity * 2);
        }

        m_Allocator.construct(m_Data + m_Size, value);
        ++m_Size;
    }

    void pop_back()
	{
        if (m_Size > 0) 
        {
            --m_Size;
            m_Allocator.destroy(m_Data + m_Size);
        }
    }

    void resize(size_type count, const value_type& value = value_type())
	{
        if (count > m_Capacity) 
        {
            reserve(count);
        }

        if (count > m_Size) 
        {
            std::uninitialized_fill_n(m_Data + m_Size, count - m_Size, value);
        }
        else 
        {
            for (size_type i = count; i < m_Size; ++i) 
            {
                m_Allocator.destroy(m_Data + i);
            }
        }

        m_Size = count;
    }

    void reserve(size_type new_capacity)
	{
        if (new_capacity > m_Capacity) 
        {
            pointer new_data = m_Allocator.allocate(new_capacity);
            std::uninitialized_copy_n(m_Data, m_Size, new_data);

            for (size_type i = 0; i < m_Size; ++i)
            {
                m_Allocator.destroy(m_Data + i);
            }

            m_Allocator.deallocate(m_Data, m_Capacity);

            m_Data     = new_data;
            m_Capacity = new_capacity;
        }
    }

    void clear()
	{
        for (size_type i = 0; i < m_Size; ++i) 
        {
            m_Allocator.destroy(m_Data + i);
        }

        m_Size = 0;
    }

    size_type size() const noexcept
	{
        return m_Size;
    }

    size_type capacity() const noexcept
	{
        return m_Capacity;
    }

    bool empty() const noexcept
	{
        return m_Size == 0;
    }

    reference operator[](size_type index)
	{
        return m_Data[index];
    }

    const_reference operator[](size_type index) const
	{
        return m_Data[index];
    }

    iterator begin() noexcept
	{
        return m_Data;
    }

    const_iterator begin() const noexcept
	{
        return m_Data;
    }

    iterator end() noexcept
	{
        return m_Data + m_Size;
    }

    const_iterator end() const noexcept
	{
        return m_Data + m_Size;
    }

private:
    allocator_type m_Allocator;
    size_type      m_Size;
    size_type      m_Capacity;
    pointer        m_Data;
};
