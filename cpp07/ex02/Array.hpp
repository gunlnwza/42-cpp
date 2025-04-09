#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <ostream>

template <typename T>
class Array
{
	private:
		T*				data;
		unsigned int	len;

	public:
		Array();
		Array(unsigned int n);
		Array(const Array<T>& other);
		Array<T>& operator=(const Array<T>& other);
		~Array();

		T& operator[](int i);
		unsigned int size() const;
};

# include "Array.tpp"

template <typename T>
std::ostream& operator<<(std::ostream& os, Array<T> &arr)
{
	unsigned int	len;

	len = arr.size();
	os << "[";
	for (unsigned int i = 0; i < len; i++)
	{
		os << arr[i];
		if (i < len - 1)
			os << ", ";
	}
	os << "]";
	return (os);
}

#endif
