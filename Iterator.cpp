namespace Tango
{
    template<typename T>
    class FixedSizeArray
    {
    private:

        class Iterator
        {
        public:
            using Tag = std::forward_iterator_tag;
            using Distance = std::ptrdiff_t;
            using ValType = T;
            using Pointer = T*;
            using Ref = T&;

            Iterator(Pointer pData)
                : mData(pData) {
            }

            Ref operator*()
            {
                return *mData;
            }
            Ref operator++()
            {
                return *(mData + 1);
            }
            Ref operator+=(int32_t pNumber)
            {
                return *(mData += pNumber);
            }
            bool operator ==(const Iterator& pOther)
            {
                return *mData == *pOther.mData ? true : false;
            }
            bool operator !=(const Iterator& pOther)
            {
                return *mData != *pOther.mData ? true : false;
            }

        private:
            Pointer mData;

        };

    public:
        FixedSizeArray() = default;
        FixedSizeArray(size_t pCapacity)
        {
            if (mArray != nullptr)
            {
                delete mArray;
                mArray = nullptr;
            }
            mArray = new T[pCapacity];
            for (size_t i = 0; i < pCapacity; ++i)
            {
                mArray[i] = 0;
            }
        }
        FixedSizeArray(const std::initializer_list<T>& pList)
        {
            if (mArray != nullptr)
            {
                delete[] mArray;
                mArray = nullptr;
            }
            mCapacity = pList.size();
            mArray = new T[pList.size()];
            static int index = 0;
            for (auto& i : pList)
            {
                mArray[index] = i;
                index++;
            }
        }
        ~FixedSizeArray()
        {
            if (mArray != nullptr)
            {
                delete[] mArray;
                mArray = nullptr;
            }
        }

        FixedSizeArray(const FixedSizeArray& pAnother)
        {
            mCapacity = pAnother.mCapacity;
            delete[] mArray;
            mArray = new T[mCapacity];
            for (size_t i = 0; i < pAnother.mCapacity; ++i)
            {
                mArray[i] = pAnother[i];
            }
        }
        FixedSizeArray& operator=(const FixedSizeArray& pAnother)
        {
            if (pAnother == *this)
                return *this;

            mCapacity = pAnother.mCapacity;
            delete[] mArray;
            mArray = new T[mCapacity];
            for (size_t i = 0; i < pAnother.mCapacity; ++i)
            {
                mArray[i] = pAnother[i];
            }
            return *this;
        }

        FixedSizeArray(FixedSizeArray&& pAnother)
        {
            mCapacity = std::move(pAnother.mCapacity);
            delete[] mArray;
            mArray = new T[mCapacity];
            for (size_t i = 0; i < pAnother.mCapacity; ++i)
            {
                mArray[i] = std::move(pAnother[i]);
            }
        }
        FixedSizeArray& operator=(FixedSizeArray&& pAnother)
        {
            if (pAnother == *this)
                return *this;

            mCapacity = std::move(pAnother.mCapacity);
            delete[] mArray;
            mArray = new T[mCapacity];
            for (size_t i = 0; i < pAnother.mCapacity; ++i)
            {
                mArray[i] = std::move(pAnother[i]);
            }
            return *this;
        }

        size_t getCapacity()
        {
            return mCapacity;
        }
        void reserve(size_t pCapacity)
        {
            if (pCapacity > mCapacity)
                return;
            T* tmpArray = new T[pCapacity];
            for (size_t i = 0; i < pCapacity; ++i)
            {
                tmpArray[i] = mArray[i];
            }
            mArray = tmpArray;
            delete[] tmpArray;
        }

        T& operator[](size_t pIndex)
        {
            return mArray[pIndex];
        }

        Iterator begin_()
        {
            return Iterator(&mArray[0]);
        }
        Iterator end_()
        {
            return Iterator(&mArray[mCapacity]);
        }

    private:
        T* mArray{ nullptr };
        size_t mCapacity{ 0 };

    };
}

int main()
{

}