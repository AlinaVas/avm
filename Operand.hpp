#pragma once

#include "IOperand.hpp"
#include "Factory.hpp"

//class Factory;

template <typename T>
class Operand : public IOperand {

public:

	Operand() = delete;
	Operand(std::string const & value, eOperandType type, Factory const * ptr) : _value(value), _type(type), _ptr(ptr) {}
	Operand(Operand const & rhs) { *this = rhs; }
	~Operand() = default;

	eOperandType		getType() const { return _type; }

	int					getPrecision() const {

		if (_type == Float)
			return 6;
		if (_type == Double)
			return 15;
		return 0;
	}

	std::string const 	&toString() const { return _value; }

	Operand				&operator=(Operand const & rhs) {

		if (this == &rhs)
			return *this;

		_value = rhs.toString();
		_type = rhs.getType();
		return *this;
	}

	IOperand const * operator+(IOperand const & rhs) const {

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


	IOperand const * operator-(IOperand const & rhs) const {

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


	IOperand const * operator*(IOperand const & rhs) const {

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


//	IOperand const * operator/(IOperand const & rhs) const;
//	IOperand const * operator%(IOperand const & rhs) const;

private:

	std::string	const	_value;
	eOperandType const	_type;

	Factory const 		*_ptr;
};

//#include "Operand.cpp"