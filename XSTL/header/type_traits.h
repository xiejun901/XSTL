#ifndef _TYPE_TRAITS_H_
#define _TYPE_TRAITS_H_
namespace XX {
	struct _true_type {};
	struct _false_type {};

	template<typename T>
	struct type_traits {
		using this_dummy_member_must_be_first	= _true_type;
		using has_trival_defalult_ctor			= _false_type;
		using has_trival_copy_ctor				= _false_type;
		using has_trival_assignment_operator	= _false_type;
		using has_trival_destructor				= _false_type;
		using is_POD_type						= _false_type;
	};

	//Æ«ÌØ»¯
	template<>
	struct type_traits<bool> {
		using has_trival_defalult_ctor			= _true_type;
		using has_trival_copy_ctor				= _true_type;
		using has_trival_assignment_operator	= _true_type;
		using has_trival_destructor				= _false_type;
		using is_POD_type						= _true_type;
	};

	template<>
	struct type_traits<char> {
		using has_trival_defalult_ctor = _true_type;
		using has_trival_copy_ctor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _false_type;
		using is_POD_type = _true_type;
	};
	template<>
	struct type_traits<unsigned char> {
		using has_trival_defalult_ctor = _true_type;
		using has_trival_copy_ctor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _false_type;
		using is_POD_type = _true_type;
	};
	template<>
	struct type_traits<signed char> {
		using has_trival_defalult_ctor = _true_type;
		using has_trival_copy_ctor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _false_type;
		using is_POD_type = _true_type;
	};
	template<>
	struct type_traits<wchar_t> {
		using has_trival_defalult_ctor = _true_type;
		using has_trival_copy_ctor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _false_type;
		using is_POD_type = _true_type;
	};

	template<>
	struct type_traits<short> {
		using has_trival_defalult_ctor = _true_type;
		using has_trival_copy_ctor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _false_type;
		using is_POD_type = _true_type;
	};
	template<>
	struct type_traits<unsigned short> {
		using has_trival_defalult_ctor = _true_type;
		using has_trival_copy_ctor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _false_type;
		using is_POD_type = _true_type;
	};

	template<>
	struct type_traits<unsigned int> {
		using has_trival_defalult_ctor = _true_type;
		using has_trival_copy_ctor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _false_type;
		using is_POD_type = _true_type;
	};
	template<>
	struct type_traits<int> {
		using has_trival_defalult_ctor = _true_type;
		using has_trival_copy_ctor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _false_type;
		using is_POD_type = _true_type;
	};

	template<>
	struct type_traits<unsigned long> {
		using has_trival_defalult_ctor = _true_type;
		using has_trival_copy_ctor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _false_type;
		using is_POD_type = _true_type;
	};
	template<>
	struct type_traits<long> {
		using has_trival_defalult_ctor = _true_type;
		using has_trival_copy_ctor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _false_type;
		using is_POD_type = _true_type;
	};

	template<>
	struct type_traits<unsigned long long> {
		using has_trival_defalult_ctor = _true_type;
		using has_trival_copy_ctor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _false_type;
		using is_POD_type = _true_type;
	};
	template<>
	struct type_traits<long long> {
		using has_trival_defalult_ctor = _true_type;
		using has_trival_copy_ctor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _false_type;
		using is_POD_type = _true_type;
	};

	template<>
	struct type_traits<float> {
		using has_trival_defalult_ctor = _true_type;
		using has_trival_copy_ctor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _false_type;
		using is_POD_type = _true_type;
	};
	template<>
	struct type_traits<double> {
		using has_trival_defalult_ctor = _true_type;
		using has_trival_copy_ctor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _false_type;
		using is_POD_type = _true_type;
	};
	template<>
	struct type_traits<long double> {
		using has_trival_defalult_ctor = _true_type;
		using has_trival_copy_ctor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _false_type;
		using is_POD_type = _true_type;
	};

	template<typename T>
	struct type_traits<T *> {
		using has_trival_defalult_ctor = _true_type;
		using has_trival_copy_ctor = _true_type;
		using has_trival_assignment_operator = _true_type;
		using has_trival_destructor = _false_type;
		using is_POD_type = _true_type;
	};

	//template<>
	//struct type_traits<char*> {
	//	using has_trival_defalult_ctor = _true_type;
	//	using has_trival_copy_ctor = _true_type;
	//	using has_trival_assignment_operator = _true_type;
	//	using has_trival_destructor = _false_type;
	//	using is_POD_type = _true_type;
	//};
	//template<>
	//struct type_traits<unsigned char*> {
	//	using has_trival_defalult_ctor = _true_type;
	//	using has_trival_copy_ctor = _true_type;
	//	using has_trival_assignment_operator = _true_type;
	//	using has_trival_destructor = _false_type;
	//	using is_POD_type = _true_type;
	//};
	//template<>
	//struct type_traits<signed char*> {
	//	using has_trival_defalult_ctor = _true_type;
	//	using has_trival_copy_ctor = _true_type;
	//	using has_trival_assignment_operator = _true_type;
	//	using has_trival_destructor = _false_type;
	//	using is_POD_type = _true_type;
	//};

	//template<>
	//struct type_traits<const char*> {
	//	using has_trival_defalult_ctor = _true_type;
	//	using has_trival_copy_ctor = _true_type;
	//	using has_trival_assignment_operator = _true_type;
	//	using has_trival_destructor = _false_type;
	//	using is_POD_type = _true_type;
	//};
	//template<>
	//struct type_traits<const unsigned char*> {
	//	using has_trival_defalult_ctor = _true_type;
	//	using has_trival_copy_ctor = _true_type;
	//	using has_trival_assignment_operator = _true_type;
	//	using has_trival_destructor = _false_type;
	//	using is_POD_type = _true_type;
	//};
	//template<>
	//struct type_traits<const signed char*> {
	//	using has_trival_defalult_ctor = _true_type;
	//	using has_trival_copy_ctor = _true_type;
	//	using has_trival_assignment_operator = _true_type;
	//	using has_trival_destructor = _false_type;
	//	using is_POD_type = _true_type;
	//};
	template<typename T>
	struct is_integer {
		using _integral = _false_type;
	};

	template<>
	struct is_integer<bool> {
		using _integral = _true_type;
	};

	template<>
	struct is_integer<char> {
		using _integral = _true_type;
	};
	template<>
	struct is_integer<signed char> {
		using _integral = _true_type;
	};
	template<>
	struct is_integer<unsigned char> {
		using _integral = _true_type;
	};

	template<>
	struct is_integer<unsigned short> {
		using _integral = _true_type;
	};
	template<>
	struct is_integer<short> {
		using _integral = _true_type;
	};

	template<>
	struct is_integer<unsigned int> {
		using _integral = _true_type;
	};
	template<>
	struct is_integer<int> {
		using _integral = _true_type;
	};

	template<>
	struct is_integer<unsigned long> {
		using _integral = _true_type;
	};
	template<>
	struct is_integer<long> {
		using _integral = _true_type;
	};

	template<>
	struct is_integer<unsigned long long> {
		using _integral = _true_type;
	};
	template<>
	struct is_integer<long long> {
		using _integral = _true_type;
	};
}
#endif