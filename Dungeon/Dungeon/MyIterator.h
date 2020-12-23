
#ifndef MyIterator_h
#define MyIterator_h

template <class T>
class MyIterator {
    private:
        T *ptr;
    
    public:
        MyIterator() { ptr = nullptr; }
        MyIterator(T *p) { ptr = p; }
        
        T *operator + (int n)  { return (ptr + n); }
        T *operator - (int n) { return (ptr - n); }
        
        T *operator ++ (int) { return ptr++; }
        T *operator -- (int) { return ptr--; }
        T *operator ++ () { return ++ptr; }
        T *operator -- () { return --ptr; }
            
        bool operator != (const MyIterator &it) noexcept { return ptr != it.ptr; }
        bool operator == (const MyIterator &it) noexcept { return ptr == it.ptr; }
        T *operator * () noexcept { return ptr; }
};


#endif
