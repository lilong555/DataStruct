#include <iostream>
template <typename T>
class vector
{
private:
    T *_data;
    size_t _size;
    size_t _cacp;

public:
    explicit vector(size_t n = 0)
    {
        _size = n;
        _cacp = (n > 0 ? n : 1);
        _data = new T[_cacp];
        for (size_t i = 0; i < n; ++i)
        {
            _data[i] = T();
        }
    }
    ~vector()
    {
        if (_data)
        {
            delete[] _data;
            _data = nullptr;
        }
    }
    vector(const vector &other)
    {
        _size = other._size;
        _cacp = other._cacp;
        _data = new T[_cacp];
        for (size_t i = 0; i < _cacp; i++)
        {
            _data[i] = other._data[i];
        }
    }
    vector &operator=(const vector &other)
    {
        if (this == &other)
        {
            return *this;
        }
        _size = other._size;
        _cacp = other._cacp;
        delete[] _data;
        _data = new T[_cacp];
        for (size_t i = 0; i < _cacp; i++)
        {
            _data[i] = other._data[i];
        }
        return *this;
    }
    T &operator[](size_t index)
    {
        if (index >= _size)
        {
            throw std::out_of_range("Index out of range");
        }
        else
        {
            return _data[index];
        }
    }
    const T &operator[](size_t index) const
    {
        if (index >= _size)
        {
            throw std::out_of_range("Index out of range");
        }
        else
        {
            return _data[index];
        }
    }
    void push_back(const T &val)
    {
        // 如果满了，需要扩容
        if (_size == _cacp)
        {
            resize_capacity(_cacp * 2); // 容量翻倍
        }
        _data[_size++] = val;
    }
    size_t size() const
    {
        return _size;
    }
    void sort(size_t l = 0, size_t r = 0) // 默认小到大排序，递归分治排序
    {
        if (l >= r)
            return;
        size_t mid = (l + r) / 2;
        sort(l, mid);
        sort(mid + 1, r);
        vector<T> temp;
        size_t L = l, R = mid + 1;
        while (L <= mid && R <= r)
        {
            if (_data[L] < _data[R])
            {
                temp.push_back(_data[L]);
                L++;
            }
            else
            {
                temp.push_back(_data[R]);
                R++;
            }
        }
        while (R <= r)
        {
            temp.push_back(_data[R++]);
        }
        while (L <= mid)
        {
            temp.push_back(_data[L++]);
        }
        size_t tot = 0;
        for (size_t i = l; i <= r; i++)
        {
            _data[i] = temp[tot++];
        }
    }

private:
    void resize_capacity(size_t newcacp)
    {
        T *newdata = new T[newcacp];
        for (size_t i = 0; i < _size; i++)
        {
            newdata[i] = _data[i];
        }
        delete[] _data;
        _data = newdata;
        _cacp = newcacp;
    }
};
int main()
{
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }
    if (a.size() > 1)
    {
        a.sort(0, a.size() - 1);
    }
    int64_t sum = 0, ans = 0;
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
    }
    for (int i = 0; i < n - 1; i++)
    {
        ans += sum;
        sum -= a[i];
    }
    std::cout << ans << std::endl;

    return 0;
}