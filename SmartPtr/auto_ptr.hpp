#pragma once

namespace moran {
	template <class T>
	class auto_ptr {
	public:
		auto_ptr(T* ptr)
			:_ptr(ptr)
		{}
		~auto_ptr()
		{
			if (_ptr)
				delete _ptr;
		}

		//auto_ptr拷贝策略是管理权转移
		auto_ptr(auto_ptr& other)
			:_ptr(other._ptr)
		{
			other._ptr = nullptr;
		}
		
		auto_ptr& operator=(auto_ptr& other)
		{
			if (other._ptr != _ptr)
			{
				if(_ptr)
					delete _ptr;
				_ptr = other._ptr;
				other._ptr = nullptr;
			}
			return *this;
		}


		T* operator->()
		{
			return _ptr;
		}
		T& operator*()
		{
			return *_ptr;
		}
	private:
		T* _ptr;
	};

}