//
//  smart_pointer.h
//  OOPTesting
//
//  Created by Hakob on 12/10/14.
//  Copyright (c) 2014 Haksist. All rights reserved.
//

#ifndef OOPTesting_smart_pointer_h
#define OOPTesting_smart_pointer_h

//#include <assert.h>
#include <type_traits>
#include <map>

//#define ENABLE_LOG #endif

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

template<class T>
class smart_pointer
{
private:
    T* data;
	static smart_pointer<T> nullPtr;
public:
    smart_pointer():data(0)
	{
		static_assert(std::is_base_of<RemovableObject, T>::value > 0, "smart_pointer illegal type of <T>");

#ifdef ENABLE_LOG
		std::cout << "smart_pointer() <" << typeid(T).name() << ">" << std::endl;
#endif
	}
    
    smart_pointer(const smart_pointer& other):data(other.data)
    {
		static_assert(std::is_base_of<RemovableObject, T>::value > 0, "smart_pointer illegal type of <T>");
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
		static_assert(std::is_base_of<RemovableObject, T>::value > 0, "smart_pointer illegal type of <T>");

		if (data != NULL)
		{
			dynamic_cast<RemovableObject*>(data)->refs++;

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
			//std::cout << "REFS COUNT " << dynamic_cast<RemovableObject*>(data)->refs << std::endl;
			if(--(dynamic_cast<RemovableObject*>(data)->refs) == 0)
            {
                delete data;
            }
			//std::cout << "Pointer to : " << data << " removed, " << dynamic_cast<RemovableObject*>(data)->refs << " left" << std::endl;
        }
#ifdef ENABLE_LOG
		std::cout << "~~~~smart_pointer() <" << typeid(T).name() << ">" << std::endl;
#endif
    }
    
    inline smart_pointer<T> clone()
    {
        smart_pointer<T> sm;
        sm.data = new T(*data);

		if (data != NULL)
			dynamic_cast<RemovableObject*>(data)->refs++;
        
        return sm;
    }

	inline bool isEmpty() //TODO this function can be operator function 
	{
		return data == NULL;
	}

	static inline smart_pointer<T>& null()
	{
		return nullPtr;
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
                delete data;
            
            data = other.data;
			//std::cout << "Added reference to: " << data << std::endl;
			if (data != NULL)
				dynamic_cast<RemovableObject*>(data)->refs++;
        }
        
        return *this;
    }
    
    inline bool operator == (const smart_pointer& other ) const
    {
        return data == other.data;
    }

	inline bool operator != (const smart_pointer& other) const
	{
		return data != other.data;
	}
};
template<class T>
smart_pointer<T>& smart_pointer<T>::null();

template<class T>
smart_pointer<T> smart_pointer<T>::nullPtr;

class RemovableObject
{
template<class T> friend class smart_pointer;
private:
	int refs = 0;

};
#endif