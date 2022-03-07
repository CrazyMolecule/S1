#ifndef LIST_H 
#define LIST_H

#include <iostream>

template<typename T>
class List
{
private:
	void replaceList(List&);

protected:
	T* m_List;
	int m_Size;
	int m_Count = 0;

public:
	List();
	List(int);
	List(List&);
	List(List&&);
	~List();

	List& operator=(List&);
	List& operator=(List&&);
	bool operator==(List&);
	T operator[](int);

	int getCount();
	bool isEmpty();
	void reverse();
};

template<typename T>
List<T>::List() : List(0) {}

template<typename T>
List<T>::List(int size) : m_List(new T[size]), m_Size(size) {}

template<typename T>
List<T>::List(List& value) : m_Size(value.m_Size), m_Count(value.m_Count)
{
	replaceList(value);
}

template<typename T>
List<T>::List(List&& value) : m_List(value.m_List), m_Size(value.m_Size), m_Count(value.m_Count)
{
	value.m_List = NULL;
	value.m_Size = NULL;
	value.m_Count = NULL;
}

template<typename T>
List<T>::~List()
{
	delete m_List;
}

template<typename T>
List<T>& List<T>::operator=(List& value)
{
	replaceList(value);

	m_Size = value.m_Size;
	m_Count = value.m_Count;

	return *this;
}

template<typename T>
List<T>& List<T>::operator=(List&& value)
{
	m_List = value.m_List;
	m_Size = value.m_Size;
	m_Count = value.m_Count;

	value.m_List = NULL;
	value.m_Size = NULL;
	value.m_Count = NULL;
	return *this;
}

template<typename T>
bool List<T>::operator==(List& other)
{
	if (m_Count == other.m_Count && m_Size == other.m_Size)
	{
		for (size_t i = 0; i < m_Count; i++)
			if (m_List[i] != other.m_List[i])
				return 0;
		return 1;
	}
	return 0;
}

template<typename T>
T List<T>::operator[](int index)
{
	return m_List[index];
}

template<typename T>
int List<T>::getCount()
{
	return m_Size;
}

template<typename T>
bool List<T>::isEmpty()
{
	return m_List == 0;
}

template<typename T>
void List<T>::replaceList(List& value)
{
	delete[] m_List;
	m_List = nullptr;

	m_List = new T[value.m_Size];
	for (size_t i = 0; i < m_Count; i++)
		m_List[i] = value.m_List[i];
}

template<typename T>
void List<T>::reverse()
{
	/*
	* Reverse List
	*/
}

#endif