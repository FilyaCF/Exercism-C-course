#pragma once

#include <memory>
#include <stdexcept>

namespace linked_list {

template<typename T>
class List {
private:
    struct Item {
        std::weak_ptr<Item> left_ptr;
        std::shared_ptr<Item> right_ptr;
        T data;
        Item(const T& item): 
            right_ptr(nullptr),
            data(item){}
    };

    std::shared_ptr<Item> head{nullptr};
    std::shared_ptr<Item> tail{nullptr};
    size_t current_size{0};

    void erase(const std::shared_ptr<Item>& ptr);
public:
    List() = default;
    List(const List<T>& other);
    List(List<T>&& other);
    void operator =(const List<T>& other);
    void operator =(List<T>&& other);
    ~List() = default;

    void push(const T& item);
    void push(T&& item);
    T pop();
    void unshift(const T& item);
    void unshift(T&& item);
    T shift();
    bool erase(const T& item);
    size_t count() const;
};

template<typename T>
size_t List<T>::count() const {
    return this->current_size;
}

template<typename T>
void List<T>::push(const T& item) {
    this->current_size++;
    if (!this->head) {
        this->head = std::make_shared<Item>(item);
        this->tail = this->head;
        return;
    }
    auto new_tail = std::make_shared<Item>(item);
    new_tail->left_ptr = this->tail;
    this->tail->right_ptr = new_tail;
    this->tail = new_tail;
}

template<typename T>
void List<T>::push(T&& item) {
    this->current_size++;
    if (!this->head) {
        this->head = std::make_shared<Item>(std::forward<T>(item));
        this->tail = this->head;
        return;
    }
    auto new_tail = std::make_shared<Item>(std::forward<T>(item));
    new_tail->left_ptr = this->tail;
    this->tail->right_ptr = new_tail;
    this->tail = new_tail;
}

template<typename T>
T List<T>::pop() {
    if (!this->current_size) {
        throw std::out_of_range("Empty List!");
    }
    this->current_size--;
    if (!this->current_size) {
        T tmp = std::move(this->head->data);
        this->head = this->tail = nullptr;
        return tmp;
    }
    auto new_tail = this->tail->left_ptr.lock();
    T tmp = std::move(this->tail->data);
    new_tail->right_ptr = nullptr;
    this->tail = new_tail;
    return tmp;
}

template<typename T>
void List<T>::unshift(const T& item) {
    this->current_size++;
    if (!this->head) {
        this->head = std::make_shared<Item>(std::forward<T>(item));
        this->tail = this->head;
        return;
    }
    auto new_head = std::make_shared<Item>(item);
    new_head->right_ptr = this->head;
    this->head->left_ptr = new_head;
    this->head = new_head;
}

template<typename T>
void List<T>::unshift(T&& item) {
    this->current_size++;
    if (!this->head) {
        this->head = std::make_shared<Item>(std::forward<T>(item));
        this->tail = this->head;
        return;
    }
    auto new_head = std::make_shared<Item>(std::forward<T>(item));
    new_head->right_ptr = this->head;
    this->head->left_ptr = new_head;
    this->head = new_head;
}

template<typename T>
T List<T>::shift() {
    if (!this->current_size) {
        throw std::out_of_range("Empty List!");
    }
    this->current_size--;
    if (!this->current_size) {
        T tmp = std::move(this->head->data);
        this->head = this->tail = nullptr;
        return tmp;
    }
    auto new_head = this->head->right_ptr;
    T tmp = std::move(this->head->data);
    new_head->left_ptr.reset();
    this->head = new_head;
    return tmp;
}

template<typename T>
void List<T>::erase(const std::shared_ptr<Item>& item) {
    if (item == this->head) this->shift();
    else if (item == this->tail) this->pop();
    else {
        this->current_size--;
        auto right = item->right_ptr;
        auto left = item->left_ptr.lock();
        left->right_ptr = right;
        right->left_ptr = left;
    }
}

template<typename T>
bool List<T>::erase(const T& item) {
    auto cur = this->head;
    while(cur) {
        if (cur->data == item) {
            this->erase(cur);
            return true;
        }
        cur = cur->right_ptr;
    }
    return false;
}

}  // namespace linked_list
