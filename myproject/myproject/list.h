#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

// Template კლასი priority_queue
// T იქნება Employee ან მისი შვილობილი კლასების base ტიპი
template<class T>
class priority_queue {
private:
    int size;       // რამდენი ელემენტია სიაში
    int capacity;   // მაქსიმალური ტევადობა
    T** list;       // დინამიკური მასივი, სადაც ინახება pointer-ები

public:
    // კონსტრუქტორი
    priority_queue(int sz = 0, int cap = 100)
        : size(sz), capacity(cap > 0 ? cap : 1)
    {
        list = new T * [capacity];

        // ყველა ადგილი თავიდან nullptr ხდება
        for (int i = 0; i < capacity; ++i)
            list[i] = nullptr;
    }

    // copy constructor წაშლილია,
    // რადგან pointer-ებთან მუშაობისას შეიძლება double delete მოხდეს
    priority_queue(const priority_queue&) = delete;

    // copy assignment-იც წაშლილია იმავე მიზეზით
    priority_queue& operator=(const priority_queue&) = delete;

    // move constructor
    priority_queue(priority_queue&& other) noexcept
        : size(other.size), capacity(other.capacity), list(other.list)
    {
        other.list = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    // move assignment operator
    priority_queue& operator=(priority_queue&& other) noexcept {
        if (this != &other) {
            // ძველი მეხსიერების გასუფთავება
            for (int i = 0; i < size; ++i)
                delete list[i];

            delete[] list;

            // ახალი ობიექტის მონაცემების გადმოტანა
            size = other.size;
            capacity = other.capacity;
            list = other.list;

            // ძველი ობიექტის განულება
            other.list = nullptr;
            other.size = 0;
            other.capacity = 0;
        }

        return *this;
    }

    // დესტრუქტორი
    // შლის ყველა დინამიკურად შექმნილ თანამშრომელს
    ~priority_queue() {
        if (list) {
            for (int i = 0; i < size; i++)
                delete list[i];

            delete[] list;
        }
    }

    // ამოწმებს სია ცარიელია თუ არა
    bool isempty() const {
        return size == 0;
    }

    // ამოწმებს სია სავსეა თუ არა
    bool isfull() const {
        return size == capacity;
    }

    // ელემენტის დამატება
    void push(T* item);

    // თანამშრომლის წაშლა სახელით
    void Delete(const std::string& name);

    // თანამშრომლის ძებნა სახელით
    int search(const std::string& name) const;

    // ერთი კონკრეტული თანამშრომლის დაბეჭდვა სახელით
    void display(const std::string& name) const;

    // ყველა თანამშრომლის დაბეჭდვა
    void display_all() const;

    // მასივის ზომის გაზრდა
    void resize(int newcap);
};

// თანამშრომლის ძებნა სახელის მიხედვით
template<class T>
inline int priority_queue<T>::search(const std::string& name) const
{
    if (isempty()) {
        return -1;
    }

    for (int i = 0; i < size; ++i) {
        if (list[i] && list[i]->get_name() == name)
            return i;
    }

    return -1;
}

// კონკრეტული თანამშრომლის დაბეჭდვა
template<class T>
inline void priority_queue<T>::display(const std::string& name) const
{
    if (isempty()) {
        std::cout << "sia carielia\n";
        return;
    }

    int index = search(name);

    if (index == -1) {
        std::cout << "ver moidzebna aseti tanamshromeli\n";
        return;
    }

    std::cout << *(list[index]) << std::endl;
}

// ყველა თანამშრომლის დაბეჭდვა
template<class T>
inline void priority_queue<T>::display_all() const
{
    if (isempty()) {
        std::cout << "sia carielia\n";
        return;
    }

    for (int i = 0; i < size; i++) {
        if (list[i])
            std::cout << *(list[i]) << std::endl;
    }
}

// მასივის ტევადობის გაზრდა
template<class T>
inline void priority_queue<T>::resize(int newcap)
{
    if (newcap <= capacity)
        return;

    T** temp = new T * [newcap];

    // ახალი მასივის განულება
    for (int i = 0; i < newcap; ++i)
        temp[i] = nullptr;

    // ძველი ელემენტების გადატანა ახალ მასივში
    for (int i = 0; i < size; i++)
        temp[i] = list[i];

    delete[] list;

    list = temp;
    capacity = newcap;
}

// ახალი თანამშრომლის დამატება
template<class T>
inline void priority_queue<T>::push(T* item)
{
    if (!item)
        throw std::invalid_argument("null item");

    // თუ სია სავსეა, ვზრდით ზომას
    if (isfull())
        resize(2 * capacity);

    // ვპოულობთ ადგილს ისე, რომ ხელფასები დალაგდეს კლებადობით
    // ანუ მაღალი salary იქნება წინ
    int pos = 0;

    while (pos < size&& list[pos]->get_salary() >= item->get_salary())
        ++pos;

    // ელემენტების გადაწევა მარჯვნივ
    for (int j = size; j > pos; --j)
        list[j] = list[j - 1];

    // ახალი თანამშრომლის ჩასმა სწორ პოზიციაზე
    list[pos] = item;

    ++size;
}

// თანამშრომლის წაშლა სახელით
template<class T>
inline void priority_queue<T>::Delete(const std::string& name)
{
    if (isempty()) {
        std::cout << "carielia sia\n";
        return;
    }

    int index = search(name);

    if (index == -1) {
        std::cout << "aseti tanamshromeli ver moidzebna\n";
        return;
    }

    // ვშლით კონკრეტულ თანამშრომელს მეხსიერებიდან
    delete list[index];

    // წაშლილი ელემენტის შემდეგ ყველა ელემენტს ვწევთ მარცხნივ
    for (int j = index; j < size - 1; j++)
        list[j] = list[j + 1];

    list[size - 1] = nullptr;

    --size;
}