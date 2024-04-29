#include <iostream>
#include <cstdio>
#include <cstring>
#include <tuple>

template<typename K, typename V>
class Map {
    K keys[290];
    V values[290];
    bool active[290] = { false };
    int nr = 0;

public:
    V& operator [](const K& key)
    {
        for (int i = 0; i < nr; i++)
        {
            if (active[i] and keys[i] == key)
                return values[i];
        }
        keys[nr] = key;
        active[nr] = true;
        return values[nr++];
    }

    void Set(const K& key, const V& value)
    {
        for (int i = 0; i < nr; i++)
        {
            if (keys[i] == key)
            {
                values[i] = value;
                return;
            }
        }
        keys[nr] = key;
        active[nr] = true;
        values[nr++] = value;
    }

    bool Get(const K& key, V& value)
    {
        for (int i = 0; i < nr; i++)
        {
            if (active[i] and keys[i] == key)
            {
                value = values[i];
                return true;
            }
        }
        return false;
    }

    int Count() const
    {
        return nr;
    }

    void Clear() {
        for (int i = 0; i < nr; i++)
            active[i] = false;
        nr = 0;
    }

    bool Delete(const K& key)
    {
        for (int i = 0; i < nr; i++)
        {
            if (active[i] and keys[i] == key)
            {
                for (int j = i; j < nr - 1; j++)
                {
                    active[j] = active[j + 1];
                    keys[j] = keys[j + 1];
                    values[j] = values[j + 1];
                }
                nr--;
                return true;
            }
        }
        return false;
    }

    bool Includes(const Map<K, V>& random_map)
    {
        for (int i = 0; i < random_map.nr; i++)
        {
            bool found = false;
            for (int j = 0; j < nr; j++)
            {
                if (random_map.keys[i] == keys[j] and active[j])
                {
                    found = true;
                    break;
                }
            }
            if (!found)
                return false;
        }
        return true;
    }

    struct Iterator {
        const Map& map;
        int index;

        bool operator!=(const Iterator& other) const {
            return index != other.map.nr;
        }

        void operator++() {
            do {
                index++;
            } while (index < map.nr && !map.active[index]);
        }

        auto operator*() const {
            return std::tuple(map.keys[index], map.values[index], index);
        }
    };

    Iterator begin() const {
        Iterator it{ *this, 0 };
        if (nr > 0 && !active[0])
            ++it;
        return it;
    }

    Iterator end() const {
        return Iterator{ *this, nr };
    }
};

int main()
{
    Map<int, const char*> m;
    Map<int, const char*> n;
    m[10] = "C++";
    m[20] = "test";
    m[30] = "Poo";
    n[30] = "Poo";
    if (m.Includes(n))
    {
        std::cout << "include" << std::endl;
    }
    for (auto [key, value, index] : m)
    {
        printf("Index:%d, Key=%d, Value=%s\n", index, key, value);
    }
    m[20] = "result";
    m.Set(10, "slobozia bradului");
    const char* get;
    m.Get(30, get);
    std::cout << get << std::endl;
    m.Delete(20);
    for (auto [key, value, index] : m)
    {
        printf("Index:%d, Key=%d, Value=%s\n", index, key, value);
    }
    m.Clear();
    return 0;
}