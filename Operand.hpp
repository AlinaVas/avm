#pragma once

#include "IOperand.hpp"
#include "Factory.hpp"

template <typename T>
class Operand : public IOperand {

public:

	Operand() = delete;
	Operand(std::string const & value, eOperandType type, Factory const * ptr) : _value(value), _type(type), _ptr(ptr) {}
	Operand(Operand const & rhs) : _value(rhs._value), _type(rhs._type), _ptr(rhs._ptr) {}
	~Operand() override = default;

	eOperandType		getType() const override { return _type; }

	int					getPrecision() const override {

		if (_type == Float)
			return 6;
		if (_type == Double)
			return 15;
		return 0;
	}

	std::string 	 	&toString() const override { return _value; }

	T					toNumber() const {

		return static_cast<T>(std::stod(_value));
	}

	Operand				&operator=(Operand const & rhs) {

		if (this == &rhs)
			return *this;

		_value = rhs.toString();
		_type = rhs.getType();
		return *this;
	}

	IOperand const * operator+(IOperand const & rhs) const override {

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


	IOperand const * operator-(IOperand const & rhs) const override {

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


	IOperand const * operator*(IOperand const & rhs) const override {

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


//	IOperand const * operator/(IOperand const & rhs) const override;
//	IOperand const * operator%(IOperand const & rhs) const override;

private:

	std::string	const	_value;
	eOperandType const	_type;

	Factory const 		*_ptr;
};

//#include "Operand.cpp"