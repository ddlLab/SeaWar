#pragma once

#include <memory>
#include <type_traits>


template<typename T, typename Enable = void>
struct is_pointer_type
{
	enum { value = false };
};

template<typename T>
struct is_pointer_type<T, typename std::enable_if<std::is_same<typename std::remove_cv<T>::type, std::shared_ptr<typename T::element_type>>::value>::type>
{
	enum { value = true };
};

template<typename T>
struct is_pointer_type<T, typename std::enable_if<std::is_same<typename std::remove_cv<T>::type, std::unique_ptr<typename T::element_type>>::value>::type>
{
	enum { value = true };
};

template<typename T>
struct is_pointer_type<T, typename std::enable_if<std::is_same<typename std::remove_cv<T>::type, std::weak_ptr<typename T::element_type>>::value>::type>
{
	enum { value = true };
};

template<typename T>
struct is_pointer_type<T, typename std::enable_if<std::is_pointer<T>::value>::type>
{
	enum { value = true };
};