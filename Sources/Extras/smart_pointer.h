
#ifndef OOPTesting_smart_pointer_h
#define OOPTesting_smart_pointer_h

#include <assert.h>
#include <typeinfo>
#include <iostream>
#include <map>

#include "../Debug/Logger.h"

//#define ENABLE_LOG

template<class T>
class ReferenceManager
{
private:
    std::map<T*, int> ref_map;
public:
    inline void add(T* ptr)
    {
        std::cout << "Added reference to: " << ptr << std::endl;
        ref_map[ptr]++;
    }
    
    inline bool remove(T* ptr)
    {
        return --ref_map[ptr] == 0;
    }
    
    inline bool has(T* ptr)
    {
        return ref_map[ptr];
    }
    
    inline int count(T* ptr)
    {
        return ref_map[ptr];
    }
};

class RemovableObject
{
	template<class T> friend class smart_pointer;
private:
	int refs = 0;

};

template<class T>
class smart_pointer
{
private:
    T* data;
	static smart_pointer<T> emptyPtr;
public:
    smart_pointer():data(NULL)
	{
		static_assert(std::is_base_of<RemovableObject, T>::value, "smart_pointer illegal type of <T>");

#ifdef ENABLE_LOG
		std::cout << "smart_pointer() <" << typeid(T).name() << ">" << std::endl;
#endif
	}
    
    smart_pointer(const smart_pointer& other):data(other.data)
    {
		static_assert(std::is_base_of<RemovableObject, T>::value, "smart_pointer illegal type of <T>");
		if (data != NULL)
		{
			dynamic_cast<RemovableObject*>(data)->refs++;

			//std::cout << "Added reference to: " << data << std::endl;
		}

#ifdef ENABLE_LOG
		std::cout << "smart_pointer(const smart_pointer& other) <" << typeid(T).name() << ">" << std::endl;
#endif
    }
    
    explicit smart_pointer(T* ptr):data(ptr)
    {
		static_assert(std::is_base_of<RemovableObject, T>::value, "smart_pointer illegal type of <T>");

		if (data != NULL)
		{
			dynamic_cast<RemovableObject*>(data)->refs++;
			//Logger::Print("Added reference of type %s \n", typeid(T).name());
			//std::cout << "Added reference to: " << data << std::endl;
		}
#ifdef ENABLE_LOG
		std::cout << "smart_pointer(" << typeid(T).name() << "* ptr)" << std::endl;
#endif
    }
    
    ~smart_pointer()
    {
        if(data != NULL)
        {
#ifdef ENABLE_LOG
		std::cout << "~~~~smart_pointer() <" << typeid(T).name() << ">" << std::endl;
#endif
			//std::cout << "REFS COUNT " << dynamic_cast<RemovableObject*>(data)->refs << std::endl;
			if(--dynamic_cast<RemovableObject*>(data)->refs == 0)
            {
#ifdef ENABLE_LOG
				Logger::Print("Object of type %s deleted\n", typeid(T).name());
#endif
				delete data;
            }

#ifdef ENABLE_LOG
			std::cout << "Pointer to : " << data << " removed, " << dynamic_cast<RemovableObject*>(data)->refs << " left" << std::endl;
#endif
        }
    }
    
    inline smart_pointer<T> clone()
    {
       // smart_pointer<T> sm;
      //  sm.data = new T(*data);

// 		if (data != NULL)
// 			dynamic_cast<RemovableObject*>(data)->refs++;
        
		T* data_copy = new T(*data);
		return smart_pointer<T>(data_copy);
    }

	inline bool isEmpty() //#TODO this function can be operator
	{
		return data == NULL;
	}

	static inline smart_pointer<T>& null()
	{
		return emptyPtr;
	}
    
    inline T& operator *()
    {
        return *data;
    }
    
    inline T* operator->()
    {
        return data;
    }
    
    inline smart_pointer& operator=(const smart_pointer& other)
    {
#ifdef ENABLE_LOG
		std::cout << "smart_pointer: try to copy " << typeid(T).name() << std::endl;
#endif
        if(this->data != other.data)
        {
			//std::cout << "Copy complete" << std::endl;
			if (data != NULL && --dynamic_cast<RemovableObject*>(data)->refs == 0)
			{
#ifdef ENABLE_LOG
				std::cout << "DATA REMOVED: try to copy " << typeid(T).name() << std::endl;
#endif
				delete data;
			}

            data = other.data;
			//std::cout << "Added reference to: " << data << std::endl;
			if (data != NULL)
				dynamic_cast<RemovableObject*>(data)->refs++;
        }
        
        return *this;
    }
    
	inline bool operator == (const T*const other) const
	{
		return data == other;
	}

	inline bool operator != (const T*const other) const
	{
		return data != other;
	}

    inline bool operator == (const smart_pointer& other ) const
    {
        return data == other.data;
    }

	inline bool operator != (const smart_pointer& other) const
	{
		return data != other.data;
	}

	inline void free()
	{
		if (data != NULL && --dynamic_cast<RemovableObject*>(data)->refs == 0)
			delete data;
	}
};


template<class T>
smart_pointer<T> smart_pointer<T>::emptyPtr;
#endif