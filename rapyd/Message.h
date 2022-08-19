#ifndef MESSAGE_H
#define MESSAGE_H 

template <typename T> 
struct Message {
private:
    T data; 
public:
    /**** FACTORY METHODS *****/
    
    // Specialised factory for const char* data with args 
    template <typename... Args> 
    static Message create(T data, Args... args) 
    requires(std::is_same_v<T, const char*>) 
    {
        return Message<T>();
    };

    // Generic factory method
    template <typename... Args> 
    static Message create(T data, Args... args) {
        return Message<T>();
    };

    void print();
    T* get_data();
};


template <typename T> 
void Message<T>::print() {
    std::cout << "Data: " << data << '\n'; 
};

template <typename T> 
T* Message<T>::get_data() {
    T* data_ptr = &data;
    return data_ptr;
};




#endif 
