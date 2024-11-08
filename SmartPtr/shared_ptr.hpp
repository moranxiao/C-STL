#pragma once
#include <mutex>

namespace moran {
	template<class T>
	struct DeleteOne {
		void operator()(T* ptr)
		{
			delete ptr;
		}
	};

	template <class T,class D = DeleteOne<T>>
	class shared_ptr {
	private:
		void Release()
		{
			bool flag = false;
			_pMtx->lock();
			if (--(*_pCount) == 0) 
			{
				//定制删除
				if (_ptr)
				{
					D()(_ptr);
					std::cout << "delete" << std::endl;
				}

				delete _pCount;
				flag = true;
			}
			_pMtx->unlock();
			//锁不能在上锁期间析构，不然会出现错误
			if (flag)
			{
				delete _pMtx;
			}
			
		}
	public:
		shared_ptr(T* ptr = nullptr)
			:_ptr(ptr),
			_pCount(new size_t(1)),
			_pMtx(new std::mutex)
		{}

		shared_ptr(const shared_ptr& other)
			:_ptr(other._ptr),
			_pCount(other._pCount),
			_pMtx(other._pMtx)
		{
			_pMtx->lock();
			(*_pCount)++;
			_pMtx->unlock();
		}

		shared_ptr& operator=(const shared_ptr& other)
		{
			if (other._ptr != _ptr)
			{
				Release();
				_ptr = other._ptr;
				_pCount = other._pCount;
				_pMtx = other._pMtx;

				_pMtx->lock();
				(*_pCount)++;
				_pMtx->unlock();
			}
			return *this;
		}

		~shared_ptr()
		{
			Release();
		}
		T* operator->()
		{
			return _ptr;
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* get() const
		{
			return _ptr;
		}
	private:
		T* _ptr;
		size_t* _pCount;
		std::mutex* _pMtx;
	};

	template <class T>
	class weak_ptr {
	public:
		weak_ptr(const shared_ptr<T>& spt)
			:_ptr(spt.get())
		{}
		weak_ptr(const weak_ptr& wpt)
			:_ptr(wpt._ptr)
		{}
		weak_ptr(T* ptr = nullptr)
			:_ptr(ptr)
		{}

		weak_ptr& operator=(const weak_ptr& wpt)
		{
			_ptr = wpt._ptr;
			return *this;
		}
		weak_ptr& operator=(const shared_ptr<T>& spt)
		{
			_ptr = spt.get();
			return *this;
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
	private:
		T* _ptr;
	};
	
	template<class T>
	struct DeleleAny {
		void operator()(T* ptr)
		{
			delete[]ptr;
		}
	};


	class A {
	public:
		A()
		{}
		~A()
		{

		}
	};
	struct Node {
		weak_ptr<Node> _prev = nullptr;
		weak_ptr<Node> _next = nullptr;
	};
	void TestSharedptr()
	{


		//shared_ptr<A,DeleleAny<A>> p1(new A[5]);
		//shared_ptr<A, DeleleAny<A>> p2(p1);
		//shared_ptr<A, DeleleAny<A>> p3(new A[4]);
		//p3 = p2;

		shared_ptr<Node> p1(new Node);
		shared_ptr<Node> p2(new Node);
		p1->_next = p2;
		p2->_prev = p1;
		

	}
}