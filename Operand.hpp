#pragma once

#include "IOperand.hpp"

template <typename T>
class Operand : public IOperand {

public:

	Operand() = delete; /////////////////////////////////// Allowed?
	Operand(std::string & value, eOperandType type);
	Operand(Operand const & rhs);
	~Operand();

	eOperandType		getType() const;
	int					getPrecision() const;
	std::string const &	toString() const;

	Operand	const		&operator=(Operand const & rhs);

private:

	std::string		_value;
	eOperandType	_type;
};

#include "Operand.tpp"