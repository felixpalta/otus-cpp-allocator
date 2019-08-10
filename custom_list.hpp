#ifndef CUSTOM_LIST_HPP
#define CUSTOM_LIST_HPP

#include <memory>

namespace otus {

template <typename T, typename A = std::allocator<T>>
class CustomList
{
public:
    using value_type = T;
    using allocator_type = A;
    CustomList(const allocator_type & a = allocator_type())
        : mAllocator(a)
        , mRootNode(nullptr)
    {}

    ~CustomList();

    struct iterator
    {
        using value_type = CustomList::value_type;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = size_t;
        using pointer = value_type*;
        using reference = value_type&;

        void * node;
        iterator() noexcept : node(nullptr) {}
        explicit iterator(void * n) : node(n) {}
        iterator & operator++();
        reference operator*();
        bool operator==(const iterator & other);
        bool operator!=(const iterator & other);
    };

    iterator push_back(const value_type & val);
    iterator begin();
    iterator end();

    bool empty() const { return mRootNode == nullptr; }

private:
    struct Node {
        value_type value;
        Node * next;
        explicit Node(const value_type & val) : value(val), next(nullptr) {}
        Node() : value(), next(nullptr) {}
    };

    using allocator_type_internal = typename allocator_type::template rebind<Node>::other;
    allocator_type_internal mAllocator;
    Node * mRootNode;

    Node * allocate();
    void deallocate(Node* node);
};

template<typename T, typename A>
typename CustomList<T, A>::iterator CustomList<T, A>::begin()
{
    return iterator{static_cast<void*>(mRootNode)};
}

template<typename T, typename A>
typename CustomList<T, A>::iterator CustomList<T, A>::end()
{
    return iterator{nullptr};
}

template<typename T, typename A>
typename CustomList<T, A>::iterator CustomList<T, A>::push_back(const value_type & val)
{
    Node ** targetNodePtr = &mRootNode;
    while (*targetNodePtr) {
        targetNodePtr = &((*targetNodePtr)->next);
    }
    *targetNodePtr = std::allocator_traits<allocator_type_internal>::allocate(mAllocator, 1);
    std::allocator_traits<allocator_type_internal>::construct(mAllocator, *targetNodePtr, val);
    return iterator{static_cast<void*>(*targetNodePtr)};
}

template<typename T, typename A>
typename CustomList<T, A>::iterator::reference CustomList<T, A>::iterator::operator*()
{
    return static_cast<Node*>(node)->value;
}

template<typename T, typename A>
typename CustomList<T, A>::iterator & CustomList<T, A>::iterator::operator++()
{
    Node * next = static_cast<Node*>(node)->next;
    node = static_cast<void*>(next);
    return *this;
}

template<typename T, typename A>
bool CustomList<T, A>::iterator::operator==(const iterator &other)
{
    return node == other.node;
}

template<typename T, typename A>
bool CustomList<T, A>::iterator::operator!=(const iterator &other)
{
    return !(*this == other);
}

template<typename T, typename A>
CustomList<T,A>::~CustomList()
{
    if (!empty()) {
        Node * next = mRootNode;
        while (next) {
            Node * prevNext = next;
            next = prevNext->next;
            std::allocator_traits<allocator_type_internal>::destroy(mAllocator, prevNext);
            std::allocator_traits<allocator_type_internal>::deallocate(mAllocator, prevNext, 1);
        }
    }
}

} // otus

#endif // CUSTOM_LIST_HPP
