//#include "Operand.hpp"

template <typename T>
Operand<T>::Operand(std::string & value, eOperandType type, Factory *ptr) : _value(value), _type(type), _ptr(ptr) {}

template <typename T>
Operand<T>::Operand(Operand<T> const & rhs) {

	*this = rhs;
}

template <typename T>
Operand<T>::~Operand() = default;

template <typename T> std::string const &
Operand<T>::toString() const { return _value; }

template <typename T> eOperandType
Operand<T>::getType() const { return _type; }

template <typename T> int
Operand<T>::getPrecision() const {

	if (_type == Float)
		return 6;
	if (_type == Double)
		return 15;
	return 0;
}

template <typename T> Operand<T> &
Operand<T>::operator=(Operand<T> const & rhs) {

	if (this == &rhs)
		return *this;

	_value = rhs.toString();
	_type = rhs.getType();
	return *this;
}

template <typename T> IOperand const *
Operand<T>::operator+(IOperand const & rhs) const {

	eOperandType type = (_type > rhs.getType()) ? _type : rhs.getType();
	long double result;

	try
	{
		result = std::stold(toString()) + std::stold(rhs.toString());
	} 
	catch (std::exception &e) 
	{
		// HOW TO MANAGE ERRORS?
		std::cout << "Error : opearator+ : " << e.what() << std::endl;
		return nullptr;
	}
	return Factory().createOperand(type, std::to_string(result));
}

template <typename T> IOperand const *
Operand<T>::operator-(IOperand const & rhs) const {

	eOperandType type = (_type > rhs.getType()) ? _type : rhs.getType();
	long double result;

	try
	{
		// порядок?
		result = std::stold(toString()) - std::stold(rhs.toString());
	} 
	catch (std::exception &e) 
	{
		// HOW TO MANAGE ERRORS?
		std::cout << "Error : opearator- : " << e.what() << std::endl;
		return nullptr;
	}
	return Factory().createOperand(type, std::to_string(result));
}

template <typename T> IOperand const *
Operand<T>::operator*(IOperand const & rhs) const {

	eOperandType type = (_type > rhs.getType()) ? _type : rhs.getType();
	long double result;

	try
	{
		result = std::stold(toString()) + std::stold(rhs.toString());
	} 
	catch (std::exception &e) 
	{
		// HOW TO MANAGE ERRORS?
		std::cout << "Error : opearator* : " << e.what() << std::endl;
		return nullptr;
	}
	return Factory().createOperand(type, std::to_string(result));
}