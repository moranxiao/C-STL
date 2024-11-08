#pragma once


namespace moran {
	template <class T>
	class unique_ptr {
	public:
		unique_ptr(T* ptr)
			:_ptr(ptr)
		{}
		unique_ptr(unique_ptr& other) = delete;
		unique_ptr& operator=(unique_ptr& other) = delete;
		~unique_ptr()
		{
			if (_ptr) delete _ptr;
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