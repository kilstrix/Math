#include <iostream>
#include <stdexcept>

using namespace std;

class Compare
{
public:
    virtual int CompareElements(void* e1, void* e2) = 0;
};

template<class T>
class ArrayIterator
{
private:
    int Current;
    T** List;
public:
    ArrayIterator(int current, T** list) : Current(current), List(list) {}

    ArrayIterator& operator ++ () {
        Current++;
        return *this;
    }

    ArrayIterator& operator -- () {
        Current--;
        return *this;
    }

    bool operator==(const ArrayIterator<T>& other) const {
        return Current == other.Current && List == other.List;
    }

    bool operator!=(const ArrayIterator<T>& other) const {
        return !(*this == other);
    }

    T* GetElement() {
        return List[Current];
    }
};

template<class T>
class Array
{
private:
    T** List;
    int Capacity;
    int Size;
public:
    Array() : List(nullptr), Capacity(0), Size(0) {}

    ~Array() {
        if (List != nullptr) {
            for (int i = 0; i < Size; ++i)
                delete List[i];
            delete[] List;
        }
    }

    Array(int capacity) : Capacity(capacity), Size(0) {
        List = new T * [Capacity];
    }

    Array(const Array<T>& otherArray) : Capacity(otherArray.Capacity), Size(otherArray.Size) {
        List = new T * [Capacity];
        for (int i = 0; i < Size; ++i)
            List[i] = new T(*(otherArray.List[i]));
    }

    T& operator[] (int index) {
        if (index < 0 || index >= Size)
            throw out_of_range("Index out of range");
        return *List[index];
    }

    const Array<T>& operator+=(const T& newElem) {
        if (Size >= Capacity)
            throw out_of_range("Array is full");
        List[Size++] = new T(newElem);
        return *this;
    }

    const Array<T>& Insert(int index, const T& newElem) {
        if (index < 0 || index > Size)
            throw out_of_range("Index out of range");

        if (Size >= Capacity)
            throw out_of_range("Array is full");

        for (int i = Size; i > index; --i)
            List[i] = List[i - 1];

        List[index] = new T(newElem);
        Size++;

        return *this;
    }

    const Array<T>& Insert(int index, const Array<T>& otherArray) {
        if (index < 0 || index > Size)
            throw out_of_range("Index out of range");

        if (Size + otherArray.Size > Capacity)
            throw out_of_range("Array capacity exceeded");

        for (int i = Size - 1; i >= index; --i)
            List[i + otherArray.Size] = List[i];

        for (int i = 0; i < otherArray.Size; ++i)
            List[index + i] = new T(*(otherArray.List[i]));

        Size += otherArray.Size;

        return *this;
    }

    void Delete(int index) {
        if (index < 0 || index >= Size)
            throw out_of_range("Index out of range");

        delete List[index];

        for (int i = index; i < Size - 1; ++i)
            List[i] = List[i + 1];

        List[Size - 1] = nullptr;
        Size--;

    }

    Array<T>& operator=(const Array<T>& otherArray) {
        if (this == &otherArray)
            return *this;

        if (List != nullptr) {
            for (int i = 0; i < Size; i++)
                delete List[i];
            delete[] List;
        }

        Capacity = otherArray.Capacity;
        Size = otherArray.Size;

        List = new T * [Capacity];
        for (int i = 0; i < Size; ++i)
            List[i] = new T(*(otherArray.List[i]));

        return *this;
    }

    void Sort() {
        for (int i = 0; i < Size - 1; i++) {
            for (int j = i + 1; j < Size; j++) {
                if (*List[i] > *List[j]) {
                    T* temp = List[i];
                    List[i] = List[j];
                    List[j] = temp;
                }
            }
        }
    }

    void Sort(int(*compare)(const T&, const T&)) {
        for (int i = 0; i < Size - 1; i++) {
            for (int j = i + 1; j < Size; j++) {
                if (compare(*List[i], *List[j]) > 0) {
                    T* temp = List[i];
                    List[i] = List[j];
                    List[j] = temp;
                }
            }
        }
    }

    void Sort(Compare* comparator) {
        for (int i = 0; i < Size - 1; i++) {
            for (int j = i + 1; j < Size; j++) {
                if (comparator->CompareElements(List[i], List[j]) > 0) {
                    T* temp = List[i];
                    List[i] = List[j];
                    List[j] = temp;
                }
            }
        }
    }

    int BinarySearch(const T& elem) {
        int st = 0, dr = Size - 1;

        while (st <= dr) {
            int mid = (st + dr) / 2;
            if (*List[mid] == elem)
                return mid;
            else if (*List[mid] < elem)
                st = mid + 1;
            else
                dr = mid - 1;
        }

        return -1;
    }

    int BinarySearch(const T& elem, int(*compare)(const T&, const T&)) {
        int st = 0, dr = Size - 1;

        while (st <= dr) {
            int mid = (st + dr) / 2;
            if (compare(*List[mid], elem) == 0)
                return mid;
            else if (compare(*List[mid], elem) < 0)
                st = mid + 1;
            else
                dr = mid - 1;
        }

        return -1;
    }

    int BinarySearch(const T& elem, Compare* comparator) {
        int st = 0, dr = Size - 1;

        while (st <= dr) {
            int mid = (st + dr) / 2;
            if (comparator->CompareElements(List[mid], (void*)&elem) == 0)
                return mid;
            else if (comparator->CompareElements(List[mid], (void*)&elem) < 0)
                st = mid + 1;
            else
                dr = mid - 1;
        }

        return -1;
    }

    int Find(const T& elem) {
        for (int i = 0; i < Size; i++) {
            if (*List[i] == elem)
                return i;
        }
        return -1;
    }

    int Find(const T& elem, int(*compare)(const T&, const T&)) {
        for (int i = 0; i < Size; ++i) {
            if (compare(*List[i], elem) == 0)
                return i;
        }
        return -1;
    }

    int Find(const T& elem, Compare* comparator) {
        for (int i = 0; i < Size; ++i) {
            if (comparator->CompareElements(List[i], &elem) == 0)
                return i;
        }
        return -1;
    }

    int GetSize() const {
        return Size;
    }

    int GetCapacity() const {
        return Capacity;
    }

    ArrayIterator<T> GetBeginIterator() {
        return ArrayIterator<T>(0, List);
    }

    ArrayIterator<T> GetEndIterator() {
        return ArrayIterator<T>(Size, List);
    }
};

int compare_function(const int& a, const int& b) {
    return a - b;
}

class Comparator : public Compare {
public:
    int CompareElements(void* e1, void* e2) override {
        int a = *static_cast<int*>(e1);
        int b = *static_cast<int*>(e2);
        return a - b;
    }
};

int main() {
    Array<int> arr(5);

    arr += 1;
    arr += 2;
    arr += 3;
    
    cout << "Element at index 0: " << arr[0] << endl;

    cout << "Size of the array: " << arr.GetSize() << endl;

    ArrayIterator<int> it = arr.GetBeginIterator();
    while (it != arr.GetEndIterator()) {
        cout << *(it.GetElement()) << " ";
        ++it;
    }
    cout << endl;

    arr.Insert(2, 4);

    arr.Delete(0);

    it = arr.GetBeginIterator();
    while (it != arr.GetEndIterator()) {
        cout << *(it.GetElement()) << " ";
        ++it;
    }
    cout << endl;
    Comparator comp;
    int index = arr.BinarySearch(4, &comp);
    if (index != -1) {
        cout << "Element found at index: " << index << endl;
    }
    else {
        cout << "Element not found." << endl;
    }

    //arr.Sort();
    //Comparator comp;
    //arr.Sort(&comp);
    arr.Sort(compare_function);
    cout << "Sorted array: ";
    for (int i = 0; i < arr.GetSize(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    try {
        arr[arr.GetSize()];
    }
    catch (out_of_range e) {
        std::cout << e.what();
    }
    return 0;
}