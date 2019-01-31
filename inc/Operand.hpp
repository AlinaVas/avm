#ifndef AVM_OPERAND_HPP
#define AVM_OPERAND_HPP

#include "IOperand.hpp"
#include "Factory.hpp"

#include <cmath>

template <typename T>
class Operand : public IOperand {

public:

	Operand() = delete;
	Operand(std::string const & value, eOperandType type) : _value(value), _type(type) {}
	Operand(Operand const & rhs) : _value(rhs._value), _type(rhs._type) {}
	~Operand() override = default;

	eOperandType		getType() const override { return _type; }

	int					getPrecision() const override {

		if (_type == Float)
			return 6;
		if (_type == Double)
			return 15;
		return 0;
	}

	std::string const 	&toString() const override { return _value; }

	Operand				&operator=(Operand const & rhs) {

		if (this == &rhs)
			return *this;

		_value = rhs.toString();
		_type = rhs.getType();
		return *this;
	}

	IOperand const * operator+(IOperand const & rhs) const override {

		eOperandType type = (_type > rhs.getType()) ? _type : rhs.getType();
		long double result = std::stold(toString()) + std::stold(rhs.toString());
		return Factory().createOperand(type, std::to_string(result));
	}


	IOperand const * operator-(IOperand const & rhs) const override {

		eOperandType type = (_type > rhs.getType()) ? _type : rhs.getType();
		long double result = std::stold(toString()) - std::stold(rhs.toString());
		return Factory().createOperand(type, std::to_string(result));
	}


	IOperand const * operator*(IOperand const & rhs) const override {

		eOperandType type = (_type > rhs.getType()) ? _type : rhs.getType();
		long double result = std::stold(toString()) * std::stold(rhs.toString());
		return Factory().createOperand(type, std::to_string(result));
	}


	IOperand const * operator/(IOperand const & rhs) const override {
		eOperandType type = (_type > rhs.getType()) ? _type : rhs.getType();
		long double result;

		if (std::stold(rhs.toString()) == 0)
			return nullptr;
		result = std::stold(toString()) / std::stold(rhs.toString());
		return Factory().createOperand(type, std::to_string(result));
	}

	IOperand const * operator%(IOperand const & rhs) const override {
		eOperandType type = (_type > rhs.getType()) ? _type : rhs.getType();
		long double result;

		if (std::stold(rhs.toString()) == 0)
			return nullptr;
		result = std::fmod(std::stold(toString()), std::stold(rhs.toString()));
		return Factory().createOperand(type, std::to_string(result));
	}

private:

	std::string const	_value;
	eOperandType const	_type;
};

#endif
