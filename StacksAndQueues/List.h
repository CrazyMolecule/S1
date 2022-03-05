#ifndef LIST_H 
#define LIST_H

#include <iostream>

template<typename T>
class List
{
public:
    List(); // null constructor
    List(int size); // default constructor
    List(List& value); // copy constructor
    List(List&& value); // move constructor
    ~List(); // destructor

    List& operator=(List& value); // copy assignment operator
    List& operator=(List&& value); // move assignment operator
    List operator+(List& other);
    bool operator==(List& other);
    friend std::ostream& operator<<(std::ostream& out, const List<T>& value)
    {
        out << "List(list={";
        for (size_t i = 0; i < value.m_Size; i++)
        {
            out << value.m_List[i];
            if (i != value.m_Size - 1)
                out << ", ";
        }
        out << "}";
        out << ", count=" << value.m_Count << ", size=" << value.m_Size << ")";

        return out;
    }

	void pushBack(T item);
	T popFront();
    int getCount(); // get count of items in queue
    bool isEmpty(); // is queue empty (m_Count == 0)

    T* m_List; // {T, T, T, T, T, ...}
    int m_Size; // count of spaces in {T, T, T, T, T, ...}
    int m_Count = 0; // count of items in {T, T, T, T, T, ...}

private:
    void replaceList(List& value);
};

// null constructor
template<typename T>
List<T>::List() : List(0) {}

// default constructor
template<typename T>
List<T>::List(int size) : m_Size(size), m_List(new T[size]) {}

// copy constructor
template<typename T>
List<T>::List(List& value) : m_Size(value.m_Size), m_Count(value.m_Count)
{
	replaceList(value);
}

// move constructor
template<typename T>
List<T>::List(List&& value) : m_Size(value.m_Size), m_List(value.m_List), m_Count(value.m_Count)
{
	value.m_List = NULL;
	value.m_Size = NULL;
	value.m_Count = NULL;
}

// destructor
template<typename T>
List<T>::~List()
{
	delete[] m_List;
}

// copy assignment operator
template<typename T>
List<T>& List<T>::operator=(List& value)
{
	replaceList(value);

	m_Size = value.m_Size;
	m_Count = value.m_Count;

	return *this;
}

// move assignment operator
template<typename T>
List<T>& List<T>::operator=(List&& value)
{
	m_Size = value.m_Size;
	m_List = value.m_List;
	m_Count = value.m_Count;

	value.m_List = NULL;
	value.m_Size = NULL;
	value.m_Count = NULL;
	return *this;
}

template<typename T>
List<T> List<T>::operator+(List& other) /// (!!!!)
{
	int count = m_Count + other.m_Count;
	int size = m_Size + other.m_Size;
	List<T> tempList(size);

	for (size_t i = 0; i < m_Count; i++)
		tempList.m_List[i] = m_List[i];
	for (size_t i = m_Count; i < count; i++)
		tempList.m_List[i] = other.m_List[i - m_Count];

	tempList.m_Count = count;

	return tempList;
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
void List<T>::pushBack(T item)
{
	T* temporary;
	if (m_Count == m_Size)
	{
		temporary = new T[m_Size + 1];
		m_Size++;
	}
	else
		temporary = new T[m_Size];

	for (size_t i = 0; i < m_Count; i++)
		temporary[i + 1] = m_List[i];
	temporary[0] = item;
	m_Count++;

	m_List = temporary;
}

template<typename T>
T List<T>::popFront()
{
	if (m_Size != 0)
	{
		T* temporary;
		T item = m_List[m_Size];

		m_Size--;
		if (m_Count != 0)
			m_Count--;
		temporary = new T[m_Size];

		for (size_t i = 0; i < m_Size; i++)
			temporary[i] = m_List[i];


		m_List = temporary;
		return item;
	}
	else
		throw;
}

// get count of items in List
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

#endif